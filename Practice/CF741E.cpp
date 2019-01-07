#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<iostream>
#include<cmath>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define pow2(x) (1<<(x))

const int maxN=101000*2;
const int maxBit=20;
const int maxSqrt=300;

class Question{
public:
    int l,r,x,y,id;
};

char S[maxN],T[maxN];
int L,L1,L2,SA[maxN],SSA[maxN],Rk[maxN],A[maxN],B[maxN],CA[maxN],CB[maxN],Height[maxBit][maxN];
int Lg2[maxN],Id[maxN],Sorter[maxN];
pair<int,int> Seq[maxBit][maxN],Ans[maxN];
vector<Question> Qn[maxN];

void GetSA();
int GetLcp(int u,int v);
bool cmp(int a,int b);
pair<int,int> GetMin(int l,int r);
pair<int,int> ChkMin(pair<int,int> p1,pair<int,int> p2);

int main(){
    for (int i=1;i<maxN;i++) Lg2[i]=log2(i);
    scanf("%s",S+1);scanf("%s",T+1);L1=strlen(S+1);L2=strlen(T+1);L=L1+L2+1;S[L1+1]='z'+1;
    for (int i=1;i<=L2;i++) S[L1+i+1]=T[i];

    for (int i=1;i<=L;i++) cout<<S[i];cout<<endl;

    GetSA();
    /*
    for (int i=1;i<=L;i++) cout<<SA[i]<<" ";cout<<endl;
    for (int i=1;i<=L;i++) cout<<Rk[i]<<" ";cout<<endl;
    for (int i=1;i<=L;i++){
	for (int j=SA[i];j<=L;j++) cout<<S[j];cout<<endl;
    }
    for (int i=1;i<=L;i++) cout<<Height[0][i]<<" ";cout<<endl;
    //*/

    for (int i=0;i<=L1;i++) Sorter[i]=i;
    sort(&Sorter[0],&Sorter[L1+1],cmp);
    for (int i=0;i<=L1;i++) Id[Sorter[i]]=i;
    for (int i=0;i<=L1;i++) cout<<Id[i]<<" ";cout<<endl;
    
    for (int i=0;i<=L1;i++) Seq[0][i]=make_pair(Id[i],i);
    for (int i=1;i<maxBit;i++)
	for (int j=0;j+pow2(i)-1<=L1;j++)
	    Seq[i][j]=ChkMin(Seq[i-1][j],Seq[i-1][j+pow2(i-1)]);

    int Q;scanf("%d",&Q);
    for (int qi=1;qi<=Q;qi++){
	int l,r,k,x,y;scanf("%d%d%d%d%d",&l,&r,&k,&x,&y);
	Ans[qi]=make_pair(-1,-1);
	if (k==1) Ans[qi]=ChkMin(Ans[qi],GetMin(l,r));
	if (k>=maxSqrt){
	    for (int i=0,j;i<=L1;i=i+k){
		int ql=max(l,i+x-1),qr=min(r,i+y-1);
		if (ql<=qr) Ans[qi]=ChkMin(Ans[qi],GetMin(ql,qr));
	    }
	}
	else Qn[k].push_back((Question){l,r,x,y,qi});
    }
    for (int K=2;K<maxSqrt;K++)
	if (Qn[K].size())
	    for (int md=0;md<K;md++){
		int cnt=-1;
		for (int i=md;i<=L1;i+=K) Seq[0][++cnt]=make_pair(Id[i],i);
		cout<<"K:"<<K<<" md:"<<md<<endl;
		for (int i=0;i<=cnt;i++) cout<<Seq[0][i].first<<" ";cout<<endl;
		for (int i=1;i<maxBit;i++)
		    for (int j=0;j+pow2(i)-1<=cnt;j++)
			Seq[i][j]=ChkMin(Seq[i-1][j],Seq[i-1][j+pow2(i-1)]);
		for (int i=0,sz=Qn[K].size();i<sz;i++)
		    if ((Qn[K][i].x<=md)&&(Qn[K][i].y>=md)){
			int L=Qn[K][i].l,R=Qn[K][i].r;
			if (L%K>md) L=L+(K-L%K);
			if (R%K<md) R=R-R%K-1;
			L=L+(md-L%K);R=R-(R%K-md);
			L=(L-md)/K;R=(R-md)/K;
			cout<<"Q:"<<Qn[K][i].id<<" "<<Qn[K][i].l<<" "<<Qn[K][i].r<<" "<<L<<" "<<R<<endl;
			cout<<Ans[Qn[K][i].id].first<<" "<<Ans[Qn[K][i].id].second<<"|"<<GetMin(L,R).first<<" "<<GetMin(L,R).second<<endl;
			if (L<=R) Ans[Qn[K][i].id]=ChkMin(Ans[Qn[K][i].id],GetMin(L,R));
		    }
	    }
    for (int i=1;i<=Q;i++) printf("%d\n",Ans[i].second);return 0;
}

