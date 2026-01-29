#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"

// δημιουργία νέου κόμβου AVL
AVLNode* create_avl_node(Citizen c) {
    AVLNode* node = (AVLNode*) malloc(sizeof(AVLNode));
    node->data = c;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

//  ύψος κόμβου
int getHeight(AVLNode* n) {
    if (!n) return 0;
    return n->height;
}

// υπολογισμός ισορροπίας
int getBalance(AVLNode* n) {
    if (!n) return 0;
    return getHeight(n->left) - getHeight(n->right);
}

// δεξιά περιστροφή
AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + ((getHeight(y->left) > getHeight(y->right)) ? getHeight(y->left) : getHeight(y->right));
    x->height = 1 + ((getHeight(x->left) > getHeight(x->right)) ? getHeight(x->left) : getHeight(x->right));

    return x;
}

// αριστερή περιστροφή
AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + ((getHeight(x->left) > getHeight(x->right)) ? getHeight(x->left) : getHeight(x->right));
    y->height = 1 + ((getHeight(y->left) > getHeight(y->right)) ? getHeight(y->left) : getHeight(y->right));

    return y;
}

// εισαγωγή 
AVLNode* insert_avl(AVLNode* root, Citizen c) {
    if (!root)
        return create_avl_node(c);

    if (strcmp(c.full_name, root->data.full_name) < 0)
        root->left = insert_avl(root->left, c);
    else if (strcmp(c.full_name, root->data.full_name) > 0)
        root->right = insert_avl(root->right, c);
    else
        return root; 
    root->height = 1 + ((getHeight(root->left) > getHeight(root->right)) ? getHeight(root->left) : getHeight(root->right));
    int balance = getBalance(root);

    // 4 περιπτώσεις ισορροπίας
    if (balance > 1 && strcmp(c.full_name, root->left->data.full_name) < 0)
        return rightRotate(root); // LL

    if (balance < -1 && strcmp(c.full_name, root->right->data.full_name) > 0)
        return leftRotate(root); // RR

    if (balance > 1 && strcmp(c.full_name, root->left->data.full_name) > 0) { // LR
        root->left = leftRotate(root->left);
        return rightRotate(root); //LR
    }

    if (balance < -1 && strcmp(c.full_name, root->right->data.full_name) < 0) { // RL
        root->right = rightRotate(root->right);
        return leftRotate(root); //RL
    }

    return root;
}

// εκτύπωση 
void print_avl(AVLNode* root) {
    if (root) {
        print_avl(root->left);
        printf("%s, %d, %s, %d\n", root->data.full_name, root->data.age, root->data.state, root->data.income);
        print_avl(root->right);
    }
}

// ευρεση ελαχιστου
AVLNode* findMin_avl(AVLNode* root) {
    AVLNode* current = root;
    while (current->left)
        current = current->left;
    return current;
}

// διαγραφή 
AVLNode* delete_avl(AVLNode* root, char* name) {
    if (!root) return root;

    if (strcmp(name, root->data.full_name) < 0)
        root->left = delete_avl(root->left, name);
    else if (strcmp(name, root->data.full_name) > 0)
        root->right = delete_avl(root->right, name);
    else {
        // Node προς διαγραφή
        if (!root->left || !root->right) {
            AVLNode* temp = root->left ? root->left : root->right;

            if (!temp) { // κανένα παιδί
                temp = root;
                root = NULL;
            } else { // ένα παιδί
                *root = *temp;
            }
            free(temp);
        } else { // δύο παιδιά
            AVLNode* temp = findMin_avl(root->right);
            root->data = temp->data;
            root->right = delete_avl(root->right, temp->data.full_name);
        }
    }

    if (!root) return root;

    root->height = 1 + ((getHeight(root->left) > getHeight(root->right)) ? getHeight(root->left) : getHeight(root->right));
    int balance = getBalance(root);

    // διατήρηση ισορροπίας
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root); // LL

    if (balance > 1 && getBalance(root->left) < 0) { // LR
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root); // RR

    if (balance < -1 && getBalance(root->right) > 0) { // RL
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// αναζήτηση
AVLNode* search_avl(AVLNode* root, char* name) {
    if (!root) return NULL;

    int cmp = strcmp(name, root->data.full_name);
    if (cmp == 0)
        return root;
    else if (cmp < 0)
        return search_avl(root->left, name);
    else
        return search_avl(root->right, name);
}
