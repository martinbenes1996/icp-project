// defs.h
// Autoři: xbenes49, xpolan09
// Projekt do předmětu ICP.
// Datum: 29.04.5018


#ifndef DEFS_H
#define DEFS_H

#include <iostream>
#include <string>
#include <map>

/**
 * @brief Type of the error.
 */
enum ErrorType {
    Ok,
    BlockError, /**< Error of a block. */
    MathError, /**< Math error. */
    TypeError, /**< Error of incompatible types. */
    WireError, /**< Error of a wire. */
    ViewError, /**< Error of a view. */
};

/**
 * @brief Port descriptor.
 */
struct PortID
{
    long key; /**< Key of the block. */
    int port; /**< Port of the block. */
};

/**
 * @brief Error to raise.
 */
struct MyError {
    public:
        /** @brief Constructor. */
        MyError(std::string msg, ErrorType code): mmsg(msg), mcode(code) {}

        /** @brief Error message getter. */
        std::string getMessage() { return mmsg; }
        /** @brief Error code getter. */
        int getCode();
    private:
        std::string mmsg = ""; /**< Error message. */
        ErrorType mcode = ErrorType::Ok; /**< Error code. */
};

/**
 * @brief Value in the block or on the wire,
 */
struct Value {
    std::string type; /**< Type of the value. */
    double value = 0; /**< Value itself. */
    bool valid = false;
    Value& operator= (const Value& v)
    {
        this->type = v.type;
        this->value = v.value;
        this->valid = v.valid;
        return *this;
    }
};

struct GuiBlockDescriptor {
    std::pair<double, double> pos;
    long type;
};

struct Result {
    double value;
    std::string type;
    int level;
};
struct SimulationResults {
    std::map<int, std::map<long,Result>> blocks;
    std::map<int, std::map<long,Result>> wires;

    void mergeWith(const SimulationResults& s)
    {
        for(auto& i: s.blocks) { 
            for(auto& j: i.second) {
                insertBlock(j.first, j.second);
            }
        }
        for(auto& i: s.wires) {
            for(auto& j: i.second) {
                insertBlock(j.first, j.second);
            }
        }
    }

    void insertBlock(long id, Result r)
    {
        if(blocks.count(r.level) == 0)
            blocks.insert( std::make_pair(r.level,std::map<long,Result>()) );

        blocks.at(r.level).insert( std::make_pair(id,r) );
    }

    void insertWire(long id, Result r)
    {
        if(wires.count(r.level) == 0)
            wires.insert( std::make_pair(r.level,std::map<long,Result>()) );

        wires.at(r.level).insert( std::make_pair(id,r) );
    }
};




#endif // DEFS_H
