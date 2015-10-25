#include <iostream>
#include <llvm/ExecutionEngine/ExecutionEngine.h>

#include "Schema.h"
#include "Codegen.h"

using namespace std;

/**
 * This is the starting point of the llvm generating phase.
 * This will take as input, the query plan from Java land,
 * and output the llvm code.
 */
int main()
{
    // This file will take as input the query plan dumped file

    // Parse query plan representation

    // Create instances of Schema
    Schema nation("nation", "data/nation.tbl");
    nation.addAttribute("nationkey", LONG);
    nation.addAttribute("name", STRING);
    nation.addAttribute("regionkey", LONG);
    nation.addAttribute("comment", STRING);

    nation.materialize();

    // Create instance of Codegen
    Codegen codegen("LLVM");

    // Create API calls in Codegen to generate loops, conditionals
    // etc.
    // This is just to demonstrate a rough API call
    codegen.print(nation.getTupPtr());

    // Call Codegen's methods to generate LLVM from various translator
    // functions like scanProduce(codegen, context), selectionProduce(args),
    // selectionConsume, etc. Calls these methods according to the parsed
    // query plan representation

    // Finally, at the end call codegen.dump(), which will dump the module
    // to build/queryexecutor.ll
    ExecutionEngine *engine = codegen.dump();

    cout << "DUMPED! Now executing!...\n\n";

    int (*FP)(int, int*) = (int (*)(int, int*))(engine->getPointerToNamedFunction("llvmStart", true));
    FP(0, NULL);
}