#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=3010;
const int maxM=maxN*maxN;
const int inf=2147473647;

class HData
{
public:
	int u,dist;
};

int n,m;
bool wd[maxN];
int edgecnt,Head[maxN],Next[maxM],V[maxM],W[maxM];
int Dist[maxN];
bool vis[maxN];
priority_queue<HData> H;

void Add_Edge(int u,int v,int w);
bool operator < (HData A,HData B);

int main(){
	mem(Head,-1);
	scanf("%d%d",&n,&m);
	int g=0,mn=inf;
	for (int i=1;i<=n;i++){
		int len;scanf("%d",&len);
		for (int j=max(len-m,1);j<=len;j++){
			wd[j]=1;mn=min(mn,j);
			if (g==0) g=j;
			else g=__gcd(g,j);
		}
	}
	if ((wd[1])||(g!=1)){
		printf("-1\n");return 0;
	}
	//for (int i=1;i<20;i++) cout<<wd[i]<<" ";cout<<endl;
	for (int i=0;i<mn;i++){
		Dist[i]=inf;
		for (int j=1;j<maxN;j++)
			if (wd[j]) Add_Edge(i,(i+j)%mn,j);
	}
	Dist[0]=0;H.push((HData){0,0});
	do{
		int u=H.top().u;H.pop();
		if (vis[u]) continue;vis[u]=1;
		for (int i=Head[u];i!=-1;i=Next[i])
			if (Dist[V[i]]>Dist[u]+W[i]){
				Dist[V[i]]=Dist[u]+W[i];
				H.push((HData){V[i],Dist[V[i]]});
			}
	}
	while (!H.empty());
	//for (int i=0;i<mn;i++) cout<<Dist[i]<<" ";cout<<endl;
	int Ans=0;
	for (int i=0;i<mn;i++)
		if (Dist[i]!=inf) Ans=max(Ans,Dist[i]-mn);
		else Ans=max(Ans,i);
	printf("%d\n",Ans);return 0;
}

void Add_Edge(int u,int v,int w){
	//cout<<"Add:"<<u<<" "<<v<<" "<<w<<endl;
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;W[edgecnt]=w;
	return;
}

bool operator < (HData A,HData B){
	return A.dist>B.dist;
}
