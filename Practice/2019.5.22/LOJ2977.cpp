#include<bits/stdc++.h>
using namespace std;

#define pw(x) (1<<(x))
#define mp make_pair
#define ft first
#define sd second
#define Min(x,y) x=min(x,y)
const int maxN=300;
const int maxK=5;
const int F1[]={1,0,-1,0};
const int F2[]={0,1,0,-1};
const int TIMES=250;
const int inf=1000000000;

int n,m,K,idcnt,Id[maxN][maxN],Gt[maxN];
int Val[maxN],TVal[maxN],Knd[maxN],F[pw(maxK)+10][maxN],vis[maxN],viscnt;
//priority_queue<pair<int,int> > H;
queue<int> Qu;
pair<int,int> P[maxN];

pair<int,int> Work();
int main(){
    srand(20020622);
    int Case;scanf("%d",&Case);
    while (Case--){
	memset(Id,0,sizeof(Id));memset(Val,0,sizeof(Val));idcnt=0;
	scanf("%d%d%d",&n,&m,&K);
	for (int i=1;i<=n;i++)
	    for (int j=1;j<=m;j++) Id[i][j]=++idcnt,scanf("%d",&Knd[Id[i][j]]),P[Id[i][j]]=mp(i,j);
	for (int i=1;i<=idcnt;i++) scanf("%d",&Val[i]);
	pair<int,int> Ans=mp(inf,inf);
	for (int ti=1;ti<=TIMES;ti++) Ans=min(Ans,Work());
	if (Ans.ft==inf) puts("-1 -1");
	else printf("%d %d\n",Ans.ft,Ans.sd);
    }
    return 0;
}
pair<int,int> Work(){
    for (int i=1;i<=idcnt;i++) Gt[i]=rand()%K;
    int l=0,r=2e6,ans1=inf,ans2=inf,PP=pw(K);
    while (l<=r){
	int mid=(l+r)>>1;memset(F,63,sizeof(F));
	for (int i=1;i<=idcnt;i++) TVal[i]=Val[i]<=mid?1000:1001;
	for (int i=1;i<=idcnt;i++) if (Knd[i]!=-1) F[pw(Gt[Knd[i]])][i]=TVal[i];
	for (int S=0;S<PP;S++){
	    memset(vis,0,sizeof(vis));
	    for (int x=1;x<=n;x++)
		for (int y=1;y<=m;y++){
		    for (int nS=(S-1)&S;nS;nS=(nS-1)&S)
			Min(F[S][Id[x][y]],F[nS][Id[x][y]]+F[S^nS][Id[x][y]]-TVal[Id[x][y]]);
		    if (F[S][Id[x][y]]!=F[0][0]) Qu.push(Id[x][y]),vis[Id[x][y]]=1;
		}
	    while (!Qu.empty()){
		int u=Qu.front();Qu.pop();
		int x=P[u].ft,y=P[u].sd;
		for (int f=0;f<4;f++){
		    int xx=x+F1[f],yy=y+F2[f];
		    if (xx<=0||yy<=0||xx>n||yy>m||Knd[Id[xx][yy]]==-1) continue;
		    if (F[S][Id[xx][yy]]>F[S][Id[x][y]]+TVal[Id[xx][yy]]){
			F[S][Id[xx][yy]]=F[S][Id[x][y]]+TVal[Id[xx][yy]];
			if (vis[Id[xx][yy]]==0){
			    Qu.push(Id[xx][yy]);vis[Id[x][y]]=1;
			}
		    }
		}
		vis[u]=0;
	    }
	}
	int Ans=inf;
	for (int i=1;i<=idcnt;i++) Ans=min(Ans,F[PP-1][i]);
	int c1=Ans/1000,c2=Ans%1000,ck=(c1+1)/2;
	ans1=c1;
	if (ck+c2<=c1) ans2=min(ans2,mid),r=mid-1;
	else l=mid+1;
    }
    return mp(ans1,ans2);
}
