#include<bits/stdc++.h>
using namespace std;

#define mp make_pair
#define ft first
#define sd second
const int maxN=1010;
const int Mod=1e9+7;

int n;
int Mp[maxN][maxN],Up0[maxN][maxN],Up1[maxN][maxN];
pair<int,int> St[maxN];

int main(){
	scanf("%d",&n);int N=1ll*n*(n+1)/2%Mod;N=1ll*N*N%Mod;
	for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) scanf("%d",&Mp[i][j]);
	int A1=0,A2=0;
	for (int b=0;b<=30;b++){
		memset(Up0,0,sizeof(Up0));memset(Up1,0,sizeof(Up1));
		for (int i=1;i<=n;i++)
			for (int j=1;j<=n;j++)
				if ((Mp[i][j]>>b)&1) Up1[i][j]=Up1[i-1][j]+1;
				else Up0[i][j]=Up0[i-1][j]+1;
		int s1=0,s2=0;
		for (int i=1;i<=n;i++)
			for (int l=1,r;l<=n;l=r+1){
				r=l;if (Up1[i][l]==0) continue;
				while (r+1<=n&&Up1[i][r+1]) ++r;
				int top=0,sum=0;St[0]=mp(l-1,0);
				for (int j=l;j<=r;j++){
					while (top&&St[top].sd>=Up1[i][j])
						sum=(sum-1ll*St[top].sd*(St[top].ft-St[top-1].ft)%Mod+Mod)%Mod,--top;
					sum=(sum+1ll*Up1[i][j]*(j-St[top].ft)%Mod)%Mod;
					St[++top]=mp(j,Up1[i][j]);
					s1=(s1+sum)%Mod;
				}
			}
		for (int i=1;i<=n;i++)
			for (int l=1,r;l<=n;l=r+1){
				r=l;if (Up0[i][l]==0) continue;
				while (r+1<=n&&Up0[i][r+1]) ++r;
				int top=0,sum=0;St[0]=mp(l-1,0);
				for (int j=l;j<=r;j++){
					while (top&&St[top].sd>=Up0[i][j])
						sum=(sum-1ll*St[top].sd*(St[top].ft-St[top-1].ft)%Mod+Mod)%Mod,--top;
					sum=(sum+1ll*Up0[i][j]*(j-St[top].ft)%Mod)%Mod;
					St[++top]=mp(j,Up0[i][j]);
					//cout<<i<<" "<<j<<" "<<sum<<endl;
					s2=(s2+sum)%Mod;
				}
			}
		s2=(N-s2+Mod)%Mod;
		A1=(A1+1ll*s1*(1<<b)%Mod)%Mod;A2=(A2+1ll*s2*(1<<b)%Mod)%Mod;
	}
	printf("%d %d\n",A1,A2);return 0;
}
