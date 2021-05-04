/* Questo esercizio è simile al precedente. Si richiede l'implementazione di un
 * albero binario di ricerca, in cui ciascun nodo contiene una chiave numerica
 * (di tipo intero) e un valore alfanumerico (di tipo stringa), che supporti,
 * oltre alle operazioni classiche insert k v, remove k, find k, clear, show,
 * anche la seguente operazione:
 * 
 * - height: restituisce l'altezza dell'albero corrente (per convenzione,
 * l'altezza dell'albero vuoto è 0 e l'altezza di un albero singoletto è 1).
 * 
 * Si richiede che le operazioni classiche insert k v, remove k, e find k prendano
 * al più tempo proporzionale all'altezza dell'albero binario di ricerca, mentre
 * l'operazione height prenda tempo costante, indipendente quindi dalla dimensione
 * o dall'altezza dell'albero.
 * 
 * 
 * Per implementare correttamente questa variante di albero di ricerca sarà
 * necessario memorizzare in ogni nodo anche l'informazione relativa all'altezza
 * del sotto-albero radicato in esso e aggiornare opportunamente questa
 * informazione durante le modifiche all'albero. 
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct node {
    int key;
    char value[100];
    int height;
    struct node *parent;
    struct node *left;
    struct node *right;
} node;

/* prototypes */
void insert(node *x, node *y, int k, char *v);
node *remove_node(node *t, int k);
void clear(node *t);
void show(node *t);
node *find(node *t, int k);
node *next(node *t);
node *min(node *t);
node *new_node(int k, char *v);
int height(node *t);

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

            if (t == NULL)
                t = new_node(k, v);
            else
            insert(t, NULL, k, v);

        } else if (strcmp(cmd, "remove") == 0)  {
            k = atoi(strtok(NULL, " "));
            t = remove_node(t, k);
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

/* inserts a new node in the tree
 * O(n) with n = # of nodes
 *
 * Worst case scenario: height(T) = n, completely unbalanced tree
 */
void insert(node *x, node *y, int k, char *v) {
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
    } else if (k < x->key){
        insert(x->left, x, k, v);  // T(m)
    } else {
        insert(x->right, x, k, v); // T(n-m-1)
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

node *remove_node(node *t, int k) {
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

    x = NULL;
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
