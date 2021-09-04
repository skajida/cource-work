#include <hdrs/polynomial.h>

#include <algorithm>
#include <sstream>

TPolynomial::iterator TPolynomial::begin() noexcept {
    return polynomial.begin();
}

TPolynomial::iterator TPolynomial::end() noexcept {
    return polynomial.end();
}

void TPolynomial::clear() {
    polynomial.clear();
}

void TPolynomial::normalize() {
    std::for_each(begin(), end(), [](TElementaryConjuction &conj) { conj.normalize(); });
    polynomial.erase(std::remove(
        begin(),
        end(),
        TElementaryConjuction(dimension, { { 0, EState::Empty } })
    ), end());
    std::sort(begin(), end());

    if (begin() == end()) {
        polynomial.push_back(TElementaryConjuction(dimension, { { 0, EState::Empty } }));
    } else {
        bool negative = false;
        for (size_t i = 1; i < polynomial.size(); ++i) {
            if (polynomial[i - 1].isInversed(polynomial[i])) {
                // cannot generate zero polynomials cause of that
                // polynomial[i - 1].setState(true);
                // polynomial[i].setState(true);
                // negative = !negative;
            } else if (polynomial[i - 1] == polynomial[i]) {
                polynomial[i - 1].setState(true);
                polynomial[i].setState(true);
            }
        }
        auto it = std::stable_partition(
            begin(),
            end(),
            [] (const TElementaryConjuction &obj) {
                return !obj.getState();
            }
        );
        polynomial.erase(it, end());
        if (negative) {
            TElementaryConjuction one = TElementaryConjuction(dimension, { { 0, EState::Positive } });
            auto [lhs, rhs] = std::equal_range(
                begin(),
                end(),
                one
            );
            if (lhs != rhs) {
                polynomial.erase(lhs);
                if (begin() == end()) {
                    polynomial.push_back(TElementaryConjuction(dimension, { { 0, EState::Empty } }));
                }
            } else {
                polynomial.insert(lhs, one);
            }
        }
    }
}

TPolynomial::TPolynomial(uint32_t dim) : dimension(dim), polynomial() { normalize(); }

TPolynomial::TPolynomial(const TPolynomial &obj)
    : dimension(obj.dimension)
    , polynomial(obj.polynomial)
{
}

TPolynomial::TPolynomial(TPolynomial &&obj)
    : dimension(obj.dimension)
    , polynomial(std::move(obj.polynomial))
{
}

TPolynomial::TPolynomial(uint32_t dim, std::vector<TElementaryConjuction> polyn)
    : dimension(dim)
    , polynomial(polyn)
{
    normalize();
}

bool TPolynomial::evaluate(uint32_t vector) const {
    vector &= (1 << dimension) - 1;
    bool result = false;
    for (const TElementaryConjuction &it : polynomial) {
        result ^= it.evaluate(vector);
    }
    return result;
}

std::string TPolynomial::vector() const {
    std::string result;
    result.reserve(1 << dimension);
    for (uint32_t i = 1 << dimension; i--; result.push_back('0' + evaluate(i)));
    return result;
}

TPolynomial& TPolynomial::operator=(const TPolynomial &obj) {
    if (dimension != obj.dimension) {
        throw std::logic_error("dimensions of operands doesn't match");
    }
    if (this != &obj) {
        polynomial = obj.polynomial;
    }
    return *this;
}

TPolynomial TPolynomial::operator+(const TPolynomial &obj) const {
    if (this == &obj) {
        return TPolynomial(dimension);
    }
    if (dimension != obj.dimension) {
        throw std::logic_error("dimensions of operands doesn't match");
    }
    TPolynomial result(dimension);
    std::merge(
        begin(),
        end(),
        obj.begin(),
        obj.end(),
        std::back_inserter(result.polynomial)
    );
    result.normalize();
    return result;
}

bool TPolynomial::operator<(const TPolynomial &obj) const {
    return polynomial.size() < obj.polynomial.size();
}

TPolynomial TPolynomial::operator*(const TElementaryConjuction &obj) const {
    TPolynomial result(*this);
    std::for_each(result.begin(), result.end(), [&obj](TElementaryConjuction &it) { it *= obj; });
    return result;
}

TPolynomial TPolynomial::operator*(const TPolynomial &obj) const {
    TPolynomial result(dimension);
    result.polynomial.reserve(polynomial.size() * obj.polynomial.size());
    for (const TElementaryConjuction &conj : obj) {
        std::copy(begin(), end(), std::back_inserter(result.polynomial));
        std::for_each(
            result.polynomial.end() - polynomial.size(),
            result.polynomial.end(),
            [&conj](TElementaryConjuction &it) { it *= conj; }
        );
    }
    result.normalize();
    return result;
}

TPolynomial::const_iterator TPolynomial::begin() const noexcept {
    return polynomial.begin();
}

TPolynomial::const_iterator TPolynomial::end() const noexcept {
    return polynomial.end();
}

std::istream& operator>>(std::istream &is, TPolynomial &obj) {
    std::streamoff pos = (is >> std::ws).tellg();
    if (is.peek() == EOF) {
        is.setstate(std::istream::failbit | std::istream::eofbit);
        return is;
    }
    std::string line;
    std::getline(is, line);
    std::istringstream iss(line);
    obj.clear();
    TElementaryConjuction conj(obj.dimension);
    while (iss >> conj) {
        obj.polynomial.push_back(std::move(conj));
        if (int32_t ch = (iss >> std::ws).peek(); ch != EOF && ch != '+') {
            is.seekg(pos);
            is.setstate(std::istream::failbit);
            return is;
        }
        iss.ignore(1);
    }
    is.clear();
    if (obj.polynomial.empty()) {
        is.seekg(pos);
        is.setstate(std::istream::failbit);
    }
    obj.normalize();
    return is;
}

std::ostream& operator<<(std::ostream &os, const TPolynomial &obj) {
    os << obj.polynomial.front();
    std::for_each(obj.begin() + 1, obj.end(), [&os](const TElementaryConjuction &conj) {
        os << '+' << conj;
    });
    return os;
}
