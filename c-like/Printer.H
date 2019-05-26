#ifndef PRINTER_HEADER
#define PRINTER_HEADER

#include "Absyn.H"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/* Certain applications may improve performance by changing the buffer size */
#define BUFFER_INITIAL 2000
/* You may wish to change _L_PAREN or _R_PAREN */
#define _L_PAREN '('
#define _R_PAREN ')'

class PrintAbsyn : public Visitor
{
 protected:
  int _n_, _i_;
  /* The following are simple heuristics for rendering terminals */
  /* You may wish to change them */
  void render(Char c);
  void render(String s);
void render(char* s);
  void indent(void);
  void backup(void);
 public:
  PrintAbsyn(void);
  ~PrintAbsyn(void);
  char* print(Visitable* v);

  llvm::Value *visitProgram(Program *p); /* abstract class */
  llvm::Value *visitProgr(Progr *p);
  llvm::Value *visitFunction(Function *p); /* abstract class */
  llvm::Value *visitFunc(Func *p);
  llvm::Value *visitListFunction(ListFunction* p);
  llvm::Value *visitDeclaration(Declaration *p); /* abstract class */
  llvm::Value *visitDecl(Decl *p);
  llvm::Value *visitListDeclaration(ListDeclaration* p);
  llvm::Value *visitStmt(Stmt *p); /* abstract class */
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
  llvm::Value *visitListStmt(ListStmt* p);
  llvm::Value *visitJmp(Jmp *p); /* abstract class */
  llvm::Value *visitSJmpBreak(SJmpBreak *p);
  llvm::Value *visitSJmpRetExp(SJmpRetExp *p);
  llvm::Value *visitSJmpReturn(SJmpReturn *p);
  llvm::Value *visitExp(Exp *p); /* abstract class */
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
  llvm::Value *visitType(Type *p); /* abstract class */
  llvm::Type  *visitTvoid(Tvoid *p);
  llvm::Type  *visitTchar(Tchar *p);
  llvm::Type  *visitTint(Tint *p);
  llvm::Value *visitListIdent(ListIdent* p);

  llvm::Value *visitInteger(Integer i);
  llvm::Value *visitDouble(Double d);
  llvm::Value *visitChar(Char c);
  llvm::Value *visitString(String s);
  llvm::Value *visitIdent(String s);
 protected:
  void inline bufAppend(const char* s)
  {
    int len = strlen(s);
    while (cur_ + len > buf_size)
    {
      buf_size *= 2; /* Double the buffer size */
      resizeBuffer();
    }
    for(int n = 0; n < len; n++)
    {
      buf_[cur_ + n] = s[n];
    }
    cur_ += len;
    buf_[cur_] = 0;
  }
  void inline bufAppend(const char c)
  {
    if (cur_ == buf_size)
    {
      buf_size *= 2; /* Double the buffer size */
      resizeBuffer();
    }
    buf_[cur_] = c;
    cur_++;
    buf_[cur_] = 0;
  }
  void inline bufAppend(String str)
  {
    const char* s = str.c_str();
    bufAppend(s);
  }
  void inline bufReset(void)
  {
    cur_ = 0;
    buf_size = BUFFER_INITIAL;
    resizeBuffer();
    memset(buf_, 0, buf_size);
  }
  void inline resizeBuffer(void)
  {
    char* temp = (char*) malloc(buf_size);
    if (!temp)
    {
      fprintf(stderr, "Error: Out of memory while attempting to grow buffer!\n");
      exit(1);
    }
    if (buf_)
    {
      strcpy(temp, buf_);
      free(buf_);
    }
    buf_ = temp;
  }
  char *buf_;
  int cur_, buf_size;
};



class ShowAbsyn : public Visitor
{
 public:
  ShowAbsyn(void);
  ~ShowAbsyn(void);
  char* show(Visitable* v);

  llvm::Value *visitProgram(Program *p); /* abstract class */
  llvm::Value *visitProgr(Progr *p);
  llvm::Value *visitFunction(Function *p); /* abstract class */
  llvm::Value *visitFunc(Func *p);
  llvm::Value *visitListFunction(ListFunction* p);
  llvm::Value *visitDeclaration(Declaration *p); /* abstract class */
  llvm::Value *visitDecl(Decl *p);
  llvm::Value *visitListDeclaration(ListDeclaration* p);
  llvm::Value *visitStmt(Stmt *p); /* abstract class */
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
  llvm::Value *visitListStmt(ListStmt* p);
  llvm::Value *visitJmp(Jmp *p); /* abstract class */
  llvm::Value *visitSJmpBreak(SJmpBreak *p);
  llvm::Value *visitSJmpRetExp(SJmpRetExp *p);
  llvm::Value *visitSJmpReturn(SJmpReturn *p);
  llvm::Value *visitExp(Exp *p); /* abstract class */
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
  llvm::Value *visitType(Type *p); /* abstract class */
  llvm::Type *visitTvoid(Tvoid *p);
  llvm::Type *visitTchar(Tchar *p);
  llvm::Type *visitTint(Tint *p);
  llvm::Value *visitListIdent(ListIdent* p);

  llvm::Value *visitInteger(Integer i);
  llvm::Value *visitDouble(Double d);
  llvm::Value *visitChar(Char c);
  llvm::Value *visitString(String s);
  llvm::Value *visitIdent(String s);
 protected:
  void inline bufAppend(const char* s)
  {
    int len = strlen(s);
    while (cur_ + len > buf_size)
    {
      buf_size *= 2; /* Double the buffer size */
      resizeBuffer();
    }
    for(int n = 0; n < len; n++)
    {
      buf_[cur_ + n] = s[n];
    }
    cur_ += len;
    buf_[cur_] = 0;
  }
  void inline bufAppend(const char c)
  {
    if (cur_ == buf_size)
    {
      buf_size *= 2; /* Double the buffer size */
      resizeBuffer();
    }
    buf_[cur_] = c;
    cur_++;
    buf_[cur_] = 0;
  }
  void inline bufAppend(String str)
  {
    const char* s = str.c_str();
    bufAppend(s);
  }
  void inline bufReset(void)
  {
    cur_ = 0;
    buf_size = BUFFER_INITIAL;
    resizeBuffer();
    memset(buf_, 0, buf_size);
  }
  void inline resizeBuffer(void)
  {
    char* temp = (char*) malloc(buf_size);
    if (!temp)
    {
      fprintf(stderr, "Error: Out of memory while attempting to grow buffer!\n");
      exit(1);
    }
    if (buf_)
    {
      strcpy(temp, buf_);
      free(buf_);
    }
    buf_ = temp;
  }
  char *buf_;
  int cur_, buf_size;
};




#endif

