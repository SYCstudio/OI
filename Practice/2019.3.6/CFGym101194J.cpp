#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

#define NAME "B"
const int maxT=33;
const int maxN=maxT*maxT*2;
const int maxM=maxN*10;
const int inf=100000000;

class Edge{
    public:
    int v,flow,w;
};

int n,m,S,T,M1[maxT][maxT],M2[maxT][maxT],Mark[maxT][maxT],Id[maxT][maxT];
int ecnt=-1,Hd[maxN],Nt[maxM],V[maxM];
Edge E[maxM];
int Dst[maxN],Flow[maxN],Path[maxN],inq[maxN],Q[maxN];

void Add(int u,int v,int flow,int w);
bool Spfa();
int main(){
    int Case;scanf("%d",&Case);
    for (int ci=1;ci<=Case;ci++){
        printf("Case #%d: ",ci);
    scanf("%d%d",&n,&m);ecnt=-1;memset(Hd,-1,sizeof(Hd));memset(Mark,0,sizeof(Mark));
    for (int i=1,idcnt=0;i<=n;i++) for (int j=1;j<=m;j++) Id[i][j]=++idcnt;
    for (int i=1;i<=n;i++) for (int j=1;j<m;j++) scanf("%d",&M1[i][j]);
    for (int i=1;i<n;i++) for (int j=1;j<=m;j++) scanf("%d",&M2[i][j]);
    int K;scanf("%d",&K);
    while (K--){
        int x,y;scanf("%d%d",&x,&y);Mark[x][y]=1;
    }
    S=n*m*2+1;T=S+1;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++)
            if ((i+j)&1){
                Add(S,Id[i][j],1,0);Add(Id[i][j]+n*m,T,1,0);
                if (i!=1) Add(Id[i][j],Id[i-1][j]+n*m,1,M2[i-1][j]);
                if (i!=n) Add(Id[i][j],Id[i+1][j]+n*m,1,M2[i][j]);
                if (!Mark[i][j]) Add(Id[i][j],Id[i][j]+n*m,1,0);
            }
            else{
                Add(S,Id[i][j],1,0);Add(Id[i][j]+n*m,T,1,0);
                if (j!=1) Add(Id[i][j],Id[i][j-1]+n*m,1,M1[i][j-1]);
                if (j!=m) Add(Id[i][j],Id[i][j+1]+n*m,1,M1[i][j]);
                if (!Mark[i][j]) Add(Id[i][j],Id[i][j]+n*m,1,0);
            }
    int flow=0,Ans=0;
    while (Spfa()){
        //cout<<Flow[T]<<" "<<Dst[T]<<endl;
        flow+=Flow[T];Ans+=Dst[T]*Flow[T];
        int now=T;
        while (now!=S){
            E[Path[now]].flow-=Flow[T];
            E[Path[now]^1].flow+=Flow[T];
            now=E[Path[now]^1].v;
        }
    }
    flow==n*m?printf("%d\n",Ans):puts("Impossible");
    }
}
void Add(int u,int v,int flow,int w){
    //cout<<"A:"<<u<<" "<<v<<" "<<flow<<" "<<w<<endl;
    Nt[++ecnt]=Hd[u];Hd[u]=ecnt;E[ecnt]=((Edge){v,flow,w});
    Nt[++ecnt]=Hd[v];Hd[v]=ecnt;E[ecnt]=((Edge){u,0,-w});
    return;
}
bool Spfa(){
    memset(Dst,128,sizeof(Dst));Dst[S]=0;int ql=0,qr=1;Q[1]=S;Flow[S]=inf;inq[S]=1;
    while (ql!=qr){
        ++ql;ql%=maxN;int u=Q[ql];
        for (int i=Hd[u];i!=-1;i=Nt[i])
            if (E[i].flow&&Dst[E[i].v]<Dst[u]+E[i].w){
                Dst[E[i].v]=Dst[u]+E[i].w;Flow[E[i].v]=min(E[i].flow,Flow[u]);Path[E[i].v]=i;
                if (!inq[E[i].v]){
                    ++qr;qr%=maxN;Q[qr]=E[i].v;inq[E[i].v]=1;
                }
            }
        inq[u]=0;
    }
    return Dst[T]!=Dst[0];
}