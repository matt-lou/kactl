/**
* Author: IDK
* Description: 2D Segment Tree. Default to min operation
*/
#pragma once

const int inf = 1e9;
int n, m, tot;
struct node {
    int l, r, rt;
} t[200010];
struct tree {
    int ls, rs, mn;
} a[20000010];
void build(int k, int l, int r) {
    t[k].l = l;
    t[k].r = r;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(k << 1, l, mid);
    build(k << 1 | 1, mid + 1, r);
}
void update2(int &k, int l, int r, int x, int v) {
    if (!k) {
        k = ++tot; a[k].mn = v;
    }
    a[k].mn = min(a[k].mn, v);
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (x <= mid) update2(a[k].ls, l, mid, x, v);
    else update2(a[k].rs, mid + 1, r, x, v);
}
void update(int k, int x, int y, int v) {
    update2(t[k].rt, 1, n, y, v);
    int l = t[k].l; int r = t[k].r;
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (x <= mid) update(k << 1, x, y, v);
    else update(k << 1 | 1, x, y, v);
}
int query2(int k, int l, int r, int x, int y) {
    if (!k) return inf;
    if (l == x && r == y) return a[k].mn;
    int mid = (l + r) >> 1;
    if (x > mid) return query2(a[k].rs, mid + 1, r, x, y);
    if (y <= mid) return query2(a[k].ls, l, mid, x, y);
    return min(query2(a[k].ls, l, mid, x, mid), query2(a[k].rs, mid + 1, r, mid + 1, y));
}
int query(int k, int x, int y, int L, int R) {
    int l = t[k].l; int r = t[k].r;
    if (l == x && r == y) return query2(t[k].rt, 1, n, L, R);
    int mid = (l + r) >> 1;
    if (x > mid) return query(k << 1 | 1, x, y, L, R);
    if (y <= mid) return query(k << 1, x, y, L, R);
    return min(query(k << 1, x, mid, L, R), query(k << 1 | 1, mid + 1, y, L, R));
}
