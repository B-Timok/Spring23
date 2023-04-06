/*
Name: Brandon Timok
Description: Implementation file for bintree class functions.
*/

#include <iostream>
#include "binTree.h"

// Constructor initializes root to nullptr
binTree::binTree() {
    root = nullptr;
}

// Destructor deallocates tree
binTree::~binTree() {
    deallocateTree(root);
}

// Builds the binary tree from a vector of strings
void binTree::buildTree(std::vector<std::string> locations) {
    root = buildTree(new binTreeNode(), locations, 0);
}

// Finds the longest zigzag path in the binary tree
std::vector<std::string> binTree::zigzag() {
    std::vector<std::string> path;
    std::vector<std::string> left_path;
    std::vector<std::string> right_path;

    return zigzag(root, true, path);

}

// Recursive function to build the binary tree
binTreeNode* binTree::buildTree(binTreeNode* r, std::vector<std::string> locations, int index) {
    
    if (index >= locations.size() || locations[index] == "_") {
        return nullptr;
    }

    r->location = locations[index];
    r->left = buildTree(new binTreeNode(), locations, (index * 2) + 1);
    r->right = buildTree(new binTreeNode(), locations, (index + 1) * 2);

    return r; 
}

// Recursive function to find the longest zigzag path
std::vector<std::string> binTree::zigzag(binTreeNode* r, bool is_left, std::vector<std::string> path){
    std::vector<std::string> alt_path;
    
    if (r == nullptr) {
        return path;
    }

    std::cout << "Node visited: " << r->location << ", is_left: " << is_left << '\n';   

    path.push_back(r->location);
    alt_path.push_back(r->location);

    if (is_left) {
        path = zigzag(r->right, false, path);
        alt_path = zigzag(r->left, true, alt_path);
    } else {
        path = zigzag(r->left, true, path);
        alt_path = zigzag(r->right, false, alt_path);
    }

    if (alt_path.size() < path.size()) {
        return path;
    } else {
        return alt_path;
    }
}

// Recursive function to deallocate the binary tree
void binTree::deallocateTree(binTreeNode* r){
    if (r != nullptr) {
        deallocateTree(r->left);
        deallocateTree(r->right);
        delete r;
        r = nullptr;
    }
}
