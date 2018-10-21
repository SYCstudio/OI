#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define IL inline

const int maxN=101000;
const int maxM=maxN<<1;
const int maxBit=18;
const int inf=2147483647;

class Modify
{
public:
    int pos,p,q;
};

class Question
{
public:
    int u,v,id,tim;
};

int n,m,Q;
ll nowans;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int Kind[maxN],Val[maxN],Wal[maxN],Cal[maxN],CCal[maxN];
int blocksize,blockcnt,top,St[maxN],Belong[maxN];
int dfncnt,dfnseq[maxN*5],Log[maxN*5],fst[maxN],lst[maxN];
int Depth[maxN],mn[maxBit][maxN*2],Fa[maxN];
Modify My[maxN];
Question Qn[maxN];
bool vis[maxN];
int Cnt[maxN];
ll Ans[maxN];

IL void Add_Edge(int u,int v);
void dfs(int u,int fa);
bool cmp(Question A,Question B);
IL void TimAdd(int t);
IL void TimBack(int t);
IL int LCA(int u,int v);
IL void Move(int u,int v);
IL void Reverse(int u);

int main()
{
    for (int i=1;i<maxN*5;i++) Log[i]=log2(i);
    mem(Head,-1);
    scanf("%d%d%d",&n,&m,&Q);
    for (int i=1;i<=m;i++) scanf("%d",&Val[i]);
    for (int i=1;i<=n;i++) scanf("%d",&Wal[i]);

    for (int i=1;i<n;i++)
    {
        int u,v;scanf("%d%d",&u,&v);
        Add_Edge(u,v);
    }
    for (int i=1;i<=n;i++) scanf("%d",&Cal[i]),CCal[i]=Cal[i];

    blocksize=pow(n,0.6666666);Depth[1]=1;
    dfs(1,0);

    //cout<<dfncnt<<endl;
    //for (int i=1;i<=dfncnt;i++) cout<<dfnseq[i]<<" ";cout<<endl;
    
    for (int i=1;i<=dfncnt;i++) mn[0][i]=dfnseq[i];
    for (int i=1;i<maxBit;i++)
        for (int j=1;j<=dfncnt;j++)
            if (j+(1<<(i-1))<=dfncnt){
                if (Depth[mn[i-1][j]]<=Depth[mn[i-1][j+(1<<(i-1))]]) mn[i][j]=mn[i-1][j];
                else mn[i][j]=mn[i-1][j+(1<<(i-1))];
            }

    int tcnt=0,qcnt=0;
    for (int i=1;i<=Q;i++)
    {
        int opt;scanf("%d",&opt);
        if (opt==0)
        {
            int pos,val;scanf("%d%d",&pos,&val);
            My[++tcnt]=((Modify){pos,Cal[pos],val});
            Cal[pos]=val;
        }
        if (opt==1)
        {
            int x,y;scanf("%d%d",&x,&y);
            if (Belong[x]>Belong[y]) swap(x,y);
            Qn[++qcnt]=((Question){x,y,qcnt,tcnt});
        }
    }

    sort(&Qn[1],&Qn[qcnt+1],cmp);

    for (int i=1;i<=n;i++) Cal[i]=CCal[i];

    int u=1,v=1,tim=0;
    for (int i=1;i<=qcnt;i++)
    {
        while (tim<Qn[i].tim) TimAdd(++tim);
        while (tim>Qn[i].tim) TimBack(tim--);
        Move(u,Qn[i].u);Move(v,Qn[i].v);u=Qn[i].u;v=Qn[i].v;
        int lca=LCA(u,v);
        Reverse(lca);
        Ans[Qn[i].id]=nowans;
        Reverse(lca);
    }

    for (int i=1;i<=qcnt;i++) printf("%lld\n",Ans[i]);
    return 0;
}

IL void Add_Edge(int u,int v)
{
    Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
    Next[++edgecnt]=Head[v];Head[v]=edgecnt;V[edgecnt]=u;
    return;
}

void dfs(int u,int fa){
    int nowtop=top;
    dfnseq[++dfncnt]=u;fst[u]=dfncnt;
    for (int i=Head[u];i!=-1;i=Next[i])
        if (V[i]!=fa)
        {
            Depth[V[i]]=Depth[u]+1;Fa[V[i]]=u;
            dfs(V[i],u);dfnseq[++dfncnt]=u;
            if (top-nowtop>=blocksize)
            {
                blockcnt++;
                while (top!=nowtop) Belong[St[top--]]=blockcnt;
            }
        }
    lst[u]=dfncnt;
    St[++top]=u;return;
}

bool cmp(Question A,Question B){
    if (Belong[A.u]==Belong[B.u]) return Belong[A.v]<Belong[B.v];
    else return Belong[A.u]<Belong[B.u];
}

IL void TimAdd(int t)
{
    if (vis[My[t].pos]){
        nowans=nowans-1ll*Wal[Cnt[My[t].p]]*Val[My[t].p];
        Cnt[My[t].p]--;
        Cnt[My[t].q]++;
        nowans=nowans+1ll*Wal[Cnt[My[t].q]]*Val[My[t].q];
        Cal[My[t].pos]=My[t].q;
    }
    else Cal[My[t].pos]=My[t].q;
    return;
}

IL void TimBack(int t)
{
    if (vis[My[t].pos]){
        nowans=nowans-1ll*Wal[Cnt[My[t].q]]*Val[My[t].q];
        Cnt[My[t].q]--;
        Cnt[My[t].p]++;
        nowans=nowans+1ll*Wal[Cnt[My[t].p]]*Val[My[t].p];
        Cal[My[t].pos]=My[t].p;
    }
    else Cal[My[t].pos]=My[t].p;
    return;
}

IL int LCA(int u,int v)
{
    int l=min(fst[u],fst[v]),r=max(lst[u],lst[v]);
    int lg=Log[r-l+1];
    if (Depth[mn[lg][l]]<=Depth[mn[lg][r-(1<<lg)+1]]) return mn[lg][l];
    else return mn[lg][r-(1<<lg)+1];
}

IL void Move(int u,int v)
{
    int lca=LCA(u,v);
    while (u!=lca) Reverse(u),u=Fa[u];
    while (v!=lca) Reverse(v),v=Fa[v];
    return;
}

IL void Reverse(int u)
{
    if (vis[u]){
        nowans=nowans-1ll*Wal[Cnt[Cal[u]]]*Val[Cal[u]];
        Cnt[Cal[u]]--;
    }
    else{
        Cnt[Cal[u]]++;
        nowans=nowans+1ll*Wal[Cnt[Cal[u]]]*Val[Cal[u]];
    }
    vis[u]^=1;return;
}

