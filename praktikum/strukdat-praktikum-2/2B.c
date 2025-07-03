#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    long long key;
    long long count;
    struct Node *left, *right;
} Node;

Node* newNode(long long key) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->key = key;
    node->left = node->right = NULL;
    node->count = 1;
    return node;
}

Node* bstInsert(Node* root, long long key) {
    if (!root) return newNode(key);
    if (key < root->key) root->left = bstInsert(root->left, key);
    else if (key > root->key) root->right = bstInsert(root->right, key);
    else if (key == root->key) root->count++;
    return root;
}

// BST search
Node* bstSearch(Node* root, long long key) {
    if (!root) return 0;
    if (key == root->key) return root;
    if (key < root->key) return bstSearch(root->left, key);
    return bstSearch(root->right, key);
}

Node* bstRemove(Node* root, long long key) {
    if (!root) return NULL;
    if (key < root->key) {
        root->left = bstRemove(root->left, key);
    } else if (key > root->key) {
        root->right = bstRemove(root->right, key);
    } else {
        if (root->count > 1) {
            root->count--;
            return root;
        }
        if (!root->left) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (!root->right) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        Node* temp = root->right;
        while (temp && temp->left) temp = temp->left;
        root->key = temp->key;
        root->count = temp->count;
        root->right = bstRemove(root->right, temp->key);
    }
    return root;
}


void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        printf("%lld(%lld) ", root->key, root->count);
        inorder(root->right);
    }
}

void postorder(Node* root) {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        printf("%lld(%lld) ", root->key, root->count);
    }
}

void preorder(Node* root) {
    if (root) {
        printf("%lld(%lld) ", root->key, root->count);
        preorder(root->left);
        preorder(root->right);
    }
}

int main(){
    int n; scanf("%d", &n);
    Node* root = NULL;

    for(int i = 0; i < n; i++){
        char command[10]; scanf("%s ", command);
        if (strcmp(command, "insert") == 0){
            long long key; scanf("%lld", &key);
            root = bstInsert(root, key);
        }
        if (strcmp(command, "remove") == 0){
            long long key; scanf("%lld", &key);
            root = bstRemove(root, key);
        }
        if (strcmp(command, "inorder") == 0){
            inorder(root); printf("\n");
        }
        if (strcmp(command, "preorder") == 0){
            preorder(root); printf("\n");
        }
        if (strcmp(command, "postorder") == 0){
            postorder(root); printf("\n");
        }
    }
    return 0;
}