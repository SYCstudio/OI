#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=51;
const int inf=2147483647;
const int meminf=1061109567;

char str[maxN];
int n,K;
int F[maxN][maxN];

int main()
{
	scanf("%d%d",&n,&K);
	scanf("%s",str+1);
	sort(&str[1],&str[n+1]);
	n=unique(&str[1],&str[n+1])-str-1;
	mem(F,63);
	F[0][0]=0;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=K;j++)
			for (int k=0;k<i;k++)
				if (str[i]-str[k]>=2)
					F[i][j]=min(F[i][j],F[k][j-1]+str[i]-'a'+1);

	int Ans=meminf;
	for (int i=1;i<=n;i++) Ans=min(Ans,F[i][K]);
	if (Ans==meminf) printf("-1\n");
	else printf("%d\n",Ans);
	return 0;
}

