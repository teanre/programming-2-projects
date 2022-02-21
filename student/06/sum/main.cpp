#include <iostream>
#include <string>
#include <vector>
#ifndef RECURSIVE_FUNC
#define RECURSIVE_FUNC
#endif

int SUM;

std::vector<std::string> split(const std::string& s, const char delimiter, bool ignore_empty = false){
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

int sum_recursive(std::vector<int>& v){
    RECURSIVE_FUNC
    // Do not remove RECURSIVE_FUNC declaration, it's necessary for automatic testing to work
    // ------------

    if (v.size() == 1)
    {
        SUM += v.at(0);
        return SUM;
    }
    else
    {
       SUM += v.back();
       v.pop_back();
       std::vector<int> new_v;
       new_v = v;
       return sum_recursive(new_v);
    }

}

// Do not modify rest of the code, or the automated testing won't work.
#ifndef UNIT_TESTING
int main()
{
    std::cout << "Enter integers separated by spaces: ";
    std::string line;
    getline(std::cin, line);
    std::vector<std::string> strings = split(line, ' ', true);
    std::vector<int> integers;
    for(const auto& s : strings){
        integers.push_back(stoi(s));
    }

    std::cout << "Sum: " << sum_recursive(integers) << std::endl;
}
#endif
