#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=210;
const int inf=2147483647;

int SG[maxN][maxN];
bool use[maxN*maxN];

int GetSG(int n,int m);

int main(){
	mem(SG,-1);
	int W,H;
	while (scanf("%d%d",&W,&H)!=EOF){
		int sg=GetSG(W,H);
		if (sg==0) printf("LOSE\n");
		else printf("WIN\n");
	}
}

int GetSG(int n,int m){
	if (n>m) swap(n,m);
	if (SG[n][m]!=-1) return SG[n][m];
	if ((n==1)&&(m==1)) return SG[n][m]=0;
	for (int i=2;i<n-1;i++) GetSG(i,m),GetSG(n-i,m);
	for (int i=2;i<m-1;i++) GetSG(n,i),GetSG(n,m-i);
	for (int i=2;i<n-1;i++) use[GetSG(i,m)^GetSG(n-i,m)]=1;
	for (int i=2;i<m-1;i++) use[GetSG(n,i)^GetSG(n,m-i)]=1;
	SG[n][m]=0;
	while (use[SG[n][m]]) SG[n][m]++;
	for (int i=2;i<n-1;i++) use[GetSG(i,m)^GetSG(n-i,m)]=0;
	for (int i=2;i<n-1;i++) use[GetSG(n,i)^GetSG(n,m-i)]=0;
	//cout<<"SG "<<n<<" "<<m<<":"<<SG[n][m]<<endl;
	return SG[n][m];
}
