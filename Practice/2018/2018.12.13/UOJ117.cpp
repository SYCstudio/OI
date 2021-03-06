#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int maxM=202000<<1;
const int inf=2147483647;

int Graph,n,m;
int edgecnt=1,Head[maxN],Next[maxM],V[maxM];
int top,St[maxM];
int D1[maxN],D2[maxN];
bool del[maxM];

void Add_Edge(int u,int v);
void dfs(int u);

int main(){
	mem(Head,-1);
	scanf("%d%d%d",&Graph,&n,&m);
	for (int i=1;i<=m;i++){
		int u,v;scanf("%d%d",&u,&v);
		Add_Edge(u,v);
	}
	if (Graph==1) for (int i=1;i<=n;i++) if (D1[i]&1) {printf("NO\n");return 0;}
	if (Graph==2) for (int i=1;i<=n;i++) if (D1[i]!=D2[i]) {printf("NO\n");return 0;}
	for (int i=1;i<=n;i++)
		if (Head[i]!=-1){
			dfs(i);break;
		}
	//cout<<"top:"<<top<<endl;
	if (top!=m) printf("NO\n");
	else{
		printf("YES\n");
		for (int i=m;i>=1;i--)
			if (Graph==1) printf("%d ",(St[i]>>1)*((St[i]&1)?(-1):(1)));
			else printf("%d ",St[i]>>1);
	}
	return 0;
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	if (Graph==1){
		Next[++edgecnt]=Head[v];Head[v]=edgecnt;V[edgecnt]=u;
		D1[u]++;D1[v]++;
	}
	else D1[u]++,D2[v]++,++edgecnt;
	return;
}

void dfs(int u){
	for (int &i=Head[u];i!=-1;)
		if (del[i>>1]==0){
			del[i>>1]=1;int j=i;i=Next[i];
			dfs(V[j]);St[++top]=j;
		}
		else i=Next[i];
	return;
}
