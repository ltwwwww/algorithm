#include "list.h"
#include <string>
#include <iostream>
using namespace std;
int main(int argc, char* argv[]){
    Node<string>* head = new Node<string>;
    head->t = "to";
    cout << head->next << endl;
    return 0;
}