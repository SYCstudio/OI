#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<map>
#include<iostream>
using namespace std;

#define Max(x,y) x=max(x,y)
#define Min(x,y) x=min(x,y)
class Data{
public:
    int f[3][3],g[3][3];
    int cnt;
    Data(){
	memset(f,-1,sizeof(f));memset(g,-1,sizeof(g));cnt=0;
	f[0][0]=0;
    }
    Data Trans(int c){
	Data R;R.cnt=min(7,cnt+(c>=2));
	for (int i=0;i<3;i++)
	    for (int j=0;j<3;j++){
		if (f[i][j]!=-1){
		    for (int k=0;i+j+k<=c&&k<3;k++) Max(R.f[j][k],min(4,f[i][j]+i+(c-i-j-k>=3)));
		    if (c>=2) for (int k=0;i+j+k<=c-2&&k<3;k++) Max(R.g[j][k],min(4,f[i][j]+i+(c-2-i-j-k>=3)));
		}
		if (g[i][j]!=-1)
		    for (int k=0;i+j+k<=c&&k<3;k++) Max(R.g[j][k],min(4,g[i][j]+i+(c-i-j-k>=3)));
	    }
	return R;
    }
};
bool operator < (Data A,Data B){
    if (A.cnt!=B.cnt) return A.cnt<B.cnt;
    for (int i=0;i<3;i++) for (int j=0;j<3;j++) if (A.f[i][j]!=B.f[i][j]) return A.f[i][j]<B.f[i][j];
    for (int i=0;i<3;i++) for (int j=0;j<3;j++) if (A.g[i][j]!=B.g[i][j]) return A.g[i][j]<B.g[i][j];
    return 0;
}

const int maxN=110;
const int maxM=maxN*4;
const int maxT=2500;
const int Mod=998244353;

int n,Fc[maxM],Ifc[maxM],idcnt=0;
map<Data,int> Mp;
int Trans[maxT][5];
int Cnt[maxN];
int F[maxM][maxT],G[maxM][maxT];

int QPow(int x,int cnt);
int C(int n,int m);
void Plus(int &x,int y);
int dfs_init(Data T);
int main(){
    dfs_init(Data());
    Fc[0]=Ifc[0]=1;for (int i=1;i<maxM;i++) Fc[i]=1ll*Fc[i-1]*i%Mod;
    Ifc[maxM-1]=QPow(Fc[maxM-1],Mod-2);for (int i=maxM-2;i>=1;i--) Ifc[i]=1ll*Ifc[i+1]*(i+1)%Mod;

    scanf("%d",&n);
    for (int i=1;i<=13;i++){
	int w,d;scanf("%d%d",&w,&d);
	++Cnt[w];
    }

    F[0][1]=1;
    for (int i=1,sum=0;i<=n;i++){
	swap(F,G);memset(F,0,sizeof(F));
	for (int j=sum;j<=i*4-2;j++)
	    for (int k=1;k<=idcnt;k++)
		if (G[j][k])
		    for (int t=Cnt[i];t<=4;t++)
			if (Trans[k][t])
			    Plus(F[j+t][Trans[k][t]],1ll*G[j][k]*C(4-Cnt[i],t-Cnt[i])%Mod);
	sum=sum+Cnt[i];
    }
    int Ans=0;

    for (int i=1;i<=n*4-13;i++){
	int sum=0;
	for (int j=1;j<=idcnt;j++) Plus(sum,F[i+13][j]);
	sum=1ll*sum*Fc[i]%Mod*Fc[n*4-13-i]%Mod;
	Plus(Ans,sum);
    }
    Ans=1ll*Ans*Ifc[n*4-13]%Mod;Plus(Ans,1);
    printf("%d\n",Ans);return 0;
}
int QPow(int x,int cnt){
    int ret=1;
    while (cnt){
	if (cnt&1) ret=1ll*ret*x%Mod;cnt>>=1;x=1ll*x*x%Mod;
    }
    return ret;
}
int C(int n,int m){
    if (n<0||m<0||n<m) return 0;
    return 1ll*Fc[n]*Ifc[m]%Mod*Ifc[n-m]%Mod;
}
void Plus(int &x,int y){
    x+=y;if (x>=Mod) x-=Mod;return;
}
int dfs_init(Data T){
    if (T.cnt>=7) return 0;
    for (int i=0;i<3;i++) for (int j=0;j<3;j++) if (T.g[i][j]>=4) return 0;
    if (Mp.count(T)) return Mp[T];
    int id=Mp[T]=++idcnt;
    for (int x=0;x<=4;x++) Trans[id][x]=dfs_init(T.Trans(x));
    return id;
}
