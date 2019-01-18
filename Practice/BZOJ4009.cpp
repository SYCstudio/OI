#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=80400;
const int maxM=maxN<<1;
const int maxB=20;

class Question{
public:
    int xl,xr,yl,yr,id;
};
class Point{
public:
    int x,y,c;
};
class SegmentData{
public:
    int ls,rs,cnt;
};

int n,P,Q,qcnt;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int dfncnt,dfn[maxN],lst[maxN],dph[maxN],Fa[maxB][maxN];
Point Plt[maxN];
int Kth[maxN],ok[maxN],Ans[maxN];
Question Qs[maxN],Bp1[maxN],Bp2[maxN];
int nodecnt,rt[maxN],rtx[maxN],Sm[maxN];
SegmentData S[maxN*20];

void Add_Edge(int u,int v);
void dfs(int u,int fa);
bool ccmp(Point A,Point B);
bool pcmp(Point A,Point B);
bool qcmp(Question A,Question B);
void Divide(int fl,int fr,int ql,int qr);
void Modify(int &x,int l,int r,int p);
int Query(int x1,int x2,int l,int r,int ql,int qr);

int main(){
    freopen("in","r",stdin);freopen("out","w",stdout);
    scanf("%d%d%d",&n,&P,&Q);mem(Head,-1);
    for (int i=1;i<n;i++){
	int u,v;scanf("%d%d",&u,&v);
	Add_Edge(u,v);Add_Edge(v,u);
    }
    dfs(1,1);
    
    for (int i=1;i<maxB;i++) for (int j=1;j<=n;j++) Fa[i][j]=Fa[i-1][Fa[i-1][j]];
    
    for (int i=1;i<=P;i++){
	int a,b;scanf("%d%d%d",&a,&b,&Plt[i].c);
	a=dfn[a];b=dfn[b];Plt[i].x=a;Plt[i].y=b;
	Plt[i+P]=Plt[i];swap(Plt[i].x,Plt[i].y);
    }
    P+=P;
    sort(&Plt[1],&Plt[P+1],ccmp);

    for (int i=1;i<=Q;i++){
	int u,v,k;scanf("%d%d%d",&u,&v,&k);
	Kth[i]=k;if (dph[u]>dph[v]) swap(u,v);
	if (dfn[v]>=dfn[u]&&lst[v]<=lst[u]){
	    int vv=v;
	    for (int j=maxB-1;j>=0;j--) if (Fa[j][vv]&&dph[Fa[j][vv]]>dph[u]) vv=Fa[j][vv];
	    Qs[++qcnt]=((Question){dfn[v],lst[v],1,dfn[vv]-1,i});
	    if (lst[vv]!=n)
		Qs[++qcnt]=((Question){dfn[v],lst[v],lst[vv]+1,n,i});
	}
	else Qs[++qcnt]=((Question){dfn[u],lst[u],dfn[v],lst[v],i});
    }
    sort(&Qs[1],&Qs[qcnt+1],qcmp);
    Divide(1,P,1,qcnt);
    for (int i=1;i<=Q;i++) printf("%d\n",Ans[i]);return 0;
}
void Add_Edge(int u,int v){
    Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
    return;
}
void dfs(int u,int fa){
    dfn[u]=++dfncnt;dph[u]=dph[fa]+1;Fa[0][u]=fa;
    for (int i=Head[u];i!=-1;i=Next[i])
	if (V[i]!=fa) dfs(V[i],u);
    lst[u]=dfncnt;return;
}
bool ccmp(Point A,Point B){
    if (A.c!=B.c) return A.c<B.c;
    return A.x<B.x;
}
bool pcmp(Point A,Point B){
    if (A.x!=B.x) return A.x<B.x;
    return A.y<B.y;
}
bool qcmp(Question A,Question B){
    if (A.xr!=B.xr) return A.xr<B.xr;
    return A.id<B.id;
}
void Divide(int fl,int fr,int ql,int qr){
    if (fl>fr) return;

    cout<<"Divide:"<<fl<<" "<<fr<<" "<<ql<<" "<<qr<<endl;
    for (int i=fl;i<=fr;i++) cout<<"("<<Plt[i].x<<" "<<Plt[i].y<<" "<<Plt[i].c<<") ";cout<<endl;
    for (int i=ql;i<=qr;i++) cout<<"("<<Qs[i].xl<<" "<<Qs[i].xr<<" "<<Qs[i].yl<<" "<<Qs[i].yr<<" "<<Qs[i].id<<") ";cout<<endl;
    
    for (int i=ql;i<=qr;i++) Sm[Qs[i].id]=0;
    nodecnt=0;rt[0]=0;rtx[0]=0;int top=0,mid=(fl+fr)>>1;
    sort(&Plt[fl],&Plt[mid+1],pcmp);
    for (int i=fl,j=ql;;i++){
	while (j<=qr&&Qs[j].xr<=rtx[top]){
	    int pre=lower_bound(&rtx[0],&rtx[top+1],Qs[j].xl)-rtx-1;
	    Sm[Qs[j].id]+=Query(rt[pre],rt[top],1,n,Qs[j].yl,Qs[j].yr);
	    ++j;
	}
	if (i>mid) break;
	++top;rt[top]=rt[top-1];rtx[top]=Plt[i].x;
	Modify(rt[top],1,n,Plt[i].y);
	while (i<mid&&Plt[i+1].x==Plt[i].x){
	    ++i;Modify(rt[top],1,n,Plt[i].y);
	}
    }
    sort(&Plt[fl],&Plt[fr+1],ccmp);
    for (int i=ql;i<=qr;i++) ok[Qs[i].id]=(Sm[Qs[i].id]>=Kth[Qs[i].id]);
    int st1=0,st2=0,p=ql-1,dvt;
    for (int i=ql;i<=qr;i++)
	if (ok[Qs[i].id]) Bp1[++st1]=Qs[i];
	else Bp2[++st2]=Qs[i];
    for (int i=1;i<=st1;i++) Qs[++p]=Bp1[i];
    dvt=p;
    for (int i=1;i<=st2;i++) Qs[++p]=Bp2[i];

    for (int i=ql;i<=qr;i++)
	if (ok[Qs[i].id]==0) Kth[Qs[i].id]-=Sm[Qs[i].id],ok[Qs[i].id]=-1;
	else if (ok[Qs[i].id]==1) Ans[Qs[i].id]=Plt[mid].c,ok[Qs[i].id]=-1;
    
    if (dvt>=ql) Divide(fl,mid-1,ql,dvt);
    if (dvt<qr) Divide(mid+1,fr,dvt+1,qr);
    return;
}
void Modify(int &x,int l,int r,int p){
    S[++nodecnt]=S[x];x=nodecnt;++S[x].cnt;
    if (l==r) return;
    int mid=(l+r)>>1;
    if (p<=mid) Modify(S[x].ls,l,mid,p);else Modify(S[x].rs,mid+1,r,p);
}
int Query(int x1,int x2,int l,int r,int ql,int qr){
    if ((l==ql)&&(r==qr)) return S[x2].cnt-S[x1].cnt;
    int mid=(l+r)>>1;
    if (qr<=mid) return Query(S[x1].ls,S[x2].ls,l,mid,ql,qr);
    else if (ql>=mid+1) return Query(S[x1].rs,S[x2].rs,mid+1,r,ql,qr);
    else return Query(S[x1].ls,S[x2].ls,l,mid,ql,mid)+Query(S[x1].rs,S[x2].rs,mid+1,r,mid+1,qr);
}
