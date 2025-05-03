#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#define INF 0x7FFFFFFF

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> arr(N);
    for (auto& a : arr) cin >> a;

    vector<int> back(N, INF);

    vector<int> ans;
    ans.push_back(arr[0]);
    back[0] = 0;
    for (int i = 1; i < N; i++) {
        int num = arr[i];

        if (num > ans.back()) {
            back[i] = static_cast<int>(ans.size());
            ans.push_back(num);
            continue;
        }

        auto it = lower_bound(ans.begin(), ans.end(), num);
        *it = num;
        back[i] = it - ans.begin();
    }

    stack<int> answer;
    int last = ans.size();
    cout << last-- << '\n';
    for (int i = N-1; i >= 0; i--) {
        if (last == back[i]) {
            answer.push(arr[i]);
            last--;
        }
    }

    while (!answer.empty()) {
        cout << answer.top() << ' ';
        answer.pop();
    }
}
