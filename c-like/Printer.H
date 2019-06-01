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

  void visitProgram(Program *p); /* abstract class */
  void visitProgr(Progr *p);
  void visitFunction(Function *p); /* abstract class */
  void visitFunc(Func *p);
  void visitListFunction(ListFunction *p);
  void visitDeclaration(Declaration *p); /* abstract class */
  void visitDecl(Decl *p);
  void visitListDeclaration(ListDeclaration *p);
  void visitStmt(Stmt *p); /* abstract class */
  void visitSComp(SComp *p);
  void visitSIfElse(SIfElse *p);
  void visitSIf(SIf *p);
  void visitSWhile(SWhile *p);
  void visitSJmp(SJmp *p);
  void visitSDeclAss(SDeclAss *p);
  void visitSDecl(SDecl *p);
  void visitSExp(SExp *p);
  void visitSEmptyComp(SEmptyComp *p);
  void visitSEmpty(SEmpty *p);
  void visitListStmt(ListStmt *p);
  void visitJmp(Jmp *p); /* abstract class */
  void visitSJmpBreak(SJmpBreak *p);
  void visitSJmpRetExp(SJmpRetExp *p);
  void visitSJmpReturn(SJmpReturn *p);
  void visitExp(Exp *p); /* abstract class */
  void visitEAssign(EAssign *p);
  void visitEMul(EMul *p);
  void visitEDiv(EDiv *p);
  void visitEMod(EMod *p);
  void visitEAdd(EAdd *p);
  void visitESub(ESub *p);
  void visitEFuncParam(EFuncParam *p);
  void visitEFunc(EFunc *p);
  void visitEVar(EVar *p);
  void visitEInteger(EInteger *p);
  void visitEChar(EChar *p);
  void visitType(Type *p); /* abstract class */
  void visitTvoid(Tvoid *p);
  void visitTchar(Tchar *p);
  void visitTint(Tint *p);
  void visitListIdent(ListIdent *p);

  void visitInteger(Integer i);
  void visitDouble(Double d);
  void visitChar(Char c);
  void visitString(String s);
  void visitIdent(String s);
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

  void visitProgram(Program *p); /* abstract class */
  void visitProgr(Progr *p);
  void visitFunction(Function *p); /* abstract class */
  void visitFunc(Func *p);
  void visitListFunction(ListFunction *p);
  void visitDeclaration(Declaration *p); /* abstract class */
  void visitDecl(Decl *p);
  void visitListDeclaration(ListDeclaration *p);
  void visitStmt(Stmt *p); /* abstract class */
  void visitSComp(SComp *p);
  void visitSIfElse(SIfElse *p);
  void visitSIf(SIf *p);
  void visitSWhile(SWhile *p);
  void visitSJmp(SJmp *p);
  void visitSDeclAss(SDeclAss *p);
  void visitSDecl(SDecl *p);
  void visitSExp(SExp *p);
  void visitSEmptyComp(SEmptyComp *p);
  void visitSEmpty(SEmpty *p);
  void visitListStmt(ListStmt *p);
  void visitJmp(Jmp *p); /* abstract class */
  void visitSJmpBreak(SJmpBreak *p);
  void visitSJmpRetExp(SJmpRetExp *p);
  void visitSJmpReturn(SJmpReturn *p);
  void visitExp(Exp *p); /* abstract class */
  void visitEAssign(EAssign *p);
  void visitEMul(EMul *p);
  void visitEDiv(EDiv *p);
  void visitEMod(EMod *p);
  void visitEAdd(EAdd *p);
  void visitESub(ESub *p);
  void visitEFuncParam(EFuncParam *p);
  void visitEFunc(EFunc *p);
  void visitEVar(EVar *p);
  void visitEInteger(EInteger *p);
  void visitEChar(EChar *p);
  void visitType(Type *p); /* abstract class */
  void visitTvoid(Tvoid *p);
  void visitTchar(Tchar *p);
  void visitTint(Tint *p);
  void visitListIdent(ListIdent *p);

  void visitInteger(Integer i);
  void visitDouble(Double d);
  void visitChar(Char c);
  void visitString(String s);
  void visitIdent(String s);
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

