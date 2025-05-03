#include <iostream>
#define MAX 10

using namespace std;

int arr[MAX][MAX];
int N, odd, even;

void print() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << arr[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}

bool canExist(int x, int y) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == x && j == y) return true;
            if (abs(x-i) == abs(y-j) && arr[i][j] == 2) return false;
        }
    }
    return true;
}

void func(int x, int y, int count, int side) {
    if (x == N) {
        if (side) odd = max(odd, count);
        else even = max(even, count);
        return;
    }

    // next index
    int nx = x;
    int ny = y + 2;
    if (ny >= N) {
        nx++;
        ny = 1;
        if (side && nx & 1) ny = 0;
        if (!side && nx % 2 == 0) ny = 0;
    }

    // can be placed
    if (arr[x][y] == 1 && canExist(x, y)) {
        arr[x][y] = 2;
        func(nx, ny, count + 1, side);
        arr[x][y] = 1;
    }
    func(nx, ny, count, side);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> arr[i][j];
        }
    }

    func(0, 0, 0, 0); // even
    func(0, 1, 0, 1); // odd

    cout << odd + even;

    return 0;
}
