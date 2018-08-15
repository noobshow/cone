/** AST node list
 * @file
 *
 * This source file is part of the Cone Programming Language C compiler
 * See Copyright Notice in conec.h
*/

#include "ir.h"
#include "nametbl.h"
#include "../parser/lexer.h"

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

// Allocate and initialize a new nodes block
Nodes *newNodes(int size) {
	Nodes *nodes;
	nodes = (Nodes*) memAllocBlk(sizeof(Nodes) + size*sizeof(INode*));
	nodes->avail = size;
	nodes->used = 0;
	return nodes;
}

// Add an INode to the end of a Nodes, growing it if full (changing its memory location)
// This assumes a nodes can only have a single parent, whose address we point at
void nodesAdd(Nodes **nodesp, INode *node) {
	Nodes *nodes = *nodesp;
	// If full, double its size
	if (nodes->used >= nodes->avail) {
		Nodes *oldnodes;
		INode **op, **np;
		oldnodes = nodes;
		nodes = newNodes(oldnodes->avail << 1);
		op = (INode **)(oldnodes+1);
		np = (INode **)(nodes+1);
		memcpy(np, op, (nodes->used = oldnodes->used) * sizeof(INode*));
		*nodesp = nodes;
	}
	*((INode**)(nodes+1)+nodes->used) = node;
	nodes->used++;
}

// Insert an INode within a list of nodes, growing it if full (changing its memory location)
// This assumes a Nodes can only have a single parent, whose address we point at
void nodesInsert(Nodes **nodesp, INode *node, size_t index) {
    Nodes *nodes = *nodesp;
    INode **op, **np;
    // If full, double its size
    if (nodes->used >= nodes->avail) {
        Nodes *oldnodes;
        oldnodes = nodes;
        nodes = newNodes(oldnodes->avail << 1);
        op = (INode **)(oldnodes + 1);
        np = (INode **)(nodes + 1);
        memcpy(np, op, (nodes->used = oldnodes->used) * sizeof(INode*));
        *nodesp = nodes;
    }
    op = (INode **)(nodes + 1) + index;
    np = op + 1;
    size_t tomove = nodes->used - index;
    switch (tomove) {
    case 1:
        *np = *op;
        break;
    default:
        memmove(np, op, tomove * sizeof(INode*));
    }
    *op = node;
    nodes->used++;
}

// Find the desired named node in a nodes list.
// Return the node, if found or NULL if not found
INamedNode *nodesFind(Nodes *nodes, Name *name) {
	INode **nodesp;
	uint32_t cnt;
	for (nodesFor(nodes, cnt, nodesp)) {
		if (isNamedNode(*nodesp)) {
			if (((INamedNode*)*nodesp)->namesym == name)
				return (INamedNode*)*nodesp;
		}
	}
	return NULL;
}
