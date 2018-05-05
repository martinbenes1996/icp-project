
/**
 * @file config.h
 * @author xbenes49, xpolan09
 * @date 5 May 2018
 * @brief configuration interface
 *
 * This module contains a global configuration, seen by all the modules.
 * It is a singleton design pattern.
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <functional>
#include <map>
#include <set>
#include <string>
#include <vector>

/**
 * @brief Type of the block (port count).
 */
enum BlockType
{
    OneIn_OneOut,
    TwoIn_OneOut,
};

/** @brief OS specific path separator. */
const std::string PathSep =
#if defined _WIN32 || defined __CYGWIN__
    "\\";
#else
    "/";
#endif

/**
 * @brief Config namespace.
 */
namespace Config
{
    /**
     * @brief Initializes configuration.
     */
    void initConfig();
    /**
     * @brief Decodes block operation type to block port type.
     * @param type      Type of the block to decode.
     * @returns BlockType of the given type.
     */
    BlockType decodeBlockType(long type);

    /**
     * @brief Gets the lambda of the given block operation type.
     *        Called for blocks with 2 inputs and 1 output.
     * @param key       Key of the block.
     */
    std::function<double(double,double)> getFunc_2I1O(long);
    /**
     * @brief Gets the lambda of the given block operation type.
     *        Called for blocks with 1 input and 1 output.
     * @param key       Key of the block.
     */
    std::function<double(double)> getFunc_1I1O(long);

    /**
     * @brief Returns vector of types of the input ports
     *        of the block with the given key.
     * @param key       Key of the block.
     * @returns Vector of the types (strings).
     */
    std::vector<std::string> getInput(long);
    /**
     * @brief Returns vector of types of the output ports
     *        of the block with the given key.
     * @param key       Key of the block.
     * @returns Vector of the types (strings).
     */
    std::vector<std::string> getOutput(long);

    /**
     * @brief Getter of blockname to block key map.
     *        It is used in the menu.
     * @returns Map mapping the block name to block key.
     */
    std::map<std::string, long>& getBlockNames();
    /**
     * @brief Decodes blockname to path to its image.
     * @param name      Block name.
     * @returns Image path.
     */
    std::string getImagePath(std::string);
    /**
     * @brief Decodes blockname to path to its highlighted image.
     * @param name      Block name.
     * @returns Image path.
     */
    std::string getHLImagePath(std::string);
    /**
     * @brief Maps the block key to the block name.
     * @param key       Block key.
     * @returns Block name.
     */
    std::string getBlockName(long);

    /**
     * @brief Adds type.
     * @param type      New type to add.
     */
    void addType(std::string);
    /**
     * @brief Removes type.
     * @param type      Type to remove.
     */
    void removeType(std::string);
    /**
     * @brief Type set getter.
     * @returns Set of the types.
     */
    std::set<std::string> getTypes();

    /**
     * @brief Returns path of the file with stylesheet.
     * @returns Stylesheet file path.
     */
    std::string getStyleFileName();

}

#endif // CONFIG_H
