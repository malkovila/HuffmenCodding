#include <iostream>

#include <algorithm>
#include <vector>
#include <map>

#include <string>

using namespace std;

vector<pair<string, int>> make_dict(string a) {//создает список из пар (буква: кол-во повторений)
	map <char, int> d;
	vector<pair<string, int>> par;
	for (auto w : a) {
		if (d.count(w) == 0) d[w] = 1;
		else d[w] ++;
	}
	for (auto w : d) {
		pair<string, int> p;
		p.first = w.first;
		p.second = w.second;
		par.push_back(p);
	}
	sort(par.begin(), par.end(), [](pair<string, int> p1, pair<string, int> p2) {
		return p1.second < p2.second;
		}); //сортируем список из пар по повторениям букв в возрастании
	return par;
}

map<char, string> make_tree(string a) {
	vector<pair<string, int>> dict = make_dict(a);
	map<char, string> d;

	while (dict.size() != 1) {
		pair<string, int>p;
		string new_el = dict[0].first + dict[1].first;
		int new_count = dict[0].second + dict[1].second;
		p.first = new_el;
		p.second = new_count;
		for (auto w : dict[0].first) {
			d[w] += "0";
		}
		for (auto w : dict[1].first) {
			d[w] += "1";
		}
		dict.erase(dict.begin());
		dict.erase(dict.begin());

		dict.push_back(p);
		sort(dict.begin(), dict.end(), [](pair<string, int> p1, pair<string, int> p2) { //функция для сортировки
			return p1.second < p2.second;
			});
	}
	return d;

}

int main() {
	setlocale(LC_ALL, "RU");
	string s, str = "";
	getline(cin, s);
	for (auto k : s) {
		for (auto i : make_tree(s)) {
			if (i.first == k)
				str += make_tree(s)[i.first];
		}
	}
	reverse(str.begin(), str.end());
	cout << make_tree(s).size() << ' ' << str.size() << endl;
	for (auto i : make_tree(s)) {
		reverse(i.second.begin(), i.second.end());
		cout << i.first << ' ' << i.second << endl;

	}
};
