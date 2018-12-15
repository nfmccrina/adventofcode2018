#pragma once

#include <string>
#include <fstream>
#include <vector>

class DataReader
{
public:
    DataReader(std::string path);
    ~DataReader();
    std::vector<std::string> readData();

private:
    std::ifstream fin;
};
