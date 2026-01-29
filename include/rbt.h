#ifndef RBT_H
#define RBT_H

#include "citizen.h"

// τύπος κόμβου Red-Black
typedef struct RBTNode {
    Citizen data;
    struct RBTNode* left;
    struct RBTNode* right;
    struct RBTNode* parent;
    char color; // 'R' = Red, 'B' = Black
} RBTNode;



// δημιουργία 
RBTNode* createNode_rbt(Citizen c);

// Rotations
RBTNode* leftRotate_rbt(RBTNode* root, RBTNode* x);
RBTNode* rightRotate_rbt(RBTNode* root, RBTNode* y);

// εισαγωγή και Fixup
RBTNode* insert_rbt(RBTNode* root, Citizen c);
RBTNode* insert_fixup_rbt(RBTNode* root, RBTNode* z);


void print_rbt(RBTNode* root);

// Αναζήτηση
RBTNode* search_rbt(RBTNode* root, char* name);

// διαγραφή και Fixup
RBTNode* delete_rbt(RBTNode* root, char* name);
RBTNode* delete_fixup_rbt(RBTNode* root, RBTNode* x);

// αλλες συναρτήσεις 
RBTNode* minimum_rbt(RBTNode* root);
RBTNode* transplant_rbt(RBTNode* root, RBTNode* u, RBTNode* v);

#endif
