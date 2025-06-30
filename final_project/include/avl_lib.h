#ifndef AVL_LIB_H
#define AVL_LIB_H

typedef struct {
    char no_komponen[7];
    char nama[26];
    int stok;
    long double harga;
    int id;
} Komponen;

// AVLNode dan AVL struct
typedef struct AVLNode_t {
    Komponen data;
    int height;
    struct AVLNode_t *left, *right;
} AVLNode;

typedef struct AVL_t {
    AVLNode *_root;
    unsigned int _size;
} AVL;

// Fungsi
int generateKomponenID(const char*);
Komponen createKomponen(const char*, const char*, int, long double);
void avl_init(AVL*);
bool avl_isEmpty(AVL*);
void append_to_file(const Komponen*);
void preorder_insert(AVLNode*, FILE*);
void avl_sync_to_file(AVL*); 
void avl_init_from_file(AVL*);
void avl_insert(AVL*, Komponen, bool);
void avl_remove(AVL*, int id);
bool avl_find(AVL*, int id);
Komponen* avl_get(AVL*, int id);
void inorder_to_array(AVLNode* root, Komponen* arr, int* idx, long double*);
#endif
