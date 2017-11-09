/** Main program file
 * @file
 *
 * This source file is part of the Cone Programming Language C compiler
 * See Copyright Notice in conec.h
*/

#include "cone.h"
#include "shared/fileio.h"
#include "shared/ast.h"
#include "shared/error.h"
#include "parser/lexer.h"
#include "parser/parser.h"

#include <stdio.h>
#include <stdlib.h>

void main(int argv, char **argc) {
	char *src;

	// Output compiler name and release level
	puts(CONE_RELEASE);

	if (argv<2) {
		puts("Specify a Cone program to compile");
		exit(1);
	}

	src = fileLoad(argc[1]);
	if (src) {
		lexInject(argc[1], src);
		parse();
	}
	else
		errorExit(ExitNF, "Cannot load source file.");

	errorSummary();
#ifdef _DEBUG
	getchar();	// Hack for VS debugging
#endif
}