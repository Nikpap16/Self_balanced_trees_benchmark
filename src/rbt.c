#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "citizen.h"
#include "rbt.h"


// δημιουργία κόμβου
RBTNode* createNode_rbt(Citizen c) {
    RBTNode* n = (RBTNode*) malloc(sizeof(RBTNode));
    n->data = c;
    n->left = n->right = n->parent = NULL;
    n->color = 'R'; // κόμβος νέος RED
    return n;
}

// Rotations
RBTNode* leftRotate_rbt(RBTNode* root, RBTNode* x) {
    RBTNode* y = x->right;
    x->right = y->left;
    if (y->left) y->left->parent = x;

    y->parent = x->parent;
    if (!x->parent) root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;

    y->left = x;
    x->parent = y;

    return root;
}

RBTNode* rightRotate_rbt(RBTNode* root, RBTNode* y) {
    RBTNode* x = y->left;
    y->left = x->right;
    if (x->right) x->right->parent = y;

    x->parent = y->parent;
    if (!y->parent) root = x;
    else if (y == y->parent->left) y->parent->left = x;
    else y->parent->right = x;

    x->right = y;
    y->parent = x;

    return root;
}

// διόρθωση μετα το insert
RBTNode* insert_fixup_rbt(RBTNode* root, RBTNode* z) {
    while (z->parent && z->parent->color == 'R') {
        RBTNode* gp = z->parent->parent;
        RBTNode* uncle = (z->parent == gp->left) ? gp->right : gp->left;

        if (uncle && uncle->color == 'R') {
            z->parent->color = 'B';
            uncle->color = 'B';
            gp->color = 'R';
            z = gp;
        } else {
            if (z->parent == gp->left) {
                if (z == z->parent->right) {
                    z = z->parent;
                    root = leftRotate_rbt(root, z);
                }
                z->parent->color = 'B';
                gp->color = 'R';
                root = rightRotate_rbt(root, gp);
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    root = rightRotate_rbt(root, z);
                }
                z->parent->color = 'B';
                gp->color = 'R';
                root = leftRotate_rbt(root, gp);
            }
        }
    }
    root->color = 'B';
    return root;
}

// εισαγωγή 
RBTNode* insert_rbt(RBTNode* root, Citizen c) {
    RBTNode* z = createNode_rbt(c);
    RBTNode* y = NULL;
    RBTNode* x = root;

    while (x) {
        y = x;
        if (strcmp(z->data.full_name, x->data.full_name) < 0) x = x->left;
        else x = x->right;
    }

    z->parent = y;
    if (!y) root = z;
    else if (strcmp(z->data.full_name, y->data.full_name) < 0) y->left = z;
    else y->right = z;

    root = insert_fixup_rbt(root, z);
    return root;
}

// εκτυπωση RBT
void print_rbt(RBTNode* root) {
    if (root) {
        print_rbt(root->left);
        printf("%s (%c)\n", root->data.full_name, root->color);
        print_rbt(root->right);
    }
}

// ευρεση ελαχιστου
RBTNode* minimum_rbt(RBTNode* root) {
    while (root->left) root = root->left;
    return root;
}

// Transplant
RBTNode* transplant_rbt(RBTNode* root, RBTNode* u, RBTNode* v) {
    if (!u->parent) root = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;

    if (v) v->parent = u->parent;
    return root;
}

// επιδιορθωση μετα τη διαγραφη
RBTNode* delete_fixup_rbt(RBTNode* root, RBTNode* x) {
    while (x && x != root && x->color == 'B') {
        if (x == x->parent->left) {
            RBTNode* w = x->parent->right;
            if (w && w->color == 'R') {
                w->color = 'B';
                x->parent->color = 'R';
                root = leftRotate_rbt(root, x->parent);
                w = x->parent->right;
            }
            if ((!w->left || w->left->color == 'B') && (!w->right || w->right->color == 'B')) {
                w->color = 'R';
                x = x->parent;
            } else {
                if (!w->right || w->right->color == 'B') {
                    if (w->left) w->left->color = 'B';
                    w->color = 'R';
                    root = rightRotate_rbt(root, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = 'B';
                if (w->right) w->right->color = 'B';
                root = leftRotate_rbt(root, x->parent);
                x = root;
            }
        } else { // mirror
            RBTNode* w = x->parent->left;
            if (w && w->color == 'R') {
                w->color = 'B';
                x->parent->color = 'R';
                root = rightRotate_rbt(root, x->parent);
                w = x->parent->left;
            }
            if ((!w->left || w->left->color == 'B') && (!w->right || w->right->color == 'B')) {
                w->color = 'R';
                x = x->parent;
            } else {
                if (!w->left || w->left->color == 'B') {
                    if (w->right) w->right->color = 'B';
                    w->color = 'R';
                    root = leftRotate_rbt(root, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = 'B';
                if (w->left) w->left->color = 'B';
                root = rightRotate_rbt(root, x->parent);
                x = root;
            }
        }
    }
    if (x) x->color = 'B';
    return root;
}

// διαγραφή
RBTNode* delete_rbt(RBTNode* root, char* name) {
    RBTNode* z = root;
    while (z && strcmp(z->data.full_name, name) != 0) {
        if (strcmp(name, z->data.full_name) < 0) z = z->left;
        else z = z->right;
    }
    if (!z) return root;

    RBTNode* y = z;
    char y_original_color = y->color;
    RBTNode* x = NULL;

    if (!z->left) { x = z->right; root = transplant_rbt(root, z, z->right); }
    else if (!z->right) { x = z->left; root = transplant_rbt(root, z, z->left); }
    else {
        y = minimum_rbt(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) {
            if (x) x->parent = y;
        } else {
            root = transplant_rbt(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        root = transplant_rbt(root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if (y_original_color == 'B' && x)
        root = delete_fixup_rbt(root, x);

    free(z);
    return root;
}

// Search
RBTNode* search_rbt(RBTNode* root, char* name) {
    if (!root) return NULL;
    int cmp = strcmp(name, root->data.full_name);
    if (cmp == 0) return root;
    else if (cmp < 0) return search_rbt(root->left, name);
    else return search_rbt(root->right, name);
}
