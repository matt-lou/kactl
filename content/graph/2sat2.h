/**
* Author: IDK
* Description: 2Sat Solver
*/
#pragma once
int n, m, du[4010], c[4010], oppo[4010];
int cnt, head[2010], to[4000010], nxt[4000010];
int cnt2, head2[2010], to2[4000010], nxt2[4000010];
int dfn[2010], low[2010], st[2010], a[2010], tot, num, k;
bool in[2010];
void add(int x, int y) {
    cnt++;
    to[cnt] = y;
    nxt[cnt] = head[x];
    head[x] = cnt;
}
void tarjan(int x) {
    tot++;
    dfn[x] = low[x] = tot;
    st[k] = x;
    k++; in[x] = true;
    for (int i = head[x]; i; i = nxt[i]) {
        int y = to[i];
        if (!dfn[y]) {
            tarjan(y);
            low[x] = min(low[x], low[y]);
        } else if (in[y]) {
            low[x] = min(low[x], dfn[y]);
        }
    }
    if (low[x] == dfn[x]) {
        num++;
        int y;
        do {
            k--;
            y = st[k];
            a[y] = num;
            in[y] = false;
        } while (y != x && k > 0);
    }
}
void add2(int x, int y) {
    cnt2++;
    to2[cnt2] = y;
    nxt2[cnt2] = head2[x];
    head2[x] = cnt2;
}
void rebuild() {
    for (int i = 0; i < n; i++) {
        for (int j = head[i]; j; j = nxt[j]) {
            if (a[i] != a[to[j]]) {
                add2(a[to[j]], a[i]);
                du[a[i]]++;
            }
        }
    }
}
void topsort() {
    queue<int> q;
    while (!q.empty())
        q.pop();
    for (int i = 1; i <= num; i++)
        if (du[i] == 0)
            q.push(i);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        if (c[x] == 0) {
            c[x] = 1;
            c[oppo[x]] = -1;
        }
        for (int i = head2[x]; i; i = nxt2[i]) {
            int y = to2[i];
            du[y]--;
            if (du[y] == 0) {
                q.push(y);
            }
        }
    }
}
void solve() {
    for (int i = 0; i < n; i++)
        if (!dfn[i])
            tarjan(i);
    for (int i = 0; i < m; i++) {
        if (a[i * 2] == a[i * 2 + 1]) {
            flag = false;
            puts("NO");
            break;
        }
        oppo[a[i * 2]] = a[i * 2 + 1];
        oppo[a[i * 2 + 1]] = a[i * 2];
    }
    if (flag) {
        puts("YES");
        rebuild();
        topsort();
        for (int i = 0; i < m; i++) {
            if (c[a[2 * i]] == 1) print(2 * i);
            else print(2 * i + 1);
        }
    }
}