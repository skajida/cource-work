#include <headers/elementary_conjuction.h>

enum {
    DIVIDER = 16,                       // 8 bits per byte * sizeof(int32_t) / 2 bits per variable
    VARIABLE = 'x'
};

void TElementaryConjuction::clear(int32_t val) {
    isAlone = val;
    std::fill(conjuction.begin(), conjuction.end(), 0);
}

void TElementaryConjuction::set(int32_t index, int32_t value) {
    conjuction[index / DIVIDER] |= value << 2 * (index % DIVIDER);
}

TElementaryConjuction::TElementaryConjuction(int32_t n)
    : dimension(n)
    , isAlone(0)
    , conjuction((n + DIVIDER - 1) / DIVIDER)
{
    //
}

TElementaryConjuction& TElementaryConjuction::operator=(const TElementaryConjuction &operand) {
    if (dimension != operand.dimension) {
        throw std::logic_error("dimensions of operands doesn't match");
    }
    conjuction.assign(operand.conjuction.begin(), operand.conjuction.end());
    isAlone = operand.isAlone;
    return *this;
}

int32_t TElementaryConjuction::operator[](int32_t index) const {
    return conjuction[index / DIVIDER] >> 2 * (index % DIVIDER) & 0b11;
}

bool TElementaryConjuction::operator<(const TElementaryConjuction &operand) const {
    if (dimension != operand.dimension) {
        throw std::logic_error("dimensions of operands doesn't match");
    }
    if (isAlone && !operand.isAlone) {
        return true;
    } else if (isAlone && isAlone != operand.isAlone) {
        return isAlone < operand.isAlone;
    } else if (isAlone) {
        return (*this)[isAlone - 1] > operand[operand.isAlone - 1];
    } else if (!operand.isAlone) {
        for (int32_t i = 0; i < dimension; ++i) {
            if ((*this)[i] != operand[i]) {
                return (*this)[i] > operand[i];
            }
        }
    }
    return false;
}

bool TElementaryConjuction::operator==(const TElementaryConjuction &operand) const {
    if (dimension != operand.dimension) {
        throw std::logic_error("dimensions of operands doesn't match");
    }
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

bool TElementaryConjuction::isZero() const {
    return isAlone == -1;
}

bool TElementaryConjuction::isInversed(const TElementaryConjuction &operand) const {
    if (dimension != operand.dimension) {
        throw std::logic_error("dimensions of operands doesn't match");
    }
    if (isAlone && isAlone == operand.isAlone
        && (*this)[isAlone - 1] != operand[operand.isAlone - 1])
    {
        return true;
    }
    return false;
}

class TVariable {
private:
    int32_t number;
public:
    inline int32_t get() const {
        return number;
    }
    friend std::istream& operator>>(std::istream&, TVariable&);
};

std::istream& operator>>(std::istream &in, TVariable &obj) {
    std::streamoff pos = (in >> std::ws).tellg();
    if (in.peek() == EOF) {
        in.setstate(std::istream::failbit | std::istream::eofbit);
        return in;
    }
    int32_t var = in.get();
    if (var != VARIABLE || isspace(in.peek()) || !(in >> obj.number)) {
        in.seekg(pos);
        in.setstate(std::istream::failbit);
    }
    return in;
}

std::istream& operator>>(std::istream &in, TElementaryConjuction &obj) {
    obj.clear(0);
    std::streamoff pos = (in >> std::ws).tellg();
    if (in.peek() == EOF) {
        in.setstate(std::istream::failbit | std::istream::eofbit);
        return in;
    }
    TVariable var;
    int32_t value = TElementaryConjuction::EMPTY;
    bool isZero = false;                        // !x1x1
    for (int32_t i = 0, ch; !in.rdstate() && ((ch = in.peek()) == '!' || ch == VARIABLE); ++i) {
        value = ch == '!' ? TElementaryConjuction::NEGATIVE : TElementaryConjuction::POSITIVE;
        if (!(in.ignore(ch == '!') >> var) || var.get() < 1 || var.get() > obj.dimension) {
            in.seekg(pos);
            in.setstate(std::istream::failbit);
            return in;
        }
        if (!in.rdstate()) {
            pos = in.tellg();
        }
        if (!isZero) {
            obj.isAlone = i ? 0 : var.get();
            if (obj[var.get() - 1] != value) {
                if (obj[var.get() - 1] == TElementaryConjuction::EMPTY) {
                    obj.set(var.get() - 1, value);
                } else {
                    isZero = true;
                }
            }
        }
    }
    if (isZero) {
        obj.clear(-1);
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
