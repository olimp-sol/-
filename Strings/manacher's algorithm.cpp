#include <iostream>
#include <vector>
#include <string>

using namespace std;


int main(){
    string s;
    cin >> s;
    int n = s.length();
    vector<int> d1(n);
    vector<int> d2(n);

    int l = 0, r = 0;
    for (int i = 0; i < n; i++ ){
        if (i <= r)
            d1[i] = min(d1[l + r - i], r - i + 1);
        else d1[i] = 1;
        while(i + d1[i] < n && i - d1[i] >= 0 && s[i + d1[i]] == s[i - d1[i]])
            d1[i]++;
        if (i + d1[i] - 1 > r)
            l = i - d1[i] + 1; r = i + d1[i] - 1;
    }

    l = 0,r = 0;
    for (int i = 0; i < n; i++ ){
        if (i <= r)
            d2[i] = min(d2[l + r - i + 1], r - i + 1);
        else d2[i] = 0;
        while(i + d2[i] < n && i - d2[i] - 1 >= 0 && s[i + d2[i]] == s[i - d2[i] - 1])
            d2[i]++;
        if (i + d2[i] - 1 > r)
            l = i - d2[i]; r = i + d2[i] - 1;
    }

    for (int i=0; i < n; i++ )
        cout << d1[i] <<" ";
        cout<<endl;
    for (int i=0; i < n; i++ )
        cout << d2[i] <<" ";
}
