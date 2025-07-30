#include<iostream>
using namespace std;
#include<vector>
#include <string>

// LAb-02: Date: 23-07-25

// -------------------------------------------------
// Task -01
bool isConstant(string s) {
   vector<char> nums = {'0' , '1' , '2' , '3' , '4' , '5' , '6' , '7' , '8' , '9'};

   for(int i = 0; i < s.size(); i++){
      char c = s[i];
      bool isCons = false;

      for(char d : nums) {
        if(c == d) {
        isCons = true;
        }
      }

      if(!isCons) {
        return false;
      }
   }

   return true;
}

// ------------------------------- task-2-----------------------------------------
void isOperator(string s) {
   vector<char> operatorArr;

   for(char c : s) {
      if(c == '+' || c == '-' || c == '/' || c == '*' || c == '%' || c == '=') {
        operatorArr.push_back(c);
      }
   }
   
   // debug(operatorArr);

   for(int i = 0; i < operatorArr.size(); i++) {
      cout << "Operator" << i << " : " << operatorArr[i] << endl;
   }
}
 
// -------------------------- Task 03----------------------------
void isCommentLine() {
   // int n;
   // cin >> n;
   // cin.ignore();


   // vector<string> lines;
   //  for (int i = 0; i < n; ++i) {
   //      string line;
   //      getline(cin, line);
   //      lines.push_back(line);
   //  }

   //  for(string s : lines) {
   //     cout << s << endl;
   //  }

   string s;
   getline(cin , s);

   int n = s.size();

   if(s[0] == '/' && s[1] == '*') {
      cout << "Multi line comment" << endl;
      return;
   }
   else if(s[0] == '/' && s[1] == '/') {
      cout << "Single line comment" << endl;
   }
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


int main() {


 // task-01
   // string s;
   // cin >> s;

   // if(isConstant(s)) {
   //    cout << "Given input is a number" << endl;
   // }else {
   //    cout << "not numeric" << endl;
   // }
   

//    task-2
   string s;
   getline(cin , s);
   
   isOperator(s); 



   // task 03
   // isCommentLine();
   


   // task-04
//    string s;
//    cin >> s;

//    if(isAlphaNumeric(s)) {
//       cout << "Alpha Numeric" << endl;
//    }
//    else {
//       cout << "Not Alpha Numeric" << endl;
//    }




    return 0;
}