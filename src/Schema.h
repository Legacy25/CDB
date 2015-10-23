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
    vector<DataType> types;
    vector<LeafValue *> tuples;
    bool materialized;

public:
    Schema(
            string tablename,
            string datafile
    );

    void addAttribute(string, DataType);
    void materialize();
    void dump() const;
    bool isMaterialized() const;

    friend ostream& operator<<(ostream &stream, const Schema &schema);
};


#endif //CDB_SCHEMA_H
