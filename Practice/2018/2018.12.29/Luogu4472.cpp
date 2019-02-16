#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<map>
#include<algorithm>
using namespace std;

#define GetX(x) (((x)%n+n-1)%n+1)
#define GetY(x) (((x)%m+m-1)%m+1)
#define uint unsigned long long
#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=510;
const int maxBit=30;
const uint base=101;
const int F1[]={-1,-1,-1,0,1,1,1,0};
const int F2[]={-1,0,1,1,1,0,-1,-1};

int n,m,K;
char Input[maxN][maxN];
uint Base[maxBit];
uint Hash[maxBit][maxN][maxN];
map<uint,int> Mp;

int main(){
	Base[0]=base;for (int i=1;i<maxBit;i++) Base[i]=Base[i-1]*Base[i-1];
	scanf("%d%d%d",&n,&m,&K);
	for (int i=1;i<=n;i++) scanf("%s",Input[i]+1);
	for (int f=0;f<8;f++){
		mem(Hash,0);
		for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) Hash[0][i][j]=Input[i][j]-'a'+1;
		for (int b=1;b<maxBit;b++)
			for (int i=1;i<=n;i++)
				for (int j=1;j<=m;j++)
					Hash[b][i][j]=Hash[b-1][i][j]*Base[b-1]+Hash[b-1][GetX(i+F1[f]*(1<<(b-1)))][GetY(j+F2[f]*(1<<(b-1)))];
		for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++){
				int x=i,y=j;uint hash=0;
				for (int b=maxBit-1;b>=0;b--)
					if (K&(1<<b)) hash=hash*Base[b]+Hash[b][x][y],x=GetX(x+F1[f]*(1<<b)),y=GetY(y+F2[f]*(1<<b));
				++Mp[hash];
			}
	}
	ll cnt=0,all=1ll*n*m*8;all*=all;
	for (map<uint,int>::iterator it=Mp.begin();it!=Mp.end();it++)
		cnt=cnt+1ll*(*it).second*(*it).second;
	ll g=__gcd(cnt,all);cnt/=g;all/=g;
	printf("%lld/%lld\n",cnt,all);return 0;
}
