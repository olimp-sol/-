#include <string>
#include <iostream>
#include <cstring>
#include <vector>
#include <map>

using namespace std;

class searchEngine {
public:
	searchEngine() { /// конструктор
		root = new node;/// создает корень
	}
	void add(const string& s) {/// добавление образца
		node* ptr = root;/// начинаем в корне
		for (unsigned int i = 0; i < s.length(); i++) {///  пробег по символам строки
			if (ptr->next[s[i]] == nullptr) {///  если перехода в боре не существует
				ptr->next[s[i]] = new (node);/// создаем вершину
				ptr->next[s[i]]->p = ptr;/// восстанавливаем предка для потомка
				ptr->next[s[i]]->ch = s[i];/// ребро от предка к потомку
			}
			ptr = ptr->next[s[i]];/// переход по бору
		}
		ptr->leaf = true;/// помечаем конец строки как лист
	}
	void check(const string& s) {///  проверка текста на образцы
		node* ptr = root;/// начинем в корне
		for (unsigned int i = 0; i < s.length(); i++) {/// идем по символам текста
			ptr = go(ptr, s[i]);/// переход в автомате по символу
			node* u = ptr;
			while (u != root) {///  проверка суффиксов на образцы
				if (u->leaf)print(u);///  если лист по выводим
				u = get_leaf_link(u);/// получаем ближайший ответ
			}
		}
	}

private:
	class node {
	public:
		node() {
			p = 0;
			link = 0;
			leaf_link = 0;
			ch = 0;
			leaf = 0;
		}
		~node() {
			map <char, node*>::iterator I;
			for (I = next.begin(); I != next.end(); I++)
				delete (*I).second;
		}
		map<char, node*>next;
		map<char, node*>go;
		node* p;/// указатель на предка
		node* link;/// суффиксная ссылка
		node* leaf_link;/// суффиксная ссылка на ближайший ответ
		char ch;/// символ ребра от предка к потомку
		bool leaf;/// признак конца образца
	};
	node* root;///  указатель на корень
	node* go(node* ptr, char c) {/// функция перехода в автомате, по символу c
		if (ptr->go[c] != nullptr)return ptr->go[c];/// существует переход в автомате?
		if (ptr->next[c] != nullptr)/// Существует переход в боре?
			ptr->go[c] = ptr->next[c];/// присваиваем переходу в автомате, переход в боре
		else/// пробуем перейти по суффиксу
			if (ptr == root)ptr->go[c] = root;///  если корень то в нем остаемся
			else ptr->go[c] = go(get_link(ptr), c);/// идем по суффиксу
		return ptr->go[c];
	}

	node* get_link(node* ptr) {/// поиск суффиксной ссылки
		if (ptr->link != nullptr)return ptr->link;///  если она уже найдена
		if (ptr == root || ptr->p == root)/// если в корне или предок корень то идем в корень
			ptr->link = root;
		else
			ptr->link = go(get_link(ptr->p), ptr->ch);/// вычисляем суфф. через суффикс предка
		return ptr->link;
	}

	node* get_leaf_link(node* ptr) {/// вычисление "хорошей" суффиксной ссылки
		if (ptr->leaf_link != nullptr)return ptr->leaf_link;///  если уже вычислена
		node* u = get_link(ptr);/// идем по суффиксной ссылке
		if (u == root)ptr->leaf_link = root;/// если суффикс ведет в корень - то и "хороший" суффикс -> в  корень
		else
			if (u->leaf)ptr->leaf_link = u;/// ведет ли суффикс в лист
			else ptr->leaf_link = get_leaf_link(u);/// рекурсивно вычисляем хорошую суффиксную ссылку
		return ptr->leaf_link;
	}

	void print(node* ptr) {
		string s;
		while (ptr != nullptr) {
			s = ptr->ch + s;
			ptr = ptr->p;
		}
		cout << s << '\n';
	}

};

int main() {
	searchEngine test;
	test.add("aaaa");
	test.add("aaa");
	test.add("a");
	//test.add("c");

	test.check("aaaaa");

}
