#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=202000*2;
const int Alpha=26;

class SAM{
public:
    int son[Alpha],len,fail,pos;
};

class SegmentData{
public:
    int ls,rs,cnt;
};

int n,samcnt=1,lst=1,root=1,F[maxN];
SAM Sm[maxN];
char Input[maxN];
vector<int> T[maxN];
int segcnt,rt[maxN];
SegmentData E[maxN*20];

void Extend(int c,int aps);
void Modify(int &x,int l,int r,int pos);
int Count(int x,int l,int r,int ql,int qr);
int Merge(int x,int y);
void dfs(int x);
void outp(int x,int l,int r);

int main(){
    freopen("in","r",stdin);freopen("out","w",stdout);
    scanf("%d",&n);scanf("%s",Input+1);
    for (int i=1;i<=n;i++) Extend(Input[i]-'a',i),Modify(rt[lst],1,n,i);

    /*
    for (int i=1;i<=samcnt;i++)
	for (int j=0;j<Alpha;j++)
	    if (Sm[i].son[j]) cout<<i<<" "<<Sm[i].son[j]<<" "<<(char)(j+'a')<<endl;
    //*/
    
    for (int i=2;i<=samcnt;i++) T[Sm[i].fail].push_back(i);
    dfs(1);int Ans=0;
    for (int i=1;i<=samcnt;i++) cout<<F[i]<<" ";cout<<endl;
    for (int i=1;i<=samcnt;i++) cout<<Sm[i].fail<<" ";cout<<endl;
    for (int i=2;i<=samcnt;i++) Ans=max(Ans,F[i]);
    printf("%d\n",Ans);return 0;
}

void Extend(int c,int aps){
    int np=++samcnt,p=lst;lst=samcnt;Sm[np].len=Sm[p].len+1;Sm[np].pos=aps;
    while (p&&Sm[p].son[c]==0) Sm[p].son[c]=np,p=Sm[p].fail;
    if (p==0) Sm[np].fail=root;
    else{
	int q=Sm[p].son[c];
	if (Sm[q].len==Sm[p].len+1) Sm[np].fail=q;
	else{
	    int nq=++samcnt;Sm[nq]=Sm[q];Sm[nq].len=Sm[p].len+1;
	    Sm[q].fail=Sm[np].fail=nq;
	    while (p&&Sm[p].son[c]==q) Sm[p].son[c]=nq,p=Sm[p].fail;
	}
    }
    return;
}
void Modify(int &x,int l,int r,int pos){
    if (x==0) x=++segcnt;++E[x].cnt;
    if (l==r) return;
    int mid=(l+r)>>1;
    if (pos<=mid) Modify(E[x].ls,l,mid,pos);else Modify(E[x].rs,mid+1,r,pos);
    return;
}
int Count(int x,int l,int r,int ql,int qr){
    if (x==0) return 0;
    if ((l==ql)&&(r==qr)) return E[x].cnt;
    int mid=(l+r)>>1;
    if (qr<=mid) return Count(E[x].ls,l,mid,ql,qr);
    else if (ql>=mid+1) return Count(E[x].rs,mid+1,r,ql,qr);
    else return Count(E[x].ls,l,mid,ql,mid)+Count(E[x].rs,mid+1,r,mid+1,qr);
}
int Merge(int x,int y){
    if ((!x)||(!y)) return x+y;
    E[x].cnt=E[x].cnt+E[y].cnt;
    E[x].ls=Merge(E[x].ls,E[y].ls);
    E[x].rs=Merge(E[x].rs,E[y].rs);
    return x;
}
void dfs(int x){
    for (int i=0,sz=T[x].size();i<sz;i++){
	dfs(T[x][i]);
	//cout<<"Merge:"<<x<<" "<<T[x][i]<<endl;
	rt[x]=Merge(rt[x],rt[T[x][i]]);
    }
    cout<<"endpos:"<<x<<endl;outp(rt[x],1,n);cout<<endl;
    cout<<Sm[Sm[x].fail].len+1<<" "<<Sm[x].len<<endl;
    for (int i=Sm[x].pos-Sm[Sm[x].fail].len+1;i<=Sm[x].pos;i++) cout<<Input[i];cout<<endl;
    F[x]=1;
    for (int i=0,sz=T[x].size();i<sz;i++){
	int v=T[x][i],l=Sm[v].pos-Sm[v].len+1,r=Sm[v].pos;
	cout<<"Calc:"<<x<<" "<<v<<" "<<Count(rt[x],1,n,l+Sm[x].len-1,r)<<endl;
	if (Count(rt[x],1,n,l+Sm[x].len-1,r)>=2) F[x]=max(F[x],F[v]+1);
    }
    cout<<F[x]<<endl;
    return;
}
void outp(int x,int l,int r){
    if (x==0) return;
    if (l==r){
	cout<<l<<" ";return;
    }
    int mid=(l+r)>>1;
    outp(E[x].ls,l,mid);outp(E[x].rs,mid+1,r);
    return;
}
/*
100
oclqnikfckoolqnikn//tkoolqnikftkoolqnikftkoolqnikftk//oolqsikftkoolqxikftkoolqnikftkoolqnikftkoolqnikftk

oclqnikfckoolqnikn//tkoolqnikftkoolqnikftkoolqnikftk//oolqsikftkoolqxikftkoolqnikftkoolqnikftkoolqnikftk
//*/
