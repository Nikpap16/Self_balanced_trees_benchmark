#ifndef AVL_H
#define AVL_H

#include "citizen.h"

// δομή κόμβου AVL
typedef struct AVLNode {
    Citizen data;
    struct AVLNode* left;
    struct AVLNode* right;
    int height;
} AVLNode;

// δηλώσεις 
AVLNode* create_avl_node(Citizen c);
AVLNode* insert_avl(AVLNode* root, Citizen c);
void print_avl(AVLNode* root);
AVLNode* findMin_avl(AVLNode* root);
AVLNode* delete_avl(AVLNode* root, char* name);
AVLNode* search_avl(AVLNode* root, char* name);

#endif
