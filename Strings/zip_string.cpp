#include<iostream>
#include<vector>

using namespace std;

void Z(string s){
    vector <int>z(s.length());
    int l=0, r=0;
    int n = s.length();
    for (int i = 1; i < n; i++){
        if (i <= r){
            z[i] = min(z[i - l],r - i + 1);
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            z[i]++;
        if (i + z[i] - 1 > r){
            l = i;
            r = i + z[i] - 1;
        }
        if (i + z[i] == n && n % (i) == 0) {cout << s.substr(0,i);return;}
    }
cout<<"NO";
}


int main(){
    string s;
    cin >> s;
    Z(s);
}
