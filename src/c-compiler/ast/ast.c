/** AST structure handlers
 * @file
 *
 * This source file is part of the Cone Programming Language C compiler
 * See Copyright Notice in conec.h
*/

#include "ast.h"
#include "../parser/lexer.h"

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

FILE *astfile;

void astPrintLn(int indent, char *str, ...) {
	int cnt;
	va_list argptr;
	for (cnt=0; cnt<indent; cnt++)
		fprintf(astfile, (cnt&3)==0? "| " : "  ");
	va_start(argptr, str);
	vfprintf(astfile, str, argptr);
	va_end(argptr);
	fprintf(astfile, "\n");
}

void astPrintNode(int indent, AstNode *node) {
	switch (node->asttype) {
	case PgmNode:
		pgmPrint(indent, (PgmAstNode *)node); break;
	case FnImplNode:
		fnImplPrint(indent, (FnImplAstNode *)node); break;
	default:
		astPrintLn(indent, "**** UNKNOWN NODE ****");
	}
}

void astPrint(AstNode *pgm) {
	astfile = fopen("program.ast", "wb");
	astPrintNode(0, pgm);
	fclose(astfile);
}