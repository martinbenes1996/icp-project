// config.h
// Autoři: xbenes49, xpolan09
// Projekt do předmětu ICP.
// Datum: 29.04.5018


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

const std::string PathSep =
#if defined _WIN32 || defined __CYGWIN__
    "\\";
#else
    "/";
#endif

namespace Config
{
    void initConfig();
    BlockType decodeBlockType(long type);

    std::function<double(double,double)> getFunc_2I1O(long);
    std::function<double(double)> getFunc_1I1O(long);

    std::vector<std::string> getInput(long);
    std::vector<std::string> getOutput(long);

    std::map<std::string, long>& getBlockNames();
    std::string getImagePath(std::string);
    std::string getBlockName(long);

}

#endif // CONFIG_H
