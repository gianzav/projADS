#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAXSIZE 1024

struct node {
    int key;
    char value[MAXSIZE];
    int height;
    struct node *left;
    struct node *right;
    struct node *parent;
};

typedef struct node node;

/* prototypes */
node *new_node(int k, char *v);
node *insert(node *x, node *y, int k, char *v);
node *remove_node(node *t, int k, node *r);
void clear(node *t);
void show(node *t);
node *find(node *t, int k);
node *next(node *t);
node *min(node *t);
int height(node *t);
node *balance(node *x);
node *right_rotate(node *x);
node *left_rotate(node *x);


int main() {

    char input[100];
    char cmd[10];
    node *t = NULL;
    int k;
    char v[100];

    while (1) {
        scanf(" %[^\n]", input);
        strcpy(cmd, strtok(input, " "));

        if (strcmp(cmd, "insert") == 0) {
            k = atoi(strtok(NULL, " "));
            strcpy(v, strtok(NULL, " "));

            if (t == NULL) {
                t = new_node(k, v);
            } else {
                node *x = insert(t, NULL, k , v);

                x = x->parent->parent;

                while(x != NULL) {
                    if (abs(height(x->left) - height(x->right)) == 2) {
                        t = balance(x);
                    } else {
                        t = x;
                    }
                    x = x->parent;
                }
            }
        } else if (strcmp(cmd, "remove") == 0)  {
            k = atoi(strtok(NULL, " "));
            node *x = new_node(0, "");
            t = remove_node(t, k, x);

            while (x != NULL) {
                if (abs(height(x->left) - height(x->right)) == 2) {
                    if (x == t) {
                        t = balance(x);
                        x = t;
                    } else {
                        x = balance(x);
                    }
                } 

                x = x->parent;
            }
        } else if (strcmp(cmd, "find") == 0) {
            k = atoi(strtok(NULL, " "));
            node *x = find(t, k);
            printf("%s\n", x->value);
        } else if (strcmp(cmd, "clear") == 0) {
            clear(t);
            t = NULL;
        } else if (strcmp(cmd, "show") == 0) {
            show(t);
            printf("\n");
        } else if (strcmp(cmd, "height") == 0){
            printf("%d\n", height(t));
        } else {
            break;
        }
    }

    return 0;
}

node *left_rotate(node *x) {
    node *y = x->parent;
    node *r = x->right;
    
    /* rotating */
    r->parent = y;
    x->right = r->left; 

    if (r->left != NULL)
        r->left->parent = x;

    r->left = x;
    x->parent = r;
    
    if (y != NULL) {
        if (x == y->left)
            y->left = r;
        else
            y->right = r;
    }

    /* updating the heights */
    x->height = fmax(height(x->left), height(x->right)) + 1;
    r->height = fmax(height(r->left), height(r->right)) + 1;

    while (y != NULL) {
        y->height = fmax(height(y->left), height(y->right)) + 1;
        y = y->parent;
    }
    return r;
}

node *right_rotate(node *x) {
    node *y = x->parent;
    node *l = x->left; /* will be the new root */

    /* rotating */
    l->parent = y;
    x->left = l->right;

    if (l->right != NULL)
        l->right->parent = x;

    l->right = x;
    x->parent = l;

    if (y != NULL) {
        if (x == y->left)
            y->left = l;
        else
            y->right = l;
    }

    /* updating the heights */
    x->height = fmax(height(x->left), height(x->right)) + 1;
    l->height = fmax(height(l->left), height(l->right)) + 1;

    while (y != NULL) {
        y->height = fmax(height(y->left), height(y->right)) + 1;
        y = y->parent;
    }

    return l;
}

/* inserts a new node in the tree
 * O(n) with n = # of nodes
 *
 * Worst case scenario: height(T) = n, completely unbalanced tree
 * 
 * Output: pointer to the new node
 */
node *insert(node *x, node *y, int k, char *v) {
    if (x == NULL) {
        x = new_node(k, v);
        x->parent = y;
        if (y != NULL) {
            if (k < y->key)
                y->left = x;
            else
                y->right = x;
        }

        while (y != NULL) {
            y->height = fmax(height(y->left), height(y->right)) + 1;
            y = y->parent;
        }

        return x;
    } else if (k < x->key){
        return insert(x->left, x, k, v);  // T(m)
    } else {
        return insert(x->right, x, k, v); // T(n-m-1)
    }
}

void show(node *t) {
    if (t == NULL) {
        printf("NULL ");
    } else {
        printf("%d:%s:%d ", t->key, t->value, t->height);
        show(t->left);
        show(t->right);
    }
}

/* finds the node whose key is k
 */
node *find(node *t, int k) {
    if (t->key == k) {
        return t;
    } else if (k < t->key){
        return find(t->left, k);
    } else {
        return find(t->right, k);
    }
}

node *next(node *t) {
    if (t->right != NULL) {
        return min(t->right);
    } else {
        while (t->parent != NULL && t->parent->key < t->key) {
            t = t->parent;
        }
        return t->parent;
    }
}

node *min(node *t) {
   if (t->left == NULL) {
       return t;
   } else {
       return min(t->left);
   }
}

/* Output: pointer to the effectively removed node
 */
node *remove_node(node *t, int k, node *r) {
    node *z = find(t, k);
    node *x; 

    /* search a replacement for z */

    if (z->left == NULL || z->right == NULL) { /* if z has only one child */
        x = z;
    } else {
        x = next(z); /* otherwise find the successor */
    }

    /* x is a leaf or has only one child, it's the node that will be deleted */

    node *v;
    if (x->left != NULL) {
        v = x->left;
    } else {
        v = x->right;
    }

    node *y = x->parent;
    if (y == NULL) { /* if x is the root */
        t = v;
    } else {
        if (x == y->left) { /* if it's a left child */
            y->left = v;
        } else { /* else it's a right child */
            y->right = v; 
        }
    }

    if (v != NULL) { /* if v is the root of a subtree of x */
        v->parent = y;
    }

    while (y != NULL) {
        y->height = fmax(height(y->left), height(y->right)) + 1;
        y = y->parent;
    }

    if (z != x) {
        z->key = x->key;
        strcpy(z->value, x->value);
    }

    *r = *x;
    return t;
}

void clear(node *t) {
    if (t != NULL) {
        clear(t->left);
        free(t);
        clear(t->right);
    }
}

node *new_node(int k, char *v) {
    node *x = (node*) malloc(sizeof(node));
    x->key = k;
    strcpy(x->value, v);
    x->height = 1;
    x->left = NULL;
    x->right = NULL;
    x->parent = NULL;

    return x;
}

int height(node *t) {
    if (t == NULL)
        return 0;
    else
        return t->height;
}

/* Pre: |height(x->left) - height(x->right)| = 2
 *      x->left and x->right are balanced
 */
node *balance(node *x) {
    node *y = x->left;
    node *z = x->right;

    int h = height(y);
    int k = height(z);

    if (h > k) { /* left subtree is bigger */
        if (height(y->left) < height(y->right))
            left_rotate(y);

        x = right_rotate(x);
    } else {
        if (height(z->left) > height(z->right))
            right_rotate(z);

        x = left_rotate(x);
    }

    return x;
}
