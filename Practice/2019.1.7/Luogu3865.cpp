#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<cmath>
using namespace std;

#define pow2(x) (1<<(x))

const int maxN=101000*4;
const int logn=10;
const int inf=2000000000;

int n,A[maxN],Lg2[maxN];
int Mns[pow2(logn)][5][logn],Req[pow2(logn)][logn];
int root,top,St[maxN],CTT[maxN][2];
int ecnt,Elr[maxN],Dph[maxN],dfn[maxN],lst[maxN];
int bcnt,Bl[maxN],L[maxN],Sid[maxN];
int Seq[15][maxN];

void Init();
void dfs(int x,int d);
int Query(int S,int l,int r);
int ST(int l,int r);

int main(){
    //freopen("in","r",stdin);freopen("out","w",stdout);
    Init();int Q;
    scanf("%d%d",&n,&Q);for (int i=1;i<=n;i++) scanf("%d",&A[i]);
   
    St[top=1]=root=1;
    for (int i=2;i<=n;i++){
	int lst=0;while ((top)&&(A[St[top]]<A[i])) lst=St[top--];
	CTT[i][0]=lst;
	if (top) CTT[St[top]][1]=i;
	else root=i;
	St[++top]=i;
    }
    dfs(root,1);
    //for (int i=1;i<=ecnt;i++) cout<<Elr[i]<<" ";cout<<endl;
    //for (int i=1;i<=ecnt;i++) cout<<Dph[i]<<" ";cout<<endl;
    //for (int i=1;i<=n;i++) cout<<dfn[i]<<" "<<lst[i]<<endl;

    for (int i=1,j;i<=ecnt;i=j){
	j=i+logn;++bcnt;Sid[bcnt]=0;L[bcnt]=i;Bl[i]=bcnt;
	for (int k=i+1;k<j;k++){
	    Sid[bcnt]<<=1;Bl[k]=bcnt;
	    if ((k<=ecnt)&&(Dph[k]==Dph[k-1]-1)) Sid[bcnt]|=1;
	}
	Seq[0][bcnt]=i+Query(Sid[bcnt],0,logn-1);

	//for (int k=i;k<j;k++) cout<<Dph[k]<<" ";cout<<endl;
    }
    //cout<<"Seq:";for (int i=1;i<=bcnt;i++) cout<<Seq[0][i]<<" ";cout<<endl;
    //cout<<"Sid:";for (int i=1;i<=bcnt;i++) cout<<Sid[i]<<" ";cout<<endl;
    for (int i=1;i<=14;i++)
	for (int j=1;j+pow2(i-1)<=bcnt;j++)
	    if (Dph[Seq[i-1][j]]<=Dph[Seq[i-1][j+pow2(i-1)]]) Seq[i][j]=Seq[i-1][j];
	    else Seq[i][j]=Seq[i-1][j+pow2(i-1)];

    for (int qi=1;qi<=Q;qi++){
	//cout<<"running on :"<<qi<<endl;
	int l,r,Ans=0;scanf("%d%d",&l,&r);
	if (dfn[l]>dfn[r]) swap(l,r);l=dfn[l];r=lst[r];
	if (Bl[l]==Bl[r]) Ans=A[Elr[Query(Sid[Bl[l]],l-L[Bl[l]],r-L[Bl[l]])+L[Bl[l]]]];
	else{
	    int ql=Bl[l]+1,qr=Bl[r]-1;
	    if (ql<=qr) Ans=max(Ans,A[Elr[ST(ql,qr)]]);
	    Ans=max(Ans,A[Elr[Query(Sid[Bl[l]],l-L[Bl[l]],logn-1)+L[Bl[l]]]]);
	    Ans=max(Ans,A[Elr[Query(Sid[Bl[r]],0,r-L[Bl[r]])+L[Bl[r]]]]);
	}
	printf("%d\n",Ans);
    }
    return 0;
}
void Init(){
    for (int i=1;i<maxN;i++) Lg2[i]=log2(i);
    for (int S=0;S<pow2(logn-1);S++){
	Req[S][0]=0;
	for (int i=1;i<logn;i++) Req[S][i]=Req[S][i-1]+((S&pow2(logn-i-1))?(-1):(1));
	for (int i=0;i<logn;i++) Mns[S][0][i]=i;
	for (int i=1;i<=4;i++)
	    for (int j=0;j+pow2(i-1)<logn;j++)
		if (Req[S][Mns[S][i-1][j]]<=Req[S][Mns[S][i-1][j+pow2(i-1)]]) Mns[S][i][j]=Mns[S][i-1][j];
		else Mns[S][i][j]=Mns[S][i-1][j+pow2(i-1)];
    }
}
void dfs(int x,int d){
    //cout<<x<<" "<<CTT[x][0]<<" "<<CTT[x][1]<<endl;
    Elr[++ecnt]=x;Dph[ecnt]=d;dfn[x]=ecnt;
    if (CTT[x][0]) dfs(CTT[x][0],d+1),Elr[++ecnt]=x,Dph[ecnt]=d;
    if (CTT[x][1]) dfs(CTT[x][1],d+1),Elr[++ecnt]=x,Dph[ecnt]=d;
    lst[x]=ecnt;return;
}
int Query(int S,int l,int r){
    //cout<<"Q:"<<S<<"["<<l<<","<<r<<"]"<<endl;
    //for (int i=0;i<logn;i++) cout<<Req[S][i]<<" ";cout<<endl;
    int lg=Lg2[r-l+1];
    if (Req[S][Mns[S][lg][l]]<=Req[S][Mns[S][lg][r-pow2(lg)+1]]) return Mns[S][lg][l];
    else return Mns[S][lg][r-pow2(lg)+1];
}
int ST(int l,int r){
    int lg=Lg2[r-l+1];
    if (Dph[Seq[lg][l]]<=Dph[Seq[lg][r-pow2(lg)+1]]) return Seq[lg][l];
    return Seq[lg][r-pow2(lg)+1];
}
