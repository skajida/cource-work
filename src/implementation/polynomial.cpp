#include <iostream>
#include <sstream>
#include <algorithm>

#include <headers/polynomial.h>

void TPolynomial::clear() {
    isNegative = false;
    polynomial.clear();
}

void TPolynomial::deleteSimilar() const {
    std::sort(polynomial.begin(), polynomial.end());
    std::vector<size_t> excesses;
    for (size_t i = 1; i < polynomial.size(); ++i) {
        if (polynomial[i - 1] == polynomial[i]) {
            excesses.push_back(i);
            excesses.push_back(++i);
        } else if (polynomial[i - 1].isInversed(polynomial[i])) {
            isNegative = !isNegative;
            excesses.push_back(i);
            excesses.push_back(++i);
        }
    }
    size_t quantity = 0;
    for (size_t i = 0; i < polynomial.size(); ++i) {
        if (std::binary_search(excesses.begin(), excesses.end(), i)) {
            ++quantity;
        } else if (quantity) {
            std::swap(polynomial[i], polynomial[i - quantity]);
        }
    }
    polynomial.erase(polynomial.end() - quantity, polynomial.end());
}

TPolynomial::TPolynomial(int32_t n) : dimension(n), isNegative(), polynomial() {
    //
}

TPolynomial TPolynomial::operator+(const TPolynomial &operand) const {
    if (dimension != operand.dimension) {
        throw std::logic_error("dimensions of operands doesn't match");
    }
    TPolynomial res(dimension);
    res.polynomial.reserve(polynomial.size() + operand.polynomial.size());
    for (const TElementaryConjuction &it : polynomial) {
        res.polynomial.push_back(it);
    }
    for (const TElementaryConjuction &it : operand.polynomial) {
        res.polynomial.push_back(it);
    }
    res.deleteSimilar();
    return res;
}

TPolynomial& TPolynomial::operator=(const TPolynomial &operand) {
    if (dimension != operand.dimension) {
        throw std::logic_error("dimensions of operands doesn't match");
    }
    isNegative = operand.isNegative;
    polynomial = operand.polynomial;
    return *this;
}

size_t TPolynomial::size() const {
    return polynomial.size() + isNegative;
}

std::istream& operator>>(std::istream &in, TPolynomial &obj) {
    obj.clear();
    std::streamoff pos_src = (in >> std::ws).tellg();
    if (in.peek() == EOF) {
        in.setstate(std::istream::failbit | std::istream::eofbit);
        return in;
    }
    std::string line;
    std::getline(in, line, '\n');
    std::istringstream sin(line);
    std::streamoff pos_cpy = sin.tellg();
    TElementaryConjuction ec(obj.dimension);
    char ch = 0;
    do {
        if (!(sin >> ec)) {
            in.seekg(pos_src);
            in.setstate(std::istream::failbit);
            return in;
        }
        pos_src += sin.tellg() - pos_cpy;
        pos_cpy = sin.tellg();
        if (!ec.isZero()) {
            obj.polynomial.push_back(ec);       // move
        }
    } while (!sin.rdstate() && sin >> ch && ch == '+');
    if (ch != 0 && ch != '+') {
        in.seekg(pos_src + sin.tellg() - pos_cpy);
        in.setstate(std::istream::failbit);
    }
    return in;
}

std::ostream& operator<<(std::ostream &out, const TPolynomial &obj) {
    obj.deleteSimilar();
    if (obj.size()) {
        out << obj.polynomial[0];
        for (size_t i = 1; i < obj.size(); ++i) {
            out << '+' << obj.polynomial[i];
        }
    } else {
        out << (obj.isNegative ? 1 : 0);
    }
    // 1+1
    if (obj.isNegative) {
        out << "+1";
    }
    return out;
}
