#include <hdrs/zero_polynomial.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout << "Input dimension you want work with:" << std::endl;
    uint32_t dimension;
    std::cin >> dimension;
    std::cout << "Input polynomial you want to shrink:" << std::endl;
    TPolynomial polynomial(dimension);
    std::cin >> polynomial;

    std::vector<TPolynomial> basis = generateZeroBasis(dimension);
    bool flag;
    do {
        flag = false;
        for (const TPolynomial &item : basis) {
            TPolynomial sum(dimension);
            sum = polynomial + item;
            if (sum < polynomial) {
                flag = true;
                polynomial = sum;
            }
        }
    } while (flag);
    std::cout << "Your polynomial has been shrinken to this form:\n" << polynomial << std::endl;
    return 0;
}
