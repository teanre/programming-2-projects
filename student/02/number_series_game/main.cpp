#include <iostream>


int main()
{
    int nr_count = 0;
    std::cout << "How many numbers would you like to have? ";
    std::cin >> nr_count;

    for (int number = 1; number < nr_count+1; ++number)
        if (number % 3 == 0 and number % 7 == 0){
            std::cout << "zip boing" << std::endl;
        } else if (number % 3 == 0){
            std::cout << "zip" << std::endl;
        } else if (number % 7 == 0){
            std::cout << "boing" << std::endl;
        } else {
            std::cout << number << std::endl;
        }

    return 0;
}
