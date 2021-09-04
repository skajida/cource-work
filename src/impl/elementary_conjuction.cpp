#include <hdrs/elementary_conjuction.h>

#include <algorithm>

TElementaryConjuction::iterator TElementaryConjuction::begin() noexcept {
    return conjuction.begin();
}

TElementaryConjuction::iterator TElementaryConjuction::end() noexcept {
    return conjuction.end();
}

void TElementaryConjuction::clear() {
    conjuction.clear();
}

void TElementaryConjuction::normalize() {
    if (begin() == end()) {
        conjuction.push_back({ 0, EState::Empty });
    } else {
        conjuction.erase(std::remove(begin(), end(), TVariable{ 0, EState::Positive }), end());
        std::sort(begin(), end());
        conjuction.erase(std::unique(begin(), end()), end());
        for (auto it = begin(); it + 1 < end(); ++it) {
            if ((it->number == 0 && it->state == EState::Empty) || (it->number == (it + 1)->number
            && it->state == EState::Positive && (it + 1)->state == EState::Negative))
            {
                clear();
                return;
            }
        }
        if (conjuction.empty()) {
            conjuction.push_back({ 0, EState::Positive });
        }
    }
}

TElementaryConjuction::TElementaryConjuction(uint32_t dim) : dimension(dim), conjuction(), excess() {}

TElementaryConjuction::TElementaryConjuction(const TElementaryConjuction &obj)
    : dimension(obj.dimension)
    , conjuction(obj.conjuction)
    , excess(obj.excess)
{
}

TElementaryConjuction::TElementaryConjuction(TElementaryConjuction &&obj)
    : dimension(obj.dimension)
    , conjuction(std::move(obj.conjuction))
    , excess(obj.excess)
{
}

TElementaryConjuction::TElementaryConjuction(uint32_t dim, std::vector<TVariable> conj)
    : dimension(dim)
    , conjuction(conj)
    , excess()
{
}

bool TElementaryConjuction::evaluate(uint32_t vector) const {
    // vector &= (1 << dimension) - 1;
    if (!conjuction.front().number) {
        return conjuction.front().state == EState::Positive;
    }
    bool result = true;
    for (const TVariable &it : conjuction) {
        result &= (vector >> (it.number - 1) & 1) ^ (it.state == EState::Negative);
    }
    return result;
}

bool TElementaryConjuction::isInversed(const TElementaryConjuction &obj) const {
    if (dimension != obj.dimension) {
        throw std::logic_error("dimensions of operands doesn't match");
    }
    return (conjuction.size() == 1 && obj.conjuction.size() == 1 &&
        conjuction[0].number == obj.conjuction[0].number &&
        static_cast<int32_t>(conjuction[0].state) + static_cast<int32_t>(obj.conjuction[0].state)
        == static_cast<int32_t>(EState::Positive) + static_cast<int32_t>(EState::Negative)
    );
}

void TElementaryConjuction::setState(bool exc) const {
    excess = exc;
}

bool TElementaryConjuction::getState() const {
    return excess;
}

bool TElementaryConjuction::empty() const {
    return conjuction.empty();
}

bool TElementaryConjuction::operator<(const TElementaryConjuction &obj) const {
    if (conjuction.size() != obj.conjuction.size()) {
        return conjuction.size() < obj.conjuction.size();
    }
    return std::lexicographical_compare(
        begin(),
        end(),
        obj.begin(),
        obj.end()
    );
}

bool TElementaryConjuction::operator==(const TElementaryConjuction &obj) const {
    if (conjuction.size() != obj.conjuction.size()) {
        return false;
    }
    return std::equal(begin(), end(), obj.begin());
}

TElementaryConjuction& TElementaryConjuction::operator=(const TElementaryConjuction &obj) {
    if (dimension != obj.dimension) {
        throw std::logic_error("dimensions of operands doesn't match");
    }
    if (this != &obj) {
        conjuction = obj.conjuction;
    }
    return *this;
}

TElementaryConjuction& TElementaryConjuction::operator*=(const TElementaryConjuction &obj) {
    conjuction.reserve(conjuction.size() + obj.conjuction.size());
    std::copy(obj.begin(), obj.end(), std::back_inserter(conjuction));
    normalize();
    return *this;
}

TElementaryConjuction::const_iterator TElementaryConjuction::begin() const noexcept {
    return conjuction.begin();
}

TElementaryConjuction::const_iterator TElementaryConjuction::end() const noexcept {
    return conjuction.end();
}

std::istream& operator>>(std::istream &is, TElementaryConjuction &obj) {
    std::streamoff pos = (is >> std::ws).tellg();
    if (is.peek() == EOF) {
        is.setstate(std::istream::failbit | std::istream::eofbit);
        return is;
    }
    obj.conjuction.clear();
    TVariable var;
    while (!isspace(is.peek()) && is >> var) {
        if (var.number > obj.dimension) {
            is.seekg(pos);
            is.setstate(std::istream::failbit);
            return is;
        }
        obj.conjuction.push_back(var);
    }
    is.clear();
    if (obj.conjuction.empty()) {
        is.seekg(pos);
        is.setstate(std::istream::failbit);
    }
    obj.normalize();
    return is;
}

std::ostream& operator<<(std::ostream &os, const TElementaryConjuction &obj) {
    std::for_each(obj.begin(), obj.end(), [&os](const TVariable &var) { os << var; });
    return os;
}
