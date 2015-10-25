#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"

#include "Operators.h"

#ifndef CDB_CODEGEN_H
#define CDB_CODEGEN_H

#define LL_FILE "build/queryexecutor.ll"

using namespace llvm;
using namespace std;



class Codegen {
private:
    Module *module;
    IRBuilder<> *builder;

public:
    Codegen(string);
    ~Codegen();

    IRBuilder<>* getBuilder() const;
    void print(const TupPtr tp);
    ExecutionEngine * dump() const;
};

#endif //CDB_CODEGEN_H
