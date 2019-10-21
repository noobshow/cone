/** Shared logic for namespace-based types
 * @file
 *
 * This source file is part of the Cone Programming Language C compiler
 * See Copyright Notice in conec.h
*/

#ifndef instype_h
#define instype_h

// Namespaced type that supports methods, properties and traits
#define INsTypeNodeHdr \
    ITypeNodeHdr; \
    NodeList nodelist; \
    Namespace namespace; \
    Nodes *subtypes

// Interface for a namespaced type
// -> nodes (NodeList) is the list of nodes
// -> namespace is the dictionary of names (methods, properties)
// -> subtypes (Nodes) is the list of trait/interface subtypes it implements
typedef struct INsTypeNode {
    INsTypeNodeHdr;
} INsTypeNode;

// Needed for helper functions
typedef struct FnDclNode FnDclNode;
typedef struct VarDclNode VarDclNode;

// Add a static function or potentially overloaded method
// If method is overloaded, add it to the link chain of same named methods
void iNsTypeAddFn(NodeList *mnodes, FnDclNode *fnnode);

// Add a property node to a method type
void iNsTypeAddProp(NodeList *mnodes, VarDclNode *fnnode);

// Find the desired named node (could be method or property)
// Return the node, if found or NULL if not found
INamedNode *iNsTypeNodeFind(NodeList *mnodes, Name *name);

// Find method that best fits the passed arguments
// 'firstmethod' is the first method that matches the name
// We follow its forward links to find one whose parameter types best match args types
FnDclNode *iNsTypeFindBestMethod(FnDclNode *firstmethod, Nodes *args);

#endif