#pragma once
#include "rbTreeNode.h"
#include <vector>
#include <stack>
#include <string>
#include <unordered_map>
#include <queue>
#include <iostream>
template <typename T>
class rbTree{
public:
    rbTree(T rootData);
    rbTree();
    ~rbTree();
    void leftRotate(rbTreeNode<T>*);
    void rightRotate(rbTreeNode<T>*);
    void InsertNode(T);
    int deleteNode(T);
    void fixTree(rbTreeNode<T>*);
    void fixTreeDelete(rbTreeNode<T>*);
    rbTreeNode<T>* findSuccessorNode(rbTreeNode<T>*);
    rbTreeNode<T>* rootNode;
    std::vector<rbTreeNode<T>*> inorderTraversal();
    void print();
};


template <typename T>
rbTree<T>::rbTree(T dataIn) : rootNode(nullptr) {
    if (rootNode == nullptr) {
        rootNode = new rbTreeNode<T>(dataIn);
        rootNode->color_tag = 0;
    }
}

template <typename T>
rbTree<T>::rbTree() : rootNode(nullptr) {

}


template <typename T>
rbTree<T>::~rbTree() {

}

// insert a node to rbTree
template <typename T>
void rbTree<T>::InsertNode(T val) {
    rbTreeNode<T>* tempNode = rootNode;
    if (tempNode == nullptr) { // empty tree
        rootNode = new rbTreeNode<T>(val);
        rootNode->leftChild = new rbTreeNode<T>(-1);
        rootNode->leftChild->color_tag = 0;
        rootNode->leftChild->fatherNode = rootNode;
        rootNode->rightChild = new rbTreeNode<T>(-1);
        rootNode->rightChild->color_tag = 0;
        rootNode->rightChild->fatherNode = rootNode;
        rootNode->color_tag = 0;
        return;
    }
    while (tempNode != nullptr) {
        if (val > tempNode->data) {
            if (tempNode->rightChild == nullptr) {
                tempNode->rightChild = new rbTreeNode<T>(val);
                tempNode->rightChild->color_tag = 1;
                tempNode->rightChild->fatherNode = tempNode;
                if (tempNode->color_tag == 1) {
                    fixTree(tempNode->rightChild);
                }
                break;
            } else {
                tempNode = tempNode->rightChild;
            }
        } else {
            if (tempNode->leftChild == nullptr) {
                tempNode->leftChild = new rbTreeNode<T>(val);
                tempNode->leftChild->color_tag = 1;
                tempNode->leftChild->fatherNode = tempNode;
                if (tempNode->color_tag == 1) {
                    fixTree(tempNode->leftChild);
                } 
                break;
            } else {
                tempNode = tempNode->leftChild;
            }
        }
    }
}

