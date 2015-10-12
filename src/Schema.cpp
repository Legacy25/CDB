#include <iostream>
#include <iosfwd>
#include <fstream>
#include <sstream>
#include <cstring>

#include "Schema.h"

using namespace std;

Schema::Schema(string tablename, string datafile)
        : tablename(tablename), datafile(datafile) {

    materialized = false;
}

void Schema::addAttribute(string attr, Type t) {
    attributes.push_back(attr);
    types.push_back(t);
}

void Schema::materialize() {
    if(materialized)
        return;

    ifstream infile(datafile);

    if(infile) {
        string line;

        while(getline(infile, line)) {

            int n = attributes.size();
            LeafValue *tuple = new LeafValue[n];
            stringstream linestream;
            linestream.str(line);
            string str;

            int i=0;
            while(getline(linestream, str, '|')) {
                switch(types.at(i)) {
                    case FLOAT:
                        tuple[i].doubleData = stod(str);
                        break;
                    case STRING:
                        int buf_size = str.size()+1;
                        tuple[i].stringData = new char[buf_size];
                        memcpy(tuple[i].stringData, str.c_str(), buf_size);
                        break;
                }
                i++;
            }
            tuples.push_back(tuple);
        }
        infile.close();
    }
    else {
        return;
    }

    materialized = true;
}

bool Schema::isMaterialized() {
    return materialized;
}

void Schema::dump() {
    if(!materialized) {
        cout << "Cannot dump, not materialized!";
        return;
    }

    int n = attributes.size();
    for(vector<LeafValue *>::iterator it = tuples.begin(); it != tuples.end(); it++) {
        LeafValue *tuple = it.operator*();
        for(int i=0; i<n; i++) {
            switch(types[i]) {
                case FLOAT:
                    cout << tuple[i].doubleData << "|";
                    break;
                case STRING:
                    cout << tuple[i].stringData << "|";
                    break;
            }
        }
        cout << endl;
    }
}

namespace util {
    string attrsVecsToCommaSepString(
            const vector<string>& attr,
            const vector<Type>& types
    ) {

        string line = "", tStr = "";
        auto a = attr.begin();
        auto t = types.begin();

        while(a != attr.end() && t != types.end())
        {
            switch(t.operator*()) {
                case FLOAT:
                    tStr = "FLOAT";
                    break;
                case STRING:
                    tStr = "STRING";
                    break;
            }
            line.append(a.operator*()).append(" ");
            line.append(tStr).append(", ");
            a++;
            t++;
        }

        return line;
    }
}

ostream& operator<<(ostream &stream, const Schema &schema) {
    string attrs = util::attrsVecsToCommaSepString(schema.attributes, schema.types);
    return stream << schema.tablename << " : " << schema.datafile << endl
           << attrs;
}