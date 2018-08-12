#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=30100;
const int maxSqrt=131;
const int maxNode=maxN*maxSqrt;
const int maxM=maxNode*8;
const int inf=2147483647;

class HData
{
public:
	int u,dist;
};

int n,m;
int Id[maxN][maxSqrt];
int edgecnt=-1,Head[maxNode],Next[maxM],V[maxM],W[maxM];
int Dist[maxNode];
priority_queue<HData> H;
queue<int> Q;
bool vis[maxNode];

int Input();
void Add_Edge(int u,int v,int w);
bool operator < (HData A,HData B);

int main(){
	mem(Head,-1);
	n=Input();m=Input();
	//scanf("%d%d",&n,&m);
	int size=min(130,(int)sqrt(n));
	int idcnt=0;
	for (int i=1;i<=n;i++) for (int j=0;j<=size;j++) Id[i][j]=++idcnt;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=size;j++){
			if (i+j<=n) Add_Edge(Id[i][j],Id[i+j][j],1),Add_Edge(Id[i+j][j],Id[i][j],1);
			Add_Edge(Id[i][j],Id[i][0],0);
		}

	/*
	for (int i=1;i<=idcnt;i++)
		for (int j=Head[i];j!=-1;j=Next[j])
			cout<<i<<" -> "<<V[j]<<" "<<W[j]<<endl;
	//*/

	int b0,b1;
	for (int i=0;i<m;i++){
		int b=Input(),p=Input();//scanf("%d%d",&b,&p);
		b++;
		if (i==0) b0=b;
		if (i==1) b1=b;
		if (p<=size){
			Add_Edge(Id[b][0],Id[b][p],0);
		}
		else{
			for (int j=b-p,k=1;j>=1;j-=p,k++) Add_Edge(Id[b][0],Id[j][0],k);
			for (int j=b+p,k=1;j<=n;j+=p,k++) Add_Edge(Id[b][0],Id[j][0],k);
		}
	}

	for (int i=1;i<=idcnt;i++) Dist[i]=inf;
	Dist[Id[b0][0]]=0;Q.push(Id[b0][0]);vis[Id[b0][0]]=1;
	do{
		int u=Q.front();Q.pop();
		for (int i=Head[u];i!=-1;i=Next[i])
			if (Dist[V[i]]>Dist[u]+W[i]){
				Dist[V[i]]=Dist[u]+W[i];
				if (vis[V[i]]==0){
					Q.push(V[i]);vis[V[i]]=1;
				}
			}
		vis[u]=0;
	}
	while (!Q.empty());
	/*H.push((HData){Id[b0][0],0});
	do{
		int u=H.top().u;H.pop();
		if (u==Id[b1][0]) break;
		if (vis[u]) continue;
		vis[u]=1;
		for (int i=Head[u];i!=-1;i=Next[i])
			if (Dist[V[i]]>Dist[u]+W[i]) H.push((HData){V[i],Dist[V[i]]=Dist[u]+W[i]});
	}
	while (!H.empty());
	//*/

	/*
	for (int i=1;i<=n;i++){
		for (int j=0;j<=size;j++)
			if (Dist[Id[i][j]]==inf) cout<<"inf ";
			else cout<<Dist[Id[i][j]]<<" ";
		cout<<endl;
	}
	//*/

	if (Dist[Id[b1][0]]==inf) printf("-1\n");
	else printf("%d\n",Dist[Id[b1][0]]);

	return 0;
}

int Input(){
	int x=0;char ch=getchar();
	while ((ch<'0')||(ch>'9')) ch=getchar();
	while ((ch>='0')&&(ch<='9')) x=x*10+ch-48,ch=getchar();
	return x;
}

void Add_Edge(int u,int v,int w){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;W[edgecnt]=w;
	return;
}

bool operator < (HData A,HData B){
	return A.dist>B.dist;
}