template <typename T>
int rbTree<T>::deleteNode(T valDelete) {
    rbTreeNode<T> *tempNode = rootNode;
    while (tempNode->data != valDelete && tempNode != nullptr) {
        if (valDelete > tempNode->data) {
            tempNode = tempNode->rightChild;
        } else {
            tempNode = tempNode->leftChild;
        }
    }
    // not find the val to delete
    if (!tempNode) {
        return -1;
    }
    int colorTag = tempNode->color_tag;
    rbTreeNode<T> *fixPos = nullptr;
    if (tempNode->leftChild == nullptr && tempNode->rightChild == nullptr) {
        delete tempNode;
        return 1;
    } else if (tempNode->leftChild == nullptr && tempNode->rightChild != nullptr) {
        fixPos = tempNode->rightChild;
        if (tempNode != rootNode) {
            if (tempNode->fatherNode->leftChild == tempNode) {
                tempNode->fatherNode->leftChild = tempNode->rightChild;
                tempNode->rightChild->fatherNode = tempNode->fatherNode;
            } else {
                tempNode->fatherNode->rightChild = tempNode->rightChild;
                tempNode->rightChild->fatherNode = tempNode->fatherNode;
            }
        } else {
            rootNode = tempNode->rightChild;
            tempNode->rightChild->fatherNode = nullptr;
        }
    } else if (tempNode->leftChild != nullptr && tempNode->rightChild == nullptr) {
        fixPos = tempNode->leftChild;
        if (tempNode != rootNode) {
            if (tempNode->fatherNode->leftChild == tempNode) {
                tempNode->fatherNode->leftChild = tempNode->leftChild;
                tempNode->leftChild->fatherNode = tempNode->fatherNode;
            } else {
                tempNode->fatherNode->rightChild = tempNode->leftChild;
                tempNode->leftChild->fatherNode = tempNode->fatherNode;
            }
        } else {
            rootNode = tempNode->leftChild;
            tempNode->leftChild->fatherNode = nullptr;
        }
    } else if (tempNode->leftChild != nullptr && tempNode->rightChild != nullptr) {
        
        if (tempNode != rootNode) {
            rbTreeNode<T> *succNode = findSuccessorNode(tempNode);
            fixPos = succNode->rightChild;
            colorTag = succNode->color_tag;

            if (succNode->fatherNode == tempNode) {
                if (tempNode == tempNode->fatherNode->leftChild) {
                    tempNode->fatherNode->leftChild = succNode;

                    succNode->leftChild = tempNode->leftChild;
                    succNode->leftChild->fatherNode = succNode;

                    succNode->fatherNode = tempNode->fatherNode;
                    succNode->color_tag = tempNode->color_tag;
                } else {
                    tempNode->fatherNode->rightChild = succNode;

                    succNode->leftChild = tempNode->leftChild;
                    succNode->leftChild->fatherNode = succNode;

                    succNode->fatherNode = tempNode->fatherNode;
                    succNode->color_tag = tempNode->color_tag;
                }
            } else {
                if (succNode->rightChild) {
                    succNode->fatherNode->leftChild = succNode->rightChild;
                    succNode->rightChild->fatherNode = succNode->fatherNode;
                }
                if (tempNode == tempNode->fatherNode->leftChild) {
                    tempNode->fatherNode->leftChild = succNode;

                    succNode->rightChild = tempNode->rightChild;
                    succNode->rightChild->fatherNode = succNode;

                    succNode->leftChild = tempNode->leftChild;
                    succNode->leftChild->fatherNode = succNode;

                    succNode->fatherNode = tempNode->fatherNode;
                    succNode->color_tag = tempNode->color_tag;
                } else {
                    tempNode->fatherNode->rightChild = succNode;

                    succNode->rightChild = tempNode->rightChild;
                    succNode->rightChild->fatherNode = succNode;

                    succNode->leftChild = tempNode->leftChild;
                    succNode->leftChild->fatherNode = succNode;

                    succNode->fatherNode = tempNode->fatherNode;
                    succNode->color_tag = tempNode->color_tag;
                }
            }
            
        } else {
            rbTreeNode<T> *succNode = findSuccessorNode(tempNode);
            fixPos = succNode->rightChild;
            colorTag = succNode->color_tag;

            if (succNode->fatherNode == tempNode) { 
                succNode->leftChild = tempNode->leftChild;
                succNode->leftChild->fatherNode = succNode;

                succNode->fatherNode = nullptr;
                rootNode = succNode;

                succNode->color_tag = tempNode->color_tag;     
            } else {
                if (succNode->rightChild) {
                    succNode->fatherNode->leftChild = succNode->rightChild;
                    succNode->rightChild->fatherNode = succNode->fatherNode;
                }    
                succNode->leftChild = tempNode->leftChild;
                succNode->leftChild->fatherNode = succNode;

                succNode->rightChild = tempNode->rightChild;
                succNode->rightChild->fatherNode = succNode;

                succNode->fatherNode = nullptr;
                rootNode = succNode;

                succNode->color_tag = tempNode->color_tag; 
            }       
        }
  
    }
    if (colorTag == 0) {
        fixTreeDelete(fixPos);
    }
    return -1;
} 

