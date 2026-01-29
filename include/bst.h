#ifndef BST_H
#define BST_H

#include "citizen.h"

// Δομή κόμβου για BST
typedef struct BSTNode {
    Citizen data;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;


BSTNode* createNode_bst(Citizen c);
BSTNode* insert_bst(BSTNode* root, Citizen c);
void print_bst(BSTNode* root);
BSTNode* findMin_bst(BSTNode* root);
BSTNode* delete_bst(BSTNode* root, char* name);
BSTNode* search_bst(BSTNode* root, char* name);

#endif
