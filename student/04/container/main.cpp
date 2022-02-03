#include <cstdlib>
#include <iostream>
#include <vector>


void read_integers(std::vector< int >& ints, int count)
{
    int new_integer = 0;
    for(int i = 0; i < count; ++i)
    {
        std::cin >> new_integer;
        // TODO: Implement your solution here
        ints.push_back(new_integer);
    }

}

// TODO: Implement your solution here
bool same_values(std::vector<int>& ints)
{
    //onko kaikki alkiot samoja

    int first_nr = ints.front();

    for (int i : ints)
    {

       if ( i != first_nr)
       {
           return false;
       }
    }

    return true;
}

bool is_ordered_non_strict_ascending(std::vector<int>& ints)
{

    int previous_nr = ints.front();

   //onko seuraava alkio joko yhtä suuri tai suurempi kuin edellinen
    for (int i : ints)
    {
       if (i < previous_nr)
       {
           return false;
       }
       previous_nr = i;
    }

    return true;
}

bool is_arithmetic_series(std::vector<int>& ints)
{

    if (same_values(ints))
    {
        return true;
    }

    std::vector<int> difference;

    //jos kahden peräkkäisen alkion erotus on aina sama
    //tökkää tähän kun kaikki nrot samoja, tyhjä vektori???

    int previous = ints.front();

    for (int i : ints)
    {
        if (i == ints.front())
        {
            continue;
        }

        int diff = (i - previous);
        difference.push_back(diff);
        previous = i;

    }


    if (!same_values(difference))
    {
        return false;
    }
    return true;
}

bool is_geometric_series(std::vector<int>& ints)
{
    //peräkkäisten termien suhdeluku vakio

    if (same_values(ints) && ints.front() == 0)
    {
        return false;
    }
    else if (same_values(ints))
    {
        return true;
    }


    std::vector<int> ratios;

    int ratio = 0;

    for (unsigned int index = 0; index < ints.size(); ++index)
    {

       if (ints.at(index) == ints.back())
       {
           continue;
       }
       else
       {
            ratio = ints.at(index+1)/ints.at(index);
            ratios.push_back(ratio);
       }
    }


    if (same_values(ratios))
    {
        return true;
    }
    else
    {

     return false;

}}

int main()
{
    std::cout << "How many integers are there? ";
    int how_many = 0;
    std::cin >> how_many;

    std::cout << "Enter the integers: ";
    std::vector<int> integers;
    read_integers(integers, how_many);

    if(same_values(integers))
        std::cout << "All the integers are the same" << std::endl;
    else
        std::cout << "All the integers are not the same" << std::endl;

    if(is_ordered_non_strict_ascending(integers))
        std::cout << "The integers are in a non-strict ascending order" << std::endl;
    else
        std::cout << "The integers are not in a non-strict ascending order" << std::endl;

    if(is_arithmetic_series(integers))
        std::cout << "The integers form an arithmetic series" << std::endl;
    else
        std::cout << "The integers do not form an arithmetic series" << std::endl;

    if(is_geometric_series(integers))
        std::cout << "The integers form a geometric series" << std::endl;
    else
        std::cout << "The integers do not form a geometric series" << std::endl;

    return EXIT_SUCCESS;
}
