/** Compiler types
 * @file
 *
 * This source file is part of the Cone Programming Language C compiler
 * See Copyright Notice in conec.h
*/

#ifndef type_h
#define type_h

#include <stdint.h>
typedef struct Symbol Symbol;

#define allocTypeAstNode(TypeAstNode) ((TypeAstNode *) memAllocBlk(sizeof(TypeAstNode)))

// Void type - e.g., for fn with no return value
typedef struct VoidTypeAstNode {
	BasicAstHdr;
} VoidTypeAstNode;

// For primitives such as integer, unsigned integet, floats
typedef struct PrimTypeAstNode {
	BasicAstHdr;
	unsigned char nbytes;	// e.g., int32 uses 4 bytes
} PrimTypeAstNode;

// For function signatures
typedef struct FnTypeAstNode {
	BasicAstHdr;
	AstNode *rettype;	// return type
	// named parameters and their types
} FnTypeAstNode;

// For pointers
typedef struct PtrTypeAstNode {
	BasicAstHdr;
	unsigned char nbytes;	// e.g., 32-bit uses 4 bytes
	unsigned char subtype;	// Simple, vtabled
	AstNode *ptrtotype;	// Type of value pointer points to
} PtrTypeAstNode;

// For arrays
typedef struct ArrTypeAstNode {
	BasicAstHdr;
	uint32_t nbrelems;		// Number of elements
	AstNode *elemtype;	// Type of array's elements
} ArrTypeAstNode;

// For identifiers that are types rather than values
typedef struct TypeTypeAstNode {
	BasicAstHdr;
	unsigned char subtype;
	AstNode *TypeAstNode;
} TypeTypeAstNode;

#include "permission.h"

// Primitive numeric types
AstNode *i8Type;
AstNode *i16Type;
AstNode *i32Type;
AstNode *i64Type;
AstNode *u8Type;
AstNode *u16Type;
AstNode *u32Type;
AstNode *u64Type;
AstNode *f32Type;
AstNode *f64Type;

// Built-in permission types
AstNode *mutPerm;
AstNode *mmutPerm;
AstNode *immPerm;
AstNode *constPerm;
AstNode *constxPerm;
AstNode *mutxPerm;
AstNode *idPerm;

// Communication block between function impl and type parser
typedef struct TypeAndName {
	FnTypeAstNode *TypeAstNode;
	struct Symbol *symname;	// NULL = no name specified
} TypeAndName;

void typInit();

#endif