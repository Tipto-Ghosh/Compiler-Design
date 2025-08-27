#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <stack>
#include <queue>
#include <deque>
#include <list>
#include <bitset>
#include <utility>
#include <limits>
#include <iomanip>
#include <numeric>
#include <functional>
#include <cassert>
#include <tuple>
#include <sstream>
#include <fstream>
using namespace std;

string trim_space(const string &s) {
    size_t start = s.find_first_not_of(" \t\n\r");
    if(start == string::npos) return "";
    size_t end = s.find_last_not_of(" \t\n\r");
    return s.substr(start, end - start + 1);
}

bool isKeywords(const string &s) {
    vector<string> keywords = {"int","float","double","char","void","long","short","bool"};
    return find(keywords.begin(), keywords.end(), s) != keywords.end();
}

bool isIdentifier(const string &s) {
    if(s.empty() || (!isalpha(s[0]) && s[0] != '_')) return false;
    for(char c : s) {
        if(!isalnum(c) && c != '_') return false;
    }
    return true;
}

bool isValidParameter(const string &param) {
    stringstream ss(param);
    string type, name;
    ss >> type >> name;
    if(!isKeywords(type)) return false;
    if(name.empty()) return true;
    return isIdentifier(name);
}

string removeComments(string s) {
    bool singleLine = false;
    bool multiLine = false;
    string res;
    for(size_t i = 0; i < s.size(); i++) {
        if(!multiLine && i+1 < s.size() && s[i] == '/' && s[i+1] == '/') {
            break;
        }
        if(!multiLine && i+1 < s.size() && s[i] == '/' && s[i+1] == '*') {
            multiLine = true;
            i++;
            continue;
        }
        if(multiLine && i+1 < s.size() && s[i] == '*' && s[i+1] == '/') {
            multiLine = false;
            i++;
            continue;
        }
        if(!multiLine) res += s[i];
    }
    return trim_space(res);
}


void analyzeFunction(string &line) {
    string s = trim_space(line);
    size_t open_parenthesis = s.find('(');
    size_t close_parenthesis = s.find(')');
    if(open_parenthesis == string::npos || close_parenthesis == string::npos || close_parenthesis < open_parenthesis) {
        cout << s << " -> invalid declaration" << endl;
        return;
    }
    string before_parenthesis = trim_space(s.substr(0, open_parenthesis));
    string after_parenthesis = trim_space(s.substr(close_parenthesis + 1));
    string params = trim_space(s.substr(open_parenthesis + 1, close_parenthesis - open_parenthesis - 1));
    stringstream ss(before_parenthesis);
    string returnType, funcName;
    ss >> returnType >> funcName;
    if(returnType.empty() || funcName.empty()) {
        cout << s << " -> invalid declaration" << endl;
        return;
    }
    if (!isKeywords(returnType)) {
        cout << s << " -> invalid return type" << endl;
        return;
    }
    if(!isIdentifier(funcName)) {
        cout << s << " -> invalid function name" << endl;
        return;
    }
    if (params.empty() && returnType != "void") {
        if (after_parenthesis == ";") {
            cout << s << " -> contains declaration but no definition" << endl;
            return;
        } else {
            cout << s << " -> invalid declaration (non-void function without params)" << endl;
            return;
        }
    }
    if(!params.empty()) {
        stringstream pss(params);
        string param;
        while(getline(pss, param, ',')) {
            param = trim_space(param);
            if(!isValidParameter(param)) {
                cout << s << " -> invalid param" << endl;
                return;
            }
        }
    }
    if(after_parenthesis.find('{') != string::npos && after_parenthesis.find('}') != string::npos) {
        cout << s << " -> contains declaration and definition" << endl;
    }
    else if(after_parenthesis == ";") {
        cout << s << " -> contains declaration but no definition" << endl;
    }
    else {
        cout << s << " -> invalid declaration" << endl;
    }
}


int main() {
    ifstream infile("input.txt");
    if(infile.is_open() == false) {
        cout << "No file" << endl;
        return 0;
    }
    bool insideFunc = false;
    string line, content;
    while(getline(infile, line)) {
        content += line + " ";
        if(content.find('{') != string::npos) insideFunc = true;
        if(insideFunc) {
            if(line.find('}') != string::npos) {
                analyzeFunction(content);
                content.clear();
                insideFunc = false;
            }
        }
        else {
            if(line.find(';') != string::npos || line.find(')') != string::npos) {
                analyzeFunction(content);
                content.clear();
            }
        }
    }
    if(!content.empty()) analyzeFunction(content);
    infile.close();
    return 0;
}
