#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"

// δημιουργία κόμβου BST
BSTNode* createNode_bst(Citizen c) {
    BSTNode* n = (BSTNode*) malloc(sizeof(BSTNode));
    n->data = c;
    n->left = n->right = NULL;
    return n;
}

// εισαγωγή σε BST
BSTNode* insert_bst(BSTNode* root, Citizen c) {
    if (!root) return createNode_bst(c);
    if (strcmp(c.full_name, root->data.full_name) < 0)
        root->left = insert_bst(root->left, c);
    else
        root->right = insert_bst(root->right, c);
    return root;
}

// εκτύπωση BST 
void print_bst(BSTNode* root) {
    if (root != NULL) {
        print_bst(root->left);
        printf("%s, %d, %s, %d\n", root->data.full_name, root->data.age,
               root->data.state, root->data.income);
        print_bst(root->right);
    }
}

// ευρεση ελάχιστου κόμβο
BSTNode* findMin_bst(BSTNode* root) {
    while (root->left != NULL)
        root = root->left;
    return root;
}

// διαγραφή κόμβου
BSTNode* delete_bst(BSTNode* root, char* name) {
    if (!root) return NULL;
    int cmp = strcmp(name, root->data.full_name);
    if (cmp < 0)
        root->left = delete_bst(root->left, name);
    else if (cmp > 0)
        root->right = delete_bst(root->right, name);
    else {
        if (!root->left) {
            BSTNode* temp = root->right;
            free(root);
            return temp;
        } else if (!root->right) {
            BSTNode* temp = root->left;
            free(root);
            return temp;
        }
        BSTNode* temp = findMin_bst(root->right);
        root->data = temp->data;
        root->right = delete_bst(root->right, temp->data.full_name);
    }
    return root;
}

// αναζητηση 
BSTNode* search_bst(BSTNode* root, char* name) {
    if (!root) return NULL;
    int cmp = strcmp(name, root->data.full_name);
    if (cmp == 0) return root;
    else if (cmp < 0) return search_bst(root->left, name);
    else return search_bst(root->right, name);
}
