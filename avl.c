#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *left, *right;
    int balance;
} node;

void print_in_order(node *n) {
    if (n == NULL)
        return;
    print_in_order(n->left);
    printf("%d\n", n->value);
    print_in_order(n->right);
}

void print_pre_order(node *n) {
    if (n == NULL)
        return;
    printf("%d\n", n->value);
    print_pre_order(n->left);
    print_pre_order(n->right);
}

void print_post_order(node *n) {
    if (n == NULL)
        return;
    print_post_order(n->left);
    print_post_order(n->right);
    printf("%d\n", n->value);
}

int count(node *n) {
    if (n == NULL)
        return 0;
    return count(n->left) + count(n->right) + 1;
}

int is_ordered(node *n) {
    if (n == NULL)
        return 1;
    
    if (n->left && n->left->value > n->value)
        return 0;
    
    if (n->right && n->right->value <= n->value)
        return 0;
    
    return is_ordered(n->left) && is_ordered(n->right);
}

int is_balanced(node *n) {
    if (n == NULL)
        return 1;
    
    if (n->balance > 1 || n->balance < -1)
        return 0;
    
    return is_balanced(n->left) && is_balanced(n->right);
}

int is_avl(node *n) {
    return is_ordered(n) && is_balanced(n);
}

int get_balance(node *n) {
    if (n == NULL)
        return 0;
    n->balance = 0;
    if (n->left != NULL)
        n->balance -= (abs(get_balance(n->left)) + 1);
    if (n->right != NULL)
        n->balance += (abs(get_balance(n->right)) + 1);
    
    return n->balance;
}

node* create(int v) {
    node *n = (node*) malloc(sizeof(node));
    n->value = v;
    n->left = NULL;
    n->right = NULL;
    n->balance = 0;
    return n;
}

node* search(node *n, int v) {
    if (n == NULL)
        return NULL;
    
    if (n->value >= v)
        return search(n->left, v);
    
    if (n->value < v)
        return search(n->right, v);
    
    if (n->value == v)
        return n;
}

node* biggest(node *n) {
    if (n && n->right)
        return biggest(n->right);
    
    return n;
}

node* smallest(node *n) {
    if (n && n->left)
        return smallest(n->left);
    return n;
}

node* rotate_left(node *n) {
    node *axis = n->right;
    n->right = axis->left;
    axis->left = n;
    return axis;
}

node* rotate_right(node *n) {
    node *axis = n->left;
    n->left = axis->right;
    axis->right = n;
    return axis;
}

node* rotate_left_right(node *n) {
    n->left = rotate_left(n->left);
    n = rotate_right(n);
    return n;
}

node* rotate_right_left(node *n) {
    n->right = rotate_right(n->right);
    n = rotate_left(n);
    return n;
}

node* rotate(node *n) {
    if (n->balance > 1) {
        if (n->right->balance < 0)
            n = rotate_right_left(n);
        else
            n = rotate_left(n);
    } else if (n->balance < -1) {
        if (n->left->balance > 0)
            n = rotate_left_right(n);
        else
            n = rotate_right(n);
    }
    
    return n;
}

node* push(node *r, node *n) {
    if (r == NULL)
        r = n;
    else if (r->value >= n->value)
        r->left = push(r->left, n);
    else if (r->value < n->value)
        r->right =push(r->right, n);
    
    r->balance = get_balance(r);
    r = rotate(r);
    
    return r;
}

int main()
{
    node *n;
    n = create(10);
    n = push(n, create(5));
    n = push(n, create(50));
    n = push(n, create(55));
    n = push(n, create(65));
    
    print_pre_order(n);

    return 0;
}
