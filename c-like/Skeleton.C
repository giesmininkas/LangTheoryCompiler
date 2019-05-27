/*** BNFC-Generated Visitor Design Pattern Skeleton. ***/
/* This implements the common visitor design pattern.
   Note that this method uses Visitor-traversal of lists, so
   List->accept() does NOT traverse the list. This allows different
   algorithms to use context information differently. */

#include "Skeleton.H"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Verifier.h"

#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/Optional.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/Host.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"


llvm::Value *Skeleton::visitProgram(Program *p) {} //abstract class
llvm::Value *Skeleton::visitFunction(Function *p) {} //abstract class
llvm::Value *Skeleton::visitDeclaration(Declaration *p) {} //abstract class
llvm::Value *Skeleton::visitStmt(Stmt *p) {} //abstract class
llvm::Value *Skeleton::visitJmp(Jmp *p) {} //abstract class
llvm::Value *Skeleton::visitExp(Exp *p) {} //abstract class
llvm::Value *Skeleton::visitType(Type *p) {} //abstract class

llvm::Value *Skeleton::visitProgr(Progr *p) {
    /* Code For Progr Goes Here */

    std::vector<llvm::Type*> arg_types;
    arg_types.push_back(builder.getInt32Ty());
    llvm::FunctionType *putchar = llvm::FunctionType::get(builder.getInt32Ty(), arg_types, false);
    llvm::Constant *func = module->getOrInsertFunction("putchar", putchar);

    p->listfunction_->accept(this);

}

llvm::Value *Skeleton::visitFunc(Func *func) {
    /* Code For Func Goes Here */

    func->type_->accept(this);

    auto return_type = type_stack.top();
    type_stack.pop();

    //visitIdent(func->ident_);
    auto function_name = func->ident_;

    //func->listdeclaration_->accept(this);
    std::vector<llvm::Type *> arg_types;
    for (auto declaration : *func->listdeclaration_) {
        auto decl = static_cast<Decl *>(declaration);
        decl->type_->accept(this);
        arg_types.push_back(type_stack.top());
        type_stack.pop();
    }

    std::vector<Ident> arg_names;
    for (auto declaration : *func->listdeclaration_) {
        auto decl = static_cast<Decl *>(declaration);
        arg_names.push_back(decl->ident_);
    }

    auto function_type = llvm::FunctionType::get(return_type, arg_types, false);
    auto function = llvm::Function::Create(function_type, llvm::Function::ExternalLinkage, function_name, module.get());

    auto i = 0;
    for (auto &arg : function->args()) {
        arg.setName(arg_names.at(i++));
    }

    auto block = llvm::BasicBlock::Create(context, "entry", function);
    builder.SetInsertPoint(block);

    named_values.clear();
    for (auto &arg : function->args()){
        auto alloca = createEntryBlockAlloca(function, arg.getType(), arg.getName());
        builder.CreateStore(&arg, alloca);
        named_values.emplace(arg.getName(), alloca);
    }

    func->stmt_->accept(this);

    /*llvm::Value *return_value = builder.CreateAlloca(llvm::Type::getInt64Ty(context));
    builder.CreateStore(llvm::ConstantInt::get(llvm::Type::getInt64Ty(context), 0), return_value);
    builder.CreateRet(return_value);*/

    /*if (!value_stack.empty()) {
        builder.CreateRet(value_stack.top());
        value_stack.pop();
    }*/

    Log(block);

    if(llvm::verifyFunction(*function, &llvm::errs())) {
        function->eraseFromParent();
        return nullptr;
    }

    //value_stack.push(function);
    return function;
}

llvm::Value *Skeleton::visitDecl(Decl *decl) {
    /* Code For Decl Goes Here */

    decl->type_->accept(this);

    auto type = type_stack.top();
    type_stack.pop();

    auto var = builder.CreateAlloca(type, nullptr, decl->ident_);
    named_values.emplace(decl->ident_, var);

    value_stack.push(var);
    return var;
}

