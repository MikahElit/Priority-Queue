//  @file priorityqueue.h
//  @author Muhammad Hakim
//  @date CS 251, Spring 2023.
//  @brief Project 5 - Priority Queue, University of Illinois Chicago
//  @description This project involves writing an abstraction class for a priority queue that works based on priority numbers assigned to elements.
//  The implementation involves using a custom binary search tree that handles priority ties by creating a linked list using the link node pointer.
//  The project requires implementing various functions that search, insert, remove, and access the custom BST while considering the duplicate linked list. 

/// Assignment details and provided code are created and
/// owned by Adam T Koehler, PhD - Copyright 2023.
/// University of Illinois Chicago - CS 251 Spring 2023

#pragma once

#include <iostream>
#include <sstream>
#include <set>

using namespace std;

template<typename T>
class priorityqueue {
private:
    struct NODE {
        int priority;  // used to build BST
        T value;  // stored data for the p-queue
        bool dup;  // marked true when there are duplicate priorities
        NODE* parent;  // links back to parent
        NODE* link;  // links to linked list of NODES with duplicate priorities
        NODE* left;  // links to left child
        NODE* right;  // links to right child
    };
    NODE* root;  // pointer to root node of the BST
    int size;  // # of elements in the pqueue
    NODE* curr;  // pointer to next item in pqueue (see begin and next)

    NODE* createNode(T value, int priority) {
        NODE* createdNode = new NODE();
        createdNode->priority = priority;
        createdNode->value = value;
        createdNode->parent = nullptr;
        createdNode->dup = false;
        createdNode->link = nullptr;
        createdNode->left = nullptr;
        createdNode->right = nullptr;
        return createdNode;
    }

    void inTraversal(NODE* root, ostream& ss) {
        // if the root is null, return immediately
        if (root == nullptr) {
            return;
        }
        // recursively visit the left subtree
        inTraversal(root->left, ss);
        // if the current node has duplicates, iterate through the linked list
        // and print each node's priority and value
        if (root->dup) {
            NODE* tmpNode = root;
            while (tmpNode != nullptr) {
                ss << tmpNode->priority << " value: " << tmpNode->value << endl;
                tmpNode = tmpNode->link;
            }
        }
        // otherwise, print the current node's priority and value
        else {
            ss << root->priority << " value: " << root->value << endl;
        }
        // recursively visit the right subtree
        inTraversal(root->right, ss);
    }

    // Post-order traversal of the binary search tree
    void postTraversal(NODE* root) {
        if (root == nullptr) {
            return;
        }
        // Traverse the left subtree
        postTraversal(root->left);
        // Traverse the right subtree
        postTraversal(root->right);
        // Traverse the link list
        postTraversal(root->link);
        // Delete the root node
        delete root;
    }

    bool isIdentical(NODE* root1, NODE* root2) const {
        // If both roots are null, the trees are identical.
        if (root1 == nullptr && root2 == nullptr) {
            return true;
        }
        // If one root is null and the other isn't, the trees are not identical.
        if (root1 == nullptr && root2 != nullptr) {
            return false;
        }
        // If the values of the nodes differ, the trees are not identical.
        if (root1->value != root2->value) {
            return false;
        }
        // Recursively check the left subtree, right subtree, and link list of both roots.
        return isIdentical(root1->left, root2->left) &&
            isIdentical(root1->right, root2->right) &&
            isIdentical(root1->link, root2->link);
    }

    void preTraverse(NODE* node) {
        if (node == nullptr) {
            return;
        }
        enqueue(node->value, node->priority);
        preTraverse(node->left);
        preTraverse(node->right);
        preTraverse(node->link);
    }



public:
    //
    // default constructor:
    //
    // Creates an empty priority queue.
    // O(1)
    //
    priorityqueue() {
        root = nullptr;
        size = 0;
        curr = root;
    }
    
    //
    // operator=
    //
    // Clears "this" tree and then makes a copy of the "other" tree.
    // Sets all member variables appropriately.
    // O(n), where n is total number of nodes in custom BST
    //
    priorityqueue& operator=(const priorityqueue& other) {
        this->clear();
        preTraverse(other.root);
        this->size = other.size;
        return *this;
    }
    
    //
    // clear:
    //
    // Frees the memory associated with the priority queue but is public.
    // O(n), where n is total number of nodes in custom BST
    //
    void clear() {
        postTraversal(root);
        size = 0;
        root = NULL;
    }
    
    //
    // destructor:
    //
    // Frees the memory associated with the priority queue.
    // O(n), where n is total number of nodes in custom BST
    //
    ~priorityqueue() {
        this->clear();
    }
    
    //
    // enqueue:
    //
    // Inserts the value into the custom BST in the correct location based on
    // priority.
    // O(logn + m), where n is number of unique nodes in tree and m is number 
    // of duplicate priorities
    //
    // This function inserts a new node with the given value and priority into the binary search tree.
    // If a node with the same priority already exists, the new node is added to the end of its link list.
    void enqueue(T value, int priority) {
        NODE* current = root;
        NODE* prev = nullptr;
        bool isDuplicate = false;

        // Find the correct location to insert the new node
        while (current != nullptr) {
            prev = current;
            if (current->priority > priority) {
                current = current->left;
            }
            else if (current->priority < priority) {
                current = current->right;
            }
            else {
                isDuplicate = true;
                current->dup = isDuplicate; // Set the duplicate flag of the existing node to true.
                break;
            }
        }
        // If a node with the same priority already exists, add the new node to its link list.
        if (isDuplicate) {
            NODE* lastNode = current;
            while (lastNode->link != nullptr) {
                lastNode = lastNode->link;
            }
            lastNode->link = createNode(value, priority);
            lastNode->link->parent = lastNode;
        }
        // Otherwise, insert the new node into the binary search tree.
        else {
            NODE* newNode = createNode(value, priority);
            newNode->parent = prev;

            if (prev == nullptr) {
                root = newNode;
            }
            else if (prev->priority > priority) {
                prev->left = newNode;
            }
            else {
                prev->right = newNode;
            }
        }

        size++;
    }



