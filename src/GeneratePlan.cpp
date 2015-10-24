#include <iostream>

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

    // Create API calls in Codegen to generate loops, conditionals
    // etc.

    // Create instance of Codegen
    Codegen codegen("LLVM");

    // Call Codegen's methods to generate LLVM from various translator
    // functions like scanProduce(codegen, context), selectionProduce(args),
    // selectionConsume, etc. Calls these methods according to the parsed
    // query plan representation

    // This is just to demonstrate a rough API call
    codegen.print("Hello World!");

    // Finally, at the end call codegen.dump(), which will dump the module
    // to build/queryexecutor.ll
    codegen.dump();
}