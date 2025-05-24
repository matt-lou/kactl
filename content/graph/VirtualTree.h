/**
 * Author: IDK
 * Description: Virtual Tree
 */
#pragma once

void solve()
{
	scanf("%d",&k);
	FOR(i,0,k) scanf("%d",&h[i]);
	sort(h,h+k,cmp);
	cnt2=stk=0;
	stk++;
	st[stk]=1;
	FOR(i,0,k) {
		int f=lca(h[i],st[stk]);
		if (f==st[stk]) {
			stk++;
			st[stk]=h[i];
			continue;
		}
		while (f==lca(h[i],st[stk-1])) {
			add2(st[stk-1],st[stk]);
			stk--;
			f=lca(h[i],st[stk]);
		}
		add2(f,st[stk]);
		st[stk]=f;
		stk++;
		st[stk]=h[i];
	}
	while (stk>1) {
		add2(st[stk-1],st[stk]);
		stk--;
	}
	work(1);
}