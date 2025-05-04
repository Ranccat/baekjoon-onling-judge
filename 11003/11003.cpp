#include <iostream>
#include <deque>

using namespace std;

int N, L;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> L;
    int arr[N];
    for (auto& a : arr)
        cin >> a;

    deque<int> dq; // index

    // growing window
    for (int i = 0; i < L; i++) {
        while (!dq.empty() && arr[dq.back()] > arr[i])
            dq.pop_back();

        dq.push_back(i);

        cout << arr[dq.front()] << ' ';
    }

    // sliding window
    for (int i = L; i < N; i++) {
        if (!dq.empty() && dq.front() <= i - L)
            dq.pop_front();

        while(!dq.empty() && arr[dq.back()] > arr[i])
            dq.pop_back();

        dq.push_back(i);

        cout << arr[dq.front()] << ' ';
    }

    return 0;
}
