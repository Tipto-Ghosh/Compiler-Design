
#include <bits/stdc++.h>
#define endl "\n"
#pragma GCC optimize ("Ofast")
#pragma GCC target ("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx")
#pragma GCC optimize ("-ffloat-store")
#pragma GCC optimize("unroll-loops,03,Ofast")
#pragma GCC target("avx2,avx,fma,bmi,bmi2,lzcnt,popcnt")
using namespace std;
using namespace chrono;
#define firstio() ios_base::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
// Author Name: Tipto_Ghosh
// Last_Updated: 14-02-2025

typedef long long ll;
typedef long long int lli;
typedef long double ld;
typedef unsigned long long int ulli;
typedef vector<int> vi;
typedef vector<long int> vli;
typedef vector<long long> vll;
typedef vector<vector<int>> vii;
typedef vector<bool> vbool;
const int N = 1e7 + 10;
const int mod = 1e9 + 7;
const double pi = 3.14159265358979323846;
const double inf_double = numeric_limits<double>::infinity();
const int inf_int = numeric_limits<int>::max();
#define all(x) (x).begin(), (x).end()

//--------------------------Debug Here-------------------------------
#ifdef ONLINE_JUDGE
#define debug(...) 
#else
template <typename T> void printVector(const vector<T>& vec) { cerr << "[ "; for (size_t i = 0; i < vec.size(); ++i) cerr << vec[i] << (i < vec.size() - 1 ? ", " : " "); cerr << "]"; }
template <typename T> void printSet(const set<T>& s) { cerr << "{ "; for (auto it = s.begin(); it != s.end(); ++it) cerr << *it << (next(it) != s.end() ? ", " : " "); cerr << "}"; }
template <typename T> void printUnorderedSet(const unordered_set<T>& us) { cerr << "{ "; for (auto it = us.begin(); it != us.end(); ++it) cerr << *it << (next(it) != us.end() ? ", " : " "); cerr << "}"; }
template <typename T> void printList(const list<T>& lst) { cerr << "( "; for (auto it = lst.begin(); it != lst.end(); ++it) cerr << *it << (next(it) != lst.end() ? ", " : " "); cerr << ")"; }
template <typename T> void printStack(stack<T> stk) { cerr << "[ "; vector<T> temp; while (!stk.empty()) { temp.push_back(stk.top()); stk.pop(); } for (size_t i = 0; i < temp.size(); ++i) cerr << temp[i] << (i < temp.size() - 1 ? ", " : " "); cerr << "]"; }
template <typename T> void printQueue(queue<T> q) { cerr << "[ "; while (!q.empty()) { cerr << q.front() << (q.size() > 1 ? ", " : " "); q.pop(); } cerr << "]"; }
template <typename K, typename V> void printUnorderedMap(const unordered_map<K, V>& umap) { cerr << "{\n"; for (auto it = umap.begin(); it != umap.end(); ++it) cerr << "  (" << it->first << ": " << it->second << ")" << (next(it) != umap.end() ? ",\n" : "\n"); cerr << "}"; }
template <typename Iter> void printIteratorRange(Iter start, Iter end) { cerr << "[ "; for (Iter it = start; it != end; ++it) cerr << *it << (next(it) != end ? ", " : " "); cerr << "]"; }
#define debug(var) debugImpl(#var, var)
#define debugRange(start, end) cerr << #start ", " #end " = "; printIteratorRange(start, end); cerr << endl;
template <typename T> void debugImpl(const string& name, const T& var) { cerr << name << " = " << var << endl; }
template <typename T> void debugImpl(const string& name, const vector<T>& vec) { cerr << name << " = "; printVector(vec); cerr << endl; }
template <typename T> void debugImpl(const string& name, const set<T>& s) { cerr << name << " = "; printSet(s); cerr << endl; }
template <typename T> void debugImpl(const string& name, const unordered_set<T>& us) { cerr << name << " = "; printUnorderedSet(us); cerr << endl; }
template <typename T> void debugImpl(const string& name, const list<T>& lst) { cerr << name << " = "; printList(lst); cerr << endl; }
template <typename T1, typename T2> void debugImpl(const string& name, const pair<T1, T2>& p) { cerr << name << " = ( " << p.first << ", " << p.second << " )" << endl; }
template <typename T> void debugImpl(const string& name, stack<T> stk) { cerr << name << " = "; printStack(stk); cerr << endl; }
template <typename T> void debugImpl(const string& name, queue<T> q) { cerr << name << " = "; printQueue(q); cerr << endl; }
template <typename K, typename V> void debugImpl(const string& name, const unordered_map<K, V>& umap) { cerr << name << " = "; printUnorderedMap(umap); cerr << endl; }
template <typename Iter> void debugImpl(const string& name, Iter start, Iter end) { cerr << name << " = "; printIteratorRange(start, end); cerr << endl; }
template <typename T> void printMaxHeap(priority_queue<T> heap) {cerr << "[ "; vector<T> temp; while (!heap.empty()) {temp.push_back(heap.top());heap.pop();}for (size_t i = 0; i < temp.size(); ++i){cerr << temp[i] << (i < temp.size() - 1 ? ", " : " ");}cerr << "]";}
template <typename T> void debugImpl(const string& name, priority_queue<T> maxHeap){cerr << name << " = ";printMaxHeap(maxHeap);cerr << endl;}
#endif

//-------------------------------------Solve Here-----------------------
#define all(x) (x).begin(), (x).end()
static const int speedup = []{ios::sync_with_stdio(0); cin.tie(0); return 0;}();


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

void Test_Case() {
   // task-01
   // string s;
   // cin >> s;

   // if(isConstant(s)) {
   //    cout << "Given input is a number" << endl;
   // }else {
   //    cout << "not numeric" << endl;
   // }
   

   // task-2
   // string s;
   // cin >> s;
   // debug(s);
   // isOperator(s); 

   // int n = s.size();
   // debug(n);
   

   // task 03
   // isCommentLine();
   


   // task-04
   string s;
   cin >> s;

   if(isAlphaNumeric(s)) {
      cout << "Alpha Numeric" << endl;
   }
   else {
      cout << "Not Alpha Numeric" << endl;
   }
}

//--------------------------Main Here-------------------------------
int main() {
    #ifndef ONLINE_JUDGE
    freopen("error.txt", "w", stderr);
    #endif
    firstio();
    auto start_time = high_resolution_clock::now();
    
    Test_Case();

    auto end_time = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end_time - start_time);
    auto duration_time = static_cast<double>(duration.count());
    cerr << "Execution Time: " << duration_time << " ms" << endl; 

    return 0;
}
