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

int n,m;
int Mat[maxN][maxN];
int R[maxN],C[maxN],S[maxN];

int main(){
	scanf("%d%d",&n,&m);
	ll sum=0;
	for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) scanf("%d",&Mat[i][j]),sum=sum+Mat[i][j];
	for (int i=1;i<=n;i++)
		for (R[i]=m;R[i]>=1;R[i]--){
			mem(S,0);bool flag=1;
			for(int j=1;j<=m;j++){
				S[j]+=S[j-1];
				if (S[j]>Mat[i][j]){
					flag=0;break;
				}
				if ((j+R[i]-1>m)&&(S[j]!=Mat[i][j])){
					flag=0;break;
				}
				int k=Mat[i][j]-S[j];
				S[j]+=k;S[j+R[i]]-=k;
			}
			if (flag) break;
		}
	for (int i=1;i<=m;i++)
		for (C[i]=n;C[i]>=1;C[i]--){
			mem(S,0);bool flag=1;
			for (int j=1;j<=n;j++){
				S[j]+=S[j-1];
				if (S[j]>Mat[j][i]){
					flag=0;break;
				}
				if ((j+C[i]-1>n)&&(S[j]!=Mat[j][i])){
					flag=0;break;
				}
				int k=Mat[j][i]-S[j];
				S[j]+=k;S[j+C[i]]-=k;
			}
			if (flag) break;
		}

	int r=R[1],c=C[1];
	for (int i=2;i<=n;i++) r=__gcd(r,R[i]);
	for (int i=2;i<=m;i++) c=__gcd(c,C[i]);
	//for (int i=1;i<=n;i++) cout<<R[i]<<" ";cout<<endl;
	//for (int i=1;i<=m;i++) cout<<C[i]<<" ";cout<<endl;
	printf("%lld\n",sum/(1ll*r*c));return 0;
}
