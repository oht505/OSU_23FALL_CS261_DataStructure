/*
 * This file is where you should implement your binary search tree.  It already
 * contains skeletons of the functions you need to implement (along with
 * documentation for each function).  Feel free to implement any additional
 * functions you might need.  Also, don't forget to include your name and
 * @oregonstate.edu email address below.
 *
 * Name: HyunTaek, Oh
 * Email: ohhyun@oregonstate.edu
 */

#include <stdlib.h>
#include <stdio.h>
#include "bst.h"
#include "stack.h"

/*
 * This structure represents a single node in a BST.  In addition to containing
 * pointers to its two child nodes (i.e. `left` and `right`), it contains two
 * fields representing the data stored at this node.  The `key` field is an
 * integer value that should be used as an identifier for the data in this
 * node.  Nodes in the BST should be ordered based on this `key` field.  The
 * `value` field stores data associated with the key.
 *
 * You should not modify this structure.
 */
struct bst_node {
  int key;
  void* value;
  struct bst_node* left;
  struct bst_node* right;
};


/*
 * This structure represents an entire BST.  It specifically contains a
 * reference to the root node of the tree.
 *
 * You should not modify this structure.
 */
struct bst {
  struct bst_node* root;
};

// declarations for helper
int bst_count(struct bst_node* root);
struct bst_node* bst_node_create(int key, void* value);
struct bst_node* bst_node_insert(struct bst_node* bst_node, int key, void* value);
int bst_node_minval(struct bst_node* bst_node);
struct bst_node* bst_node_remove(struct bst_node* bst_node, int key);
int bst_count_height(struct bst_node* bst_node);
int bst_has_path_sum(struct bst_node* bst_node, int sum);
int bst_cal_range_sum(struct bst_node* bst_node,int* sm, int lower, int upper);


/*
 * This function should allocate and initialize a new, empty, BST and return
 * a pointer to it.
 */
struct bst* bst_create() {
    struct bst* bst = malloc(sizeof(struct bst));

    if (bst) {
        bst->root = NULL;
        return bst;
    }
    else {
        printf("Fail to create bst\n");
    }
  
}
// Helper function for checking any node in the tree

int bst_isempty(struct bst* bst) {
    if (bst) {
        return bst->root == NULL;
    }
    else {
        printf("No bst\n");
    }
}

/*
 * This function should free the memory associated with a BST.  While this
 * function should up all memory used in the BST itself, it should not free
 * any memory allocated to the pointer values stored in the BST.  This is the
 * responsibility of the caller.
 *
 * Params:
 *   bst - the BST to be destroyed.  May not be NULL.
 */
void bst_free(struct bst* bst) {
    if (bst) {

        while (!bst_isempty(bst)) {
            bst_remove(bst, bst->root->key);
        }
        
        
        free(bst);
    }
    else {
        printf("No bst to free\n");
    }
  return;
}

// Helper function for counting the number of nodes
int bst_count(struct bst_node* bst_node){
    struct bst_node* curr = bst_node;
    int size = 1;

    if (curr->left != NULL) {
        size += bst_count(curr->left);
    }

    if (curr->right != NULL) {
        size += bst_count(curr->right);
    }

    return size;
}

/*
 * This function should return the total number of elements stored in a given
 * BST.
 *
 * Params:
 *   bst - the BST whose elements are to be counted.  May not be NULL.
 */
int bst_size(struct bst* bst) {
    if (bst) {
        int size = 0;

        if (bst->root != NULL) {
            size = bst_count(bst->root);
        }

        return size;
    }
    else {
        printf("No bst to check size\n");
    }
}

// Helper function for generating node
struct bst_node* bst_node_create(int key, void* value) {
    struct bst_node* node = malloc(sizeof(struct bst_node));
    node->key = key;
    node->value = value;
    node->left = NULL;
    node->right = NULL;
  
    return node;
}


// Helper function for inserting into subtree
struct bst_node* bst_node_insert(struct bst_node* bst_node, int key, void* value) {

    struct bst_node* curr = bst_node;

    if (curr == NULL) {
        return bst_node_create(key, value);
    }
    else if(key < curr->key){
        curr->left = bst_node_insert(curr->left, key, value);

    } 
    else {  
        curr->right = bst_node_insert(curr->right, key, value);

    }

  return curr;
}

