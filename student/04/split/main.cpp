#include <iostream>
#include <string>
#include <vector>
#include <string>


// TODO: Implement split function here
// Do not change main function

std::vector <std::string> split(std::string const& text,
                                const char splitting_char,
                                bool pass_or_not = false)
{
    std::vector<std::string> parts;

    std::string::size_type start = 0;
    std::string::size_type end = 0;


    while (start <= text.size())
    {
        std::string part = "";

        end = text.find(splitting_char, start);

        if (end == std::string::npos)
        {
            end = text.size();
        }

        part = text.substr(start, (end - start));

        if (part != "" || !pass_or_not)
        {
            parts.push_back(part);
        }

        start = end+1;

    }
    return parts;
}



int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}
