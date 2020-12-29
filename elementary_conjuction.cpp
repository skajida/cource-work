#include "headers/elementary_conjuction.h"

enum {
    DIVIDER = 16,
    VARIABLE = 'x'
};

void TElementaryConjuction::clear() {
    for (int32_t &it : conjuction) {
        it = 0;
    }
}

void TElementaryConjuction::set(int32_t index, int32_t value) {
    conjuction[index / DIVIDER] += value << 2 * (index % DIVIDER);
}

TElementaryConjuction::TElementaryConjuction(int32_t n)
    : dimension(n)
    , isAlone()
    , conjuction(n / DIVIDER + !!(n % DIVIDER))
{
    //
}

TElementaryConjuction& TElementaryConjuction::operator=(const TElementaryConjuction &operand) {
    for (int32_t i = 0; i < dimension; ++i) {
        conjuction[i] = operand.conjuction[i];
    }
    isAlone = operand.isAlone;
    return *this;
}

int32_t TElementaryConjuction::operator[](int32_t index) const {
    return conjuction[index / DIVIDER] >> 2 * (index % DIVIDER) & NEGATIVE;
}

bool TElementaryConjuction::operator<(const TElementaryConjuction &operand) const {
    if (isAlone && !operand.isAlone) {
        return true;
    } else if (isAlone && isAlone != operand.isAlone) {
        return isAlone < operand.isAlone;
    } else if (isAlone) {
        return (*this)[isAlone - 1] > operand[operand.isAlone - 1];
    }
    if (!operand.isAlone) {
        for (int32_t i = 0; i < dimension; ++i) {
            if ((*this)[i] != operand[i]) {
                return (*this)[i] > operand[i];
            }
        }
    }
    return false;
}

bool TElementaryConjuction::operator==(const TElementaryConjuction &operand) const {
    if (isAlone && isAlone == operand.isAlone) {
        return (*this)[isAlone - 1] == operand[operand.isAlone - 1];
    }
    if (!isAlone && !operand.isAlone) {
        for (size_t i = 0; i < conjuction.size(); ++i) {
            if (conjuction[i] != operand.conjuction[i]) {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool TElementaryConjuction::isInversed(const TElementaryConjuction &operand) const {
    if (isAlone && isAlone == operand.isAlone && (*this)[isAlone - 1] != operand[operand.isAlone - 1]) {
        return true;
    }
    return false;
}

std::istream& operator>>(std::istream &in, TElementaryConjuction &obj) {
    enum class EStates {
        Variable,
        Number,
        End,
        Error
    };
    int32_t ch;
    while (isspace(ch = in.peek())) {
        in.get();
    }
    if (ch == EOF) {
        return in;
    }
    obj.clear();
    int32_t value = TElementaryConjuction::EMPTY, number = 0, firstEntry = 0;
    EStates currentState = EStates::Variable;
    while (currentState != EStates::End) {
        ch = in.peek();
        switch (currentState) {
        case EStates::Variable:
            if (ch == '!') {
                value = TElementaryConjuction::NEGATIVE;
            } else {
                currentState = ch == VARIABLE ? EStates::Number : EStates::Error;
                if (value == TElementaryConjuction::EMPTY) {
                    value = TElementaryConjuction::POSITIVE;
                }
            }
            number = 0;
            break;
        case EStates::Number:
            if (isdigit(ch)) {
                number *= 10;
                number += ch - '0';
            } else if (number && number - 1 < obj.dimension) {
                // if (obj[number - 1] != TElementaryConjuction::EMPTY) {
                    //
                // }
                obj.isAlone = firstEntry ? 0 : number;
                firstEntry = number;
                obj.set(number - 1, value);
                number = 0;
                value = ch == '!' ? TElementaryConjuction::NEGATIVE
                    : ch == VARIABLE ? TElementaryConjuction::POSITIVE
                    : TElementaryConjuction::EMPTY;
                currentState = ch == '!' ? EStates::Variable
                    : ch == VARIABLE ? EStates::Number
                    : EStates::End;

            } else {
                currentState = EStates::Error;
            }
            break;
        default:
            throw std::invalid_argument("Wrong input while reading elementary conjuction");
        }
        if (currentState != EStates::End && currentState != EStates::Error) {
            in.get();
        }
    }
    return in;
}

std::ostream& operator<<(std::ostream &out, const TElementaryConjuction &obj) {
    for (int32_t i = 0; i < obj.dimension; ++i) {
        if (obj[i] == TElementaryConjuction::NEGATIVE) {
            out << '!';
        }
        if (obj[i] != TElementaryConjuction::EMPTY) {
            out << static_cast<char>(VARIABLE) << i + 1;
        }
    }
    return out;
}
