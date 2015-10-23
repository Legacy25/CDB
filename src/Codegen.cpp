#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Bitcode/ReaderWriter.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/FileSystem.h"

#include "Codegen.h"

using namespace llvm;
using namespace std;


LLVMContext &context = getGlobalContext();

Type *int32Type = Type::getInt32Ty(context);
Type *int32PtrType = Type::getInt32PtrTy(context);
Type *int64Type = Type::getInt64Ty(context);
Type *int64PtrType = Type::getInt64PtrTy(context);

static Constant *printfFunc;

Codegen::Codegen(string ModuleName) {

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
            ArrayRef<Type *>({int32Type, int32PtrType}),
            false
    );
    Function *mainFunction = Function::Create(
            mainFunctionType,
            Function::ExternalLinkage,
            "main",
            module
    );

    BasicBlock *entry = BasicBlock::Create(context, "entry", mainFunction);
    builder->SetInsertPoint(entry);


    Value *longFmt = builder->CreateGlobalStringPtr("%l|");
    Value *doubleFmt = builder->CreateGlobalStringPtr("%lf|");
    Value *stringFmt = builder->CreateGlobalStringPtr("%s|");
    Value *dateFmt = builder->CreateGlobalStringPtr("%s|");
}

Codegen::~Codegen() {
    delete module;
    delete builder;
}

IRBuilder<>* Codegen::getBuilder() const {
    return builder;
}

void Codegen::dump() const {
    builder->CreateRet(ConstantInt::get(int32Type, 0));
    string error;
    raw_fd_ostream out(LL_FILE, error, sys::fs::OpenFlags::F_RW);
    WriteBitcodeToFile(module, out);
}

void Codegen::print(const char* str) {
    Value *v = builder->CreateGlobalStringPtr(str);
    builder->CreateCall(printfFunc, vector<Value *>({v}));
}