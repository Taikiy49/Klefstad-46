#include <iostream>
#include <stack>
using namespace std;

void error(string msg, char c){
    std::cout << "ERROR: " << c << " " << msg << endl;
}

bool is_balanced(string s){
    std::stack<char> bal;
    for (char c : s){
        if (c == '{' || c == '[' || c == '(' || c == '<'){
            bal.push(c);
        }
        else{
            if (c == '}' || c == ']' || c == ')' || c == '>'){
                if (bal.empty())
                    return false;

                else if ((c == '}' && bal.top() != '{') || (c == ']' && bal.top() != '[') || (c == ')' && bal.top() != '(') || (c == '>' && bal.top() != '<')){
                    return false;
                }
                else bal.pop();
            }
        }
    }
    return bal.empty();
}

void test_is_balanced()
{
}