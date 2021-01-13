#include <iostream>
#include <algorithm>

#include "polynomial.h"

void TPolynomial::clear() {
    isNegative = false;
    polynomial.clear();
}

void TPolynomial::deleteSimilar() {
    std::sort(polynomial.begin(), polynomial.end());
    std::vector<size_t> excesses;
    for (size_t i = 0; i < polynomial.size(); ++i) {
        if (i + 1 == polynomial.size()) {
            break;
        }
        if (polynomial[i] == polynomial[i + 1]) {
            excesses.push_back(i++);
            excesses.push_back(i);
        } else if (polynomial[i].isInversed(polynomial[i + 1])) {
            isNegative = !isNegative;
            excesses.push_back(i++);
            excesses.push_back(i);
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
    polynomial.resize(polynomial.size() - quantity, TElementaryConjuction(dimension));
}

TPolynomial::TPolynomial(int32_t n) : dimension(n), isNegative(), polynomial() {
    //
}

TPolynomial TPolynomial::operator+(const TPolynomial &operand) const {
    TPolynomial res(dimension);
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
    isNegative = operand.isNegative;
    polynomial = operand.polynomial;
    return *this;
}

size_t TPolynomial::size() const {
    return polynomial.size() + isNegative;
}

std::istream& operator>>(std::istream &in, TPolynomial &obj) {
    enum class EStates {
        Conjuction,
        End,
        Error
    };
    obj.clear();
    EStates currentState = EStates::Conjuction;
    while (currentState != EStates::End) {
        TElementaryConjuction conj(obj.dimension);
        switch (currentState) {
        case EStates::Conjuction:
            if (in >> conj) {
                obj.polynomial.push_back(conj);
                int32_t ch = in.peek();
                while (ch != '\n' && ch != EOF && isspace(ch)) {
                    in.get();
                    ch = in.peek();
                }
                if (ch == '\n' || ch == EOF) {
                    currentState = EStates::End;
                } else if (!isspace(ch) && ch != '+') {
                    currentState = EStates::Error;
                }
            } else {
                currentState = EStates::End;
            }
            break;
        default:
            throw std::invalid_argument("Wrong input while reading polynomial");
        }
        in.get();
    }
    return in;
}

std::ostream& operator<<(std::ostream &out, TPolynomial &obj) {
    obj.deleteSimilar();
    if (obj.size()) {
        out << obj.polynomial[0];
        for (size_t i = 1; i < obj.size(); ++i) {
            out << '+' << obj.polynomial[i];
        }
    } else {
        out << (obj.isNegative ? 1 : 0);
    }
    if (obj.isNegative) {
        out << "+1";
    }
    return out;
}
