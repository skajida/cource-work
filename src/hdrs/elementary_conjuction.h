#pragma once

#include <hdrs/variable.h>

#include <vector>

class TElementaryConjuction {
    using const_iterator = std::vector<TVariable>::const_iterator;
    using iterator = std::vector<TVariable>::iterator;
private:
    const uint32_t dimension;
    std::vector<TVariable> conjuction;
    mutable bool excess;

    iterator begin() noexcept;
    iterator end() noexcept;

    void clear();
public:
    void normalize();

    explicit TElementaryConjuction(uint32_t dim);
    TElementaryConjuction(const TElementaryConjuction&);
    TElementaryConjuction(TElementaryConjuction&&);
    TElementaryConjuction(uint32_t, std::vector<TVariable>);

    bool evaluate(uint32_t vector) const;

    bool isInversed(const TElementaryConjuction&) const;

    void setState(bool) const;
    bool getState() const;

    bool empty() const;
    bool operator<(const TElementaryConjuction&) const;
    bool operator==(const TElementaryConjuction&) const;
    TElementaryConjuction& operator=(const TElementaryConjuction&);

    TElementaryConjuction& operator*=(const TElementaryConjuction&);

    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;

    friend std::istream& operator>>(std::istream&, TElementaryConjuction&);
    friend std::ostream& operator<<(std::ostream&, const TElementaryConjuction&);
};
