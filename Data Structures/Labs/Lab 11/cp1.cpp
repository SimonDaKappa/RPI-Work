#include <iostream>

class Node{
public:
    Node(const int v) : value(v), left(NULL), right(NULL) {}

    int value;
    Node* left;
    Node* right;
};

bool shape_match(Node* p1, Node* p2){
    if(p1 == NULL && p2 == NULL)
        return true;
    if(p1 == NULL || p2 == NULL)
        return false;
    bool match;
    match = shape_match(p1->left, p2->left);
    if(!match) return false;
    match = shape_match(p1->right, p2->right);
    if(!match) return false;
    return true;
}

void print_tree(Node* p){
    if(p == NULL)
        return;
    std::cout << p->value << '\n';
    print_tree(p->left);
    print_tree(p->right);
}


int main(){

    // First Tree
    Node* root = new Node(5);
    root->left = new Node(7);
    root->right = new Node(13);
    root->left->left = new Node(6);
    root->left->right = new Node(11);
    root->right->right = new Node(21);

    // Second Tree

    Node *root_2 = new Node(17);
    root_2->left = new Node(9);
    root_2->right = new Node(22);
    root_2->left->left = new Node(10);
    root_2->left->right = new Node(1);
    root_2->right->right = new Node(8);

    print_tree(root);
}


