#include <iostream>
#include <vector>
#include <cstdint>

#pragma once

class TElementaryConjuction {
    enum {
        EMPTY = 0,
        POSITIVE = 1,
        NEGATIVE = 3
    };
private:
    const int32_t dimension;
    int32_t isAlone;
    std::vector<int32_t> conjuction;

    void clear();
    void set(int32_t, int32_t);
public:
    explicit TElementaryConjuction(int32_t);

    TElementaryConjuction& operator=(const TElementaryConjuction&);
    int32_t operator[](int32_t) const;
    bool operator<(const TElementaryConjuction&) const;
    bool operator==(const TElementaryConjuction&) const;

    bool isInversed(const TElementaryConjuction&) const;

    friend std::istream& operator>>(std::istream&, TElementaryConjuction&);
    friend std::ostream& operator<<(std::ostream&, const TElementaryConjuction&);
};
