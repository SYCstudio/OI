#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<string>
#include<iostream>
using namespace std;

class Trie{
    public:
    int son[2],a,b,c,d,end;
};

const int maxN=500001*10;
const int maxM=maxN*2;

int n,nodecnt,tcnt=0,edgecnt=-1,Hd[maxN],Nt[maxM],V[maxM];
string I[maxN/10];
Trie T[maxN];
int dfncnt,dfn[maxN],low[maxN],idcnt,Id[maxN],top,St[maxN],ink[maxN];

bool icmp(string A,string B);
void Insert(string S,int id,int opt);
void Add_Edge(int u,int v);
void tarjan(int u);
int main(){
    //freopen("in","r",stdin);
    cin>>n;for (int i=1;i<=n;i++) cin>>I[i];memset(Hd,-1,sizeof(Hd));
    sort(&I[1],&I[n+1],icmp);nodecnt=n+n+4;T[0].a=n+n+1;T[0].b=n+n+2;T[0].c=n+n+3;T[0].d=n+n+4;
    //for (int i=1;i<=n;i++) cout<<I[i]<<" ";cout<<endl;
    for (int i=1;i<=n;i++){
        int p=0;while (p<=I[i].length()-1&&I[i][p]!='?') ++p;
        if (p==I[i].length()) Insert(I[i],i,0),Add_Edge(i*2,i*2-1);
        else{
            I[i][p]='0';Insert(I[i],i,0);
            I[i][p]='1';Insert(I[i],i,1);
        }
    }
    //cout<<nodecnt<<endl;
    for (int i=1;i<=nodecnt;i++) if (dfn[i]==0) tarjan(i);
    bool flag=1;
    for (int i=1;i<=n&&flag;i++) if (Id[2*i]==Id[2*i-1]) flag=0;
    //cout<<"A"<<endl;
    //for (int i=1;i<=n;i++) cout<<Id[2*i-1]<<" "<<Id[2*i]<<endl;
    cerr<<nodecnt<<" "<<edgecnt<<endl;
    flag?puts("YES"):puts("NO");return 0;
}
bool icmp(string A,string B){
    return A.length()<B.length();
}
void Insert(string S,int id,int opt){
    int now=0,lst=0,len=S.length()-1;
    for (int i=0;i<=len;i++){
        int c=S[i]-'0';
        if (T[now].son[c]==0){
            T[now].son[c]=++tcnt;
            T[tcnt].a=++nodecnt;T[tcnt].b=++nodecnt;T[tcnt].c=++nodecnt;T[tcnt].d=++nodecnt;
            Add_Edge(T[now].c,T[tcnt].a);Add_Edge(T[tcnt].a,T[tcnt].c);
            Add_Edge(T[tcnt].d,T[tcnt].b);Add_Edge(T[tcnt].b,T[now].d);
        }
        lst=now;now=T[now].son[c];
    }
    if (T[now].end){
        int t=++tcnt;T[t].a=++nodecnt;T[t].b=++nodecnt;T[t].c=++nodecnt;T[t].d=++nodecnt;
        Add_Edge(T[now].c,T[t].a);Add_Edge(T[t].a,T[t].c);
        Add_Edge(T[t].d,T[t].b);Add_Edge(T[t].b,T[now].d);
        int c=S[len]-'0';T[lst].son[c]=t;now=t;
    }
    Add_Edge(T[now].a,2*id-opt);Add_Edge(T[now].d,2*id-opt);
    Add_Edge(2*id-(opt^1),T[now].c);Add_Edge(2*id-(opt^1),T[now].b);
    T[now].end=1;return;
}
void Add_Edge(int u,int v){
    //cout<<u<<" "<<v<<endl;
    Nt[++edgecnt]=Hd[u];Hd[u]=edgecnt;V[edgecnt]=v;return;
}
void tarjan(int u){
    dfn[u]=low[u]=++dfncnt;St[++top]=u;ink[u]=1;
    for (int i=Hd[u];i!=-1;i=Nt[i]){
        int v=V[i];
        if (!dfn[v]){
            tarjan(v);low[u]=min(low[u],low[v]);
        }
        else if (ink[v]) low[u]=min(low[u],low[v]);
    }
    if (dfn[u]==low[u]){
        ++idcnt;int v;
        do v=St[top--],Id[v]=idcnt,ink[v]=0;while (v!=u);
    }
    return;
}