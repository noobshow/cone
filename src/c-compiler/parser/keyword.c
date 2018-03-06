/** Keyword Initialization
 * @file
 *
 * The lexer divides up the source program into tokens, producing each for the parser on demand.
 * The lexer assumes UTF-8 encoding for the source program.
 *
 * This source file is part of the Cone Programming Language C compiler
 * See Copyright Notice in conec.h
*/

#include "keyword.h"
#include "lexer.h"
#include "../ast/ast.h"
#include "../shared/nametbl.h"
#include "../shared/memory.h"

#include <string.h>

Name *keyAdd(char *keyword, uint16_t toktype) {
	Name *sym;
	NamedAstNode *node;
	sym = nameFind(keyword, strlen(keyword));
	sym->node = node = (NamedAstNode*)memAllocBlk(sizeof(AstNode));
	node->asttype = KeywordNode;
	node->flags = toktype;
	return sym;
}

void keywordInit() {
	// Declare built-in types and publish their names to the name table
	permDclNames();
	nbrDclNames();

	keyAdd("fn", FnToken);
	keyAdd("struct", StructToken);
	keyAdd("alloc", AllocToken);
	keyAdd("mod", ModToken);
	keyAdd("return", RetToken);
	keyAdd("if", IfToken);
	keyAdd("elif", ElifToken);
	keyAdd("else", ElseToken);
	keyAdd("while", WhileToken);
	keyAdd("break", BreakToken);
	keyAdd("continue", ContinueToken);
	keyAdd("not", NotToken);
	keyAdd("or", OrToken);
	keyAdd("and", AndToken);
	keyAdd("as", AsToken);

	keyAdd("true", trueToken);
	keyAdd("false", falseToken);
}
