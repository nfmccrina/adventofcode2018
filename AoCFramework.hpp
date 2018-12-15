#pragma once

#include <string>
#include <vector>
#include <functional>
#include <fstream>
#include <iostream>

template<typename SolutionType>
class AoCFramework
{
public:
    AoCFramework(const std::string& dataPath, const std::function<SolutionType(std::vector<std::string>)>& computation);
    void run();

private:
    // private methods
    std::vector<std::string> readInput();
    SolutionType runCalculation();

    // private data
    const std::string& path;
    const std::function<SolutionType(std::vector<std::string>)>& computation;

};

template<typename SolutionType>
AoCFramework<SolutionType>::AoCFramework(const std::string& dataPath,
    const std::function<SolutionType(std::vector<std::string>)>& computation)
    : path {dataPath}, computation {computation}
{
}

template<typename SolutionType>
void AoCFramework<SolutionType>::run()
{
    SolutionType answer = runCalculation();

    std::cout << "Answer: " << answer << std::endl;
}

template<typename SolutionType>
SolutionType AoCFramework<SolutionType>::runCalculation()
{
    return computation(readInput());
}

template<typename SolutionType>
std::vector<std::string> AoCFramework<SolutionType>::readInput()
{
    std::ifstream fin;
    std::vector<std::string> lines;

    fin.open(path);

    while (!fin.eof())
    {
        std::string currentLine;

        std::getline(fin, currentLine);

        lines.push_back(currentLine);
    }

    fin.close();

    return lines;
}
