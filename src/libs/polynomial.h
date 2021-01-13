#include <vector>

#include "elementary_conjuction.h"

#pragma once

class TPolynomial {
private:
    const int32_t dimension;
    bool isNegative;
    std::vector<TElementaryConjuction> polynomial;

    void clear();
    void deleteSimilar();
public:
    explicit TPolynomial(int32_t);

    TPolynomial operator+(const TPolynomial&) const;
    TPolynomial& operator=(const TPolynomial&);

    size_t size() const;

    friend std::istream& operator>>(std::istream&, TPolynomial&);
    friend std::ostream& operator<<(std::ostream&, TPolynomial&);
};
