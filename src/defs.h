
/**
 * @file defs.h
 * @author xbenes49, xpolan09
 * @date 5 May 2018
 * @brief Global types
 *
 * This module contains a types, used in whole project.
 */

#ifndef DEFS_H
#define DEFS_H

#include <iostream>
#include <string>
#include <map>
#include <QPointF>

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
    NotAnError, /**< Not an error. */
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
    bool valid = false; /**< Weather the value is valid. */
    /**
     * @brief Assignment operator for value.
     * @param v         Value to assign.
     * @returns Reference to the object.
     */
    Value& operator= (const Value& v)
    {
        this->type = v.type;
        this->value = v.value;
        this->valid = v.valid;
        return *this;
    }
};

/**
 * @brief Describes the graphic block.
 */
struct GuiBlockDescriptor {
    std::pair<double, double> pos; /**< Position of the block in the scene. */
    long type; /**< Type of the placed block. */
    Value val; /**< Value of the placed input block. */
};

/**
 * @brief State of the wire (to save/load).
 */
struct wireState {
    //int id;
    //double point1_x;
    //double point1_y;
    //double point2_x;
    //double point2_y;
    int block1_id; /**< ID of input block. */
    int block2_id; /**< ID of output block. */
    int connector1; /**< Connector of the input block. */
    int connector2; /**< Connector of the output block. */
};

/**
 * @brief Result of the computation.
 */
struct Result {
    double value; /**< Result value. */
    std::string type; /**< Result type. */
    int level; /**< Level of the block. */

    /**
     * @brief Typecast of Result to Value.
     * @returns Casted Value.
     */
    explicit operator Value()
    {
        Value v;
        v.type = this->type;
        v.value = this->value;
        v.valid = true;
        return v;
    }
};

/**
 * @brief Results of the simulation (wires and blocks).
 */
struct SimulationResults {
    std::map<int, std::map<long,Result>> blocks = std::map<int, std::map<long,Result>>(); /**< Blocks results. */
    std::map<int, std::map<long,Result>> wires = std::map<int, std::map<long,Result>>(); /**< WIres results. */

    /**
     * @brief Returns max level of all blocks.
     * @returns Max block level.
     */
    static int getMaxLevel();
    /**
     * @brief Max block level setter.
     * @param max       New max level value.
     */
    static void setMaxLevel(int max);
    /**
     * @brief Resets the max level (to 0).
     */
    static void resetMaxLevel();

    /**
     * @brief Merge with another results into this.
     * @param s         Another results.
     */
    void mergeWith(const SimulationResults& s)
    {
        for(auto& i: s.blocks) {
            for(auto& j: i.second) {
                insertBlock(j.first, j.second);
            }
        }
        for(auto& i: s.wires) {
            for(auto& j: i.second) {
                insertWire(j.first, j.second);
            }
        }
    }

    /**
     * @brief Block inserter.
     * @param id        Id of the block (key).
     * @param r         Computated result.
     */
    void insertBlock(long id, Result r)
    {
        if(r.level > SimulationResults::getMaxLevel())
            SimulationResults::setMaxLevel(r.level);
        if(this->blocks.count(r.level) == 0)
            this->blocks.insert(std::make_pair(r.level,std::map<long,Result>()) );
        for(auto& i: this->blocks)
        {
            if(i.first == r.level) {
                if(i.second.count(id) == 0) {
                    i.second.insert(std::make_pair(id,r));
                } else if(i.second.at(id).level < r.level) {
                    i.second.at(id).level = r.level;
                }
            }
            else {
                if(i.second.count(id) > 0) {
                    i.second.erase(id);
                }
            }
        }
    }
    /**
     * @brief Wire inserter.
     * @param id        Id of the wire (key).
     * @param r         Computated result.
     */
    void insertWire(long id, Result r)
    {
        if(r.level > SimulationResults::getMaxLevel())
            SimulationResults::setMaxLevel(r.level);
        if(this->wires.count(r.level) == 0)
            this->wires.insert(std::make_pair(r.level,std::map<long,Result>()) );
        for(auto& i: this->wires)
        {
            if(i.first == r.level) {
                if(i.second.count(id) == 0) {
                    i.second.insert(std::make_pair(id,r));
                } else if(i.second.at(id).level < r.level) {
                    i.second.at(id).level = r.level;
                }
            }
            else {
                if(i.second.count(id) > 0) {
                    i.second.erase(id);
                }
            }
        }
    }
};


#endif // DEFS_H