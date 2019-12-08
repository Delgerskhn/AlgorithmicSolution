#include <iostream>
#include <sstream>
using namespace std;

int main()
{
    string str;
    cin >> str;
    stringstream ss(str);
    char c;
    int number;
    while (ss >> number)
    {
        cout << number << endl;
        ss >> c; //unshifting the comma into char;
    }
}