llvm::Value *Skeleton::visitSComp(SComp *scomp) {
    /* Code For SComp Goes Here */

    scomp->liststmt_->accept(this);

}

llvm::Value *Skeleton::visitSIfElse(SIfElse *sifelse) {
    /* Code For SIfElse Goes Here */

    sifelse->exp_->accept(this);
    auto cond = value_stack.top();
    value_stack.pop();

    //cond = builder.CreateLoad(cond);
    /*cond->print(llvm::errs());
    llvm::errs() << "\n";*/


    auto cond_value = builder.CreateICmpNE(cond, llvm::ConstantInt::get(cond->getType(), 0, true), "ifcond");
    Log(cond_value);

    auto function = builder.GetInsertBlock()->getParent();

    auto then = llvm::BasicBlock::Create(context, "then", function);
    auto else_ = llvm::BasicBlock::Create(context, "else");
    auto merge = llvm::BasicBlock::Create(context, "ifcont");

    auto br = builder.CreateCondBr(cond_value, then, else_);
    Log(br);
    builder.SetInsertPoint(then);

    sifelse->stmt_1->accept(this);
    llvm::Value *then_value = nullptr;
    if(!value_stack.empty()){
        then_value = value_stack.top();
        value_stack.pop();
        Log(then_value);
    }


    builder.CreateBr(merge);
    then = builder.GetInsertBlock();

    function->getBasicBlockList().push_back(else_);
    builder.SetInsertPoint(else_);
    sifelse->stmt_2->accept(this);
    llvm::Value *else_value = nullptr;
    if(!value_stack.empty()){
        else_value = value_stack.top();
        value_stack.pop();
        Log(else_value);
    }

    builder.CreateBr(merge);
    else_ = builder.GetInsertBlock();

    function->getBasicBlockList().push_back(merge);
    builder.SetInsertPoint(merge);

    return nullptr;
}

llvm::Value *Skeleton::visitSIf(SIf *sif) {
    /* Code For SIf Goes Here */

    sif->exp_->accept(this);
    auto cond = value_stack.top();
    value_stack.pop();

    auto cond_value = builder.CreateICmpNE(cond, llvm::ConstantInt::get(cond->getType(), 0, true), "ifcond");
    auto function = builder.GetInsertBlock()->getParent();

    auto then = llvm::BasicBlock::Create(context, "then", function);
    auto merge = llvm::BasicBlock::Create(context, "ifcont");

    builder.CreateCondBr(cond_value, then, merge);
    builder.SetInsertPoint(then);

    sif->stmt_->accept(this);
    llvm::Value *then_value = nullptr;
    if(!value_stack.empty()){
        then_value = value_stack.top();
        value_stack.pop();
        Log(then_value);
    }

    builder.CreateBr(merge);
    then = builder.GetInsertBlock();

    function->getBasicBlockList().push_back(merge);
    builder.SetInsertPoint(merge);

    return nullptr;
}

llvm::Value *Skeleton::visitSWhile(SWhile *swhile) {
    /* Code For SWhile Goes Here */

    auto function = builder.GetInsertBlock()->getParent();
    auto preheader = builder.GetInsertBlock();

    auto header = llvm::BasicBlock::Create(context, "loop_cond", function);
    auto loop_block = llvm::BasicBlock::Create(context, "loop", function);
    auto after = llvm::BasicBlock::Create(context, "afterloop", function);

    builder.CreateBr(header);
    Log(preheader);

    builder.SetInsertPoint(header);
    swhile->exp_->accept(this);
    auto end_cond = value_stack.top();
    value_stack.pop();
    auto end_cond_value = builder.CreateICmpNE(end_cond, llvm::ConstantInt::get(end_cond->getType(), 0, true), "loopcond");
    builder.CreateCondBr(end_cond_value, loop_block, after);

    builder.SetInsertPoint(loop_block);
    swhile->stmt_->accept(this);
    builder.CreateBr(header);
    Log(loop_block);

    builder.SetInsertPoint(after);

    return nullptr;
}

