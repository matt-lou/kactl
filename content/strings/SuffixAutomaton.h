/**
* Author: IDK
* Description: Suffix Automaton
*/
#pragma once

struct SAM {
    int tot, lst, rt;
    int link[maxn], len[maxn], nxt[maxn][26];
    int cnt[maxn], sum[maxn], tp[maxn];
    int newnode(int l) {
        memset(nxt[tot], 0, sizeof(nxt[tot]));
        cnt[tot] = 0;
        len[tot] = l;
        link[tot] = 0;
        return tot++;
    }
    void extend(int ch) {
        int p = lst;
        int cur = newnode(len[p] + 1);
        while (!nxt[p][ch]) {
            nxt[p][ch] = cur;
            p = link[p];
        }
        int q = nxt[p][ch];
        if (q == cur) {
            link[cur] = rt;
        } else if (len[q] == len[p] + 1) {
            link[cur] = q;
        } else {
            int nq = newnode(len[p] + 1);
            link[nq] = link[q];
            link[cur] = link[q] = nq;
            memcpy(nxt[nq], nxt[q], sizeof(nxt[q]));
            while (nxt[p][ch] == q) {
                nxt[p][ch] = nq;
                p = link[p];
            }
        }
        cnt[cur] = 1;
        lst = cur;
        ans += len[cur] - len[link[cur]];
    }
    void work() {
        FOR(i,0,tot) sum[len[i]]++;
        FOR(i,1,len[lst]+1) sum[i] += sum[i - 1];
        FOR(i,0,tot) tp[sum[len[i]]--] = i;
        for (int i = tot; i; i--) {
            int p = tp[i];
            cnt[link[p]] += cnt[p];
            if (cnt[p] > 1) ans = max(ans, 1LL * cnt[p] * len[p]);
        }
    }

    void init(char *s) {
        int l = strlen(s);
        tot = 0;
        rt = newnode(0);
        lst = rt;
        FOR(i,0,l) extend(s[i] - 'a');
        work();
    }
} sam;