#include<bits/stdc++.h>
using namespace std;

#define pb push_back
const int maxN=101000*2;
const int Alpha=26;

class SAM{
public:
    int son[Alpha],len,fail;
};
class SegmentData{
public:
    int ls,rs,cnt;
};

int n,lst=1,smcnt=1,sgcnt=0,rt[maxN];
char In[maxN];
SAM Sm[maxN];
SegmentData Sg[maxN*40];
vector<int> Pt[maxN];
int Pos[maxN];

void Extend(int c);
void Insert(int &x,int l,int r,int p);
void dfs_build(int u);
int Merge(int x,int y);
int Query(int x,int l,int r,int ql,int qr);
int main(){
    scanf("%s",In+1);n=strlen(In+1);
    for (int i=1;i<=n;i++) Extend(In[i]-'a'),Insert(rt[lst],1,n,i);
    for (int i=2;i<=smcnt;i++) Pt[Sm[i].fail].pb(i);
    dfs_build(1);

    int Q;scanf("%d",&Q);
    while (Q--){
	int l,r,top=0;scanf("%d%d",&l,&r);scanf("%s",In+1);int len=strlen(In+1);
	for (int i=1,now=1;i<=len;i++){
	    int c=In[i]-'a';
	    if (Sm[now].son[c]==0) break;
	    now=Sm[now].son[c];
	    if (l+i-1>r||Query(rt[now],1,n,l+i-1,r)==0) break;
	    Pos[top=i]=now;
	}
	Pos[0]=1;bool flag=0;In[len+1]='a'-1;
	for (int i=top;i>=0;i--){
	    int c=In[i+1]-'a';
	    for (int j=c+1;j<Alpha;j++)
		if (Sm[Pos[i]].son[j]&&l+i<=r&&Query(rt[Sm[Pos[i]].son[j]],1,n,l+i,r)){
		    flag=1;
		    for (int k=1;k<=i;k++) printf("%c",In[k]);
		    printf("%c",(char)(j+'a'));puts("");break;
		}
	    if (flag) break;
	}
	if (!flag) puts("-1");
    }
    return 0;
}
void Extend(int c){
    int np=++smcnt,p=lst;lst=np;Sm[np].len=Sm[p].len+1;
    while (p&&Sm[p].son[c]==0) Sm[p].son[c]=np,p=Sm[p].fail;
    if (p==0) Sm[np].fail=1;
    else{
	int q=Sm[p].son[c];
	if (Sm[q].len==Sm[p].len+1) Sm[np].fail=q;
	else{
	    int nq=++smcnt;Sm[nq]=Sm[q];Sm[nq].len=Sm[p].len+1;Sm[q].fail=Sm[np].fail=nq;
	    while (p&&Sm[p].son[c]==q) Sm[p].son[c]=nq,p=Sm[p].fail;
	}
    }
    return;
}
void Insert(int &x,int l,int r,int p){
    Sg[++sgcnt]=Sg[x];x=sgcnt;++Sg[x].cnt;
    if (l==r) return;
    int mid=(l+r)>>1;
    if (p<=mid) Insert(Sg[x].ls,l,mid,p);else Insert(Sg[x].rs,mid+1,r,p);
}
void dfs_build(int u){
    for (int i=0;i<Pt[u].size();i++) dfs_build(Pt[u][i]),rt[u]=Merge(rt[u],rt[Pt[u][i]]);
    return;
}
int Merge(int u,int v){
    if (!u||!v) return u+v;
    int id=++sgcnt;Sg[id].cnt=Sg[u].cnt+Sg[v].cnt;
    Sg[id].ls=Merge(Sg[u].ls,Sg[v].ls);
    Sg[id].rs=Merge(Sg[u].rs,Sg[v].rs);
    return id;
}
int Query(int x,int l,int r,int ql,int qr){
    if (!x) return 0;
    if (l==ql&&r==qr) return Sg[x].cnt;
    int mid=(l+r)>>1;
    if (qr<=mid) return Query(Sg[x].ls,l,mid,ql,qr);
    else if (ql>=mid+1) return Query(Sg[x].rs,mid+1,r,ql,qr);
    else return Query(Sg[x].ls,l,mid,ql,mid)+Query(Sg[x].rs,mid+1,r,mid+1,qr);
}
