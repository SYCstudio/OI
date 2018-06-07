#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1000100;
const int inf=47483647;

int n;
int L[maxN],R[maxN];
ll H[maxN];
ll F[2][maxN][2],Pos[2][maxN],Cnt[2];

ll Calc();

int main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	for (int i=1;i<=n;i++) cin>>L[i]>>R[i];
	for (int i=1;i<=n;i++) H[i]=R[i];
	ll Ans=0;
	Ans+=Calc();//cout<<Ans<<endl;
	for (int i=1;i<=n;i++) H[i]=maxN-L[i];
	Ans+=Calc();
	cout<<Ans<<endl;
	return 0;
}

ll Calc()
{
	Cnt[1]=0;
	for (int i=1;i<=3;i++)
		for (int j=H[i];j<=H[i]+3;j++)
			if (j>=H[1]) Pos[1][++Cnt[1]]=j;
	mem(F,63);
	for (int i=1;i<=Cnt[1];i++) F[1][i][0]=Pos[1][i]-H[1];
	int now=1;
	for (int i=2;i<=n;i++)
	{
		now^=1;Cnt[now]=0;
		int l=max(1,i-2),r=min(n,i+2);
		for (int j=l;j<=r;j++)
			for (int k=H[j];k<=H[j]+2;k++)
				if (k>=H[i]) Pos[now][++Cnt[now]]=k;
		//cout<<H[i]<<":"<<endl;
		//for (int j=1;j<=Cnt[now];j++) cout<<Pos[now][j]<<" ";cout<<endl;
		for (int j=1;j<=Cnt[now];j++)
		{
			F[now][j][0]=F[now][j][1]=inf;
			for (int k=1;k<=Cnt[now^1];k++)
				if (Pos[now][j]>Pos[now^1][k]) F[now][j][1]=min(F[now][j][1],F[now^1][k][0]);
				else if (Pos[now][j]<Pos[now^1][k]) F[now][j][0]=min(F[now][j][0],F[now^1][k][1]);
				else
				{
					F[now][j][0]=min(F[now][j][0],F[now^1][k][0]);
					F[now][j][1]=min(F[now][j][1],F[now^1][k][1]);
				}
			F[now][j][0]+=Pos[now][j]-H[i];
			F[now][j][1]+=Pos[now][j]-H[i];
		}
	}
	ll Ret=inf;
	//for (int i=1;i<=Cnt[now];i++) cout<<F[now][i][0]<<" ";cout<<endl;
	for (int i=1;i<=Cnt[now];i++) Ret=min(Ret,F[now][i][0]);
	return Ret;
}
