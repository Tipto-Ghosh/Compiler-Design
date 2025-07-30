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



// check punctuatuins
bool isPuntuation(string s) {
    vector<char> puntuations = {';' , ',' , '(' , ')' , '{' , '}' , '[' , ']'};

    for(char c : s) {
        for(char pun : puntuations) {
            if(c == pun) {
                return true;
            }
        }
    }
    return false;
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
// check operator
bool isOperator(string s) {
   
   for(char c : s) {
      if(c == '+' || c == '-' || c == '/' || c == '*' || c == '%' || c == '=') {
        return true;
      }
   }
   
   return false;
}


// check contants
bool isConstants(string s) {
    if (s.empty()) return false;
    
    bool isInt= true;
    // int check
    for(char c : s) {
        if(!isDigit(c)) {
           isInt = false;
           break;
        }
    }
    if(isInt) {
        return true;
    }

    int countDecimalPoint = 0;

    for (char c : s) {
        if (c == '.') {
            countDecimalPoint++;
            if (countDecimalPoint > 1) return false;
        } else if (!isDigit(c)) {
            return false;
        }
    }
  
    return countDecimalPoint == 1;
}

// check indentifiers
bool isIdentifier(string s) {
    bool isValidName = isAlphaNumeric(s); 
    bool isKey = isKeywords(s);

    return (isValidName && !isKey);
}


void tokenTypes(string s) {
    // tokens types are: indentifer , puntuation , keyword , operator , constants

    if(isKeywords(s)) {
        cout << s << " -> keyword" << endl;
    }
    else if(isIdentifier(s)) {
        cout << s << " -> Identifier" << endl;
    }
    else if(isOperator(s)) {
        cout << s << " -> Operator" << endl;
    }
    else if(isPuntuation(s)) {
        cout << s << " -> Punctuation" << endl;
    }
    else if(isConstants(s)) {
        cout << s << " -> Constants" << endl;
    }
    else {
        cout << s << " -> Unknown Token" << endl;
    }
}

string trim(const string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end = s.find_last_not_of(" \t\r\n");
    if (start == string::npos) return "";
    return s.substr(start, end - start + 1);
}

void singleLineTokenization() {
    ifstream infile("tokens.txt");
    
    if(infile.is_open() == false) {
        cout << "No file" << endl;
        return;
    }

    string token;

    while(getline(infile , token)) {
        if(!token.empty())  {
            token = trim(token);
            tokenTypes(token);
        }
    }

    infile.close();

}

void multipleLineTokenization() {
    ifstream infile("tokens.txt");
    
    if(infile.is_open() == false) {
        cout << "No file" << endl;
        return;
    }

    string token;
    
    while(getline(infile , token)) {
        // split a line based on $
        int n = token.length();
        
        string curr_token;
        for(int i = 0; i < n; i++) {
            if(token[i] != '$') {
                curr_token.push_back(token[i]);
            }
            else {
                curr_token = trim(curr_token);
                tokenTypes(curr_token);
                curr_token.clear();
            }
        }

        if(curr_token.length() != 0) {
            curr_token = trim(curr_token);
            tokenTypes(curr_token);
        }
    }
}


string tokenTypes2(string s) {
    // tokens types are: indentifer , puntuation , keyword , operator , constants

    if(isKeywords(s)) {
        return "keyword";
    }
    else if(isIdentifier(s)) {
        return "Identifier";
    }
    else if(isOperator(s)) {
        return "Operator";
    }
    else if(isPuntuation(s)) {
        return "Punctuation";
    }
    else if(isConstants(s)) {
        return "Constants";
    }
    else {
        return "Unknown Token";
    }
}
// print all the tokens of a single line
void multipleLineTokenization_version_02() {
    ifstream infile("tokens.txt");
    
    if(infile.is_open() == false) {
        cout << "No file" << endl;
        return;
    }

    string token;
    
    while(getline(infile , token)) {
        // split a line based on $
        int n = token.length();
        
        vector<pair<string , string>> current_lines_all_tokens;

        string curr_token;
        for(int i = 0; i < n; i++) {
            if(token[i] != '$') {
                curr_token.push_back(token[i]);
            }
            else {
                curr_token = trim(curr_token);
                string type = tokenTypes2(curr_token);
                
                current_lines_all_tokens.push_back({curr_token , type});

                curr_token.clear();
            }
        }

        if(curr_token.length() != 0) {
            curr_token = trim(curr_token);
            string type = tokenTypes2(curr_token);
            current_lines_all_tokens.push_back({curr_token , type});
        }

        // print current lines all tokens
        for(auto val : current_lines_all_tokens) {
            cout << "[ " << val.first << " : " << val.second << " ] ";
        }
        cout << endl;
    }
}

int main(){

    // cout << "Enter tokens: ";
    
    // string line;
    // getline(cin , line);

    // stringstream ss(line);
    // string token;

    // while(ss >> token) {
    //     tokenTypes(token);
    // }

    multipleLineTokenization_version_02();

    
    return 0;
}