template <typename T>
void rbTree<T>::fixTree(rbTreeNode<T> *curNode) {
    rbTreeNode<T>* tempCurNode = curNode;
    rbTreeNode<T>* uncleNode;
    rbTreeNode<T>* fatherNode;
    rbTreeNode<T>* grandFatherNode;
    while (tempCurNode->fatherNode && tempCurNode->fatherNode->color_tag == 1) {
        grandFatherNode = tempCurNode->fatherNode->fatherNode;
        if (tempCurNode->fatherNode == grandFatherNode->leftChild) {
            uncleNode = grandFatherNode->rightChild;
            if (uncleNode && uncleNode->color_tag == 1) {
                tempCurNode->fatherNode->color_tag = 0;
                uncleNode->color_tag = 0;
                grandFatherNode->color_tag = 1;
                tempCurNode = grandFatherNode;
            } else {
                if (tempCurNode == tempCurNode->fatherNode->rightChild) {
                    tempCurNode = tempCurNode->fatherNode;
                    leftRotate(tempCurNode);
                }
                tempCurNode->fatherNode->color_tag = 0;
                tempCurNode->fatherNode->fatherNode->color_tag = 1;
                rightRotate(tempCurNode->fatherNode->fatherNode);
            }
        } else {
            uncleNode = grandFatherNode->leftChild;
            if (uncleNode && uncleNode->color_tag == 1) {
                tempCurNode->fatherNode->color_tag = 0;
                uncleNode->color_tag = 0;
                grandFatherNode->color_tag = 1;
                tempCurNode = grandFatherNode;
            } else {
                if (tempCurNode == tempCurNode->fatherNode->leftChild) {
                    tempCurNode = tempCurNode->fatherNode;
                    rightRotate(tempCurNode);
                }
                tempCurNode->fatherNode->color_tag = 0;
                tempCurNode->fatherNode->fatherNode->color_tag = 1;
                leftRotate(tempCurNode->fatherNode->fatherNode);
            }
        }
    }
    rootNode->color_tag = 0;
    // while (true) {
    //     if (tempCurNode->fatherNode == nullptr) {
    //         break;
    //     }
    //     if (tempCurNode->fatherNode->color_tag == 1) {
    //         break;
    //     }
    //     rbTreeNode<T> *fatherNode = tempCurNode->fatherNode;
    //     rbTreeNode<T> *grandFatherNode = fatherNode->fatherNode;
    //     if (grandFatherNode) {
    //         if (fatherNode == grandFatherNode->leftChild) {
    //             uncleNode = grandFatherNode->rightChild;
    //             if (uncleNode) {
    //                 // sitution 1 father and uncle is red, recoler them and grandfather(only when grandfather is not root)
    //                 if (uncleNode->color_tag == 1) {
    //                     uncleNode->color_tag = 0;
    //                     fatherNode->color_tag = 0;
    //                     if (grandFatherNode != rootNode) {
    //                         grandFatherNode = 1;
    //                     } else {
    //                         break;
    //                     }
    //                     tempCurNode = grandFatherNode;
    //                 }
    //             } else if (tempCurNode == fatherNode->rightChild) {
    //                 // 叔叔是黑色节点，当前节点为右孩子，左旋，父节点作为当前节点
    //             }
    //         }
    //     }
    // }
}

template <typename T>
void rbTree<T>::fixTreeDelete(rbTreeNode<T>* curNode) {
    while (curNode != rootNode && curNode->color_tag == 0) {
        if (curNode == curNode->fatherNode->leftChild) {
            rbTreeNode<T> *brotherNode = curNode->fatherNode->rightChild;
            if (brotherNode->color_tag == 1) {
                brotherNode->color_tag = 0;
                curNode->fatherNode->color_tag = 1;
                leftRotate(curNode->fatherNode);
                brotherNode = curNode->fatherNode->rightChild;
            }
            if (brotherNode->leftChild->color_tag == 0 && brotherNode->rightChild->color_tag == 0) {
                brotherNode->color_tag = 1;
                curNode = curNode->fatherNode;
                continue;
            } else if (brotherNode->rightChild->color_tag == 0) { // brother's right is black
                brotherNode->leftChild->color_tag = 0;
                brotherNode->color_tag = 1;
                rightRotate(brotherNode);
                brotherNode = curNode->fatherNode->rightChild;
            }
            brotherNode->color_tag = curNode->fatherNode->color_tag;
            curNode->fatherNode->color_tag = 0;
            brotherNode->rightChild->color_tag = 0;
            leftRotate(curNode->fatherNode);
            curNode = rootNode;
        } else {
            rbTreeNode<T> *brotherNode = curNode->fatherNode->leftChild;
            if (brotherNode->color_tag == 1) {
                brotherNode->color_tag = 0;
                curNode->fatherNode->color_tag = 1;
                rightRotate(curNode->fatherNode);
                brotherNode = curNode->fatherNode->leftChild;
            }
            if (brotherNode->rightChild->color_tag == 0 && brotherNode->leftChild->color_tag == 0) {
                brotherNode->color_tag = 1;
                curNode = curNode->fatherNode;
                continue;
            } else if (brotherNode->leftChild->color_tag == 0) { // brother's right is black
                brotherNode->rightChild->color_tag = 0;
                brotherNode->color_tag = 1;
                leftRotate(brotherNode);
                brotherNode = curNode->fatherNode->leftChild;
            }
            brotherNode->color_tag = curNode->fatherNode->color_tag;
            curNode->fatherNode->color_tag = 0;
            brotherNode->leftChild->color_tag = 0;
            rightRotate(curNode->fatherNode);
            curNode = rootNode;
        }
    }
    curNode->color_tag = 0;
}

