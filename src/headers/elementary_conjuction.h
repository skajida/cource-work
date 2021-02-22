#pragma once

#include <iostream>
#include <vector>
#include <cstdint>

class TElementaryConjuction {
    enum {
        EMPTY = 0b00,
        POSITIVE = 0b01,
        NEGATIVE = 0b11
    };
private:
    const int32_t dimension;
    int32_t isAlone;
    std::vector<int32_t> conjuction;

    void clear(int32_t isAloneVal);
    void set(int32_t idx, int32_t val);
public:
    explicit TElementaryConjuction(int32_t dim);

    TElementaryConjuction& operator=(const TElementaryConjuction&);
    int32_t operator[](int32_t idx) const;
    bool operator<(const TElementaryConjuction&) const;
    bool operator==(const TElementaryConjuction&) const;

    bool isZero() const;
    bool isInversed(const TElementaryConjuction&) const;

    friend std::istream& operator>>(std::istream&, TElementaryConjuction&);
    friend std::ostream& operator<<(std::ostream&, const TElementaryConjuction&);
};
