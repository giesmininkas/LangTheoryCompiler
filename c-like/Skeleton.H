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

    llvm::Value *visitProgram(Program *p);
    llvm::Value *visitFunction(Function *p);
    llvm::Value *visitDeclaration(Declaration *p);
    llvm::Value *visitStmt(Stmt *p);
    llvm::Value *visitJmp(Jmp *p);
    llvm::Value *visitExp(Exp *p);
    llvm::Value *visitType(Type *p);
    llvm::Value *visitProgr(Progr *p);
    llvm::Value *visitFunc(Func *p);
    llvm::Value *visitDecl(Decl *p);
    llvm::Value *visitSComp(SComp *p);
    llvm::Value *visitSIfElse(SIfElse *p);
    llvm::Value *visitSIf(SIf *p);
    llvm::Value *visitSWhile(SWhile *p);
    llvm::Value *visitSJmp(SJmp *p);
    llvm::Value *visitSDeclAss(SDeclAss *p);
    llvm::Value *visitSDecl(SDecl *p);
    llvm::Value *visitSExp(SExp *p);
    llvm::Value *visitSEmptyComp(SEmptyComp *p);
    llvm::Value *visitSEmpty(SEmpty *p);
    llvm::Value *visitSJmpBreak(SJmpBreak *p);
    llvm::Value *visitSJmpRetExp(SJmpRetExp *p);
    llvm::Value *visitSJmpReturn(SJmpReturn *p);
    llvm::Value *visitEAssign(EAssign *p);
    llvm::Value *visitEMul(EMul *p);
    llvm::Value *visitEDiv(EDiv *p);
    llvm::Value *visitEAdd(EAdd *p);
    llvm::Value *visitESub(ESub *p);
    llvm::Value *visitEFuncParam(EFuncParam *p);
    llvm::Value *visitEFunc(EFunc *p);
    llvm::Value *visitEVar(EVar *p);
    llvm::Value *visitEInteger(EInteger *p);
    llvm::Value *visitEChar(EChar *p);
    llvm::Type  *visitTvoid(Tvoid *p);
    llvm::Type  *visitTchar(Tchar *p);
    llvm::Type  *visitTint(Tint *p);
    llvm::Value *visitListFunction(ListFunction *p);
    llvm::Value *visitListDeclaration(ListDeclaration *p);
    llvm::Value *visitListStmt(ListStmt *p);
    llvm::Value *visitListIdent(ListIdent *p);

    llvm::Value *visitInteger(Integer x);
    llvm::Value *visitChar(Char x);
    llvm::Value *visitDouble(Double x);
    llvm::Value *visitString(String x);
    llvm::Value *visitIdent(Ident x);

};


#endif