llvm::Value *Skeleton::visitSJmp(SJmp *sjmp) {
    /* Code For SJmp Goes Here */

    sjmp->jmp_->accept(this);
    return nullptr;
}

llvm::Value *Skeleton::visitSDeclAss(SDeclAss *sdeclass) {
    /* Code For SDeclAss Goes Here */

    sdeclass->declaration_->accept(this);
    sdeclass->exp_->accept(this);

    auto value = value_stack.top();
    value_stack.pop();
    auto var = value_stack.top();
    value_stack.pop();

    if(value->getType() != var->getType()->getContainedType(0))
        value = builder.CreateIntCast(value, var->getType()->getContainedType(0), true);

    auto assignment = builder.CreateStore(value, var);

    Log(value);
    Log(assignment);
    return assignment; //value_stack.top();
}

llvm::Value *Skeleton::visitSDecl(SDecl *sdecl) {
    /* Code For SDecl Goes Here */
    sdecl->declaration_->accept(this);

    return value_stack.top();
}

llvm::Value *Skeleton::visitSExp(SExp *sexp) {
    /* Code For SExp Goes Here */

    sexp->exp_->accept(this);
    llvm::Value *return_val = nullptr;
    if(value_stack.size() > 0)
        return_val = value_stack.top();
    return return_val;
}

llvm::Value *Skeleton::visitSEmptyComp(SEmptyComp *semptycomp) {
    /* Code For SEmptyComp Goes Here */

    return nullptr;
}

llvm::Value *Skeleton::visitSEmpty(SEmpty *sempty) {
    /* Code For SEmpty Goes Here */

    return nullptr;
}

llvm::Value *Skeleton::visitSJmpBreak(SJmpBreak *sjmpbreak) {
    /* Code For SJmpBreak Goes Here */


}

llvm::Value *Skeleton::visitSJmpRetExp(SJmpRetExp *sjmpretexp) {
    /* Code For SJmpRetExp Goes Here */

    sjmpretexp->exp_->accept(this);
    builder.CreateRet(value_stack.top());
    value_stack.pop();
}

llvm::Value *Skeleton::visitSJmpReturn(SJmpReturn *sjmpreturn) {
    /* Code For SJmpReturn Goes Here */
    builder.CreateRet(llvm::Constant::getNullValue(llvm::Type::getVoidTy(context)));
}

llvm::Value *Skeleton::visitEAssign(EAssign *eassign) {
    /* Code For EAssign Goes Here */

    auto var = visitIdent(eassign->ident_);

    eassign->exp_->accept(this);
    auto value = value_stack.top();
    value_stack.pop();

    if(value->getType() != var->getType()->getContainedType(0))
        value = builder.CreateIntCast(value, var->getType()->getContainedType(0), true);
    //value_stack.push();
    //builder.CreateStore(value, var);
    return builder.CreateStore(value, var);//value_stack.top();
}

llvm::Value *Skeleton::visitEMul(EMul *emul) {
    /* Code For EMul Goes Here */

    emul->exp_1->accept(this);
    emul->exp_2->accept(this);

    llvm::Value *rhs = value_stack.top();
    value_stack.pop();
    llvm::Value *lhs = value_stack.top();
    value_stack.pop();

    llvm::Value *mulvalue = builder.CreateMul(lhs, rhs, "multmp");
    value_stack.push(mulvalue);
    return value_stack.top();
}

llvm::Value *Skeleton::visitEDiv(EDiv *ediv) {
    /* Code For EDiv Goes Here */

    ediv->exp_1->accept(this);
    ediv->exp_2->accept(this);

    llvm::Value *rhs = value_stack.top();
    value_stack.pop();
    llvm::Value *lhs = value_stack.top();
    value_stack.pop();

    llvm::Value *divvalue = builder.CreateSDiv(lhs, rhs, "divtmp");
    value_stack.push(divvalue);
    return value_stack.top();
}

