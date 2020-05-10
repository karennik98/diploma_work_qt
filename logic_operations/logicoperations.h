#ifndef LOGICOPERATIONS_H
#define LOGICOPERATIONS_H
#include <cstddef>

class LogicOperations
{
public:
    // save logic value on size_t is wrong
    static size_t AND(size_t val1, size_t val2);
    static size_t OR(size_t val1, size_t val2);
    static size_t NOT(size_t val);
    static size_t XOR(size_t val1, size_t val2);
    static size_t XNOR(size_t val1, size_t val2);
    static size_t NAND(size_t val1, size_t val2);
    static size_t NOR(size_t val1, size_t val2);
};

#endif // LOGICOPERATIONS_H
