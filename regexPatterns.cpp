#include <bits/stdc++.h>
using namespace std;
vector<string> split_string(string input_string)
{
    vector<string> splits;
    int space = input_string.find(" ");
    splits.push_back(input_string.substr(0, space));
    splits.push_back(input_string.substr(space + 1,
                                         input_string.size()));
    return splits;
}
int main()
{
    int N;
    cin >> N; //getting the number of input strings
    vector<string> firstNames;
    for (int N_itr = 0; N_itr < N; N_itr++)
    {
        string firstNameEmailID_temp;
        getline(cin, firstNameEmailID_temp);
        vector<string> firstNameEmailID =
            split_string(firstNameEmailID_temp);
        string firstName = firstNameEmailID[0];
        string emailID = firstNameEmailID[1];
        regex reg("([a-zA-Z0-9]{1,50}@gmail.com)");
        smatch matches;
        if (regex_search(emailID, matches, reg))
            firstNames.push_back(firstName);
    }
    sort(firstNames.begin(), firstNames.end());
    for (int i = 0; i < firstNames.size(); i++)
    {
        cout << firstNames[i] << endl;
    }
}