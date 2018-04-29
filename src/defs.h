#ifndef DEFS_H
#define DEFS_H

#include <iostream>
#include <string>

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
};

struct Computation
{
    long key;
    Value result;
};

struct GuiBlockDescriptor {
    std::pair<double, double> pos;
    long type;
};




#endif // DEFS_H