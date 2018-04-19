#ifndef CONFIG_H
#define CONFIG_H

#include <functional>
#include <map>
#include <string>
#include <vector>


enum BlockType
{
    OneIn_OneOut,
    TwoIn_OneOut,
};

namespace Config
{
    void initConfig();
    BlockType decodeBlockType(long key);

    std::function<double(double,double)> getFunc_2I1O(long);
    std::function<double(double)> getFunc_1I1O(long);

    std::vector<std::string> getInput(long);
    std::vector<std::string> getOutput(long);

    std::string getGType();

    std::map<std::string, long> getBlockNames();
    std::string getDefaultBlockName();

}

#endif // CONFIG_H
