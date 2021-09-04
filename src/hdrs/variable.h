#pragma once

#include <iostream>
#include <cstdint>

constexpr char VARIABLE = 'x';          // default variable symbol

enum class EState {
    Empty    = 0b00,
    Positive = 0b01,
    Negative = 0b11
};

struct TVariable {
    uint32_t number;
    EState state;

    bool operator<(const TVariable&) const;
    bool operator==(const TVariable&) const;

    friend std::istream& operator>>(std::istream&, TVariable&);
    friend std::ostream& operator<<(std::ostream&, const TVariable&);
};

/*
 * 0  : number =  0, state = EState::Empty
 * 1  : number =  0, state = EState::Positive
 * x12: number = 12, state = EState::Positive
 * !x3: number =  3, state = EState::Negative
 */
