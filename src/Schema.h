#include <vector>
#include <string>

#include "Operators.h"

#ifndef CDB_SCHEMA_H
#define CDB_SCHEMA_H

using namespace std;

class Schema {
private:
    string tablename;
    string datafile;
    vector<string> attributes;
    vector<Type> types;
    vector<LeafValue *> tuples;
    bool materialized;

public:
    Schema(
            string tablename,
            string datafile
    );

    void addAttribute(string, Type);
    void materialize();
    void dump();
    bool isMaterialized();

    friend ostream& operator<<(ostream &stream, const Schema &schema);
};


#endif //CDB_SCHEMA_H
