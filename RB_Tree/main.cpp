#include "rbTreeNode.h"
#include "rbTree.h"



int main(int argc, char* argv[]) {
    rbTree<int> *myTree = new rbTree<int>();
    myTree->InsertNode(1);
    for (int i = 2; i <= 10; ++i) {
        myTree->InsertNode(i);
    }
    myTree->print();
    myTree->deleteNode(10);
    myTree->print();
    return 0;
}
