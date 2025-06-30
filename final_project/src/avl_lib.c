// File: src/avl_lib.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/avl_lib.h"

#define filepath "./src/data.bin"
#define backup "./src/data_backup.bin"

int generateKomponenID(const char *no_komponen) {
    int prefix = (int)no_komponen[0];
    int number = atoi(no_komponen + 1);
    return prefix * 100000 + number;
}

Komponen createKomponen(const char *kode, const char *nama, int stok, long double harga) {
    Komponen k;
    strncpy(k.no_komponen, kode, 7);
    strncpy(k.nama, nama, 26);
    k.stok = stok;
    k.harga = harga;
    k.id = generateKomponenID(kode);
    return k;
}

AVLNode* _avl_createNode(Komponen value) {
    AVLNode *newNode = (AVLNode*) malloc(sizeof(AVLNode));
    newNode->data = value;
    newNode->height = 1;
    newNode->left = newNode->right = NULL;
    return newNode;
}

int _height(AVLNode *node) {
    return node ? node->height : 0;
}

int _max(int a, int b) {
    return a > b ? a : b;
}

int _getBalance(AVLNode *node) {
    return node ? _height(node->left) - _height(node->right) : 0;
}

AVLNode* _rotateRight(AVLNode *y) {
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = _max(_height(y->left), _height(y->right)) + 1;
    x->height = _max(_height(x->left), _height(x->right)) + 1;
    return x;
}

AVLNode* _rotateLeft(AVLNode *x) {
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = _max(_height(x->left), _height(x->right)) + 1;
    y->height = _max(_height(y->left), _height(y->right)) + 1;
    return y;
}

AVLNode* _insert(AVLNode *node, Komponen value) {
    if (!node) return _avl_createNode(value);

    if (value.id < node->data.id)
        node->left = _insert(node->left, value);
    else if (value.id > node->data.id)
        node->right = _insert(node->right, value);
    else return node;

    node->height = 1 + _max(_height(node->left), _height(node->right));
    int balance = _getBalance(node);

    if (balance > 1 && value.id < node->left->data.id) return _rotateRight(node);
    if (balance < -1 && value.id > node->right->data.id) return _rotateLeft(node);
    if (balance > 1 && value.id > node->left->data.id) {
        node->left = _rotateLeft(node->left);
        return _rotateRight(node);
    }
    if (balance < -1 && value.id < node->right->data.id) {
        node->right = _rotateRight(node->right);
        return _rotateLeft(node);
    }
    return node;
}

AVLNode* _findMin(AVLNode *node) {
    AVLNode *curr = node;
    while (curr && curr->left) curr = curr->left;
    return curr;
}

AVLNode* _remove(AVLNode *node, int id) {
    if (!node) return node;

    if (id < node->data.id)
        node->left = _remove(node->left, id);
    else if (id > node->data.id)
        node->right = _remove(node->right, id);
    else {
        AVLNode *temp;
        if (!node->left || !node->right) {
            temp = node->left ? node->left : node->right;
            if (!temp) {
                temp = node;
                node = NULL;
            } else *node = *temp;
            free(temp);
        } else {
            temp = _findMin(node->right);
            node->data = temp->data;
            node->right = _remove(node->right, temp->data.id);
        }
    }

    if (!node) return node;

    node->height = 1 + _max(_height(node->left), _height(node->right));
    int balance = _getBalance(node);

    if (balance > 1 && _getBalance(node->left) >= 0) return _rotateRight(node);
    if (balance > 1 && _getBalance(node->left) < 0) {
        node->left = _rotateLeft(node->left);
        return _rotateRight(node);
    }
    if (balance < -1 && _getBalance(node->right) <= 0) return _rotateLeft(node);
    if (balance < -1 && _getBalance(node->right) > 0) {
        node->right = _rotateRight(node->right);
        return _rotateLeft(node);
    }
    return node;
}

AVLNode* _search(AVLNode *root, int id) {
    while (root) {
        if (id < root->data.id)
            root = root->left;
        else if (id > root->data.id)
            root = root->right;
        else
            return root;
    }
    return NULL;
}

void avl_init(AVL *avl) {
    avl->_root = NULL;
    avl->_size = 0u;
}

bool avl_isEmpty(AVL *avl) {
    return avl->_root == NULL;
}

void append_to_file(const Komponen *k) {
    FILE *f = fopen(filepath, "ab");
    if (!f) return;
    fwrite(k, sizeof(Komponen), 1, f);
    fclose(f);
}

void preorder_insert(AVLNode *root, FILE *f) {
    if (root) {
        fwrite(&root->data, sizeof(Komponen), 1, f);
        preorder_insert(root->left, f);
        preorder_insert(root->right, f);
    }
}

void avl_sync_to_file(AVL *avl) {
    FILE *f = fopen(filepath, "wb");
    if (!f) return;
    preorder_insert(avl->_root, f);
    fclose(f);
}

void avl_init_from_file(AVL *avl) {
    FILE *f = fopen(filepath, "rb");
    Komponen k;
    avl_init(avl);
    if (!f) return;

    while (fread(&k, sizeof(Komponen), 1, f) == 1)
        avl_insert(avl, k, false);

    fclose(f);
}

void avl_insert(AVL *avl, Komponen value, bool writeToFile) {
    if (!avl_find(avl, value.id)) {
        avl->_root = _insert(avl->_root, value);
        avl->_size++;
        if (writeToFile)
            append_to_file(&value);
    }
}

void avl_remove(AVL *avl, int id) {
    if (avl_find(avl, id)) {
        avl->_root = _remove(avl->_root, id);
        avl->_size--;
        avl_sync_to_file(avl);
    }
}

bool avl_find(AVL *avl, int id) {
    return _search(avl->_root, id) != NULL;
}

Komponen* avl_get(AVL *avl, int id) {
    AVLNode *node = _search(avl->_root, id);
    return node ? &node->data : NULL;
}

void inorder_to_array(AVLNode* root, Komponen* arr, int* idx, long double* total_asset) {
    if (root) {
        inorder_to_array(root->left, arr, idx, total_asset);
        arr[*idx] = root->data; (*idx)++;
        *total_asset += (root->data.harga * (long double)root->data.stok);
        inorder_to_array(root->right, arr, idx, total_asset);
    }
}
