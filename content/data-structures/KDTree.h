/**
* Author: IDK
* Description: KDTree
*/
#pragma once

const int inf = 2e9;
struct node {
	int l, r, d[2], mn[2], mx[2];
} t[2000010];
int n, m, nowd, ans, rt;
bool cmp(node x, node y) {
	if (x.d[nowd] == y.d[nowd]) {
		return x.d[nowd ^ 1] < y.d[nowd ^ 1];
	}
	return x.d[nowd] < y.d[nowd];
}
void pushup(int k) {
	if (t[k].l) {
		t[k].mx[0] = max(t[k].mx[0], t[t[k].l].mx[0]);
		t[k].mx[1] = max(t[k].mx[1], t[t[k].l].mx[1]);
		t[k].mn[0] = min(t[k].mn[0], t[t[k].l].mn[0]);
		t[k].mn[1] = min(t[k].mn[1], t[t[k].l].mn[1]);
	}
	if (t[k].r) {
		t[k].mx[0] = max(t[k].mx[0], t[t[k].r].mx[0]);
		t[k].mx[1] = max(t[k].mx[1], t[t[k].r].mx[1]);
		t[k].mn[0] = min(t[k].mn[0], t[t[k].r].mn[0]);
		t[k].mn[1] = min(t[k].mn[1], t[t[k].r].mn[1]);
	}
}
int build(int l, int r, int d) {
	int mid = (l + r) >> 1;
	nowd = d;
	nth_element(t + l, t + mid, t + r + 1, cmp);
	if (l < mid) t[mid].l = build(l, mid - 1, d ^ 1);
	if (r > mid) t[mid].r = build(mid + 1, r, d ^ 1);
	t[mid].mx[0] = t[mid].mn[0] = t[mid].d[0];
	t[mid].mx[1] = t[mid].mn[1] = t[mid].d[1];
	pushup(mid);
	return mid;
}
int dis(int k, int x, int y) {
	int res = 0;
	if (x > t[k].mx[0]) res += x - t[k].mx[0];
	if (x < t[k].mn[0]) res += t[k].mn[0] - x;
	if (y > t[k].mx[1]) res += y - t[k].mx[1];
	if (y < t[k].mn[1]) res += t[k].mn[1] - y;
	return res;
}
void update(int k) {
	int x = rt, d = 0;
	while (true) {
		t[x].mx[0] = max(t[x].mx[0], t[k].d[0]);
		t[x].mx[1] = max(t[x].mx[1], t[k].d[1]);
		t[x].mn[0] = min(t[x].mn[0], t[k].d[0]);
		t[x].mn[1] = min(t[x].mn[1], t[k].d[1]);
		if (t[k].d[d] < t[x].d[d]) {
			if (!t[x].l) {
				t[x].l = k;
				return;
			}
			x = t[x].l;
		} else {
			if (!t[x].r) {
				t[x].r = k;
				return;
			}
			x = t[x].r;
		}
		d ^= 1;
	}
}
void query(int k, int x, int y) {
	int d, dl, dr;
	d = abs(t[k].d[0] - x) + abs(t[k].d[1] - y);
	ans = min(ans, d);
	if (t[k].l) dl = dis(t[k].l, x, y);
	else dl = inf;
	if (t[k].r) dr = dis(t[k].r, x, y);
	else dr = inf;
	if (dl < dr) {
		if (dl < ans) query(t[k].l, x, y);
		if (dr < ans) query(t[k].r, x, y);
	} else {
		if (dr < ans) query(t[k].r, x, y);
		if (dl < ans) query(t[k].l, x, y);
	}
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d", &t[i].d[0], &t[i].d[1]);
	}
	rt = build(1, n, 0);
	while (m--) {
		int op, x, y;
		scanf("%d%d%d", &op, &x, &y);
		if (op == 1) {
			n++;
			t[n].mx[0] = t[n].mn[0] = t[n].d[0] = x;
			t[n].mx[1] = t[n].mn[1] = t[n].d[1] = y;
			update(n);
		} else {
			ans = inf;
			query(rt, x, y);
			printf("%d\n", ans);
		}
	}
	return 0;
}