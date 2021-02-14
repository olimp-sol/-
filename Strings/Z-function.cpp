#include <iostream>
#include <vector>
#include <string>

using namespace std;
vector<int> Z(string s);
vector<int> Z_trivial(string s);

int main(){
    string s;
    cin >> s;
    vector<int>res;

    res = Z_trivial(s);

    //res = Z(s);

    for (int i=0; i < res.size(); i++ )
        cout << res[i] <<" ";
}

vector<int> Z(string s){
    int n= s.length();
    vector<int> z(n);
    int l=0,r=0;
    for (int i=1; i<n; i++ ){
        if (i <= r)
            z[i] = min(z[i - l], r - i + l);
        while(i + z[i] < n && s[z[i]] == s[z[i] + i])
            z[i]++;
        if (i + z[i] - 1 > r)
            l = i; r = i + z[i] - 1;
    }
    return z;
}

vector<int> Z_trivial(string s) {
	int n = s.length();
	vector<int> z(n);
	for (int i = 1; i < n; i++)
		while (i + z[i] < n && s[z[i]] == s[i + z[i]])
			z[i]++;
	return z;
}
