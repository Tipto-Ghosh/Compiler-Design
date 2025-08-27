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

    size_t start = s.find_first_not_of(" \t\r\n");

    size_t end = s.find_last_not_of(" \t\r\n");

    if(start == string::npos) return "";

    return s.substr(start, end - start + 1);

}
 
bool isAlpha(char ch) {

    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');

}
 
bool isDigit(char c) {

    return (c >= '0' && c <= '9');

}
 
bool isAlphaNumeric(string s) {

    if(s.empty()) return false;

    if(!(isAlpha(s[0]) || s[0] == '_')) return false;

    for(int i = 1; i < (int)s.size(); i++) {

        if(!(isAlpha(s[i]) || isDigit(s[i]) || s[i] == '_')) return false;

    }

    return true;

}
 
bool isKeywords(string word) {

    vector<string> keys = {"void","int","float","main","double","string","const","bool","char","return"};

    for(string key : keys) if(word == key) return true;

    return false;

}
 
bool isIdentifier(string s) {

    return isAlphaNumeric(s) && !isKeywords(s);

}
 
bool isValidParameter(string &p) {

    if(p.empty()) return false;

    stringstream ss(p);

    string data_type, variable_name;

    ss >> data_type >> variable_name;

    if(data_type.empty()) return false;

    if(!isKeywords(data_type)) return false;

    if(variable_name.empty()) return true;

    return isIdentifier(variable_name);

}
 
void analyzeFunction(string &line) {

    string s = trim_space(line);

    if(s.empty()) return;

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

    if(!isKeywords(returnType)) {

        cout << s << " -> invalid return type" << endl;

        return;

    }

    if(!isIdentifier(funcName)) {

        cout << s << " -> invalid function name" << endl;

        return;

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

    } else if(after_parenthesis.find(';') != string::npos) {

        cout << s << " -> contains declaration but no definition" << endl;

    } else {

        cout << s << " -> invalid declaration" << endl;

    }

}
 
bool looksLikeFunctionStart(const string &line) {

    string s = trim_space(line);

    if(s.empty()) return false;

    stringstream ss(s);

    string firstWord;

    ss >> firstWord;

    return isKeywords(firstWord);

}
 
int main() {

    ifstream infile("input.txt");

    if(!infile.is_open()) return 0;
 
    string line, content;

    bool in_multiline_comment = false;
 
    while(getline(infile, line)) {

        string trimmed = trim_space(line);

        if(trimmed.empty()) continue;
 

        if(in_multiline_comment) {

            size_t endComment = trimmed.find("*/");

            if(endComment != string::npos) {

                trimmed = trimmed.substr(endComment + 2);

                in_multiline_comment = false;

                trimmed = trim_space(trimmed);

                if(trimmed.empty()) continue;

            } else continue;

        }
 
        size_t startComment = trimmed.find("/*");

        size_t lineComment = trimmed.find("//");
 
        if(startComment != string::npos && (lineComment == string::npos || startComment < lineComment)) {

            in_multiline_comment = true;

            trimmed = trimmed.substr(0, startComment);

            trimmed = trim_space(trimmed);

            if(trimmed.empty()) continue;

        }
 
        if(lineComment != string::npos) {

            trimmed = trimmed.substr(0, lineComment);

            trimmed = trim_space(trimmed);

            if(trimmed.empty()) continue;

        }
 
        if(!content.empty() && looksLikeFunctionStart(trimmed)) {

            analyzeFunction(content);

            content.clear();

        }
 
        content += trimmed + " ";
 
        if(trimmed.find('}') != string::npos || trimmed.find(';') != string::npos) {

            analyzeFunction(content);

            content.clear();

        }

    }
 
    if(!content.empty()) analyzeFunction(content);
 
    infile.close();

    return 0;

}
 
 