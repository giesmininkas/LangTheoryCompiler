#ifndef SKELETON_HEADER
#define SKELETON_HEADER
/* You might want to change the above name. */

#include <unordered_map>
#include <stack>
#include "Absyn.H"
#include "llvm/IR/Value.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"

class Skeleton : public Visitor
{
private:
    llvm::LLVMContext context;
    std::unique_ptr<llvm::Module> module;
    llvm::IRBuilder<> builder;
    std::unordered_map<std::string, llvm::AllocaInst*> named_values;
    std::stack<llvm::Value*> value_stack;
    std::stack<llvm::Type*> type_stack;

    std::map<std::string, std::unique_ptr<Function>> FunctionProtos; // issisaugoti funckciju sarasa
public:

    Skeleton();
    void Compile(const std::string &output_file, Program *);
    llvm::AllocaInst *createEntryBlockAlloca(llvm::Function *function, llvm::Type *type, const std::string &var_name);
    void Log(llvm::Value *value);

    void visitProgram(Program* p);
    void visitFunction(Function* p);
    void visitDeclaration(Declaration* p);
    void visitStmt(Stmt* p);
    void visitJmp(Jmp* p);
    void visitExp(Exp* p);
    void visitType(Type* p);
    void visitProgr(Progr* p);
    void visitFunc(Func* p);
    void visitDecl(Decl* p);
    void visitSComp(SComp* p);
    void visitSIf(SIf* p);
    void visitSIfElse(SIfElse* p);
    void visitSWhile(SWhile* p);
    void visitSJmp(SJmp* p);
    void visitSDeclAss(SDeclAss* p);
    void visitSDecl(SDecl* p);
    void visitSExp(SExp* p);
    void visitSEmptyComp(SEmptyComp* p);
    void visitSEmpty(SEmpty* p);
    void visitSJmpBreak(SJmpBreak* p);
    void visitSJmpRetExp(SJmpRetExp* p);
    void visitSJmpReturn(SJmpReturn* p);
    void visitEAssign(EAssign* p);
    void visitEMul(EMul* p);
    void visitEDiv(EDiv* p);
    void visitEMod(EMod* p);
    void visitEAdd(EAdd* p);
    void visitESub(ESub* p);
    void visitEFuncParam(EFuncParam* p);
    void visitEVar(EVar* p);
    void visitEInteger(EInteger* p);
    void visitEChar(EChar* p);
    void visitTvoid(Tvoid* p);
    void visitTchar(Tchar* p);
    void visitTint(Tint* p);
    void visitListFunction(ListFunction* p);
    void visitListDeclaration(ListDeclaration* p);
    void visitListStmt(ListStmt* p);
    void visitListExp(ListExp* p);

    void visitInteger(Integer x);
    void visitChar(Char x);
    void visitDouble(Double x);
    void visitString(String x);
    void visitIdent(Ident x);

};


#endif
