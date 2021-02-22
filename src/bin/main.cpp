#include <iostream>
#include <random>
#include <ctime>

#include <headers/elementary_conjuction.h>
#include <headers/polynomial.h>

bool pureCheck(TPolynomial &p, const std::vector<TPolynomial> &basis) {
    for (const TPolynomial &item : basis) {
        TPolynomial sum = p + item;
        if (sum.size() < p.size()) {
            p = sum;                            // move
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
        basis.push_back(tmp);                   // move
    }

    std::cerr << "SRC POLYNOMIAL: " << p << '\n';
    std::cerr << "TOTAL " << basis.size() << " ELEMS IN BASIS" << '\n';
    for (const TPolynomial &item : basis) {
        std::cerr << item << '\n';
    }
    std::cerr << "END OF DEBUG OUTPUT" << std::endl;

    while (pureCheck(p, basis)) {
        for (int32_t i = 0; i < 10'000; ++i) {
            TPolynomial sum = p + basis[gen() % basis.size()];
            if (sum.size() < p.size()) {
                p = sum;                        // move
            }
        }
        std::cerr << "ITERATION COMPLETE" << std::endl;
    }
    out << p;
}

void print(std::istream &in, int quant) {
    for (int i = 0; i < quant; ++i) {
        std::cerr << static_cast<char>(in.get());
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    process(std::cin, std::cout);
    return 0;
}
