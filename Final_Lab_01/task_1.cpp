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



// write a program that reads input from text file and check
/*
  -> proper function decleration(return type , function name , ())
  -> definition given or not {} is given or not.
*/


string trim_space(const string &s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end = s.find_last_not_of(" \t\r\n");

    if(start == string :: npos) {
        return "";
    }

    return s.substr(start , end - start + 1);
}

bool isAlpha(char ch) {
   
  for(char c = 'A'; c <= 'Z'; c++) {
     if(ch == c) {
        return true;
     }
  }

  for(char c = 'a'; c <= 'z'; c++) {
     if(ch == c) {
        return true;
     }
  }

  return false;
}

bool isDigit(char c) {
   vector<char> digits = {'0' , '1' , '2' , '3' , '4' , '5' , '6' , '7' , '8' , '9'};
   
   for(char ch : digits) {
      if(ch == c) {
         return true;
      }
   }

   return false;
}

bool isAlphaNumeric(string s) {
     
   if(!(isAlpha(s[0]) || s[0] == '_')) {
       return false;
   }     


   for(int i = 1; i < s.size(); i++) {
      if(!((isAlpha(s[i])) || (isDigit(s[i])) || (s[i] == '_'))) {
         return false;
      }
   }

   return true;
}
// check keywords
bool isKeywords(string word) {
    vector<string> keys = {"int" , "float" , "main" , "double" , "string" , "const" , "bool" , "char" , "return"};

    for(string key : keys) {
        if(word == key) {
            return true;
        }
    }

    return false;
}
// check indentifiers
bool isIdentifier(string s) {
    bool isValidName = isAlphaNumeric(s); 
    bool isKey = isKeywords(s);

    return (isValidName && !isKey);
}
bool isValidParameter(string &p) {
    if(p.empty()) {
        return false;
    }

    // 2 things datatype and variable

    stringstream ss(p);

    string data_type , variable_name;
    ss >> data_type >> variable_name;

    if(data_type.empty()) {
        return false;
    }
    if(isKeywords(data_type) == false) {
        return false;
    }
    

    if(variable_name.empty()) {
        return true;
    }
    if(isIdentifier(variable_name) == false) {
        return false;
    }

    return true;
}



void analyzeFunction(string &line) {
    string s = trim_space(line);

    // check ()
    size_t open_parenthesis = s.find('(');
    size_t close_parenthesis = s.find(')');

    if(open_parenthesis == string :: npos || close_parenthesis == string :: npos || close_parenthesis < open_parenthesis) {
        cout << s << " -> invalid decleration" << endl;
        return;
    }
    

    string before_parenthesis = trim_space(s.substr(0 , open_parenthesis));
    string after_parenthesis = trim_space(s.substr(close_parenthesis + 1));
    string params = trim_space(s.substr(open_parenthesis + 1 , close_parenthesis - open_parenthesis - 1));
    
    
    stringstream ss(before_parenthesis);
    string returnType, funcName;
    ss >> returnType >> funcName;
    
    if(returnType.empty() || funcName.empty()) {
        cout << s << " -> invalid decleration" << endl;
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

    // paramters
    if(!params.empty()) {
        stringstream pss(params);

        string param;
        while(getline(pss , param , ',')) {
            param = trim_space(param);

            if(!isValidParameter(param)) {
                cout << s << " -> invalid param" << endl;
                return;
            }
        }
    }

    // definition
    if(after_parenthesis.find('{') != string :: npos && after_parenthesis.find('}')) {
        cout << s << " -> have declaration and definition" << endl;
    }
    else {
        cout << s << " -> have declaration but no definition" << endl;
    }

}

int main(){

    ifstream infile("input.txt");
    
    if(infile.is_open() == false) {
        cout << "No file" << endl;
        return 0;
    }
    
    bool insideFunc = false;
    string line , content;
    while(getline(infile , line)) {
        content += line + " ";

        if(content.find('{') != string :: npos) {
            insideFunc = true;
        }

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

    infile.close();

    return 0;
}