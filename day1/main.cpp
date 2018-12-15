#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <string>
#include <vector>

int part_one();
int part_two();

class OverflowException
{

};

int main(int argc, char* argv[])
{
    //int result = part_one();
    int result = part_two();
    std::cout << "Answer: " << result << std::endl;
    return 0;
}

int part_two()
{
    std::ifstream fin("data.txt");
    int result = 0;
    std::vector<int> freqList;
    std::vector<int> foundFreqs;

    while (!fin.eof())
    {
        std::string currentLine;
        std::getline(fin, currentLine);

        if (currentLine.length() > 1)
        {
            bool isPositive = currentLine[0] == '+';
            int value = std::stoi(std::string(currentLine, 1, currentLine.length() - 1));

            if (!isPositive)
            {
                value = -value;
            }

            freqList.push_back(value);
        }
    }

    fin.close();

    bool completed = false;

    while (!completed)
    {
        for (auto it = freqList.cbegin(); it != freqList.cend(); it++)
        {
            int newResult = result + *it;

            if ((*it > 0 && newResult < result) || (*it < 0 && newResult > result))
            {
                std::cout << "Overflow!" << std::endl;
                throw OverflowException{};
            }
            else
            {
                result = newResult;
            }

            auto bsit = std::lower_bound(foundFreqs.begin(), foundFreqs.end(), result);

            if (bsit == foundFreqs.end() || *bsit != result)
            {
                foundFreqs.insert(bsit, result);
            }
            else
            {
                completed = true;
                break;
            }
        }
    }

    return result;
}

int part_one()
{
    std::ifstream fin("data.txt");
    int result = 0;

    while (!fin.eof())
    {
        std::string currentLine;
        std::getline(fin, currentLine);

        if (currentLine.length() > 1)
        {
            bool isPositive = currentLine[0] == '+';
            int value = std::stoi(std::string(currentLine, 1, currentLine.length() - 1));
            if (!isPositive)
            {
                value = -value;
            }

            int newResult = result + value;

            if ((isPositive && newResult < result) || (!isPositive && newResult > result))
            {
                std::cout << "Overflow!" << std::endl;
                break;
            }
            else
            {
                result = newResult;
            }
        }
    }

    fin.close();

    return result;
}
