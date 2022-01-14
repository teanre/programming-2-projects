#include <iostream>


int main()
{
    int nr_count = 0;
    std::cout << "How many numbers would you like to have? ";
    std::cin >> nr_count;

    for (int number = 1; number < nr_count+1; ++number) {
        std::cout << number << std::endl;
    }

    return 0;
}
