#include <stdint.h>

#ifndef CDB_OPERATOR_H
#define CDB_OPERATOR_H

typedef enum {
    LONG = 1,
    DOUBLE = 2,
    STRING = 3,
    DATE = 4
} DataType;

typedef int64_t LeafValue;

#endif //CDB_OPERATOR_H