llvm::Value *Skeleton::visitEAdd(EAdd *eadd) {
    /* Code For EAdd Goes Here */

    eadd->exp_1->accept(this);
    eadd->exp_2->accept(this);

    llvm::Value *rhs = value_stack.top();
    value_stack.pop();
    llvm::Value *lhs = value_stack.top();
    value_stack.pop();

    llvm::Value *addvalue = builder.CreateAdd(lhs, rhs, "addtmp");
    value_stack.push(addvalue);
    return value_stack.top();
}

llvm::Value *Skeleton::visitESub(ESub *esub) {
    /* Code For ESub Goes Here */

    esub->exp_1->accept(this);
    esub->exp_2->accept(this);

    llvm::Value *rhs = value_stack.top();
    value_stack.pop();
    llvm::Value *lhs = value_stack.top();
    value_stack.pop();

    llvm::Value *subvalue = builder.CreateSub(lhs, rhs, "subtmp");
    value_stack.push(subvalue);
    return value_stack.top();
}

llvm::Value *Skeleton::visitEFuncParam(EFuncParam *efuncparam) {
    /* Code For EFuncParam Goes Here */

    //visitIdent(efuncparam->ident_);
    efuncparam->listident_->accept(this);

    auto callee_func = module->getFunction(efuncparam->ident_);
    if (!callee_func)
        return nullptr;

    if (callee_func->arg_size() != efuncparam->listident_->size())
        return nullptr;

    std::vector<llvm::Value *> value;
    for (auto &arg : callee_func->args()) {
        auto val = value_stack.top();
        val = builder.CreateLoad(val, arg.getName());
        if(val->getType() != arg.getType())
            val = builder.CreateIntCast(val, arg.getType(), true);

        value.push_back(val);
        value_stack.pop();
    }
    std::reverse(value.begin(), value.end());

    value_stack.push(builder.CreateCall(callee_func, value, "callfunc"));
    return value_stack.top();
}

llvm::Value *Skeleton::visitEFunc(EFunc *efunc) {
    /* Code For EFunc Goes Here */
    //visitIdent(efunc->ident_);
    auto callee_func = module->getFunction(efunc->ident_);
    if (!callee_func)
        return nullptr;

    if (callee_func->arg_size() != 0)
        return nullptr;

    value_stack.push(builder.CreateCall(callee_func, llvm::None, "callfunc"));
    return value_stack.top();
}

llvm::Value *Skeleton::visitEVar(EVar *evar) {
    /* Code For EVar Goes Here */
    //No code needed
    llvm::Value *var = visitIdent(evar->ident_);
    auto load = builder.CreateLoad(var);
    value_stack.push(load);
    return load;
    //value_stack.push(var);
    //return var;
}

llvm::Value *Skeleton::visitEInteger(EInteger *einteger) {
    /* Code For EInteger Goes Here */
    visitInteger(einteger->integer_);
    value_stack.push(llvm::ConstantInt::get(llvm::Type::getInt64Ty(context), einteger->integer_));
    return value_stack.top();
}

llvm::Value *Skeleton::visitEChar(EChar *echar) {
    /* Code For EChar Goes Here */
    visitChar(echar->char_);
    value_stack.push(llvm::ConstantInt::get(llvm::Type::getInt8Ty(context), echar->char_));
    return value_stack.top();
}

llvm::Type *Skeleton::visitTvoid(Tvoid *tvoid) {
    /* Code For Tvoid Goes Here */
    type_stack.push(llvm::Type::getVoidTy(context));
    return type_stack.top();
}

llvm::Type *Skeleton::visitTchar(Tchar *tchar) {
    /* Code For Tchar Goes Here */
    type_stack.push(llvm::Type::getInt8Ty(context));
    return type_stack.top();
}

