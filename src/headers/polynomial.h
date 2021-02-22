#pragma once

#include <headers/elementary_conjuction.h>

class TPolynomial {
private:
    const int32_t dimension;
    mutable bool isNegative;
    mutable std::vector<TElementaryConjuction> polynomial;

    void clear();
    void deleteSimilar() const;
public:
    explicit TPolynomial(int32_t dim);

    TPolynomial operator+(const TPolynomial&) const;
    TPolynomial& operator=(const TPolynomial&);

    size_t size() const;

    friend std::istream& operator>>(std::istream&, TPolynomial&);
    friend std::ostream& operator<<(std::ostream&, const TPolynomial&);
};
