#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>

using namespace std;
#define CONST 31

vector <long long int> Hash(string s);
vector <long long int> P;

int main(){
    string s;
    cin>>s;
    int Count = 0;
    int n  = s.length();

    P.resize(n);
    P[0] = 1;
    for (int i = 1; i < n; i++){
        P[i] = P[i - 1] * CONST;
    }

    vector <long long int> H;
    H = Hash(s);

    for (int len = 1; len <= n; len++){
        set <long long int> res;
        for (int i = 0; i < n - len + 1; i++){

            long long int hs = H[i + len - 1];
            if (i > 0) hs -= H[i - 1];
            hs *= P[n - i - 1];
            res.insert(hs);
        }
        Count += res.size();
        res.clear();
    }
    cout<< Count;
}

vector <long long int> Hash(string s){
    vector <long long int> H(s.length());
    H[0] = (s[0] - 'a' + 1) * P[0];
    for (int i = 1; i < s.length(); i++){
        H[i] = H[i - 1] + (s[i] - 'a' + 1) * P[i];
    }
    return H;
}
