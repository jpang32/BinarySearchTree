#include <iostream>

using namespace std;

class Node {
		

	public:
		Node(int);
		int value;
};

Node::Node (int value) {
	this->value = value;
}



int main() {

	Node* n1;
	Node n2(4);

	n1 = &n2;
	n1->value = 8;

	
	cout << n2.value << endl;

}