#include "DataReader.hpp"

DataReader::DataReader(std::string path)
{
    fin.open(path);
}

DataReader::~DataReader()
{
    fin.close();
}

std::vector<std::string> DataReader::readData()
{
    std::vector<std::string> lines;

    while (!fin.eof())
    {
        std::string currentLine;

        std::getline(fin, currentLine);

        lines.push_back(currentLine);
    }

    return lines;
}
