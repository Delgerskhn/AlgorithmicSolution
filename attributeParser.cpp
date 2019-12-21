#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <bits/stdc++.h>
using namespace std;

vector<string> produce(string query)
{
    int dot = query.find(".");
    string name;
    vector<string> ret;
    if (dot == -1)
    {
        name = query.substr(0, query.find("~"));
        query = query.substr(query.find("~"), query.length());
    }
    else
    {
        name = query.substr(0, query.find("."));
        query = query.substr(query.find("."), query.length());
    }
    ret.push_back(name);
    ret.push_back(query);
    return ret;
}

map<string, string> getAttr(string hl)
{
    map<string, string> attobj;
    regex reg("([\\w]+ = \"[^ ]+\")");
    smatch match;
    regex_search(hl, match, reg);
    while (regex_search(hl, match, reg))
    {
        string temp = match[0].str();
        hl = match.suffix().str();
        int ind = temp.find("=");
        string val = temp.substr(ind + 3, temp.length() - ind - 4);
        string name = temp.substr(0, ind - 1);
        attobj[name] = val;
    }
    return attobj;
}

string getName(string tag)
{
    string name;
    int ind = tag.find(" ");
    if (tag[1] == '/')
        name = tag.substr(2, tag.length() - 3);
    else if (ind == -1)
        name = tag.substr(1, tag.length() - 2);
    else
        name = tag.substr(1, ind - 1);
    return name;
}

class Tag
{
public:
    string name;
    map<string, string> attr;
    map<string, Tag *> nodes;
    Tag(string name, map<string, string> *attr)
    {
        this->name = name;
        this->attr = *attr;
    };
    void setNodes(Tag *node)
    {
        this->nodes[node->name] = node;
    };
    string get(string query)
    {
        int dot = query.find(".");
        if (dot == -1)
        {
            return this->attr[query.substr(1, query.length() - 1)];
        }
        else
        {
            query = query.substr(1, query.length() - 1);
            vector<string> produced = produce(query);
            string name = produced[0];
            query = produced[1];
            if (this->nodes.find(name) == this->nodes.end())
                return "Not Found!";
            else
                return this->nodes[name]->get(query);
        }
    }
};

int main()
{
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int n, q;
    cin >> n >> q;
    cin.ignore();

    vector<Tag *> stack;
    map<string, Tag *> parentNode;

    for (int i = 0; i < n; i++)
    {
        string tag;
        getline(cin, tag);
        map<string, string> attr = getAttr(tag);
        string name = getName(tag);
        Tag *temp;
        if (tag[1] != '/')
            temp = new Tag(name, &attr);
        if (stack.size() > 0 && stack[stack.size() - 1]->name == name)
            stack.pop_back();
        else
        {
            if (stack.size() > 0)
                stack[stack.size() - 1]->setNodes(temp);
            stack.push_back(temp);
            if (stack.size() == 1)
                parentNode[name] = temp;
        }
    }

    for (int i = 0; i < q; i++)
    {
        string query;
        getline(cin, query);
        vector<string> produced = produce(query);
        string pName = produced[0];
        query = produced[1];
        string result;
        if (parentNode.find(pName) == parentNode.end())
            result = "";
        else
            result = parentNode[pName]->get(query);
        if (result.length())
            cout << result << endl;
        else
            cout << "Not Found!" << endl;
    }

    return 0;
}
