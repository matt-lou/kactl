/**
* Author: IDK
* Description: Persistent segment tree
*/
#pragma once
struct tree {
    int l, r, x;
} t[200010 << 5];
int n, m, a[200010], id[200010], root[200010], b[200010], cnt;
int build(int l, int r) {
    cnt++;
    int rt = cnt; t[rt].x = 0;
    if (l >= r) return rt;
    int mid = (l + r) >> 1;
    t[rt].l = build(l, mid);
    t[rt].r = build(mid + 1, r);
    return rt;
}
int update(int k, int l, int r, int x) {
    cnt++;
    int rt = cnt;
    t[rt].l = t[k].l; t[rt].r = t[k].r; t[rt].x = t[k].x + 1;
    if (l >= r) return rt;
    int mid = (l + r) >> 1;
    if (x <= mid) t[rt].l = update(t[k].l, l, mid, x);
    else t[rt].r = update(t[k].r, mid + 1, r, x);
    return rt;
}
int query(int u, int v, int l, int r, int x) {
    if (l >= r) return l;
    int mid = (l + r) >> 1;
    int num = t[t[v].l].x - t[t[u].l].x;
    if (num >= x) return query(t[u].l, t[v].l, l, mid, x);
    return query(t[u].r, t[v].r, mid + 1, r, x - num);
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]); b[i] = a[i];
    }
    sort(b + 1, b + n + 1);
    int d = unique(b + 1, b + n + 1) - b - 1;
    root[0] = build(1, d);
    for (int i = 1; i <= n; i++) {
        int x = lower_bound(b + 1, b + d + 1, a[i]) - b;
        root[i] = update(root[i - 1], 1, d, x);
    }
    while (m--) {
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        int x = query(root[l - 1], root[r], 1, d, k);
        printf("%d\n", b[x]);
    }
    return 0;
}