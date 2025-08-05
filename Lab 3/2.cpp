#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <cctype>
using namespace std;


bool isDelimiter(char ch) {
    string delimiters = "[]{}(),:;";

    for(int i = 0; i < delimiters.length(); i++) {
        if(ch == delimiters[i]) {
            return true;
        }
    }
    return false;
}

int main() {

    ifstream file("program.txt");

    string line;
    
    vector<char> delimiters;
    vector<string> integers;
    vector<string> realNumbers;
    
    
    regex realNumberPattern(R"(\b\d+\.\d+\b)");
    regex integerPattern(R"(\b\d+\b)");
    
    while(getline(file , line)) {
        
        for(char ch : line) {
            if(isDelimiter(ch)) {
                delimiters.push_back(ch);
            }
        }
        
        
        sregex_iterator iter(line.begin() , line.end() , realNumberPattern);
        sregex_iterator end;

        while(iter != end) {
            realNumbers.push_back(iter->str());
            iter ++;
        }

        string temp = regex_replace(line, realNumberPattern, " ");

        sregex_iterator iterator2(temp.begin() , temp.end() , integerPattern);
        
        while(iterator2 != end) {
            integers.push_back(iterator2->str());
            iterator2 ++;
        }
    }

    file.close();



    cout << "All the delimiters" << endl;
    for(int i = 0; i < delimiters.size(); i++) {
        cout << delimiters[i] << " ";
    }
    cout << endl;

    cout << "All the integers" << endl;
    for(int i = 0; i < integers.size(); i++) {
        cout << integers[i] << " ";
    }
    cout << endl;

    cout << "All the real numbers" << endl;
    for(int i = 0; i < realNumbers.size(); i++) {
        cout << realNumbers[i] << " ";
    }
    

    return 0;
}