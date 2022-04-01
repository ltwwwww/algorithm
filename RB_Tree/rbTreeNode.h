#pragma once
template <typename T>
class rbTreeNode{
public:
    rbTreeNode(T);
    ~rbTreeNode();
    rbTreeNode* leftChild;
    rbTreeNode* rightChild;
    rbTreeNode* fatherNode;
    T data;
    int color_tag; //1 red 0 black
};


template <typename T>
rbTreeNode<T>::rbTreeNode(T dataIn):leftChild(nullptr), rightChild(nullptr),\
                                     fatherNode(nullptr), data(dataIn), color_tag(0){
    data = dataIn;
    color_tag = 1; // default is red
}

template <typename T>
rbTreeNode<T>::~rbTreeNode() {
    
}