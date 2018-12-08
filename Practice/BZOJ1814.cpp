#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=12;
const int inf=2147483647;

int n,m;
char Mp[maxN+5][maxN+5];
ll F[2][1594323+100],Pow3[maxN];

int main(){
	Pow3[0]=1;for (int i=1;i<=15;i++) Pow3[i]=Pow3[i-1]*3;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%s",Mp[i]+1);
	int lstx=0,lsty;
	for (int i=n;(i>=1)&&(lstx==0);i--) for (int j=m;(j>=1)&&(lstx==0);j--) if (Mp[i][j]=='.') lstx=i,lsty=j;
	int now=0;
	int up=3;for (int i=1;i<=m;i++) up=up*3;
	ll Ans=0;
	F[now][0]=1;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++){
			now^=1;mem(F[now],0);
			for (int k=0;k<up;k++)
				if (F[now^1][k]){
					int x=k%3,y=k/Pow3[j-1]%3,key=F[now^1][k];
					if (j==1) cout<<i-1<<" "<<m<<" "<<k<<" "<<key<<" "<<x<<" "<<y<<endl;
					else cout<<i<<" "<<j-1<<" "<<k<<" "<<key<<" "<<x<<" "<<y<<endl;
					if (Mp[i][j]=='.'){
						if (x==0){
							if ((y==0)&&(i<n)&&(j<m)) F[now][k+Pow3[j-1]+2]+=key;
							if (y==1) F[now][k]+=key,F[now][k-Pow3[j-1]+1]+=key;
							if (y==2) F[now][k]+=key,F[now][k-Pow3[j-1]*2+2]+=key;
						}
						if (x==1){
							if (y==0) F[now][k]+=key,F[now][k-1+Pow3[j-1]]+=key;
							if (y==1){
								int opt=0,p=j;
								while (((k/Pow3[p]%3!=2)||opt)&&(p<=m)){
									if (k/Pow3[p]%3==1) ++opt;
									else if (k/Pow3[p]%3==2) --opt;
									++p;
								}
								if (p<=m) F[now][k-Pow3[j-1]-1-Pow3[p]]+=key;
							}
							if ((y==2)&&(i==lstx)&&(j==lsty)) Ans+=key;
						}
						if (x==2){
							if (y==0) F[now][k]+=key,F[now][k-2+Pow3[j-1]*2]+=key;
							if (y==1) F[now][k-2-Pow3[j-1]]+=key;
							if ((y==2)&&(j>=2)){
								int opt=0,p=j-2;
								while (((k/Pow3[p]%3!=1)||opt)&&(p>=1)){
									if (k/Pow3[p]%3==1) --opt;
									else if (k/Pow3[p]%3==2) ++opt;
									--p;
								}
								if (p>=1) F[now][k-2-Pow3[j-1]*2+Pow3[p]]+=key;
							}
						}
					}
					else{
						if ((x==0)&&(y==0)) F[now][k]+=key;
					}
				}
		}
	printf("%lld\n",Ans);return 0;
}
