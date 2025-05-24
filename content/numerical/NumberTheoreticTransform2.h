/**
* Author: IDK
* Description: NTT
*/
int N, pw3[maxn], pwinv3[maxn], w[maxn];
void polyclear(int *a, int n) {
    FOR(i,0,n) a[i] = 0;
}
void polycopy(int *a, int *b, int n) {
    FOR(i,0,n) b[i] = a[i];
}
void polyadd(int *a, int *b, int n) {
    FOR(i,0,n) a[i] = (a[i] + b[i]) % Mod;
}
void pre() {
    int p = pw(3, (Mod - 1) / N);
    pw3[0] = 1;
    FOR(i,1,N+1) pw3[i] = 1LL * pw3[i - 1] * p % Mod;
}
void precal(int n, int f) {
    int m = n >> 1; int tmp = N / n;
    if (f == 1)
        for (int i = 0, j = 0; i < m; i++, j += tmp)
            w[i] = pw3[j];
    else
        for (int i = 0, j = N; i < m; i++, j -= tmp)
            w[i] = pw3[j];
}
void rader(int *a, int n) {
    for (int i = 0, j = 0; i < n; i++) {
        if (i > j) swap(a[i], a[j]);
        int k = n;
        do {
            k >>= 1; j ^= k;
        } while (j < k);
    }
}
void ntt(int *a, int f, int n) {
    rader(a, n);
    for (int i = 2; i <= n; i <<= 1) {
        int m = i >> 1;
        precal(i, f);
        for (int j = 0; j < n; j += i) {
            for (int k = 0; k < m; k++) {
                int x = 1LL * a[j + k + m] * w[k] % Mod;
                a[j + k + m] = a[j + k] - x < 0 ? a[j + k] - x + Mod : a[j + k] - x;
                a[j + k] = a[j + k] + x >= Mod ? a[j + k] + x - Mod : a[j + k] + x;
            }
        }
    }
    if (f == -1) {
        int inv = pw(n, Mod - 2);
        for (int i = 0; i < n; i++) a[i] = 1LL * a[i] * inv % Mod;
    }
}
void polymul(int *a, int *b, int n) {
    static int tmp[maxn];
    polycopy(b, tmp, n);
    ntt(a, 1, n);
    ntt(tmp, 1, n);
    FOR(i,0,n) a[i] = 1LL * a[i] * tmp[i] % Mod;
    ntt(a, -1, n);
}
void polyinv(int *a, int *b, int n) {
    static int tmp[maxn], A[maxn];
    int m = n;
    b[0] = pw(a[0], Mod - 2);
    n = 2;
    while ((n >> 1) < m) {
        polycopy(b, tmp, n >> 1);
        n <<= 1;
        for (int i = n >> 2; i <= n; i++) b[i] = tmp[i] = 0;
        polymul(b, b, n); polycopy(a, A, n >> 1);
        for (int i = n >> 1; i <= n; i++) b[i] = A[i] = 0;
        polymul(b, A, n);
        for (int i = 0; i < (n >> 1); i++)
            b[i] = (2LL * tmp[i] - b[i] + Mod) % Mod;
    }
}
void polyder(int *a, int *b, int n) {
    FOR(i,1,n) b[i - 1] = 1LL * a[i] * i % Mod;
    b[n - 1] = 0;
}
void polyint(int *a, int *b, int n) {
    for (int i = n - 1; i; i--) b[i] = 1LL * a[i - 1] * pw(i, Mod - 2) % Mod;
    b[0] = 0;
}
void polyln(int *a, int *b, int n) {
    static int tmp[maxn];
    polyinv(a, b, n); polyder(a, tmp, n);
    int len = 1;
    while ((len >> 1) < n) len <<= 1;
    for (int i = n; i < len; i++) b[i] = tmp[i] = 0;
    polymul(tmp, b, len); polyint(tmp, b, n);
}
void polyexp(int *a, int *b, int n) {
    static int tmp[maxn];
    b[0] = 1; int m = n; n = 2;
    while ((n >> 1) < m) {
        polyln(b, tmp, n);
        FOR(i,0,n) tmp[i] = (Mod - tmp[i]) % Mod;
        tmp[0] = (tmp[0] + 1) % Mod;
        polyadd(tmp, a, n); n <<= 1;
        for (int i = n >> 1; i < n; i++) b[i] = tmp[i] = 0;
        polymul(b, tmp, n);
        for (int i = n >> 1; i < n; i++) b[i] = 0;
    }
}
void polypw(int *a, int *b, ll y, int n) {
    static int tmp[maxn];
    int d = 0, p;
    while (!a[d] && d < n) d++;
    if (d >= n) {
        polycopy(a, b, n); return;
    }
    p = a[d];
    int inv = pw(p, Mod - 2);
    for (int i = d; i < n; i++) tmp[i - d] = 1LL * inv * a[i] % Mod;
    polyln(tmp, b, n - d);
    for (int i = 0; i < n - d; i++) b[i] = 1LL * b[i] * y % Mod;
    polyexp(b, tmp, n - d); polyclear(b, n);
    p = pw(p, y);
    for (ll i = y * d; i < n; i++) b[i] = 1LL * tmp[(ll) i - y * d] * p % Mod;
}
int m, a[maxn], ans[maxn];
int main() {
    ll k;
    // Read in m,k,a[0..m)
    N = 1;
    while ((N >> 1) < m) N <<= 1;
    pre();
    polypw(a, ans, k, m);
    for (int i = 0; i < m; i++) printf("%d ", ans[i]);
    return 0;
}