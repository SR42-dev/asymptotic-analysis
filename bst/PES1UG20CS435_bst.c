// Name: Sriram R
// SRN: PES1UG20CS435

#include "bst.h"
#include <stdlib.h>

/*
 ** Do not use global variables.
 ** Mark any functions that you declare in this file that are not in the header as static
 ** Do not use static variables
 ** All occurences of count_ptr indicate that the number of comparison
 ** operations need to be stored in the location pointed by it
 ** The implementation can assume it is initialized to 0.
*/

// Initializes the root of the bst
void init_bst(bst_t* bst)
{
    bst->root = NULL;
}

// Inserts element key into the Binary search tree
// Stores the number of comparisons at the location
// pointed by count_ptr

node_t* recursiveInsert(node_t* node, int key, int* count_ptr)
{
    if (node == NULL)
    {
        node_t* node1 = (node_t*)malloc(sizeof(node_t));
        node1->key = key;
        return node1;
    }
    else
    {
        if ((node->key) > key)
        {
            *count_ptr++;
            node->left = recursiveInsert(node->left, key, count_ptr);
        }
        else
        {
            *count_ptr++;
            node->right = recursiveInsert(node->right, key, count_ptr);           
        }
    }
    return node;
}

void insert(bst_t* tree, int key, int* count_ptr)
{
    tree->root = recursiveInsert(tree->root, key, count_ptr);
}

// Delete key from the BST
// Replaces node with in-order successor

node_t* recursiveDelete(node_t* r, int key, int* count_ptr)
{
    node_t* temp;
    node_t* p;

    if (r == NULL) return r;

    if (key < r->key)
    {
        *count_ptr++;
        r->left = recursiveDelete(r->left, key, count_ptr);
    }

    else if (key > r->key)
    {
        *count_ptr++;
        r->right = recursiveDelete(r->right, key, count_ptr);
    }

    else
    {
        if (r->left == NULL)
        {
            *count_ptr++;
            temp = r->right;
            free(r);
            return temp;
        }

        else if (r->right == NULL)
        {
            *count_ptr++;
            temp = r->left;
            free(r);
            return temp;
        }

        else
        {
            p = r->right;
            while (p->left != NULL) p = p->left;
            r->key = p->key;
            r->right = recursiveDelete(r->right, p->key, count_ptr);
        }
    }
    return r;
}

void delete_element(bst_t* tree, int key, int* count_ptr)
{
    tree->root = recursiveDelete(tree->root, key, count_ptr);
}

// Searches for the element key in the bst
// Returns the element if found, else -1
int recursiveSearch(node_t* node, int key, int* count_ptr)
{
    if (node == NULL) return -1;

    else
    {
        if (node->key == key)
        {
            *count_ptr++;
            return key;
        }

        else if (node->key < key)
        {
            *count_ptr++;
            return recursiveSearch(node->right, key, count_ptr);
        }

        else
        {
            *count_ptr++;
            return recursiveSearch(node->left, key, count_ptr);
        }
    }
}
int search(const bst_t* tree, int key, int* count_ptr)
{
    return recursiveSearch(tree->root, key, count_ptr);
}

// Returns the maximum element in the BST
int recursive_find_max(node_t* node, int* count_ptr)
{
    if (node == NULL) return -1;

    else
    {
        if (node->right == NULL)
        {
            *count_ptr++;
            return node->key;
        }

        else return recursive_find_max(node->right, count_ptr);
    }
}
int find_max(const bst_t* tree, int* count_ptr)
{
    return recursive_find_max(tree->root, count_ptr);
}

// Deletes all the elements of the bst
void recursiveFree(node_t* node)
{
    if (node == NULL) return;

    recursiveFree(node->left);
    recursiveFree(node->right);

    free(node);
}
void free_bst(bst_t* bst)
{
    recursiveFree(bst->root);
    free(bst);
}

// Deletes all the elements if the bst and ensures it can be used again
void clear_bst(bst_t* bst)
{
    recursiveFree(bst->root);
    bst->root = NULL;
}