void GetSA(){
    for (int i=1;i<=L;i++) CA[S[i]]++;
    for (int i=1;i<maxN;i++) CA[i]+=CA[i-1];
    for (int i=L;i>=1;i--) SA[CA[S[i]]--]=i;
    Rk[SA[1]]=1;
    for (int i=2;i<=L;i++){
	Rk[SA[i]]=Rk[SA[i-1]];
	if (S[SA[i]]!=S[SA[i-1]]) Rk[SA[i]]++;
    }
    for (int len=1;Rk[SA[L]]!=L;len<<=1){
	mem(CA,0);mem(CB,0);
	for (int i=1;i<=L;i++) ++CA[A[i]=Rk[i]],++CB[B[i]=(i+len<=L)?Rk[i+len]:0];
	for (int i=1;i<maxN;i++) CA[i]+=CA[i-1],CB[i]+=CB[i-1];
	for (int i=L;i>=1;i--) SSA[CB[B[i]]--]=i;
	for (int i=L;i>=1;i--) SA[CA[A[SSA[i]]]--]=SSA[i];
	Rk[SA[1]]=1;
	for (int i=2;i<=L;i++){
	    Rk[SA[i]]=Rk[SA[i-1]];
	    if ((A[SA[i]]!=A[SA[i-1]])||(B[SA[i]]!=B[SA[i-1]])) ++Rk[SA[i]];
	}
    }
    for (int i=1,j=0;i<=L;i++){
	if (j) --j;
	while (S[i+j]==S[SA[Rk[i]-1]+j]) ++j;
	Height[0][Rk[i]]=j;
    }
    for (int i=1;i<20;i++)
	for (int j=1;j+pow2(i-1)<=L;j++)
	    Height[i][j]=min(Height[i-1][j],Height[i-1][j+pow2(i-1)]);
    return;
}
int GetLcp(int u,int v){
    u=Rk[u];v=Rk[v];if (u>v) swap(u,v);
    ++u;int lg=Lg2[v-u+1];
    return min(Height[lg][u],Height[lg][v-pow2(lg)+1]);
}
bool cmp(int a,int b){
    if (a==b) return 0;
    int lcp=0,opt=(a>b);if (a>b) swap(a,b);
    if (b-a>=L2){
	int dt=b-(a+L2);
	lcp=GetLcp(L1+2,a+1);
	if (lcp<L2) return (S[L1+2+lcp]<S[a+1+lcp])^opt;
	lcp=GetLcp(a+1,a+L2+1);
	if (lcp<dt) return (S[a+1+lcp]<S[a+L2+1+lcp])^opt;
	lcp=GetLcp(a+dt+1,L1+2);
	if (lcp<L2) return (S[a+dt+1+lcp]<S[L1+2+lcp])^opt;
	return opt^1;
    }
    else{
	lcp=GetLcp(L1+2,a+1);
	if (lcp<b-a) return (S[L1+2+lcp]<S[a+1+lcp])^opt;
	lcp=GetLcp(L1+1+b-a,L1+2);
	if (lcp<a+L2-b) return (S[L1+1+b-a+lcp]<S[L1+2+lcp])^opt;
	lcp=GetLcp(a+1,L1+1+a+L2-b);
	if (lcp<b-a) return (S[a+1+lcp]<S[L1+1+a+L2-b])^opt;
    }
}
pair<int,int> GetMin(int l,int r){
    int lg=Lg2[r-l+1];
    return ChkMin(Seq[lg][l],Seq[lg][r-pow2(lg)+1]);
}
pair<int,int> ChkMin(pair<int,int> p1,pair<int,int> p2){
    //cout<<"ChkMin:"<<p1<<" "<<p2<<endl;
    if (p1.first==-1) return p2;
    if (p2.first==-1) return p1;
    if (p1.first<=p2.first) return p1;
    return p2;
}
