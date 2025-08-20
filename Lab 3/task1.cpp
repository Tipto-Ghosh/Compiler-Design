#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#define MAX_LINES 1000
 
string keywords[] = {

    "int", "float", "double", "char", "return", "void", "if", "else", "for", "while",
    "break", "continue", "class", "struct", "public", "private", "protected",
    "switch", "case", "default", "do", "bool", "true", "false", "const", "static"
};

int keywordCount = sizeof(keywords) / sizeof(keywords[0]);
 
string operators[] = {
    "+", "-", "*", "/", "%", "=", "==", "!=", "<", ">", "<=", ">=", "++", "--",
    "+=", "-=", "*=", "/=", "&&", "||", "!", "&", "|", "^", "~", "<<", ">>"

};

int operatorCount = sizeof(operators) / sizeof(operators[0]);
 
bool isLetter(char ch) {

    int ascii = (int)ch;

    return (ascii >= 65 && ascii <= 90) || (ascii >= 97 && ascii <= 122);

}
 
bool isDigit(char ch) {

    int ascii = (int)ch;

    return ascii >= 48 && ascii <= 57;

}
 
bool isWhitespace(char ch) {

    int ascii = (int)ch;

    return ascii == 32 || ascii == 9 || ascii == 10 || ascii == 13;

}
 
bool isValidIdentifier(string token) {

    if (token.length() == 0) return false;

    char first = token[0];

    int ascii = (int)first;

    if (!(isLetter(first) || ascii == 95)) return false;
 
    for (int i = 1; i < token.length(); i++) {

        ascii = (int)token[i];

        if (!(isLetter(token[i]) || isDigit(token[i]) || ascii == 95)) {

            return false;

        }

    }

    return true;

}
 
bool isKeyword(string token) {

    for (int i = 0; i < keywordCount; i++) {

        if (token == keywords[i]) return true;
    }

    return false;

}
 
bool isOperator(string token) {

    for (int i = 0; i < operatorCount; i++) {

        if (token == operators[i]) return true;

    }

    return false;

}
 
bool isNumber(string token) {

    if (token.length() == 0) return false;

    for (int i = 0; i < token.length(); i++) {

        if (!isDigit(token[i])) return false;

    }

    return true;

}
 
void classifyToken(string token) {

    if (isKeyword(token)) {

        cout << token << " --> Keyword" << endl;

    } else if (isOperator(token)) {

        cout << token << " --> Operator" << endl;

    } else if (isNumber(token)) {

        cout << token << " --> Number" << endl;

    } else if (isValidIdentifier(token)) {

        cout << token << " --> Valid Identifier" << endl;

    } else if (isDigit(token[0])) {

        cout << token << " --> Invalid Identifier (starts with number)" << endl;

    } else {

        cout << token << " --> Invalid Identifier" << endl;

    }

}
 
void tokenizeLine(string line) {
    string token = "";

    
    size_t commentPos = line.find("//");
    
    if (commentPos != string::npos) {
    
        string codePart = line.substr(0, commentPos);
        string commentPart = line.substr(commentPos);

        
        for (int i = 0; i < codePart.length(); i++) {
            char ch = codePart[i];

            if (isWhitespace(ch) || ch == ';' || ch == '(' || ch == ')' || ch == '{' || ch == '}') {
                if (token != "") {
                    classifyToken(token);
                    token = "";
                }

                if (!isWhitespace(ch)) {
                    string punct(1, ch);
                    cout << punct << " --> Punctuation" << endl;
                }
            }
            else if (ch == '+' || ch == '-' || ch == '=' || ch == '>' || ch == '<' ||
                     ch == '!' || ch == '&' || ch == '|') {
                if (token != "") {
                    classifyToken(token);
                    token = "";
                }

                string op(1, ch);
                if (i + 1 < codePart.length()) {
                    char next = codePart[i + 1];
                    if (next == '=' || (ch == '+' && next == '+') || (ch == '-' && next == '-') ||
                        (ch == '&' && next == '&') || (ch == '|' && next == '|') ||
                        (ch == '<' && next == '<') || (ch == '>' && next == '>')) {
                        op += next;
                        i++;
                    }
                }
                classifyToken(op);
            }
            else {
                token += ch;
            }
        }

        if (token != "") {
            classifyToken(token);
        }

        
        cout << commentPart << " --> Comment" << endl;
        return; 
    }

    // if no comment    
    for (int i = 0; i < line.length(); i++) {
        char ch = line[i];

        if (isWhitespace(ch) || ch == ';' || ch == '(' || ch == ')' || ch == '{' || ch == '}') {
            if (token != "") {
                classifyToken(token);
                token = "";
            }

            if (!isWhitespace(ch)) {
                string punct(1, ch);
                cout << punct << " --> Punctuation" << endl;
            }
        }
        else if (ch == '+' || ch == '-' || ch == '=' || ch == '>' || ch == '<' ||
                 ch == '!' || ch == '&' || ch == '|') {
            if (token != "") {
                classifyToken(token);
                token = "";
            }

            string op(1, ch);
            if (i + 1 < line.length()) {
                char next = line[i + 1];
                if (next == '=' || (ch == '+' && next == '+') || (ch == '-' && next == '-') ||
                    (ch == '&' && next == '&') || (ch == '|' && next == '|') ||
                    (ch == '<' && next == '<') || (ch == '>' && next == '>')) {
                    op += next;
                    i++;
                }
            }
            classifyToken(op);
        }
        else {
            token += ch;
        }
    }

    if (token != "") {
        classifyToken(token);
    }
}
 
int main() {

    string filename = "tokenization.txt";

    ifstream file(filename);
 
    if (!file.is_open()) {

        cout << "File failed to open." << endl;

        return 1;

    }
 
    string line;

    int lineCount = 0;
 
    while (getline(file, line) && lineCount < MAX_LINES) {

        cout << "Line " << (lineCount + 1) << ": " << line << endl;

        tokenizeLine(line);

        lineCount++;

    }
 
    file.close();

    return 0;

}

 