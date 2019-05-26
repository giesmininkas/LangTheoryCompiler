/*** BNFC-Generated Pretty Printer and Abstract Syntax Viewer ***/

#include <string>
#include "Printer.H"
#define INDENT_WIDTH 2


//You may wish to change render
void PrintAbsyn::render(Char c)
{
  if (c == '{')
  {
     bufAppend('\n');
     indent();
     bufAppend(c);
     _n_ = _n_ + INDENT_WIDTH;
     bufAppend('\n');
     indent();
  }
  else if (c == '(' || c == '[')
     bufAppend(c);
  else if (c == ')' || c == ']')
  {
     backup();
     bufAppend(c);
  }
  else if (c == '}')
  {
     int t;
     _n_ = _n_ - INDENT_WIDTH;
     for (t=0; t<INDENT_WIDTH; t++) {
       backup();
     }
     bufAppend(c);
     bufAppend('\n');
     indent();
  }
  else if (c == ',')
  {
     backup();
     bufAppend(c);
     bufAppend(' ');
  }
  else if (c == ';')
  {
     backup();
     bufAppend(c);
     bufAppend('\n');
     indent();
  }
  else if (c == 0) return;
  else
  {
     bufAppend(' ');
     bufAppend(c);
     bufAppend(' ');
  }
}
void PrintAbsyn::render(String s_)
{
  const char *s = s_.c_str() ;
  if(strlen(s) > 0)
  {
    bufAppend(s);
    bufAppend(' ');
  }
}
void PrintAbsyn::render(char* s)
{
  if(strlen(s) > 0)
  {
    bufAppend(s);
    bufAppend(' ');
  }
}
void PrintAbsyn::indent()
{
  int n = _n_;
  while (n > 0)
  {
    bufAppend(' ');
    n--;
  }
}
void PrintAbsyn::backup()
{
  if (buf_[cur_ - 1] == ' ')
  {
    buf_[cur_ - 1] = 0;
    cur_--;
  }
}
PrintAbsyn::PrintAbsyn(void)
{
  _i_ = 0; _n_ = 0;
  buf_ = 0;
  bufReset();
}

PrintAbsyn::~PrintAbsyn(void)
{
}

char* PrintAbsyn::print(Visitable *v)
{
  _i_ = 0; _n_ = 0;
  bufReset();
  v->accept(this);
  return buf_;
}
llvm::Value *PrintAbsyn::visitProgram(Program*p) {} //abstract class

