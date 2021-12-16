#include <stack>
#include <string>
#include <iostream>
#include <cctype>

using namespace std;
//only below ten + - * /
int main(int argc, char* argv[]){
    stack<char> operations;
    stack<int> nums;
    string s;
    getline(cin, s);
    for(string::const_iterator it = s.begin(); it != s.end(); ++it){
        if(isnumber(*it)){
            nums.push(*it - '0');
        }else if((*it == ')')){
            if(operations.top() == '+'){
                operations.pop();
                int l = nums.top();
                nums.pop();
                int r = nums.top();
                nums.pop();
                nums.push( l + r );
            }else if(operations.top() == '-'){
                operations.pop();
                int l = nums.top();
                nums.pop();
                int r = nums.top();
                nums.pop();
                nums.push( r - l );
            }else if(operations.top() == '*'){
                operations.pop();
                int l = nums.top();
                nums.pop();
                int r = nums.top();
                nums.pop();
                nums.push( r * l );
            }else if(operations.top() == '/'){
                operations.pop();
                int l = nums.top();
                nums.pop();
                int r = nums.top();
                nums.pop();
                nums.push( r / l );
            }
        }else if(*it == '+' || *it == '-' || *it == '*' || *it == '/'){
            operations.push(*it);
        }
    }
    cout << nums.top() << endl;
    return 0;
}