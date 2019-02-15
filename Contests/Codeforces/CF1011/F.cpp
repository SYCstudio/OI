#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1000100;
const int inf=2147483647;

int n,m;
int Son[maxN][2],Opt[maxN];
char str[10];
int F[maxN],Cover[maxN],Cnt[maxN];

void dfs1(int u);
void dfs2(int u,int c);

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%s",str);
		if (str[0]=='A'){
			Opt[i]=1;
			int u,v;scanf("%d%d",&u,&v);
			Son[i][0]=u;Son[i][1]=v;
		}
		if (str[0]=='O'){
			Opt[i]=2;
			int u,v;scanf("%d%d",&u,&v);
			Son[i][0]=u;Son[i][1]=v;
		}
		if (str[0]=='X'){
			Opt[i]=3;Cnt[i]=1;
			int u,v;scanf("%d%d",&u,&v);
			Son[i][0]=u;Son[i][1]=v;
		}
		if (str[0]=='N'){
			Opt[i]=4;Cnt[i]=1;
			int u;scanf("%d",&u);
			Son[i][0]=u;
		}
		if (str[0]=='I'){
			Opt[i]=5;scanf("%d",&F[i]);
		}
	}
	dfs1(1);

	for (int i=1;i<=n;i++)
		if (Opt[i]==1){
			if (F[Son[i][0]]==0) Cover[Son[i][1]]=1;
			if (F[Son[i][1]]==0) Cover[Son[i][0]]=1;
		}
		else if (Opt[i]==2){
			if (F[Son[i][0]]==1) Cover[Son[i][1]]=1;
			if (F[Son[i][1]]==1) Cover[Son[i][0]]=1;
		}

	dfs2(1,Cover[1]);

	//for (int i=1;i<=n;i++) cout<<Cover[i]<<" ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<Cnt[i]<<" ";cout<<endl;

	for (int i=1;i<=n;i++)
		if (Opt[i]==5){
			if (Cover[i]) printf("%d",F[1]);
			else printf("%d",F[1]^1);
		}
	return 0;
}

void dfs1(int u)
{
	if (Opt[u]==5) return;
	else if (Opt[u]==4){
		Cnt[Son[u][0]]+=Cnt[u];
		dfs1(Son[u][0]);
		F[u]=!F[Son[u][0]];
	}
	else{
		Cnt[Son[u][0]]+=Cnt[u];Cnt[Son[u][1]]+=Cnt[u];
		dfs1(Son[u][0]);dfs1(Son[u][1]);
		if (Opt[u]==1) F[u]=F[Son[u][0]]&F[Son[u][1]];
		if (Opt[u]==2) F[u]=F[Son[u][0]]|F[Son[u][1]];
		if (Opt[u]==3) F[u]=F[Son[u][0]]^F[Son[u][1]];
	}
	return;
}

void dfs2(int u,int c){
	Cover[u]|=c;
	if (Opt[u]==5) return;
	else if (Opt[u]==4) dfs2(Son[u][0],Cover[u]);
	else{
		dfs2(Son[u][0],Cover[u]);
		dfs2(Son[u][1],Cover[u]);
	}
	return;
}
