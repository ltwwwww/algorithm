#include "stack.h"
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::cin;
using std::string;

int main(int argc, char* argv[]){
    Stack<string> s(2);
    string str;
    while (cin >> str)
    {
        if(str != "-") s.push(str);
        else if(!s.isEmpty()) cout << s.pop() +  " " << endl;
    }
    cout << "(" << s.size() << " left on stack)" << endl;
    return 0;
}