#ifndef DEFS_H
#define DEFS_H

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
 * @brief Value in the block or on the wire,
 */
struct Value {
    std::string type; /**< Type of the value. */
    double value = 0; /**< Value itself. */
    
    /** @brief Assignment operator overload. */
    Value& operator=(const Value& v) { type = v.type; value = v.value; return *this; }
    /** @brief Equality operator overload. */
    bool operator==(const Value& v) { return (type == v.type) && (value == v.value); }
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

#endif // DEFS_H