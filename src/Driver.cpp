#include <iostream>

#include "Schema.h"

using namespace std;

int main()
{
    Schema nation("nation", "data/nation.tbl");
    nation.addAttribute("nationkey", LONG);
    nation.addAttribute("name", STRING);
    nation.addAttribute("regionkey", LONG);
    nation.addAttribute("comment", STRING);

    cout << nation << endl;

    nation.materialize();
    nation.dump();
}