llvm::Type *Skeleton::visitTint(Tint *tint) {
    /* Code For Tint Goes Here */

    type_stack.push(llvm::Type::getInt64Ty(context));
    return type_stack.top();
}


llvm::Value *Skeleton::visitListFunction(ListFunction *listfunction) {
    for (ListFunction::iterator i = listfunction->begin(); i != listfunction->end(); ++i) {
        (*i)->accept(this);
    }
}

llvm::Value *Skeleton::visitListDeclaration(ListDeclaration *listdeclaration) {
    for (ListDeclaration::iterator i = listdeclaration->begin(); i != listdeclaration->end(); ++i) {
        (*i)->accept(this);
    }
}

llvm::Value *Skeleton::visitListStmt(ListStmt *liststmt) {
    for (ListStmt::iterator i = liststmt->begin(); i != liststmt->end(); ++i) {
        (*i)->accept(this);
    }
}

llvm::Value *Skeleton::visitListIdent(ListIdent *listident) {
    for (ListIdent::iterator i = listident->begin(); i != listident->end(); ++i) {
        value_stack.push(visitIdent(*i));
    }
}


llvm::Value *Skeleton::visitInteger(Integer x) {
    /* Code for Integer Goes Here */
    //No code needed
    return nullptr;
}

llvm::Value *Skeleton::visitChar(Char x) {
    /* Code for Char Goes Here */
    //No code needed
    return nullptr;
}

llvm::Value *Skeleton::visitDouble(Double x) {
    /* Code for Double Goes Here */
    //No code needed
    return nullptr;
}

llvm::Value *Skeleton::visitString(String x) {
    /* Code for String Goes Here */
    //No code needed
    return nullptr;
}

llvm::Value *Skeleton::visitIdent(Ident x) {
    /* Code for Ident Goes Here */
    return named_values.at(x);
}


void Skeleton::Compile(const std::string& output_file, Program *top_node) {

    using namespace llvm;
    using namespace llvm::sys;

    auto TargetTriple = sys::getDefaultTargetTriple();
    module->setTargetTriple(TargetTriple);


    std::string Error;
    auto Target = TargetRegistry::lookupTarget(TargetTriple, Error);

    // Print an error and exit if we couldn't find the requested target.
    // This generally occurs if we've forgotten to initialise the
    // TargetRegistry or we have a bogus target triple.
    if (!Target) {
        errs() << Error;
        abort();
    }

    auto CPU = "generic";
    auto Features = "";

    TargetOptions opt;
    auto RM = Optional<Reloc::Model>();
    auto TheTargetMachine =
            Target->createTargetMachine(TargetTriple, CPU, Features, opt, RM);

    module->setDataLayout(TheTargetMachine->createDataLayout());


    std::error_code EC;
    raw_fd_ostream dest(output_file, EC, sys::fs::F_None);

    if (EC) {
        errs() << "Could not open file: " << EC.message();
        abort();
    }

    legacy::PassManager pass;
    auto FileType = TargetMachine::CGFT_ObjectFile;

    if (TheTargetMachine->addPassesToEmitFile(pass, dest, nullptr, FileType)) {
        errs() << "TheTargetMachine can't emit a file of this type";
        abort();
    }


    top_node->accept(this); // the magic


    pass.run(*module);
    dest.flush();

    module->print(llvm::errs(), nullptr);
    outs() << "Wrote " << output_file << "\n";

}

Skeleton::Skeleton() : builder(context){
    using namespace llvm;

    module = std::make_unique<Module>("code", context);
}

llvm::AllocaInst *Skeleton::createEntryBlockAlloca(llvm::Function *function, llvm::Type *type, const std::string &var_name) {
    llvm::IRBuilder<> tmp_builder(&function->getEntryBlock(), function->getEntryBlock().begin());
    return tmp_builder.CreateAlloca(type, 0, var_name);
}

void Skeleton::Log(llvm::Value *value) {
    value->print(llvm::errs());
    llvm::errs() << "\n";
}



