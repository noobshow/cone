/** Standard library initialization
 * @file
 *
 * This source file is part of the Cone Programming Language C compiler
 * See Copyright Notice in conec.h
*/

#include "../ir/ir.h"
#include "../ir/nametbl.h"
#include "../parser/lexer.h"

#include <string.h>

Name *keyAdd(char *keyword, uint16_t toktype) {
	Name *sym;
	INamedNode *node;
	sym = nametblFind(keyword, strlen(keyword));
	sym->node = node = (INamedNode*)memAllocBlk(sizeof(INode));
	node->asttype = KeywordTag;
	node->flags = toktype;
	return sym;
}

void keywordInit() {
	keyAdd("include", IncludeToken);
	keyAdd("mod", ModToken);
	keyAdd("extern", ExternToken);
	keyAdd("fn", FnToken);
	keyAdd("struct", StructToken);
	keyAdd("alloc", AllocToken);
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

PermNode *newPermNodeStr(char *name, char ptyp, uint16_t flags) {
    Name *namesym = nametblFind(name, strlen(name));
    PermNode *perm = newPermNode(namesym, ptyp, flags);
    namesym->node = (INamedNode*)perm;
    return perm;
}

// Declare built-in permission types and their names
void stdPermInit() {
	uniPerm = newPermNodeStr("uni", UniPerm, MayRead | MayWrite | RaceSafe | MayIntRefSum | IsLockless);
	mutPerm = newPermNodeStr("mut", MutPerm, MayRead | MayWrite | MayAlias | MayAliasWrite | IsLockless);
	immPerm = newPermNodeStr("imm", ImmPerm, MayRead | MayAlias | RaceSafe | MayIntRefSum | IsLockless);
	constPerm = newPermNodeStr("const", ConstPerm, MayRead | MayAlias | IsLockless);
	mutxPerm = newPermNodeStr("mutx", MutxPerm, MayRead | MayWrite | MayAlias | MayIntRefSum | IsLockless);
	idPerm = newPermNodeStr("id", IdPerm, MayAlias | RaceSafe | IsLockless);
}

// Set up the standard library, whose names are always shared by all modules
void stdlibInit() {
	lexInject("std", "");

    anonName = nametblFind("_", 1);
    selfName = nametblFind("self", 4);
    thisName = nametblFind("this", 4);

	keywordInit();
	stdPermInit();
	stdNbrInit();

	voidType = (INode*)newVoidNode();
}