/*
 * This function should insert a new key/value pair into the BST.  The key
 * should be used to order the key/value pair with respect to the other data
 * stored in the BST.  The value should be stored along with the key, once the
 * right location in the tree is found.
 *
 * Params:
 *   bst - the BST into which a new key/value pair is to be inserted.  May not
 *     be NULL.
 *   key - an integer value that should be used to order the key/value pair
 *     being inserted with respect to the other data in the BST.
 *   value - the value being inserted into the BST.  This should be stored in
 *     the BST alongside the key.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void bst_insert(struct bst* bst, int key, void* value) {
    if (bst) {
        bst->root = bst_node_insert(bst->root, key, value);
    }
    else {
        printf("No bst to insert value\n");
    }
  return;
}
// Helper function for finding minimum value

int bst_node_minval(struct bst_node* bst_node) {
    struct bst_node* curr = bst_node;

    while (curr->left != NULL) {
        curr = curr->left;
    }
    
    return curr->key;
}


// Helper function for deleting a node
struct bst_node* bst_node_remove(struct bst_node* bst_node, int key) {

    struct bst_node* curr = bst_node;

    if (curr == NULL) {
        return NULL;
    }
 
    if (curr->key < key) {
        curr->right = bst_node_remove(curr->right, key);
    }
    else if (curr->key > key) {
        curr->left = bst_node_remove(curr->left, key);
    }
    else {
        if (curr->left == NULL && curr->right == NULL) {
            free(curr);
            return NULL;
        }
        else if (curr->left == NULL || curr->right == NULL) {
            struct bst_node* temp;

            if (curr->left == NULL) {
                temp = curr->right;
            }
            else {
                temp = curr->left;
            }
            free(curr);
            return temp;
        }
        else {
            curr->key = bst_node_minval(curr->right);
            curr->right = bst_node_remove(curr->right, curr->key);
        }
    }
    return curr;
    
}

/*
 * This function should remove a key/value pair with a specified key from a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should remove the first one it encounters (i.e. the one closest to
 * the root of the tree).
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair to be removed from the BST.
 */
void bst_remove(struct bst* bst, int key) {
    if (bst) {
        bst->root = bst_node_remove(bst->root, key);
    }
    else {
        printf("No bst to remove key\n");
    }
  return;
}



/*
 * This function should return the value associated with a specified key in a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should return the first one it encounters (i.e. the one closest to
 * the root of the tree).  If the BST does not contain the specified key, this
 * function should return NULL.
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair whose value is to be returned.
 *
 * Return:
 *   Should return the value associated with the key `key` in `bst` or NULL,
 *   if the key `key` was not found in `bst`.
 */
void* bst_get(struct bst* bst, int key) {
    if (bst) {
        struct bst_node* curr = bst->root;

        while (curr != NULL) {
            if (curr->key == key) {
                return curr->value;
            }
            else if (key < curr->key) {
                curr = curr->left;
            }
            else {
                curr = curr->right;
            }
        }
    }
    else {
        printf("No bst to get\n");
    }
    return NULL;
}

/*****************************************************************************
 **
 ** BST puzzle functions
 **
 *****************************************************************************/

// Helper function for counting height
int bst_count_height(struct bst_node* bst_node) {
    struct bst_node* curr = bst_node;

    if (curr == NULL) {
        return -1;
    }
    
    int left = bst_count_height(curr->left);
    int right = bst_count_height(curr->right);
        
    if (left > right) {
        return left + 1;
    }
    else {
         return right + 1;
    }
}
/*
 * This function should return the height of a given BST, which is the maximum
 * depth of any node in the tree (i.e. the number of edges in the path from
 * the root to that node).  Note that the height of an empty tree is -1 by
 * convention.
 *
 * Params:
 *   bst - the BST whose height is to be computed
 *
 * Return:
 *   Should return the height of bst.
 */
 int bst_height(struct bst* bst) {
     if (bst) {
         
         return bst_count_height(bst->root);
     }
     else {
         printf("No bst to calculate its height\n");
     }
 }

 // Helper function for finding path sum
 int bst_has_path_sum(struct bst_node* bst_node, int sum) {
     
     struct bst_node* curr = bst_node;

     if (curr == NULL) {
         return 0;
     } 
     
     if (curr->left == NULL && curr->right == NULL) {
         if (sum == curr->key) {
             return 1;
         }
         else {
             return 0;
         }
     }
     return (bst_has_path_sum(curr->left, sum-curr->key)||bst_has_path_sum(curr->right, sum-curr->key));
     
}

/*
 * This function should determine whether a specified value is a valid path
 * sum within a given BST.  In other words, this function should check whether
 * the given BST contains any path from the root to a leaf in which the keys
 * sum to the specified value.
 *
 * Params:
 *   bst - the BST whose paths sums to search
 *   sum - the value to search for among the path sums of `bst`
 *
 * Return:
 *   Should return 1 if `bst` contains any path from the root to a leaf in
 *   which the keys add up to `sum`.  Should return 0 otherwise.
 */
