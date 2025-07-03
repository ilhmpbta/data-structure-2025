#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct AVLNode {
    long long key;
    int height;
    struct AVLNode *left, *right;
} AVLNode;

int height(AVLNode* node) {
    return node ? node->height : 0;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

AVLNode* newAVLNode(long long key) {
    AVLNode* node = (AVLNode*) malloc(sizeof(AVLNode));
    node->key = key;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

int getBalance(AVLNode* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

AVLNode* rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return x;
}

AVLNode* rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

AVLNode* avlInsert(AVLNode* node, long long key) {
    if (!node) return newAVLNode(key);
    if (key < node->key) node->left = avlInsert(node->left, key);
    else if (key > node->key) node->right = avlInsert(node->right, key);
    else if (key == node->key) printf("%lld is already in the tree\n", key);
    else return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key) return rotateRight(node);
    if (balance < -1 && key > node->right->key) return rotateLeft(node);
   
    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

AVLNode* avlDelete(AVLNode* root, long long key) {
    if (!root) return NULL;

    if (key < root->key) root->left = avlDelete(root->left, key);
    else if (key > root->key) root->right = avlDelete(root->right, key);
    else {
        if (!root->left || !root->right) {
            AVLNode* temp = root->left ? root->left : root->right;
            free(root);
            return temp;
        } else {
            AVLNode* temp = root->right;
            while (temp && temp->left) temp = temp->left;
            root->key = temp->key;
            root->right = avlDelete(root->right, temp->key);
        }
    } if (!root) return NULL;

    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0) return rotateRight(root);
    if (balance < -1 && getBalance(root->right) <= 0) return rotateLeft(root);
    
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

int avlSearch(AVLNode* root, long long key) {
    if (!root) return 0;
    if (key == root->key) return 1;
    if (key < root->key) return avlSearch(root->left, key);
    return avlSearch(root->right, key);
}

void avlPath(AVLNode* root, long long key) {
    if (!root) return;
    if (key == root->key) {
        printf("%lld\n", root->key);
        return;
    }
    if (key < root->key) {
        printf("%lld ", root->key);
        avlPath(root->left, key);
    } else {
        printf("%lld ", root->key);
        avlPath(root->right, key);
    }
}

int main(){
    int N; scanf("%d", &N);
    AVLNode* root = NULL;

    for(int i = 0; i < N; i++){
        char command[10];
        long long key;
        scanf("%s %lld", command, &key);
        if(strcmp("INSERT", command) == 0){
            root = avlInsert(root, key);
            printf("%lld inserted\n", key);
        }
        if(strcmp("DELETE", command) == 0){
            if(avlSearch(root, key)){
                printf("%lld deleted\n", key);
                root = avlDelete(root, key);
            } else {
                printf("%lld is not found in the tree\n", key);
            }
        }
        if(strcmp("FIND", command) == 0){
            if(avlSearch(root, key)){
                printf("%lld found with path: ", key);
                avlPath(root, key);
            } else {
                printf("%lld not found\n", key);
            }
        }
    }
}