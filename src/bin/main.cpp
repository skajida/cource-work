#include <iostream>
#include <random>
#include <ctime>

#include <headers/elementary_conjuction.h>
#include <headers/polynomial.h>

bool pureCheck(TPolynomial &p, const std::vector<TPolynomial> &basis) {
    for (const TPolynomial &item : basis) {
        TPolynomial sum = p + item;
        if (sum < p) {
            p = std::move(sum);
            return true;
        }
    }
    return false;
}

void process(std::istream &in, std::ostream &out) {
    static std::mt19937 gen(time(0));
    int32_t dimension;
    in >> dimension;
    TPolynomial p(dimension), tmp(dimension);
    in >> p;
    std::vector<TPolynomial> basis;
    while (in >> tmp) {
        basis.push_back(std::move(tmp));
    }
    while (pureCheck(p, basis)) {
        for (int32_t i = 0; i < 10'000; ++i) {
            TPolynomial sum = p + basis[gen() % basis.size()];
            if (sum < p) {
                p = std::move(sum);
            }
        }
    }
    out << p;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    process(std::cin, std::cout);
    return 0;
}
