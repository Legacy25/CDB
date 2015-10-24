#include "ScanTranslator.h"

extern LLVMContext &context;

extern Type *int32Type;
extern Type *int32PtrType;
extern Type *int64Type;
extern Type *int64PtrType;

void scanProduce(const Codegen* codegen, const Context* context) {
    IRBuilder<> *builder = codegen->getBuilder();
    // Use builder or api calls from codegen to generate the rest
    // of the llvm code
}
