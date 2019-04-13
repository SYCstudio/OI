#include<bits/stdc++.h>
using namespace std;

const int maxN=101000;

int n,Q;
vector<int> T[maxN],Vt[maxN];
pair<int,int> Qn[maxN];
int Mark[maxN],Label[maxN],Dep[maxN],Cov[maxN],Wht[maxN];

void dfs_init(int u,int dep);
void dfs_build(int u,int lst,int wht);
void dfs_mark(int u);
void dfs_del(int u);
void dfs_rebuild(int u,int cov,int ldep);
int main(){
	scanf("%d%d",&n,&Q);
	for (int i=2;i<=n;i++){
		int fa;scanf("%d",&fa);T[fa].push_back(i);
	}
	for (int i=1;i<=Q;i++) scanf("%d%d",&Qn[i].first,&Qn[i].second);

	int srt=sqrt(Q);dfs_init(1,1);
	for (int l=1,r;l<=Q;l=r+1){
		r=min(Q,l+srt-1);Mark[1]=1;
		for (int i=l;i<=r;i++) Mark[Qn[i].second]=1;
		dfs_build(1,0);
		for (int i=l;i<=r;i++)
			if (Qn[i].first==1) dfs_mark(Qn[i].second);
			else if (Qn[i].first==2) dfs_del(Qn[i].second);
			else Label[Qn[i].second]?puts("black"):puts("white");
		for (int i=1;i<=n;i++) cout<<Label[i]<<" ";cout<<endl;
		dfs_rebuild(1,0,0);
		cout<<"After:"<<r<<endl;
		for (int i=1;i<=n;i++) cout<<Label[i]<<" ";cout<<endl;
	}
	return 0;
}
void dfs_init(int u,int dep){
	Dep[u]=dep;for (int i=0,sz=T[u].size();i<sz;i++) dfs_init(T[u][i],dep+1);return;
}
void dfs_build(int u,int lst,int wht){
	if (Mark[u]){
		if (lst) Vt[lst].push_back(u);
		lst=u;Wht[u]=
	}
	for (int i=0,sz=T[u].size();i<sz;i++) dfs_build(T[u][i],lst);return;
}
void dfs_mark(int u){
	Label[u]++;Cov[u]=0;
	for (int i=0,sz=Vt[u].size();i<sz;i++) if (Dep[u]+Label[u]>Dep[Vt[u][i]]) dfs_mark(Vt[u][i]);
	return;
}
void dfs_del(int u){
	Label[u]=0;Cov[u]=1;for (int i=0,sz=Vt[u].size();i<sz;i++) dfs_del(Vt[u][i]);return;
}
void dfs_rebuild(int u,int cov,int ldep){
	cov|=Cov[u];ldep+=Label[u];Vt[u].clear();
	if (!Mark[u]) if (cov||ldep==0) Label[u]=0;else Label[u]=1;
	else Label[u]=(Label[u]>=1);
	for (int i=0,sz=T[u].size();i<sz;i++) dfs_rebuild(T[u][i],cov,max(0,ldep-1));
	Cov[u]=Mark[u]=0;return;
}
