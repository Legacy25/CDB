
#ifndef CDB_OPERATOR_H
#define CDB_OPERATOR_H

#include <vector>

#include "DataTypes.h"
#include "Schema.h"

using namespace std;

class Translator {
protected:
    const Translator *lChild, *rChild, *parent;

public:
    Translator();

    void setLeft(const Translator*);
    void setRight(const Translator*);
    void setParent(const Translator*);

    virtual void produce() const = 0;
    virtual void consume() const = 0;
};

class ScanTranslator: public Translator {
private:
    const TupPtr tp;

public:
    ScanTranslator(const Schema*);

    void produce() const;
    void consume() const;
};

class PrintTranslator: public Translator {
private:
    int *types;

public:
    PrintTranslator(const Schema*);

    void produce() const;
    void consume() const;
};

#endif //CDB_OPERATOR_H