    //
    // dequeue:
    //
    // returns the value of the next element in the priority queue and removes
    // the element from the priority queue.
    // O(logn + m), where n is number of unique nodes in tree and m is number 
    // of duplicate priorities
    //
    T dequeue() {
    if (root == nullptr) {
        return T();
    }

    NODE* curr = root;
    NODE* parent = nullptr;

    // Find the minimum node
    while (curr->left != nullptr) {
        parent = curr;
        curr = curr->left;
    }

    T valueOut = curr->value;

    if (curr->dup == false) {
        // No duplicates, simply remove the node
        if (curr == root) {
            root = curr->right;
        } else {
            parent->left = curr->right;
        }
        if (curr->right != nullptr) {
            curr->right->parent = parent;
        }
        delete curr;
    } else {
        // There are duplicates, promote the next node in the link list
        NODE* next = curr->link;
        next->dup = curr->link->link != nullptr;
        next->parent = parent;
        next->right = curr->right;
        if (next->right != nullptr) {
            next->right->parent = next;
        }
        if (curr == root) {
            root = next;
        } else {
            parent->left = next;
        }
        delete curr;
    }

    size--;
    return valueOut;
}
    
    //
    // Size:
    //
    // Returns the # of elements in the priority queue, 0 if empty.
    // O(1)
    //
    int Size() {
        return size; // TO DO: update this return
    }
    
    //
    // begin
    //
    // Resets internal state for an inTraversal traversal.  After the
    // call to begin(), the internal state denotes the first inTraversal
    // node; this ensure that first call to next() function returns
    // the first inTraversal node value.
    //
    // O(logn), where n is number of unique nodes in tree
    //
    // Example usage:
    //    pq.begin();
    //    while (tree.next(value, priority)) {
    //      cout << priority << " value: " << value << endl;
    //    }
    //    cout << priority << " value: " << value << endl;
    void begin() {
        curr = root;
        while (curr->left != nullptr) {
            curr = curr->left;
        }
    }
    
    //
    // next
    //
    // Uses the internal state to return the next inTraversal priority, and
    // then advances the internal state in anticipation of future
    // calls.  If a value/priority are in fact returned (via the reference
    // parameter), true is also returned.
    //
    // False is returned when the internal state has reached null,
    // meaning no more values/priorities are available.  This is the end of the
    // inTraversal traversal.
    //
    // O(logn), where n is the number of unique nodes in tree
    //
    // Example usage:
    //    pq.begin();
    //    while (pq.next(value, priority)) {
    //      cout << priority << " value: " << value << endl;
    //    }
    //    cout << priority << " value: " << value << endl;
    //
    bool next(T& value, int& priority) {
        // If current node is null, return false.
        if (curr == nullptr) {
            return false;
        }

        // Store current node's value and priority.
        value = curr->value;
        priority = curr->priority;

        // If current node has a link, traverse the link and return true.
        if (curr->link != nullptr) {
            curr = curr->link;
            return true;
        }

        // Traverse up the tree until a node is found that has a right subtree or the root is reached.
        while (curr->parent != nullptr && curr->priority == curr->parent->priority) {
            curr = curr->parent;
        }

        // If current node has a right subtree, traverse down the leftmost path of the right subtree and return true.
        if (curr->right != NULL) {
            curr = curr->right;
            while (curr->left != NULL) {
                curr = curr->left;
            }
            return true;
        }
        // If current node doesn't have a right subtree, traverse up the tree until a node is found that is a left child of its parent, or the root is reached.
        while (curr->parent != nullptr) {
            if (curr->parent->left == curr) {
                curr = curr->parent;
                return true;
            }
            curr = curr->parent;
        }
        curr = nullptr;
        // If root is reached, return false.
        return false;
    }

    
    //
    // toString:
    //
    // Returns a string of the entire priority queue, in order.  Format:
    // "1 value: Ben
    //  2 value: Jen
    //  2 value: Sven
    //  3 value: Gwen"
    //
    string toString(){
        stringstream ss;
        inTraversal(root, ss);
        return ss.str();
    }
    
    //
    // peek:
    //
    // returns the value of the next element in the priority queue but does not
    // remove the item from the priority queue.
    // O(logn + m), where n is number of unique nodes in tree and m is number 
    // of duplicate priorities
    //
    T peek() {
        // Start at the root and follow the leftmost path to find the node with the
        // minimum priority.
        NODE* curr = root;
        while (curr->left != nullptr) {
            curr = curr->left;
        }
        // Return the value of the node with minimum priority.
        return curr->value;
    }

    
    //
    // ==operator
    //
    // Returns true if this priority queue as the priority queue passed in as
    // other.  Otherwise returns false.
    // O(n), where n is total number of nodes in custom BST
    //
    bool operator==(const priorityqueue& other) const {
        if (size != other.size) {
            return false;
        }
        else {
            return isIdentical(root, other.root);
        }
    }
    
    //
    // getRoot - Do not edit/change!
    //
    // Used for testing the BST.
    // return the root node for testing.
    //
    void* getRoot() {
        return root;
    }
};
