#include <iostream>
#include <vector>
#include <queue>
#define MAX 1000

using namespace std;

class Node {
public:
    int x, y, l, r;

public:
    Node(const int x, const int y, const int l, const int r) {
        this->x = x;
        this->y = y;
        this->l = l;
        this->r = r;
    }
};

int N, M, L, R;
int arr[MAX][MAX];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    queue<Node> q;

    cin >> N >> M >> L >> R;
    for (int i = 0; i < N; i++) {
        string str;
        cin >> str;
        for (int j = 0; j < M; j++) {
            arr[i][j] = str[j] - 48;

            if (arr[i][j] == 2) {
                q.emplace(i, j, 0, 0);
                arr[i][j] = 1;
                continue;
            }

            if (arr[i][j] == 1) {
                arr[i][j] = -1;
            }
        }
    }

    while (!q.empty()) {
        const auto node = q.front();
        q.pop();

        int cx = node.x;
        int cy = node.y;
        int cl = node.l;
        int cr = node.r;

        int nx = cx + 1;
        while (nx < N && arr[nx][cy] == 0) {
            arr[nx][cy] = 1;
            q.emplace(nx, cy, cl, cr);
            nx++;
        }
        nx = cx - 1;
        while (nx >= 0 && arr[nx][cy] == 0) {
            arr[nx][cy] = 1;
            q.emplace(nx, cy, cl, cr);
            nx--;
        }

        int ny = cy + 1;
        if (ny < M && arr[cx][ny] == 0 && cr < R) {
            arr[cx][ny] = 1;
            q.emplace(cx, ny, cl, cr + 1);
        }

        ny = cy - 1;
        if (ny >= 0 && arr[cx][ny] == 0 && cl < L) {
            arr[cx][ny] = 1;
            q.emplace(cx, ny, cl + 1, cr);
        }
    }

    int count = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (arr[i][j] == 1)
                count++;
        }
    }

    cout << count;

    return 0;
}