template <typename T>
void rbTree<T>::leftRotate(rbTreeNode<T> *curNode) {
    rbTreeNode<T>* rightChild = curNode->rightChild;
    rbTreeNode<T>* fatherNode = curNode->fatherNode;
    curNode->rightChild = rightChild->leftChild;
    if (curNode->rightChild)
        curNode->rightChild->fatherNode = curNode;

    rightChild->fatherNode = fatherNode;
    if (fatherNode == nullptr) {
        rootNode = rightChild;
    } else if (curNode == fatherNode->leftChild) {
        fatherNode->leftChild = rightChild;
    } else {
        fatherNode->rightChild = rightChild;
    }
    rightChild->leftChild = curNode;
    curNode->fatherNode = rightChild;
}

template <typename T>
void rbTree<T>::rightRotate(rbTreeNode<T> *curNode) {
    rbTreeNode<T> *fatherNode = curNode->fatherNode;
    rbTreeNode<T> *leftChild = curNode->leftChild;
    curNode->leftChild = leftChild->rightChild;
    if (curNode->leftChild)
        curNode->leftChild->fatherNode = curNode;

    leftChild->rightChild = curNode;
    if (fatherNode == nullptr) {
        rootNode = leftChild;
    } else if (curNode == fatherNode->leftChild) {
        fatherNode->leftChild = leftChild;
    } else {
        fatherNode->rightChild = leftChild;
    }
    curNode->fatherNode = leftChild;
    leftChild->fatherNode = fatherNode;
}

template <typename T>
rbTreeNode<T>* rbTree<T>::findSuccessorNode(rbTreeNode<T>* curNode) {
    rbTreeNode<T> *tempNode = curNode->rightChild;
    while (tempNode->leftChild != nullptr) {
        tempNode = tempNode->leftChild;
    }
    return tempNode;
}

template <typename T>
std::vector<rbTreeNode<T>*> rbTree<T>::inorderTraversal() {
    std::vector<rbTreeNode<T>*> res;
    std::stack<rbTreeNode<T>*> stk;
    rbTreeNode<T>* temp = rootNode;
    while (temp != nullptr || !stk.empty()) {
        while (temp) {
            stk.push(temp);
            temp = temp->leftChild;
        }
        temp = stk.top();
        stk.pop();
        res.push_back(temp);
        temp = temp->rightChild;
    }
    return res;
}

template <typename T>
void rbTree<T>::print() {
    if (!rootNode) return;
    auto tmp = rootNode;
    std::vector<rbTreeNode<T>*> intv = inorderTraversal();
    std::string template_str;
    int location = 0;
    std::unordered_map<rbTreeNode<T>*, int> first_locations;
    for (auto &i : intv) {
        location = template_str.size();
        template_str += std::to_string(i->data) + " ";
        first_locations[i] = location;
    }
    for (auto &i : template_str) i = ' ';
    std::queue<rbTreeNode<T>* > q;
    q.push(rootNode);
    while (!q.empty()) {
        int curLevelSize = q.size();
        int cur_loc = 0;
        std::string tmp_str1 = template_str, tmp_str2 = template_str;
        for (int i = 1; i <= curLevelSize; ++i) {
            auto node = q.front();
            q.pop();
            cur_loc = first_locations[node];
            std::string num_str = std::to_string(node->data);
            //左边，如果存在左孩子，那么在第二行对应位置打印'/'，在第一行补上'_'
            if (node->leftChild) {
                q.push(node->leftChild);
                int first_loc = first_locations[node->leftChild] + 1;
                tmp_str2[first_loc++] = '/';
                while (first_loc < cur_loc)tmp_str1[first_loc++] = '_';
            }
            //中间,对应位置打印节点值（有可能为多位数）
            for (int j = 0; j < num_str.length(); ++j, ++cur_loc) {
                tmp_str1[cur_loc] = num_str[j];
            }
            //右边，如果存在右孩子，那么在第二行对应位置打印'\'，在第一行补上'_'
            if (node->rightChild) {
                q.push(node->rightChild);
                int last_loc = first_locations[node->rightChild] - 1;
                tmp_str2[last_loc] = '\\';
                while (cur_loc < last_loc) {
                    tmp_str1[cur_loc++] = '_';
                }
            }
        }
        //打印两行
        std::cout << tmp_str1 << std::endl;
        std::cout << tmp_str2 << std::endl;
    }
}