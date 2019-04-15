#include<bits/stdc++.h>
using namespace std;

const int maxN=101000;

int n,Q;
vector<int> T[maxN],Vt[maxN];
pair<int,int> Qn[maxN];
int Mark[maxN],Label[maxN],Dep[maxN],Wht[maxN],Cov[maxN];

void dfs_build(int u,int lst,int wht,int dep);
void dfs_mark(int u);
void dfs_del(int u);
void dfs_rebuild(int u,int cov,int ldep);
int main(){
    scanf("%d%d",&n,&Q);
    for (int i=2;i<=n;i++){
	int fa;scanf("%d",&fa);T[fa].push_back(i);
    }
    for (int i=1;i<=Q;i++) scanf("%d%d",&Qn[i].first,&Qn[i].second);

    int srt=sqrt(Q);
    for (int l=1,r;l<=Q;l=r+1){
	r=min(Q,l+srt-1);
	for (int i=l;i<=r;i++) Mark[Qn[i].second]=1;
	dfs_build(1,0,0,0);
	for (int i=l;i<=r;i++)
	    if (Qn[i].first==1) dfs_mark(Qn[i].second);
	    else if (Qn[i].first==2) dfs_del(Qn[i].second);
	    else Label[Qn[i].second]?puts("black"):puts("white");
	dfs_rebuild(1,0,Cov[1]);
    }
    return 0;
}
void dfs_build(int u,int lst,int wht,int dep){
    if (Mark[u]&&lst){
	Vt[lst].push_back(u);
	Wht[u]=wht;Dep[u]=dep;
    }
    for (int i=0,sz=T[u].size();i<sz;i++)
	if (Mark[u]) dfs_build(T[u][i],u,1,1);
	else dfs_build(T[u][i],lst,wht+(Label[u]==0),dep+1);
    return;
}
void dfs_mark(int u){
    Label[u]++;
    for (int i=0,sz=Vt[u].size();i<sz;i++) if (Label[u]>Wht[Vt[u][i]]) dfs_mark(Vt[u][i]);
    return;
}
void dfs_del(int u){
    Label[u]=0;Cov[u]=1;for (int i=0,sz=Vt[u].size();i<sz;i++) Wht[Vt[u][i]]=Dep[Vt[u][i]],dfs_del(Vt[u][i]);return;
}
void dfs_rebuild(int u,int cov,int ldep){
    cov|=Cov[u];
    if (!Mark[u]) Label[u]=ldep+(Label[u]&&!cov);
    for (int i=0,sz=T[u].size();i<sz;i++) dfs_rebuild(T[u][i],cov,max(0,Label[u]-1));
    Label[u]=(Label[u]>=1);
    Cov[u]=Mark[u]=0;Vt[u].clear();return;
}
