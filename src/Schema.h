#include <vector>
#include <string>

#include "Operators.h"

#ifndef CDB_SCHEMA_H
#define CDB_SCHEMA_H

class Schema {
private:
    std::string tablename;
    std::string datafile;
    std::vector<std::string> attributes;
    std::vector<Type> types;
    std::vector<LeafValue *> tuples;
    bool materialized;

public:
    Schema(
            std::string tablename,
            std::string datafile
    );

    void addAttribute(std::string, Type);
    void materialize();
    void dump();
    bool isMaterialized();

    friend std::ostream& operator<<(std::ostream &stream, const Schema &schema);
};


#endif //CDB_SCHEMA_H
