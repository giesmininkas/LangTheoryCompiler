CC = g++
CCFLAGS = -g -W -Wall

FLEX = flex
FLEX_OPTS = -Pc-like

BISON = bison
BISON_OPTS = -t -pc-like

OBJS = Absyn.o Lexer.o Parser.o Printer.o

.PHONY: clean distclean

all: Testc-like

clean:
	rm -f *.o Testc-like c-like.aux c-like.log c-like.pdf c-like.dvi c-like.ps c-like

distclean: clean
	rm -f Absyn.C Absyn.H Test.C Parser.C Parser.H Lexer.C Skeleton.C Skeleton.H Printer.C Printer.H Makefile c-like.l c-like.y c-like.tex 

Testc-like: ${OBJS} Test.o
	@echo "Linking Testc-like..."
	${CC} ${CCFLAGS} ${OBJS} Test.o -o Testc-like

Absyn.o: Absyn.C Absyn.H
	${CC} ${CCFLAGS} -c Absyn.C

Lexer.C: c-like.l
	${FLEX} -oLexer.C c-like.l

Parser.C: c-like.y
	${BISON} c-like.y -o Parser.C

Lexer.o: Lexer.C Parser.H
	${CC} ${CCFLAGS} -c Lexer.C

Parser.o: Parser.C Absyn.H
	${CC} ${CCFLAGS} -c Parser.C

Printer.o: Printer.C Printer.H Absyn.H
	${CC} ${CCFLAGS} -c Printer.C

Skeleton.o: Skeleton.C Skeleton.H Absyn.H
	${CC} ${CCFLAGS} -c Skeleton.C

Test.o: Test.C Parser.H Printer.H Absyn.H
	${CC} ${CCFLAGS} -c Test.C

