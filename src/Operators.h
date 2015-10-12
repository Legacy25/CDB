#ifndef CDB_OPERATOR_H
#define CDB_OPERATOR_H


typedef union {
    double doubleData;
    char* stringData;
} LeafValue;

typedef enum {
    FLOAT = 1,
    STRING = 2,
} Type;



class Operator {
public:
    virtual LeafValue* getNext() = 0;
    virtual void reset() = 0;
};

//class ScanOperator : public Operator {
//private:
//
//public:
//    ScanOperator();
//    ~ScanOperator();
//    virtual LeafValue* getNext();
//    virtual void reset();
//};

#endif //CDB_OPERATOR_H
