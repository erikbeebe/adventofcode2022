#include <cstring>
#include <deque>
#include <fstream>
#include <iostream>
#include <hash_map>
#include <locale>
#include <set>
#include <stack>
#include <string>
#include <sstream>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "utils.h"

using namespace std;

void PrintDeque(deque<char> s)
{
    if (s.empty())
        return;
    char x = s.back();
 
    s.pop_back();
    PrintDeque(s);
 
    cout << x << " ";
    s.push_back(x);
}

void PrintStack(stack<char> s)
{
    if (s.empty())
        return;
    char x = s.top();

    s.pop();
    PrintStack(s);
 
    cout << x << " ";
    s.push(x);
}
