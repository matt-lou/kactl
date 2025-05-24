/**
* Author: IDK
* Description: HLD2. Perform dfs1, dfs2 indepedently.
*/
#pragma once
struct node
{
	int l,r,s,x;
}t[400010];
int n,m,rt,Mod,a[100010],b[100010];
int tot,id[100010],fa[100010],sz[100010],top[100010],dep[100010],son[100010];
int cnt,head[100010],to[200010],nxt[200010];
void add(int x,int y) {
	cnt++; to[cnt]=y;
	nxt[cnt]=head[x];
	head[x]=cnt;
}
void pushdown(int k) {
	if (!t[k].x) return;
	t[k<<1].s+=t[k].x*(t[k<<1].r-t[k<<1].l+1);
	t[k<<1|1].s+=t[k].x*(t[k<<1|1].r-t[k<<1|1].l+1);
	t[k<<1].s%=Mod; t[k<<1|1].s%=Mod;
	t[k<<1].x+=t[k].x; t[k<<1|1].x+=t[k].x;
	t[k].x=0;
}
void pushup(int k) {
	t[k].s=t[k<<1].s+t[k<<1|1].s;
	t[k].s%=Mod;
}
void build(int k,int l,int r) {
	t[k].l=l; t[k].r=r;
	if (l==r) {
		t[k].s=b[l]; return;
	}
	int mid=(l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	pushup(k);
}
void update(int k,int x,int y,int w) {
	int l=t[k].l, r=t[k].r;
	if (l==x && r==y) {
		t[k].s+=w*(r-l+1); t[k].s%=Mod;
		t[k].x+=w; return;
	}
	pushdown(k);
	int mid=(l+r)>>1;
	if (x>mid) update(k<<1|1,x,y,w);
	else if (y<=mid)
		update(k<<1,x,y,w);
	else {
		update(k<<1,x,mid,w);
		update(k<<1|1,mid+1,y,w);
	}
	pushup(k);
}
int query(int k,int x,int y) {
	int l=t[k].l, r=t[k].r;
	if (l==x && r==y) return t[k].s;
	pushdown(k);
	int mid=(l+r)>>1;
	if (x>mid)
 		return query(k<<1|1,x,y);
	else if (y<=mid)
		return query(k<<1,x,y);
	else
		return (query(k<<1,x,mid)+query(k<<1|1,mid+1,y))%Mod;
}
void dfs1(int x) {
	sz[x]=1; int mx=0;
	for (int i=head[x];i;i=nxt[i]) {
		int y=to[i];
		if (y==fa[x]) continue;
		fa[y]=x; dep[y]=dep[x]+1;
		dfs1(y); sz[x]+=sz[y];
		if (sz[y]>mx) {
			mx=sz[y]; son[x]=y;
		}
	}
}
void dfs2(int x,int tf) {
	tot++; id[x]=tot;
	top[x]=tf; b[tot]=a[x];
	if (!son[x]) return;
	dfs2(son[x],tf);
	for (int i=head[x];i;i=nxt[i]) {
		int y=to[i];
		if (y==fa[x] || y==son[x]) continue;
		dfs2(y,y);
	}
}
void update2(int x,int y,int w) {
	int fx=top[x], fy=top[y];
	while (fx!=fy) {
		if (dep[fx]<dep[fy]) {
			swap(x,y); swap(fx,fy);
		}
		update(1,id[fx],id[x],w);
		x=fa[fx]; fx=top[x];
	}
	if (dep[x]>dep[y]) swap(x,y);
	update(1,id[x],id[y],w);
}
int query2(int x,int y){
	int res=0, fx=top[x], fy=top[y];
	while (fx!=fy) {
		if (dep[fx]<dep[fy]) {
			swap(x,y); swap(fx,fy);
		}
		res=(res+query(1,id[fx],id[x]))%Mod;
		x=fa[fx]; fx=top[x];
	}
	if (dep[x]>dep[y]) swap(x,y);
	res=(res+query(1,id[x],id[y]))%Mod;
	return res;
}