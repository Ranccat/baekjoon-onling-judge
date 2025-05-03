#include <iostream>
#include <queue>
#include <cstring>
#include <climits>

using namespace std;

class Node {
public:
    int mx, my;
    int x, y;
    Node(const int mx, const int my, const int x, const int y) {
        this->mx = mx;
        this->my = my;
        this->x = x;
        this->y = y;
    }
};


char arr[7][7];
int visited[1<<7][1<<7][7][7];
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

char changeDoor(const char c) {
    if (c == 'C')
        return 'D';
    if (c == 'D')
        return 'C';
    return c;
}

char currentDoor(const Node& node) {
    char door = arr[node.x][node.y];
    if ((node.mx >> node.x) & 1)
        door = changeDoor(door);
    if ((node.my >> node.y) & 1)
        door = changeDoor(door);
    return door;
}

bool canMove(const Node& now, const Node& next, const int dir) {
    const char curDoor = currentDoor(now);
    const char nextDoor = currentDoor(next);

    if (curDoor == 'B' || nextDoor == 'B')
        return false;
    if (curDoor == 'A') {
        if (nextDoor == 'A')
            return true;
        if (nextDoor == 'C' && dir >= 2)
            return true;
        if (nextDoor == 'D' && dir <= 1)
            return true;
        return false;
    }
    if (curDoor == 'C' && (nextDoor == 'C' || nextDoor == 'A') && dir >= 2)
        return true;
    if (curDoor == 'D' && (nextDoor == 'D' || nextDoor == 'A') && dir <= 1)
        return true;
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> arr[i][j];
        }
    }

    memset(visited, 0xFF, sizeof(visited));
    visited[0][0][0][0] = 0;
    queue<Node> q;
    q.emplace(0, 0, 0, 0);
    while (!q.empty()) {
        const auto node = q.front();
        q.pop();
        const int cmx = node.mx;
        const int cmy = node.my;
        const int cx = node.x;
        const int cy = node.y;

        for (int dir = 0; dir < 4; dir++) {
            int nx = cx + dx[dir];
            int ny = cy + dy[dir];

            if (nx < 0 || ny < 0 || nx >= N || ny >= M)
                continue;
            if (visited[cmx][cmy][nx][ny] >= 0)
                continue;
            if (!canMove(node, Node(cmx, cmy, nx, ny), dir))
                continue;
            visited[cmx][cmy][nx][ny] = visited[cmx][cmy][cx][cy] + 1;
            q.emplace(cmx, cmy, nx, ny);
        }

        const int nmx = cmx ^ (1 << cx);
        const int nmy = cmy ^ (1 << cy);
        if (visited[nmx][nmy][cx][cy] >= 0)
            continue;
        visited[nmx][nmy][cx][cy] = visited[cmx][cmy][cx][cy] + 1;
        q.emplace(nmx, nmy, cx, cy);
    }

    int ans = INT_MAX;
    for (int i = 0; i < (1 << N); ++i) {
        for (int j = 0; j < (1 << M); ++j) {
            if (visited[i][j][N-1][M-1] >= 0)
                ans = min(ans, visited[i][j][N-1][M-1]);
        }
    }
    cout << (ans == INT_MAX ? -1 : ans) << '\n';

    return 0;
}
