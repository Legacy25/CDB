#include <iostream>
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Bitcode/ReaderWriter.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/ExecutionEngine/MCJIT.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/Support/TargetSelect.h"

#include "Codegen.h"

using namespace llvm;
using namespace std;

static Function *mainFunction;
LLVMContext &context = getGlobalContext();

Type *int32Type = Type::getInt32Ty(context);
Type *int32PtrType = Type::getInt32PtrTy(context);
Type *int64Type = Type::getInt64Ty(context);
Type *int64PtrType = Type::getInt64PtrTy(context);


Value *longFmt;
Value *doubleFmt;
Value *stringFmt;
Value *dateFmt;
Value *newLine;

static int nameCtr = 0;

static Constant *printfFunc;

Codegen::Codegen(string ModuleName) {

    InitializeNativeTarget();

    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();

    // Useful globals to help generate IR
    module = new Module(StringRef(ModuleName), context);
    builder = new IRBuilder<>(context);


    // Declare C standard library printf so that we can call it
    vector<Type *> printfArgsTypes({Type::getInt8PtrTy(context)});
    FunctionType *printfType = FunctionType::get(int32Type, printfArgsTypes, true);
    printfFunc = module->getOrInsertFunction("printf", printfType);

    // The main function
    FunctionType *mainFunctionType = FunctionType::get(
            int32Type,
            ArrayRef<Type *>({}),
            false
    );
    mainFunction = Function::Create(
            mainFunctionType,
            Function::ExternalLinkage,
            "llvmStart",
            module
    );

    BasicBlock *entry = BasicBlock::Create(context, "entry", mainFunction);
    builder->SetInsertPoint(entry);

    longFmt = builder->CreateGlobalStringPtr("%lu|");
    doubleFmt = builder->CreateGlobalStringPtr("%lf|");
    stringFmt = builder->CreateGlobalStringPtr("%s|");
    dateFmt = builder->CreateGlobalStringPtr("%s|");
    newLine = builder->CreateGlobalStringPtr("\n");
}

Codegen::~Codegen() {
    delete module;
    delete builder;
}

IRBuilder<>* Codegen::getBuilder() const {
    return builder;
}

ExecutionEngine* Codegen::dump() const {
    builder->CreateRet(ConstantInt::get(int32Type, 0));
    module->dump();
    string error;
    raw_fd_ostream out(LL_FILE, error, sys::fs::OpenFlags::F_RW);
    WriteBitcodeToFile(module, out);

    ExecutionEngine *executionEngine = EngineBuilder(module).
            setErrorStr(&error).
            setUseMCJIT(true).
            create();

    executionEngine->finalizeObject();
    return executionEngine;
}

void Codegen::print(const TupPtr tp) {
    Type *ptrToPtr = PointerType::get(int64PtrType, 0);
    Value *ptr = builder->CreateIntToPtr(ConstantInt::get(int64Type, tp.ptr), ptrToPtr);
    Value *ac = ConstantInt::get(int32Type, tp.att_count);
    Value *tc = ConstantInt::get(int32Type, tp.tup_count);

    Value *loopVar =
            builder->CreateAlloca(
                    int32Type,
                    ConstantInt::get(int32Type, 1),
                    "loopVar"+to_string(nameCtr++)
            );
    builder->CreateStore(ConstantInt::get(int32Type, 0), loopVar);

    BasicBlock *loopBody = BasicBlock::Create(context, "loopBody"+to_string(nameCtr++), mainFunction);
    builder->CreateBr(loopBody);
    builder->SetInsertPoint(loopBody);

    // Print
    Value *i = builder->CreateLoad(loopVar);

    Value* indices[1];
    indices[0] = i;
    ArrayRef<Value *> indicesRef(indices);

    Value *tuple = builder->CreateLoad(builder->CreateInBoundsGEP(ptr, indicesRef));

    Value* indices1[1];
    indices1[0] = ConstantInt::get(int64Type, 1);
    ArrayRef<Value *> indicesRef1(indices1);
    Value *data = builder->CreateLoad(builder->CreateInBoundsGEP(tuple, indicesRef1));
    vector<Value *> args({stringFmt, data});
    builder->CreateCall(printfFunc, ArrayRef<Value*>(args));

    Value *inc = builder->CreateAdd(i, ConstantInt::get(int32Type, 1));
    builder->CreateStore(inc, loopVar);
    BasicBlock *afterLoop = BasicBlock::Create(context, "afterloop"+to_string(nameCtr++), mainFunction);
    Value *cmp = builder->CreateICmpSLT(inc, tc);
    builder->CreateCondBr(cmp, loopBody, afterLoop);

    builder->SetInsertPoint(afterLoop);
}