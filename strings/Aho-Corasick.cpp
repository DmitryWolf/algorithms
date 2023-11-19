#include <bits/stdc++.h>
#define IOS ios::sync_with_stdio(false); cin.tie(nullptr)
using namespace std;
typedef long long ll;


class Trie {
    struct Vertex {
        bool isTerminal = 0;
        map<char, Vertex> next;
        Vertex *sufLink = 0;
        map<char, Vertex *> autLink;
    } root;

public:
    void insert(const string &s) {
        Vertex *v = &root;
        for (char c : s)
            v = &v->next[c];
        v->isTerminal = 1;
    }

    void build(int alphabetSize) {
        queue<Vertex *> q;
        root.sufLink = &root;
        q.push(&root);

        while (!q.empty()) {
            Vertex *v = q.front();
            q.pop();

            for (auto &[c, to] : v->next) {
                to.sufLink = (v == &root ? &root : v->sufLink->autLink[c]);                
                q.push(&to);
            }

            for (char c = 'a'; c < 'a' + alphabetSize; c++) {
                if (v->next.count(c))
                    v->autLink[c] = &v->next[c];
                else
                    v->autLink[c] = (v == &root ? &root : v->sufLink->autLink[c]);
            }

            v->isTerminal |= v->sufLink->isTerminal;
        }
    }

    bool check(const string &s) {
        Vertex *v = &root;
        for (char c : s) {
            v = v->autLink[c];
            if (v->isTerminal)
                return 1;
        }
        return 0;
    }
};


class Trie2 {
    struct Vertex {
        vector<int> termIndexes;
        Vertex *termLink = 0;
        unordered_map<char, Vertex> next;
        Vertex *sufLink = 0;
        unordered_map<char, Vertex *> autLink;
    } root;
    int stringCount = 0;

public:
    void insert(const string &s) {
        Vertex *v = &root;
        for (char c : s)
            v = &v->next[c];
        v->termIndexes.push_back(stringCount++);
    }

    void build(int alphabetSize) {
        queue<Vertex *> q;
        root.sufLink = &root;
        q.push(&root);

        while (!q.empty()) {
            Vertex *v = q.front();
            q.pop();

            for (auto &[c, to] : v->next) {
                to.sufLink = (v == &root ? &root : v->sufLink->autLink[c]);
                q.push(&to);
            }

            for (char c = 'a'; c < 'a' + alphabetSize; c++) {
                if (v->next.count(c))
                    v->autLink[c] = &v->next[c];
                else
                    v->autLink[c] = (v == &root ? &root : v->sufLink->autLink[c]);
            }

            v->termLink = (!v->sufLink->termIndexes.empty() ? v->sufLink : v->sufLink->termLink);
        }
    }

    vector<vector<int>> check(const string &s) {
        vector<vector<int>> res(stringCount);

        Vertex *v = &root;
        for (int i = 0; i < s.size(); i++) {
            v = v->autLink[s[i]];

            if (!v->termIndexes.empty() || v->termLink)
                for (Vertex *term = (!v->termIndexes.empty() ? v : v->termLink); term; term = term->termLink)
                    for (int termIndex : term->termIndexes)
                        res[termIndex].push_back(i);
        }

        return res;
    }
};



ll solve() {
    return 0;
}

int main() {
    IOS;
    ll tc = 1;
    //cin >> tc;
    while (tc--) {
        solve();
    }
    return 0;
}
