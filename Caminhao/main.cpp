#include <iostream>
#include <bits/stdc++.h>

using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);

#define ll long long
#define vi vector<int>
#define iii tuple<int,int,int>
const int INF = 1e9;
const int UNVISITED = -1;
const int VISITED = 1;

vector<iii> EL;
vector<vector<pair<int,int>>> AL;
vector<vector<int>> ans;
vi dfs_num;
vi p;

class UnionFind {
private:
    vi p, rank;
public:
    UnionFind (int n) {
        p.assign(n, 0); for (int i = 0; i < n; ++i) p[i] = i;
        rank.assign(n, 0);
    }
    int findSet(int i) {return (p[i] == i ? i : p[i] = findSet(p[i])); }
    bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }

    void unionSet (int i, int j) {
        if (isSameSet(i, j)) return;
        int x = findSet(i), y = findSet(j);
        if (rank[x] > rank[y]) swap(x, y);
        p[x] = y;
        if (rank[x] == rank[y]) ++rank[y];
    }
};

int comp(iii a, iii b) {
    return a > b;
}

void DFS(int pivot, int u, int minV) {
    dfs_num[u] = VISITED;
    ans[pivot][u] = minV;
    ans[u][pivot] = minV;
    for (auto [v, w] : AL[u]) {
        if (dfs_num[v] == VISITED) continue;
        DFS(pivot, v, min(minV, w));
    }
}

int main() {
    fastio;
    int N, M, Q;
    cin >> N >> M >> Q;
    EL.resize(M);
    AL.assign(N, vector<pair<int,int>>());
    ans.assign(N, vector<int> (N,INF));
    p.resize(N);
    p[0] = -1;
    for (int i = 0; i < M; ++i) {
        int a, b, w; cin >> a >> b >> w;
        --a; --b;
        EL[i] = {w, a, b};
    }

    sort (EL.begin(), EL.end(), comp);
    UnionFind UF(N);
    int num_taken = 0;
    for (auto &[w,u,v] : EL) {
        if (UF.isSameSet(u, v)) continue;
        AL[u].emplace_back(v, w);
        AL[v].emplace_back(u, w);
        UF.unionSet(u, v);
        ++num_taken;
        if (num_taken == N-1) break;
    }

    for (int i = 0; i < N; ++i) {
        dfs_num.assign(N, UNVISITED);
        DFS(i, i, INF);
    }

    for (int i = 0; i < Q; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        cout << ans[a][b] << '\n';
    }

    return 0;
}