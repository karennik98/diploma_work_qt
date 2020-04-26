#include "logicoperations.h"
#include <stdexcept>

size_t LogicOperations::AND(size_t val1, size_t val2) {
    switch (val1) {
    case 0 :
        switch (val2) {
        case 0:
            return 0;
        case 1:
            return 0;
        }
    case 1 :
        switch (val2) {
        case 0:
            return 0;
        case 1:
            return 1;

        }
    }

    throw std::runtime_error("Wrong logic value!");
}

size_t LogicOperations::OR(size_t val1, size_t val2) {
    switch (val1) {
    case 0 :
        switch (val2) {
        case 0:
            return 0;
        case 1:
            return 1;
        }
    case 1 :
        switch (val2) {
        case 0:
            return 1;
        case 1:
            return 1;

        }
    }

    throw std::runtime_error("Wrong logic value!");
}

size_t LogicOperations::XOR(size_t val1, size_t val2) {
    switch (val1) {
    case 0 :
        switch (val2) {
        case 0:
            return 0;
        case 1:
            return 1;
        }
    case 1 :
        switch (val2) {
        case 0:
            return 1;
        case 1:
            return 0;

        }
    }

    throw std::runtime_error("Wrong logic value!");
}

size_t LogicOperations::XNOR(size_t val1, size_t val2) {
    switch (val1) {
    case 0 :
        switch (val2) {
        case 0:
            return 1;
        case 1:
            return 0;
        }
    case 1 :
        switch (val2) {
        case 0:
            return 0;
        case 1:
            return 1;

        }
    }

    throw std::runtime_error("Wrong logic value!");
}

size_t LogicOperations::NAND(size_t val1, size_t val2) {
    switch (val1) {
    case 0 :
        switch (val2) {
        case 0:
            return 1;
        case 1:
            return 1;
        }
    case 1 :
        switch (val2) {
        case 0:
            return 1;
        case 1:
            return 0;

        }
    }

    throw std::runtime_error("Wrong logic value!");
}

size_t LogicOperations::NOR(size_t val1, size_t val2) {
    switch (val1) {
    case 0 :
        switch (val2) {
        case 0:
            return 1;
        case 1:
            return 0;
        }
    case 1 :
        switch (val2) {
        case 0:
            return 0;
        case 1:
            return 0;

        }
    }

    throw std::runtime_error("Wrong logic value!");
}

size_t LogicOperations::NOT(size_t val) {
    switch (val) {
    case 0:
        return 1;
    case 1:
        return 0;
    }

    throw std::runtime_error("Wrong logic value!");
}
