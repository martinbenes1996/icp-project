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
    TypeError, /**< Error of incompatible types. */
    WireError, /**< Error of a wire. */
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

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

#define B_2I1O 0x01
#define B_1I1O 0x02
inline long unmask(long type) { return type >> 8; }




#endif // DEFS_H