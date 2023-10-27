#include <bits/stdc++.h>
using namespace std;
struct automata {
private:
	struct state {
		int len, link;
		map<char, int> next;
	};
	//const static int MAXLEN = 10000; // (1)
	//state st[MAXLEN * 2]; // (1)
	vector<state> st;
	int sz, last;
	void res(int n) {st.resize(2 * n);}
public:
	automata(int n/*(2)*/) {
		res(n);
		sz = last = 0;
		st[0].len = 0;
		st[0].link = -1;
		++sz;
		/*
		// этот код нужен, только если автомат строится много раз для разных строк:
		for (int i=0; i<MAXLEN*2; ++i)
			st[i].next.clear();
		*/
	}
	void sa_extend(char c) {
		int cur = sz++;
		st[cur].len = st[last].len + 1;
		int p;
		for (p = last; p != -1 && !st[p].next.count(c); p = st[p].link)
			st[p].next[c] = cur;
		if (p == -1)
			st[cur].link = 0;
		else {
			int q = st[p].next[c];
			if (st[p].len + 1 == st[q].len)
				st[cur].link = q;
			else {
				int clone = sz++;
				st[clone].len = st[p].len + 1;
				st[clone].next = st[q].next;
				st[clone].link = st[q].link;
				for (; p != -1 && st[p].next[c] == q; p = st[p].link)
					st[p].next[c] = clone;
				st[q].link = st[cur].link = clone;
			}
		}
		last = cur;
	}
};
int main() {
  string s = "ab";
	automata a(s.size()/*(2)*/);
	for (auto it : s) {
		a.sa_extend(it);
	}
  return 0;
} 
