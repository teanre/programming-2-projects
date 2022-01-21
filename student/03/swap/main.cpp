#include <cstdlib>
#include <iostream>

// Write your swap function here.

void swap(int& nr1, int& nr2){

    int new1 = nr2;

    int new2= nr1;

    nr1 = new1;
    nr2 = new2;

    //return (nr1, nr2);
}

#ifndef UNIT_TESTING
int main()
{
    std::cout << "Enter an integer: ";
    int i = 0;
    std::cin >> i;

    std::cout << "Enter another integer: ";
    int j = 0;
    std::cin >> j;

    swap(i, j);
    std::cout << "The integers are " << i << " and " << j << std::endl;

    return EXIT_SUCCESS;
}
#endif