int bst_path_sum(struct bst* bst, int sum) {
    if (bst) {

        return bst_has_path_sum(bst->root, sum);
    }
    else {
        printf("No bst to sum\n");
    }
}
int bst_cal_range_sum(struct bst_node* bst_node,int* sm, int lower, int upper) {
    
    struct bst_node* curr = bst_node;

    if (curr != NULL){
      if(curr->key >= lower && curr->key <= upper){
        (*sm) += curr->key;
      }
      bst_cal_range_sum(curr->left, sm, lower, upper);
      bst_cal_range_sum(curr->right, sm, lower, upper);
    }
    
}

/*
 * This function should compute a range sum in a given BST.  Specifically, it
 * should compute the sum of all keys in the BST between a given lower bound
 * and a given upper bound.  For full credit, you should not process any subtree
 * whose keys cannot be included in the range sum.
 *
 * Params:
 *   bst - the BST within which to compute a range sum
 *   lower - the lower bound of the range over which to compute a sum; this
 *     should be considered an *inclusive* bound; in other words a key that's
 *     equal to this bound should be included in the sum
 *   upper - the upper bound of the range over which to compute a sum; this
 *     should be considered an *inclusive* bound; in other words a key that's
 *     equal to this bound should be included in the sum
 *
 * Return:
 *   Should return the sum of all keys in `bst` between `lower` and `upper`.
 */
int bst_range_sum(struct bst* bst, int lower, int upper) {
    if (bst) {
        int s = 0;
        bst_cal_range_sum(bst->root, &s, lower, upper);
        return s;
    }
    else {
        printf("No bst to get range sum\n");
    }

}

/*****************************************************************************
 **
 ** BST iterator definition (extra credit only)
 **
 *****************************************************************************/

/*
 * Structure used to represent a binary search tree iterator.  It contains
 * only a reference to a stack to be used to implement the iterator.
 *
 * You should not modify this structure.
 */
struct bst_iterator {
  struct stack* stack;
};

/*
 * This function should allocate and initialize an iterator over a specified
 * BST and return a pointer to that iterator.
 *
 * Params:
 *   bst - the BST for over which to create an iterator.  May not be NULL.
 */
struct bst_iterator* bst_iterator_create(struct bst* bst) {
    if (bst) {
        struct bst_iterator* iter = malloc(sizeof(struct bst_iterator));
        iter->stack = stack_create();

        struct bst_node* curr = bst->root;
        while (curr != NULL) {
            stack_push(iter->stack, curr);
            curr = curr->left;
        }
        return iter;
    }
    else {
        printf("Fail to create bst\n");
    }
  
}

/*
 * This function should free all memory allocated to a given BST iterator.
 * It should NOT free any memory associated with the BST itself.  This is the
 * responsibility of the caller.
 *
 * Params:
 *   iter - the BST iterator to be destroyed.  May not be NULL.
 */
void bst_iterator_free(struct bst_iterator* iter) {
  if (iter){
    stack_free(iter->stack);
    free(iter);
  }
  else{
    printf("No iter to free\n");
  }
  return;
}

/*
 * This function should indicate whether a given BST iterator has more nodes
 * to visit.  It should specifically return 1 (true) if the iterator has at
 * least one more node to visit or 0 (false) if it does not have any more
 * nodes to visit.
 *
 * Param:
 *   iter - the BST iterator to be checked for remaining nodes to visit.  May
 *     not be NULL.
 */
int bst_iterator_has_next(struct bst_iterator* iter) {
  if(iter){
    return (!stack_isempty(iter->stack));
  }else{
    printf("No iter to check next\n");
  }
}

/*
 * This function should return both the value and key associated with the
 * current node pointed to by the specified BST iterator and advnce the
 * iterator to point to the next node in the BST (in in-order order).
 *
 * Because a function can't return two things, the key associated with the
 * current node should be returned the normal way, while its value should be
 * returned via the argument `value`.  Specifically, the argument `value`
 * is a pointer to a void pointer.  The current BST node's value (a void
 * pointer) should be stored at the address represented by `value` (i.e. by
 * dereferencing `value`).  This will look something like this:
 *
 *   *value = current_node->value;
 *
 * Parameters:
 *   iter - BST iterator.  The key and value associated with this iterator's
 *     current node should be returned, and the iterator should be updated to
 *     point to the next node in the BST (in in-order order).  May not be NULL.
 *   value - pointer at which the current BST node's value should be stored
 *     before this function returns.
 *
 * Return:
 *   This function should return the key associated with the current BST node
 *   pointed to by `iter`.
 */
int bst_iterator_next(struct bst_iterator* iter, void** value) {
  if(iter){
    struct bst_node* curr = stack_pop(iter->stack);
    if(value){
      *value = curr->value;
    }
    struct bst_node* right_side = curr->right;
    while (right_side != NULL){
      stack_push(iter->stack, right_side);
      right_side = right_side->left;
    }
    return curr->key;
    
  }else{
    printf("No iter\n");
  }
}
