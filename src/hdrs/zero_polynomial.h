#pragma once

#include <hdrs/polynomial.h>

enum class EMode {
    Zero,
    One,
    Positive/*,
    Negative*/
};

int32_t binpow(int32_t base, int32_t exp);

std::vector<TPolynomial> generateZeroBasis(uint32_t dimension);
