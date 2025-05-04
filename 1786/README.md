#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> fail(const string& pattern) {
    int l = (int)pattern.length();
    vector<int> prefix(l, 0);
    int k = 0; // previous longest prefix

    for (int i = 1; i < l; i++) {
        while (k > 0 && pattern[k] != pattern[i]) k = prefix[k-1];
        if (pattern[k] == pattern[i]) k++;
        prefix[i] = k;
    }

    return prefix;
}

vector<int> kmp(const string& text, const string& pattern) {
    vector<int> result(1, 0);
    int n = (int)text.length();
    int m = (int)pattern.length();

    vector<int> prefix = fail(pattern);
    int k = 0;

    for (int i = 0; i < n; i++) {
        while (k > 0 && pattern[k] != text[i]) k = prefix[k-1];
        if (pattern[k] == text[i]) k++;
        if (k == m) {
            result[0]++;
            result.push_back(i-m+2);
            k = prefix[k-1];
        }
    }

    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string s1, s2;
    getline(cin, s1);
    getline(cin, s2);

    auto v = kmp(s1, s2);

    for (const auto& a : v) cout << a << '\n';

    return 0;
}