llvm::Value *PrintAbsyn::visitProgr(Progr* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  if(p->listfunction_) {_i_ = 0; p->listfunction_->accept(this);}
  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

llvm::Value *PrintAbsyn::visitFunction(Function*p) {} //abstract class

llvm::Value *PrintAbsyn::visitFunc(Func* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  _i_ = 0; p->type_->accept(this);
  visitIdent(p->ident_);
  render('(');
  if(p->listdeclaration_) {_i_ = 0; p->listdeclaration_->accept(this);}  render(')');
  _i_ = 0; p->stmt_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

llvm::Value *PrintAbsyn::visitListFunction(ListFunction *listfunction)
{
  for (ListFunction::const_iterator i = listfunction->begin() ; i != listfunction->end() ; ++i)
  {
    (*i)->accept(this);
    render("");
  }
}llvm::Value *PrintAbsyn::visitDeclaration(Declaration*p) {} //abstract class

llvm::Value *PrintAbsyn::visitDecl(Decl* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  _i_ = 0; p->type_->accept(this);
  visitIdent(p->ident_);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

llvm::Value *PrintAbsyn::visitListDeclaration(ListDeclaration *listdeclaration)
{
  for (ListDeclaration::const_iterator i = listdeclaration->begin() ; i != listdeclaration->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listdeclaration->end() - 1) render(',');
  }
}llvm::Value *PrintAbsyn::visitStmt(Stmt*p) {} //abstract class

llvm::Value *PrintAbsyn::visitSComp(SComp* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render('{');
  if(p->liststmt_) {_i_ = 0; p->liststmt_->accept(this);}  render('}');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

llvm::Value *PrintAbsyn::visitSIfElse(SIfElse* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("if");
  render('(');
  _i_ = 0; p->exp_->accept(this);
  render(')');
  _i_ = 0; p->stmt_1->accept(this);
  render("else");
  _i_ = 0; p->stmt_2->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

llvm::Value *PrintAbsyn::visitSIf(SIf* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("if");
  render('(');
  _i_ = 0; p->exp_->accept(this);
  render(')');
  _i_ = 0; p->stmt_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

llvm::Value *PrintAbsyn::visitSWhile(SWhile* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("while");
  render('(');
  _i_ = 0; p->exp_->accept(this);
  render(')');
  _i_ = 0; p->stmt_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

llvm::Value *PrintAbsyn::visitSJmp(SJmp* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  _i_ = 0; p->jmp_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

llvm::Value *PrintAbsyn::visitSDeclAss(SDeclAss* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  _i_ = 0; p->declaration_->accept(this);
  render('=');
  _i_ = 0; p->exp_->accept(this);
  render(';');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

llvm::Value *PrintAbsyn::visitSDecl(SDecl* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  _i_ = 0; p->declaration_->accept(this);
  render(';');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

llvm::Value *PrintAbsyn::visitSExp(SExp* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  _i_ = 0; p->exp_->accept(this);
  render(';');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

llvm::Value *PrintAbsyn::visitSEmptyComp(SEmptyComp* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render('{');
  render('}');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

llvm::Value *PrintAbsyn::visitSEmpty(SEmpty* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render(';');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

llvm::Value *PrintAbsyn::visitListStmt(ListStmt *liststmt)
{
  for (ListStmt::const_iterator i = liststmt->begin() ; i != liststmt->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != liststmt->end() - 1) render("");
  }
}llvm::Value *PrintAbsyn::visitJmp(Jmp*p) {} //abstract class

llvm::Value *PrintAbsyn::visitSJmpBreak(SJmpBreak* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("break");
  render(';');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

llvm::Value *PrintAbsyn::visitSJmpRetExp(SJmpRetExp* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("return");
  _i_ = 0; p->exp_->accept(this);
  render(';');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

llvm::Value *PrintAbsyn::visitSJmpReturn(SJmpReturn* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("return");
  render(';');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

llvm::Value *PrintAbsyn::visitExp(Exp*p) {} //abstract class

llvm::Value *PrintAbsyn::visitEAssign(EAssign* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  visitIdent(p->ident_);
  render('=');
  _i_ = 1; p->exp_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

llvm::Value *PrintAbsyn::visitEMul(EMul* p)
{
  int oldi = _i_;
  if (oldi > 1) render(_L_PAREN);

  _i_ = 1; p->exp_1->accept(this);
  render('*');
  _i_ = 2; p->exp_2->accept(this);

  if (oldi > 1) render(_R_PAREN);

  _i_ = oldi;
}

llvm::Value *PrintAbsyn::visitEDiv(EDiv* p)
{
  int oldi = _i_;
  if (oldi > 1) render(_L_PAREN);

  _i_ = 1; p->exp_1->accept(this);
  render('/');
  _i_ = 2; p->exp_2->accept(this);

  if (oldi > 1) render(_R_PAREN);

  _i_ = oldi;
}

llvm::Value *PrintAbsyn::visitEAdd(EAdd* p)
{
  int oldi = _i_;
  if (oldi > 2) render(_L_PAREN);

  _i_ = 2; p->exp_1->accept(this);
  render('+');
  _i_ = 3; p->exp_2->accept(this);

  if (oldi > 2) render(_R_PAREN);

  _i_ = oldi;
}

llvm::Value *PrintAbsyn::visitESub(ESub* p)
{
  int oldi = _i_;
  if (oldi > 2) render(_L_PAREN);

  _i_ = 2; p->exp_1->accept(this);
  render('-');
  _i_ = 3; p->exp_2->accept(this);

  if (oldi > 2) render(_R_PAREN);

  _i_ = oldi;
}

llvm::Value *PrintAbsyn::visitEFuncParam(EFuncParam* p)
{
  int oldi = _i_;
  if (oldi > 2) render(_L_PAREN);

  visitIdent(p->ident_);
  render('(');
  if(p->listident_) {_i_ = 0; p->listident_->accept(this);}  render(')');

  if (oldi > 2) render(_R_PAREN);

  _i_ = oldi;
}

llvm::Value *PrintAbsyn::visitEFunc(EFunc* p)
{
  int oldi = _i_;
  if (oldi > 2) render(_L_PAREN);

  visitIdent(p->ident_);
  render('(');
  render(')');

  if (oldi > 2) render(_R_PAREN);

  _i_ = oldi;
}

llvm::Value *PrintAbsyn::visitEVar(EVar* p)
{
  int oldi = _i_;
  if (oldi > 3) render(_L_PAREN);

  visitIdent(p->ident_);

  if (oldi > 3) render(_R_PAREN);

  _i_ = oldi;
}

llvm::Value *PrintAbsyn::visitEInteger(EInteger* p)
{
  int oldi = _i_;
  if (oldi > 3) render(_L_PAREN);

  visitInteger(p->integer_);

  if (oldi > 3) render(_R_PAREN);

  _i_ = oldi;
}

llvm::Value *PrintAbsyn::visitEChar(EChar* p)
{
  int oldi = _i_;
  if (oldi > 3) render(_L_PAREN);

  visitChar(p->char_);

  if (oldi > 3) render(_R_PAREN);

  _i_ = oldi;
}

llvm::Value *PrintAbsyn::visitType(Type*p) {} //abstract class

llvm::Type *PrintAbsyn::visitTvoid(Tvoid* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("void");

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

llvm::Type *PrintAbsyn::visitTchar(Tchar* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("char");

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

llvm::Type *PrintAbsyn::visitTint(Tint* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("int");

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

llvm::Value *PrintAbsyn::visitListIdent(ListIdent *listident)
{
  for (ListIdent::const_iterator i = listident->begin() ; i != listident->end() ; ++i)
  {
    visitIdent(*i) ;
    if (i != listident->end() - 1) render(',');
  }
}llvm::Value *PrintAbsyn::visitInteger(Integer i)
{
  char tmp[16];
  sprintf(tmp, "%d", i);
  bufAppend(tmp);
}
llvm::Value *PrintAbsyn::visitDouble(Double d)
{
  char tmp[16];
  sprintf(tmp, "%g", d);
  bufAppend(tmp);
}
llvm::Value *PrintAbsyn::visitChar(Char c)
{
  bufAppend('\'');
  bufAppend(c);
  bufAppend('\'');
}
llvm::Value *PrintAbsyn::visitString(String s)
{
  bufAppend('\"');
  bufAppend(s);
  bufAppend('\"');
}
llvm::Value *PrintAbsyn::visitIdent(String s)
{
  render(s);
}

ShowAbsyn::ShowAbsyn(void)
{
  buf_ = 0;
  bufReset();
}

ShowAbsyn::~ShowAbsyn(void)
{
}

char* ShowAbsyn::show(Visitable *v)
{
  bufReset();
  v->accept(this);
  return buf_;
}
llvm::Value *ShowAbsyn::visitProgram(Program* p) {} //abstract class

llvm::Value *ShowAbsyn::visitProgr(Progr* p)
{
  bufAppend('(');
  bufAppend("Progr");
  bufAppend(' ');
  bufAppend('[');
  if (p->listfunction_)  p->listfunction_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
llvm::Value *ShowAbsyn::visitFunction(Function* p) {} //abstract class

llvm::Value *ShowAbsyn::visitFunc(Func* p)
{
  bufAppend('(');
  bufAppend("Func");
  bufAppend(' ');
  bufAppend('[');
  if (p->type_)  p->type_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  visitIdent(p->ident_);
  bufAppend(' ');
  bufAppend('[');
  if (p->listdeclaration_)  p->listdeclaration_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend('[');
  if (p->stmt_)  p->stmt_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
llvm::Value *ShowAbsyn::visitListFunction(ListFunction *listfunction)
{
  for (ListFunction::const_iterator i = listfunction->begin() ; i != listfunction->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listfunction->end() - 1) bufAppend(", ");
  }
}

llvm::Value *ShowAbsyn::visitDeclaration(Declaration* p) {} //abstract class

llvm::Value *ShowAbsyn::visitDecl(Decl* p)
{
  bufAppend('(');
  bufAppend("Decl");
  bufAppend(' ');
  bufAppend('[');
  if (p->type_)  p->type_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  visitIdent(p->ident_);
  bufAppend(')');
}
llvm::Value *ShowAbsyn::visitListDeclaration(ListDeclaration *listdeclaration)
{
  for (ListDeclaration::const_iterator i = listdeclaration->begin() ; i != listdeclaration->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listdeclaration->end() - 1) bufAppend(", ");
  }
}

llvm::Value *ShowAbsyn::visitStmt(Stmt* p) {} //abstract class

llvm::Value *ShowAbsyn::visitSComp(SComp* p)
{
  bufAppend('(');
  bufAppend("SComp");
  bufAppend(' ');
  bufAppend('[');
  if (p->liststmt_)  p->liststmt_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend(')');
}
llvm::Value *ShowAbsyn::visitSIfElse(SIfElse* p)
{
  bufAppend('(');
  bufAppend("SIfElse");
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  p->stmt_1->accept(this);
  bufAppend(' ');
  p->stmt_2->accept(this);
  bufAppend(')');
}
llvm::Value *ShowAbsyn::visitSIf(SIf* p)
{
  bufAppend('(');
  bufAppend("SIf");
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend('[');
  if (p->stmt_)  p->stmt_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
llvm::Value *ShowAbsyn::visitSWhile(SWhile* p)
{
  bufAppend('(');
  bufAppend("SWhile");
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend('[');
  if (p->stmt_)  p->stmt_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
llvm::Value *ShowAbsyn::visitSJmp(SJmp* p)
{
  bufAppend('(');
  bufAppend("SJmp");
  bufAppend(' ');
  bufAppend('[');
  if (p->jmp_)  p->jmp_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
llvm::Value *ShowAbsyn::visitSDeclAss(SDeclAss* p)
{
  bufAppend('(');
  bufAppend("SDeclAss");
  bufAppend(' ');
  bufAppend('[');
  if (p->declaration_)  p->declaration_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend(')');
}
llvm::Value *ShowAbsyn::visitSDecl(SDecl* p)
{
  bufAppend('(');
  bufAppend("SDecl");
  bufAppend(' ');
  bufAppend('[');
  if (p->declaration_)  p->declaration_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend(')');
}
llvm::Value *ShowAbsyn::visitSExp(SExp* p)
{
  bufAppend('(');
  bufAppend("SExp");
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend(')');
}
llvm::Value *ShowAbsyn::visitSEmptyComp(SEmptyComp* p)
{
  bufAppend("SEmptyComp");
}
llvm::Value *ShowAbsyn::visitSEmpty(SEmpty* p)
{
  bufAppend("SEmpty");
}
llvm::Value *ShowAbsyn::visitListStmt(ListStmt *liststmt)
{
  for (ListStmt::const_iterator i = liststmt->begin() ; i != liststmt->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != liststmt->end() - 1) bufAppend(", ");
  }
}

llvm::Value *ShowAbsyn::visitJmp(Jmp* p) {} //abstract class

llvm::Value *ShowAbsyn::visitSJmpBreak(SJmpBreak* p)
{
  bufAppend("SJmpBreak");
}
llvm::Value *ShowAbsyn::visitSJmpRetExp(SJmpRetExp* p)
{
  bufAppend('(');
  bufAppend("SJmpRetExp");
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend(')');
}
llvm::Value *ShowAbsyn::visitSJmpReturn(SJmpReturn* p)
{
  bufAppend("SJmpReturn");
}
llvm::Value *ShowAbsyn::visitExp(Exp* p) {} //abstract class

llvm::Value *ShowAbsyn::visitEAssign(EAssign* p)
{
  bufAppend('(');
  bufAppend("EAssign");
  bufAppend(' ');
  visitIdent(p->ident_);
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
llvm::Value *ShowAbsyn::visitEMul(EMul* p)
{
  bufAppend('(');
  bufAppend("EMul");
  bufAppend(' ');
  p->exp_1->accept(this);
  bufAppend(' ');
  p->exp_2->accept(this);
  bufAppend(')');
}
llvm::Value *ShowAbsyn::visitEDiv(EDiv* p)
{
  bufAppend('(');
  bufAppend("EDiv");
  bufAppend(' ');
  p->exp_1->accept(this);
  bufAppend(' ');
  p->exp_2->accept(this);
  bufAppend(')');
}
llvm::Value *ShowAbsyn::visitEAdd(EAdd* p)
{
  bufAppend('(');
  bufAppend("EAdd");
  bufAppend(' ');
  p->exp_1->accept(this);
  bufAppend(' ');
  p->exp_2->accept(this);
  bufAppend(')');
}
llvm::Value *ShowAbsyn::visitESub(ESub* p)
{
  bufAppend('(');
  bufAppend("ESub");
  bufAppend(' ');
  p->exp_1->accept(this);
  bufAppend(' ');
  p->exp_2->accept(this);
  bufAppend(')');
}
llvm::Value *ShowAbsyn::visitEFuncParam(EFuncParam* p)
{
  bufAppend('(');
  bufAppend("EFuncParam");
  bufAppend(' ');
  visitIdent(p->ident_);
  bufAppend(' ');
  bufAppend('[');
  if (p->listident_)  p->listident_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend(')');
}
llvm::Value *ShowAbsyn::visitEFunc(EFunc* p)
{
  bufAppend('(');
  bufAppend("EFunc");
  bufAppend(' ');
  visitIdent(p->ident_);
  bufAppend(' ');
  bufAppend(')');
}
llvm::Value *ShowAbsyn::visitEVar(EVar* p)
{
  bufAppend('(');
  bufAppend("EVar");
  bufAppend(' ');
  visitIdent(p->ident_);
  bufAppend(')');
}
llvm::Value *ShowAbsyn::visitEInteger(EInteger* p)
{
  bufAppend('(');
  bufAppend("EInteger");
  bufAppend(' ');
  visitInteger(p->integer_);
  bufAppend(')');
}
llvm::Value *ShowAbsyn::visitEChar(EChar* p)
{
  bufAppend('(');
  bufAppend("EChar");
  bufAppend(' ');
  visitChar(p->char_);
  bufAppend(')');
}
llvm::Value *ShowAbsyn::visitType(Type* p) {} //abstract class

llvm::Type *ShowAbsyn::visitTvoid(Tvoid* p)
{
  bufAppend("Tvoid");
}
llvm::Type *ShowAbsyn::visitTchar(Tchar* p)
{
  bufAppend("Tchar");
}
llvm::Type *ShowAbsyn::visitTint(Tint* p)
{
  bufAppend("Tint");
}
llvm::Value *ShowAbsyn::visitListIdent(ListIdent *listident)
{
  for (ListIdent::const_iterator i = listident->begin() ; i != listident->end() ; ++i)
  {
    visitIdent(*i) ;
    if (i != listident->end() - 1) bufAppend(", ");
  }
}

llvm::Value *ShowAbsyn::visitInteger(Integer i)
{
  char tmp[16];
  sprintf(tmp, "%d", i);
  bufAppend(tmp);
}
llvm::Value *ShowAbsyn::visitDouble(Double d)
{
  char tmp[16];
  sprintf(tmp, "%g", d);
  bufAppend(tmp);
}
llvm::Value *ShowAbsyn::visitChar(Char c)
{
  bufAppend('\'');
  bufAppend(c);
  bufAppend('\'');
}
llvm::Value *ShowAbsyn::visitString(String s)
{
  bufAppend('\"');
  bufAppend(s);
  bufAppend('\"');
}
llvm::Value *ShowAbsyn::visitIdent(String s)
{
  bufAppend('\"');
  bufAppend(s);
  bufAppend('\"');
}

