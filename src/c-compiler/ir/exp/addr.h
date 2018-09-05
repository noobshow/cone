/** Handling for address-of expression nodes
 * @file
 *
 * This source file is part of the Cone Programming Language C compiler
 * See Copyright Notice in conec.h
*/

#ifndef addr_h
#define addr_h

typedef struct AddrNode {
	ITypedNodeHdr;
	INode *exp;
} AddrNode;

AddrNode *newAddrNode();
void addrPrint(AddrNode *node);
void addrPass(PassState *pstate, AddrNode *node);

#endif