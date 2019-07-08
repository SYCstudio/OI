#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
const int maxN=110;
int n;
int lcnt=0,Leaf[maxN],Sz[maxN],isl[maxN];
vector<int> Anc[maxN];
int Mp[maxN][maxN],Fa[maxN];

bool cmp(int a,int b);
void dfs(int u,int fa);
int main()
{
	scanf("%d",&n);
	if (n==2) {
		printf("! 1\n");
		return 0;
	}
	for (int i=1; i<=n; i++) {
		printf("? %d ",n-1);
		for (int j=1; j<=n; j++) if (i!=j) printf("%d ",j);
		printf("\n");
		fflush(stdout);
		int In;
		scanf("%d",&In);
		if (In==n-1) isl[Leaf[++lcnt]=i]=1;
	}
	//cout<<"GetLeaf:";for (int i=1;i<=lcnt;i++) cout<<Leaf[i]<<" ";cout<<endl;
	//cout<<"chose root:"<<Leaf[1]<<endl;
	for (int i=2; i<=lcnt; i++) {
		for (int j=1; j<=n; j++)
			if (isl[j]==0) {
				printf("? 3 %d %d %d\n",Leaf[1],Leaf[i],j);
				fflush(stdout);
				int In;
				scanf("%d",&In);
				if (In==3) ++Sz[j],Anc[i].push_back(j);
			}
	}
	/*
	for (int i=2;i<=lcnt;i++){
	    cout<<Leaf[i]<<":";for (int j=0,sz=Anc[i].size();j<sz;j++) cout<<Anc[i][j]<<" ";cout<<endl;
	}
	cout<<"Sz:";for (int i=1;i<=n;i++) cout<<Sz[i]<<" ";cout<<endl;
	//*/
	for (int i=2; i<=lcnt; i++) {
		sort(Anc[i].begin(),Anc[i].end(),cmp);
		Mp[Leaf[i]][Anc[i][0]]=Mp[Anc[i][0]][Leaf[i]]=1;
		int sz=Anc[i].size();
		for (int j=1; j<sz; j++) Mp[Anc[i][j]][Anc[i][j-1]]=Mp[Anc[i][j-1]][Anc[i][j]]=1;
		Mp[Anc[i][sz-1]][Leaf[1]]=Mp[Leaf[1]][Anc[i][sz-1]]=1;
	}
	/*
	for (int i=1;i<=n;i++){
	    for (int j=1;j<=n;j++)
	        cout<<Mp[i][j];
	    cout<<endl;
	}
	//*/
	dfs(1,0);
	printf("! ");
	for (int i=2; i<=n; i++) printf("%d ",Fa[i]);
	return 0;
}
bool cmp(int a,int b)
{
	return Sz[a]<Sz[b];
}
void dfs(int u,int fa)
{
	Fa[u]=fa;
	for (int i=1; i<=n; i++) if (Mp[u][i]&&i!=fa) dfs(i,u);
	return;
}