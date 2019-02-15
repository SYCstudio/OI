#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=3010;
const int maxM=maxN*maxN;
const int inf=2147483647;

int A,B,M;
int K1[maxN],K2[maxN];
bool Mp[maxN][maxN];
int timcnt,Tim[maxN],Match[maxN];
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];

void Add_Edge(int u,int v);
bool Hungary(int u);
int Solve();
int Count(int key);

int main(){
	//int TTT;scanf("%d",&TTT);
	mem(Head,-1);
	scanf("%d%d%d",&A,&B,&M);
	for (int i=1;i<=A;i++) scanf("%d",&K1[i]);
	for (int i=1;i<=B;i++) scanf("%d",&K2[i]);
	for (int i=1;i<=M;i++){
		int u,v;scanf("%d%d",&u,&v);
		Mp[u][v]=1;
	}

	for (int i=1;i<=B;i++)
		for (int j=i+1;j<=B;j++)
			if ( ((K2[i]^K2[j])&1) && ( (Count(K2[i]|K2[j])&1)==0) )
				Add_Edge(i,j),Add_Edge(j,i);

	timcnt++;
	int Ans=Solve();
	for (int i=1;i<=A;i++)
		for (int j=i;j<=A;j++)
			if ((i==j)||( (K1[i]^K1[j])&1)){
				timcnt++;int notingraph=0;
				for (int k=1;k<=B;k++) if ((!Mp[i][k])||(!Mp[j][k])) Tim[k]=timcnt,notingraph++;
				Ans=max(Ans,Solve()-notingraph+1+(i!=j));
			}
	printf("%d\n",Ans);return 0;
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

int Solve(){
	mem(Match,-1);
	int cnt=0;
	for (int i=1;i<=B;i++)
		if ((Match[i]==-1)&&(Tim[i]!=timcnt))
			cnt+=Hungary(i);
	return B-cnt;
}

bool Hungary(int u){
	Tim[u]=timcnt;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (Tim[V[i]]!=timcnt){
			Tim[V[i]]=timcnt;
			if ((Match[V[i]]==-1)||(Hungary(Match[V[i]]))){
				Match[u]=V[i];Match[V[i]]=u;return 1;
			}
		}
	return 0;
}

int Count(int key){
	int ret=0;
	while (key) key-=(key)&(-key),ret++;
	return ret;
}
