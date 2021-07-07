#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>

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

Node::Node (int v) {
    value = v;
}

int Node::setValue(int v) {
    value = v;
    return value;
}

int Node::getValue() const {
    return value;
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
        Node* findBFS(int);
        Node* findDFS(int);
        friend ostream& operator<<(ostream& os, const Tree& t);

};

Tree::Tree (Node* n) {
    root = n;
}

Tree::Tree (int value) {
    Node root(value);

    this->root = &root;
}

bool Tree::addIterative(Node* n) {
    Node* parent = root;
    Node* current = root;
    int c = 0;

    if (*n == *current) {
        cout << "Failed to add " << n->getValue() << ", as this node already exists!" << endl;
        return 0;
    }

    if (n->getValue() < parent->getValue()) {
        current = parent->left;
    } else {
        current = parent->right;
    }

    cout << parent->getValue() << endl;

    while(current != NULL) {

        cout << "iter: " << ++c << endl;

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

bool Tree::addIterative(int v) {
    Node n(v);

    return this->addIterative(&n);
}

bool Tree::addRecursive(Node* n, Node* root) {

    cout << n->getValue() << endl;

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

bool Tree::addRecursive(int v) {
    Node n(v);

    return this->addRecursive(&n, this->root);
}

Node* Tree::findBFS(int value) {

    Node* current = root;

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

    Node* current = root;

    stack<Node*> nodeStack;

    nodeStack.push(current);

    while(!nodeStack.empty()) {

        current = nodeStack.top();
        
        if (current->left) {
            nodeStack.push(current->left);
            continue;
        } else if (current->right) {
            nodeStack.push(current->right);
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

    Tree t(3);

    //t.addIterative(4);
    //t.addRecursive(7);
    //t.addIterative(5);


    Node n(3);
    Node n1(4);
    Node* p = &n1;

    cout << n.getValue() << endl;
    cout << p->getValue() << endl;
}