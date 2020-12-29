#include <fstream>
#include <random>
#include <ctime>
#include "headers/elementary_conjuction.h"
#include "headers/polynomial.h"

void process(std::istream &in, std::ostream &out) {
    static std::mt19937 gen(time(0));
    int32_t dimension;
    in >> dimension;
    TPolynomial p(dimension), tmp(dimension);
    in >> p;
    std::vector<TPolynomial> basis;
    while (in >> tmp) {
        basis.push_back(tmp);
    }
    basis.push_back(tmp); // костыль, подумаю как фиксить
    for (int32_t i = 0; i < 100'000; ++i) {
        TPolynomial sum = p + basis[gen() % basis.size()];
        if (sum.size() < p.size()) {
            p = sum;
        }
    }
    out << p;
}

// ./main %PATH_TO_INPUT_FILE% %PATH_TO_OUTPUT_FILE%
int main(int argc, char const *argv[]) {
    if (argc < 3) {
        return 0;
    }
    std::ifstream in(argv[1]);
    if (!in.is_open()) {
        return 0;
    }
    std::ofstream out(argv[2]);
    process(in, out);
    return 0;
}
