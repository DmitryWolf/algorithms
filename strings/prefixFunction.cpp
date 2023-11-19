#include <bits/stdc++.h>
#define IOS ios::sync_with_stdio(false); cin.tie(nullptr)
using namespace std;
typedef long long ll;


vector<int> prefixFunction(const string &s) {
    vector<int> p(s.size());
    for (int i = 1; i < s.size(); i++) {
        int border = p[i - 1];
        while (border > 0 && s[i] != s[border])
            border = p[border - 1];
        p[i] = border + (s[i] == s[border]);
    }
    return p;
}


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

/*
Применения:

Поиск подстроки pattern в тексте text за O(N) (алгоритм Кнута-Морриса-Пратта). 
Составляется строка pattern#text, вычисляется её префикс-функция. 
Вхождения завершаются в позициях, для которых p[i] == pattern.size().

Определение минимального периода period строки s за O(N). period = s.size() - p.back().

Определение числа различных подстрок строки s за O(N^2). 
Пусть известен ответ prevRes для строки prevSuffix = s.substr(i + 1), 
за O(N) вычислим ответ res для строки suffix = s.substr(i). 
Новые подстроки — те, которые начинаются в начале строки и не встречаются далее. 
Вычисляем префикс-функцию для suffix, пусть maxP = *max_element(p.begin(), p.end()). 
В prevSuffix уже встречались все префиксы длиной <= maxP, 
поэтому res = prevRes + (suffix.size() - maxP).
*/
