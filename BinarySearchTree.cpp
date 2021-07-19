#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>
#include <set>

using namespace std;


class Node {

    private:
        int value;

    public:
        Node(int);

        Node* left = NULL;
        Node* right = NULL;
        Node* parent = NULL;
    
        int setValue(int);
        int getValue() const;
        friend bool operator==(Node &lhs, const Node& rhs);
};

Node::Node (int value) {
    this->value = value;
}

int Node::setValue(int value) {
    this->value = value;
    return this->value;
}

int Node::getValue() const {
    return this->value;
}

bool operator==(Node &lhs, const Node& rhs) {
    return lhs.value == rhs.value;    
}


class Tree {

    private:
        int count = 0;

    public:
        Tree(Node*);
        Tree(int);

        Node* root;

        bool addIterative(Node*);
        bool addIterative(int);
        bool addRecursive(Node*, Node*);
        bool addRecursive(int);
        Node* find(int);
        Node* findBFS(int);
        Node* findDFS(int);
        friend ostream& operator<<(ostream& os, const Tree& t);

};

Tree::Tree (Node* n) {
    this->root = n;
}

Tree::Tree (int value) {

    this->root = new Node(value);

}

bool Tree::addIterative(Node* n) {
    Node* parent = root;
    Node* current = root;

    if (*n == *current) {
        cout << "Failed to add " << n->getValue() << ", as this node already exists!" << endl;
        return 0;
    }

    if (n->getValue() < parent->getValue()) {
        current = parent->left;
    } else {
        current = parent->right;
    }

    while(current != NULL) {

        if (*n == *current) {
            cout << "Failed to add " << n->getValue() << ", as this node already exists!" << endl;
            return 0;
        }
    
        if (n->getValue() < current->getValue()) {
            parent = current;
            current = parent->left;
        } else {
            parent = current;
            current = parent->right;
        }

    }

    if (n->getValue() < parent->getValue()) {
        parent->left = n;
    } else {
        parent->right = n;
    }

    this->count++;
    return 1;

}

bool Tree::addIterative(int value) {
    Node* n = new Node(value);

    return this->addIterative(n);
}

bool Tree::addRecursive(Node* n, Node* root) {

    if (*n == *root) {
        cout << "Failed to add " << n->getValue() << ", as this node already exists!" << endl;
        return 0;
    }
    
    if (n->getValue() < root->getValue()) {
        if (root->left == NULL) {
            root->left = n;
            this->count++;
            return 1;
        }
        this->addRecursive(n, root->left);
    } else {
        if (root->right == NULL) {
            root->right = n;
            this->count++;
            return 1;
        }
        this->addRecursive(n, root->right);
    }

    return 0;
 
}

bool Tree::addRecursive(int value) {
    Node* n = new Node(value);

    return this->addRecursive(n, this->root);
}

Node* Tree::find(int value) {
    
    Node* current = this->root;
    
    while(current != NULL) {
        if (current->getValue() == value) {
            return current;   
        } else if (current -> getValue() < value) {
            current = current->right;
        } else {
            current = current->left;
        }

    }

    return NULL;

}

Node* Tree::findBFS(int value) {

    Node* current = this->root;

    queue<Node*> nodeQueue;

    nodeQueue.push(current);

    while(!nodeQueue.empty()) {

        current = nodeQueue.front();
        nodeQueue.pop();
        if (value == current->getValue()) return current;

        if (current->left) nodeQueue.push(current->left);
        if (current->right) nodeQueue.push(current->right);
    }

    return NULL;

}

Node* Tree::findDFS(int value) {

    Node* current = this->root;

    stack<Node*> nodeStack;
    set<int> visited;

    nodeStack.push(current);
    visited.insert(current->getValue());

    while(!nodeStack.empty()) {

        current = nodeStack.top();
        
        if (current->left && !visited.count(current->left->getValue())) {
            nodeStack.push(current->left);
            visited.insert(current->left->getValue());
            continue;
        } else if (current->right && !visited.count(current->right->getValue())) {
            nodeStack.push(current->right);
            visited.insert(current->right->getValue());
            continue;
        }

        current = nodeStack.top();
        nodeStack.pop();
        
        if(value == current->getValue()) return current;
        
    }

    return NULL;

}

ostream& operator<<(ostream& os, const Tree& t) {

    Node* current = t.root;

    os << current->getValue();

    return os;
    
}


int main() {

    Tree* t = new Tree(4);


    t->addIterative(5);
    t->addIterative(6);
    t->addIterative(7);

    t->addRecursive(1);
    t->addRecursive(2);
    t->addRecursive(3);
    t->addRecursive(5);
    t->addRecursive(6);
    t->addRecursive(7);
    t->addRecursive(8);

    //cout << t->find(3)->getValue() << endl;
    //cout << t->findBFS(5)->getValue() << endl;
    cout << t->findDFS(7)->getValue() << endl;

    delete t;

}