#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "../DataReader.hpp"

bool hasTwo(const std::string& s);
bool hasThree(const std::string& s);
bool areIdsMatching(const std::string& s1, const std::string& s2);
std::string getCommonCharacters(const std::string& s1, const std::string& s2);
int part_one();
std::string part_two();


int main(int argc, char* argv[])
{
    //int answer = part_one();
    std::string answer = part_two();

    std::cout << "Answer: " << answer << std::endl;
    return 0;
}

int part_one()
{
    DataReader reader("part_one_data.txt");

    int twoCount {0};
    int threeCount {0};
    std::vector<std::string> lines = reader.readData();

    for (auto it = lines.cbegin(); it != lines.cend(); it++)
    {
        if (hasTwo(*it))
        {
            twoCount++;
        }

        if (hasThree(*it))
        {
            threeCount++;
        }
    }

    return twoCount * threeCount;
}

std::string part_two()
{
    DataReader reader("part_two_data.txt");
    std::vector<std::string> lines = reader.readData();

    for (auto it = lines.cbegin(); it != lines.cend(); it++)
    {
        for (auto it2 = lines.cbegin(); it2 != lines.cend(); it2++)
        {
            if (areIdsMatching(*it, *it2))
            {
                return getCommonCharacters(*it, *it2);
            }
        }
    }

    return "";
}

std::string getCommonCharacters(const std::string& s1, const std::string& s2)
{
    std::stringstream ss;

    auto it1 = s1.cbegin();
    auto it2 = s2.cbegin();

    while (it1 != s1.cend() && it2 != s2.cend())
    {
        if (*it1 == *it2)
        {
            ss << *it1;
        }

        it1++;
        it2++;
    }

    return ss.str();
}

bool areIdsMatching(const std::string& s1, const std::string& s2)
{
    int mismatchCount {0};

    auto it1 = s1.cbegin();
    auto it2 = s2.cbegin();

    while (it1 != s1.cend() && it2 != s2.cend())
    {
        if (*it1 != *it2)
        {
            mismatchCount++;

            if (mismatchCount > 1)
            {
                return false;
            }
        }

        it1++;
        it2++;
    }

    return mismatchCount == 1;
}

bool hasTwo(const std::string& s)
{
    for (auto it = s.cbegin(); it != s.cend(); it++)
    {
        int letterCount = std::count(s.begin(), s.end(), *it);

        if (letterCount == 2)
        {
            return true;
        }
    }

    return false;
}

bool hasThree(const std::string& s)
{
    for (auto it = s.cbegin(); it != s.cend(); it++)
    {
        int letterCount = std::count(s.begin(), s.end(), *it);

        if (letterCount == 3)
        {
            return true;
        }
    }

    return false;
}
