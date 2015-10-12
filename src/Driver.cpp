#include <iostream>

#include "Schema.h"

using namespace std;

int main()
{
    Schema nation("nation", "data/nation.tbl");
    nation.addAttribute("nationkey", FLOAT);
    nation.addAttribute("name", STRING);
    nation.addAttribute("regionkey", FLOAT);
    nation.addAttribute("comment", STRING);

    cout << nation << endl;

    nation.materialize();
    nation.dump();
}