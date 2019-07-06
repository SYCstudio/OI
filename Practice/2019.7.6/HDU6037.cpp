#include<bits/stdc++.h>
using namespace std;

typedef __int128_t int128;
typedef double ld;
typedef long long ll;
typedef unsigned ull;
#define pb push_back
#define mp make_pair
#define ft first
#define sd second

const int maxP=1010;
const int128 maxNum=1e24;
const int maxN=202000;
const int maxG=19;

int notp[maxP],pcnt,Pri[maxP];
int Seq[maxP],idcnt;
map<int128,int> Mp;
ld G[maxN][maxG],F[maxN];
int128 Num[maxN];

void Init();
void dfs(int p,int limit,int128 n);
int main(){
    //freopen("in","r",stdin);
    //freopen("output","w",stdout);
    Init();

    /*
    for (int i=0;i<=18;i++){
	int size=0;
	for (int j=0;j<Mod;j++) size+=G[i][j].size();
	cerr<<size<<" ";
    }cerr<<endl;
    //*/

    int cas=0;char inp[30];int m;
    while (scanf("%s%d",inp+1,&m)!=EOF){
	int128 n=0;int len=strlen(inp+1);
	for (int i=1;i<=len;i++) n=n*10+inp[i]-'0';
	for (int i=1;i<=m;i++){
	    int p;scanf("%d",&p);
	    while (n%p==0) ++Seq[i],n=n/p;
	}
	sort(&Seq[1],&Seq[m+1]);reverse(&Seq[1],&Seq[m+1]);
	int128 mul=1;
	for (int i=1;i<=18;i++) for (int j=1;j<=Seq[i];j++) mul=mul*Pri[i];
	
	printf("Case #%d: %.10lf\n",++cas,F[Mp[mul]]);
	
	for (int i=1;i<=m;i++) Seq[i]=0;
    }
    return 0;
}
void Init(){
    notp[1]=1;
    for (int i=2;i<maxP;i++){
	if (!notp[i]) Pri[++pcnt]=i;
	for (int j=1;j<=pcnt&&1ll*i*Pri[j]<maxP;j++){
	    notp[i*Pri[j]]=1;if (i%Pri[j]==0) break;
	}
    }
    dfs(1,100,1);
    for (int i=2;i<=idcnt;i++){
	int128 X=Num[i];ld sigma=1;
	for (int j=1;j<=18;j++) while (X%Pri[j]==0) ++Seq[j],X/=Pri[j];
	for (int j=18;j>=1;j--)
	    if (Seq[j]){
		int p=j;sigma=sigma*(Seq[j]+1);
		while (p<18&&Seq[p+1]==Seq[p]) ++p;
		G[i][j]=G[i][j+1]+G[Mp[Num[i]/Pri[p]]][j];
	    }
	F[i]=(G[i][1]+sigma)/(sigma-1);
	//cout<<i<<" "<<(ll)Num[i]<<" "<<F[i]<<" "<<sigma<<" "<<G[i][0]<<endl;
	for (int j=1;j<=18;j++) G[i][j]+=F[i];
	for (int j=1;j<=18;j++) Seq[j]=0;
    }
    return;
}
ull Hs(vector<int> &v){
    ull ret=0;
    for (int i=1;i<=18;i++) ret=ret*79+v[i];
    return ret;
}
void dfs(int p,int limit,int128 n){
    assert(p<=19);
    Mp[n]=++idcnt;Num[idcnt]=n;
    n=n*Pri[p];
    for (int i=1;i<=limit&&n<=maxNum;i++,n=n*Pri[p]) dfs(p+1,i,n);
    return;
}
