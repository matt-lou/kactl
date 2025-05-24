/**
* Author: IDK
* Description: Find all articulation points (using array flag) in a directed graph. u = node, fa = father
*/
#pragma once
int n, m;
int dfn[100001], low[100001], idx, res;
bool vis[100001], flag[100001];
vector<int> edge[100001];
void Tarjan(int u, int fa) {
    vis[u] = true;
    low[u] = dfn[u] = ++idx;
    int child = 0;
    for (const auto &v: edge[u]) {
        if (!vis[v]) {
            child++;
            Tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if (fa != u && low[v] >= dfn[u] && !flag[u]) {
                flag[u] = true;
                res++;
            }
        } else if (v != fa) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (fa == u && child >= 2 && !flag[u]) {
        flag[u] = true;
        res++;
    }
}
