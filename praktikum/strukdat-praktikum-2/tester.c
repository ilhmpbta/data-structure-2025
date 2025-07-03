#include <stdio.h>
#include <stdlib.h>

#define MAX_A 1000000        
#define newline() putchar_unlocked('\n')

static int n;
static int raw[200005];       
static int sorted[200005];    
static int tree[200005];
static int parent_of_val[MAX_A + 1];
static int idx = 0;            

int cmp_int(const void *a, const void *b) {
    return (*(const int *)a) - (*(const int *)b);
}

void inorder_fill(int pos) {
    if (pos >= n) return;
    inorder_fill(pos * 2 + 1);            
    tree[pos] = sorted[idx++];             
    inorder_fill(pos * 2 + 2);             
}

int main(void) {
    if (scanf("%d", &n) != 1) return 0;

    for (int i = 0; i < n; ++i) {
        scanf("%d", &raw[i]);
        sorted[i] = raw[i];
    }

    qsort(sorted, n, sizeof(int), cmp_int);
    inorder_fill(0);

    for (int i = 0; i < n; ++i) {
        int val = tree[i];
        int par = (i == 0) ? -1 : tree[(i - 1) >> 1];
        parent_of_val[val] = par;
    }

    for (int i = 0; i < n; ++i) {
        int val = sorted[i];
        printf("%d%c", parent_of_val[val], (i + 1 == n) ? '\n' : ' ');
    }

    return 0;
}
