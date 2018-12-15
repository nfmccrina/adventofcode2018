#include "AoCFramework.hpp"

// Example use of framework

int doStuff(std::vector<std::string> input);

int main(int argc, char* argv[])
{
    AoCFramework<int> framework {"data.txt", doStuff};

    framework.run();
    return 0;
}

int doStuff(std::vector<std::string> input)
{
    return 4;
}
