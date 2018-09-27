#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<map>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define NAME "stone"

const int maxN=1010000;
const int inf=2147483647;

int n,m;
char s1[maxN],s2[maxN];
int q1[maxN],q2[maxN],sum[maxN][3][3];
map<char,int> Mp;

int main(){
	scanf("%s",s1+1);scanf("%s",s2+1);
	n=strlen(s1+1);m=strlen(s2+1);Mp['R']=0;Mp['G']=1;Mp['B']=2;
	for (int i=1;i<=n;i++) q1[i]=Mp[s1[i]];
	for (int i=1;i<=m;i++) q2[i]=Mp[s2[i]];
	for (int i=2;i<=n;i++){
		for (int j=0;j<3;j++) for (int k=0;k<3;k++) sum[i][j][k]=sum[i-1][j][k];
		sum[i][q1[i-1]][q1[i]]++;
	}
	ll Ans=0;
	for (int i=1,l,r;i<=m;i++)
		if (i==1){
			l=r=1;
			while ((r<n)&&(q1[r]!=q2[i])) r++;
			Ans+=(r-l+1);
		}
		else{
			r++;
			while ((r<n)&&(q1[r]!=q2[i])) r++;
			r=min(r,n);
			if (q1[l]==q2[i-1]) l++;
			if (l>n) break;
			Ans+=(r-l+1);
			if (q2[i]!=q2[i-1])
				Ans-=(sum[r][q2[i]][q2[i-1]]-sum[l][q2[i]][q2[i-1]]);
		}
	printf("%lld\n",Ans);return 0;
}
