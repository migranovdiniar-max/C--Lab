#include <iostream>
#include "sign.h"

int main() {
    SIGN p("Ivanov", "Ivan", "Aries", 1, 1, 2000);

    p.print();

    std::cout << "\nВведите нового человека:\n";
    SIGN q;
    std::cin >> q;

    std::cout << "\nВы ввели:\n" << q << std::endl;

    return 0;
}
