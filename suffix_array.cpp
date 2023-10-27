#include <bits/stdc++.h>
using namespace std;
void countSort(vector<int>& p, const vector<int>& rank) {
    int n = p.size();

    vector<int> rankCount(n);
    for (int i = 0; i < n; i++)
        rankCount[rank[i]]++;

    vector<int> rankFrom(n);
    for (int i = 1; i < n; i++)
        rankFrom[i] = rankFrom[i - 1] + rankCount[i - 1];

    vector<int> sortedP(n);
    for (int elem : p)
        sortedP[rankFrom[rank[elem]]++] = elem;
    p.swap(sortedP);
}

vector<int> makeSuffixArray(string s) {
    s += '\0';
    int n = s.size();

    vector<int> p(n);
    for (int i = 0; i < n; i++)
        p[i] = i;
    sort(p.begin(), p.end(), [&](int i, int j) { return s[i] < s[j]; });

    vector<int> c(n);
    // мин лекс символ имеет класс 0
    // далее берем предыдущий класс и делаем +1 если символы не равны
    c[p[0]] = 0;
    for (int i = 1; i < n; i++)
        c[p[i]] = c[p[i - 1]] + (s[p[i]] != s[p[i - 1]]); 

    vector<pair<int, int>> pairc(n);
    for (int len = 1; len < n; len *= 2) {
        // "добавялем" классы
        for (int i = 0; i < n; i++)
            pairc[i] = { c[i], c[(i + len) % n] };
        
        // у нас есть отсортированные строчки длины len/2
        // к этим строчкам приделаем в начало еще строки длины len/2
        for (int i = 0; i < n; i++)
            p[i] = (p[i] - len + n) % n;
        countSort(p, c);

        c[p[0]] = 0;
        for (int i = 1; i < n; i++)
            c[p[i]] = c[p[i - 1]] + (pairc[p[i]] != pairc[p[i - 1]]);
    }
    //return vector<int>(p.begin() + 1, p.end());
    return p;
}
int lowerBound(const string& s, const vector<int>& p, const string& t) {
    int l = 0, r = p.size();
    while (l + 1 < r) {
        int m = l + (r - l) / 2;
        if (s.compare(p[m], t.size(), t) >= 0)
            r = m;
        else
            l = m;
    }
    return r;
}

int upperBound(const string& s, const vector<int>& p, const string& t) {
    int l = 0, r = p.size();
    while (l + 1 < r) {
        int m = l + (r - l) / 2;
        if (s.compare(p[m], t.size(), t) > 0)
            r = m;
        else
            l = m;
    }
    return r;
}

int stringsCount(const string& s, const vector<int>& p, const string& t) {
    return upperBound(s, p, t) - lowerBound(s, p, t);
}

vector<int> makeLCP(const string& s, const vector<int>& p) {
    int n = p.size();
    // массив c (классов эквивалентности)
    vector<int> positionInP(n);
    for (int i = 0; i < n; i++)
        positionInP[p[i]] = i;

    vector<int> lcp(n);
    for (int i = 0, len = 0; i < n - 1; i++, len = max(len - 1, 0)) {
        int j = p[positionInP[i] - 1];
        while (s[i + len] == s[j + len])
            len++;
        lcp[positionInP[i]] = len;
    }
    return lcp;
}
long long distinctSubstringsCount(const vector<int>& p, const vector<int>& lcp) {
    long long res = 0;
    for (int i = 1; i < p.size(); i++)
        res += (p.size() - 1 - p[i]) - lcp[i];
    return res;
}
string longestCommonSubstring(const string& a, const string& b) {
    string s = a + "#" + b;
    auto p = makeSuffixArray(s);
    auto lcp = makeLCP(s, p);

    int len = 0, from = 0;
    for (int i = 1; i < p.size(); i++) {
        if ((p[i] < a.size() && p[i - 1] > a.size() ||
            p[i] > a.size() && p[i - 1] < a.size()) && lcp[i] > len) {
            len = lcp[i];
            from = min(p[i], p[i - 1]);
        }
    }
    return a.substr(from, len);
}
int main() {
  string s = "abbca";
  vector<int> sa = makeSuffixArray(s);
  vector<int> LCP = makeLCP(s, sa);
  return 0;
}
