#include<bits/stdc++.h>
using namespace std;

#define pb push_back
const int maxN=132000;
const int Mod=998244353;
const int SRT=2000;//sqrt(maxN);
const int maxB=17;

class TrieData{
public:
    int sum,son[2];
    TrieData(){
	sum=son[0]=son[1]=0;return;
    }
};

int n,m,Q,tcnt;
int Eu[maxN],Ev[maxN],Ew[maxN],Val[maxN];
int BIT[maxN],Dg[maxN],upcnt=0,Upseq[maxN],rt[maxN];
vector<int> Lk[maxN],Kl[maxN],Br[maxN];
TrieData T[maxN*600];

void Add(int x,int k);
int Query(int x);
void Insert(int &x,int val,int key);
int Query(int x,int xr,int limit);
inline void Plus(int &x,int y);
int main(){
    scanf("%d%d%d",&n,&m,&Q);
    for (int i=1;i<=n;i++) scanf("%d",&Val[i]);
    for (int i=1;i<=m;i++) scanf("%d%d%d",&Eu[i],&Ev[i],&Ew[i]),++Dg[Eu[i]],++Dg[Ev[i]];
    for (int i=1;i<=n;i++) if (Dg[i]>SRT) Upseq[++upcnt]=i;
    for (int i=1;i<=m;i++)
	if (Dg[Eu[i]]<=SRT&&Dg[Ev[i]]<=SRT){
	    Add(Val[Eu[i]]^Val[Ev[i]],Ew[i]);
	    Br[Eu[i]].pb(i);Br[Ev[i]].pb(i);
	}
	else{
	    int pot=Eu[i];
	    if (Dg[Ev[i]]>Dg[Eu[i]]) pot=Ev[i];
	    Lk[pot].pb(i);Kl[pot^Eu[i]^Ev[i]].pb(i);
	    Insert(rt[pot],Val[pot^Eu[i]^Ev[i]],Ew[i]);
	}

    while (Q--){
	int ty,a,b;scanf("%d%d%d",&ty,&a,&b);
	if (ty==1){
	    for (int i=0,sz=Kl[a].size();i<sz;i++){
		int id=Kl[a][i],v=a^Eu[id]^Ev[id];
		Insert(rt[v],Val[a],Mod-Ew[id]);
		Insert(rt[v],b,Ew[id]);
	    }
	    if (Dg[a]<=SRT)
		for (int i=0,sz=Br[a].size();i<sz;i++){
		    int id=Br[a][i],v=a^Eu[id]^Ev[id];
		    Add(Val[a]^Val[v],Mod-Ew[id]);
		    Add(b^Val[v],Ew[id]);
		}
	    Val[a]=b;
	}
	else if (ty==2){
	    if (Dg[Eu[a]]<=SRT&&Dg[Ev[a]]<=SRT){
		Add(Val[Eu[a]]^Val[Ev[a]],(b-Ew[a]+Mod)%Mod);
	    }
	    else{
		int pot=Eu[a];
		if (Dg[Ev[a]]>Dg[Eu[a]]) pot=Ev[a];
		Insert(rt[pot],Val[pot^Eu[a]^Ev[a]],(b-Ew[a]+Mod)%Mod);
	    }
	    Ew[a]=b;
	}
	else if (ty==3){
	    int Ans=Query(b);
	    if (a) Ans=(Ans-Query(a-1)+Mod)%Mod;
	    for (int i=1;i<=upcnt;i++){
		int u=Upseq[i];
		Plus(Ans,Query(rt[u],Val[u],b));
		if (a) Plus(Ans,(Mod-Query(rt[u],Val[u],a-1))%Mod);
	    }
	    printf("%d\n",Ans);
	}
    }
    return 0;
}
void Add(int x,int k){
    ++x;
    while (x<maxN){
	Plus(BIT[x],k);x+=(x)&(-x);
    }
    return;
}
int Query(int x){
    ++x;
    int sum=0;
    while (x){
	Plus(sum,BIT[x]);x-=(x)&(-x);
    }
    return sum;
}
/*
void Insert(int b,int &x,int val,int key){
    if (x==0) x=++tcnt;Plus(T[x].sum,key);
    if (b==-1) return;
    Insert(b-1,T[x].son[(val>>b)&1],val,key);
    return;
}
//*/
void Insert(int &x,int val,int key){
    if (x==0) x=++tcnt;Plus(T[x].sum,key);
    int now=x;
    for (int i=maxB-1;i>=0;i--){
	if (T[now].son[(val>>i)&1]==0) T[now].son[(val>>i)&1]=++tcnt;
	now=T[now].son[(val>>i)&1];Plus(T[now].sum,key);
    }
    return;
}
/*
int Query(int b,int x,int xr,int limit){
    if (!x) return 0;
    if (b==-1) return T[x].sum;
    int cr=(xr>>b)&1,cl=(limit>>b)&1;
    if (cl==0) return Query(b-1,T[x].son[cr],xr,limit);
    else return (Query(b-1,T[x].son[cr^1],xr,limit)+T[T[x].son[cr]].sum)%Mod;
}
//*/
int Query(int x,int xr,int limit){
    int sum=0,now=x;
    for (int i=maxB-1;i>=0;i--){
	int cr=(xr>>i)&1,cl=(limit>>i)&1;
	if (cl==0) now=T[now].son[cr];
	else Plus(sum,T[T[now].son[cr]].sum),now=T[now].son[cr^1];
    }
    Plus(sum,T[now].sum);
    return sum;
}
//*/
inline void Plus(int &x,int y){
    x+=y;if (x>=Mod) x-=Mod;return;
}
