#include <string>
#include <iostream>
#include <map>

using namespace std;

class Bor {
public:
	Bor() {
		root = new node;
	}
	~Bor() {
		delete root;
	}
	void add(const string& s) {
		node* ptr = root;
		for (int i = 0; i < s.length(); i++) {
			if (ptr->next[s[i]] == nullptr)
				ptr->next[s[i]] = new (node);
			ptr = ptr->next[s[i]];
		}
		ptr->leaf = true;
	}
	bool check(const string& s) {
		node* ptr = root;
		for (int i = 0; i < s.length(); i++) {
			if (ptr->next[s[i]] == nullptr)return false;
			ptr = ptr->next[s[i]];
		}
		return ptr->leaf;
	}
	class node {
	public:
		node() {
			leaf = 0;
		}
		~node() {
			map <char, node*>::iterator I;
			for (I = next.begin(); I != next.end(); I++)
				delete (*I).second;
		}
		map<char, node*>next;
		bool leaf;
	};
	node* root;
};


int main() {
	Bor bor;
	bor.add("abab");
	cout << bor.check("aba")<<'\n';
	cout << bor.check("aba");
}
