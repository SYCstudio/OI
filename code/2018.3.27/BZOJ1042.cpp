#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define ull unsigned long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=100100;
const int maxW=100000;
const int inf=2147483647;

int n;
ull c[4];
ull d[4];
ull F[4][maxN];

int main()
{
	ios::sync_with_stdio(false);
	
	cin>>c[0]>>c[1]>>c[2]>>c[3];
	for (int i=0;i<4;i++)
	{
		F[i][0]=0;
		for (int j=1;j<c[i];j++) F[i][j]=F[max(i-1,0)][j];
		F[i][c[i]]=F[max(i-1,0)][c[i]]+1;
		for (int j=c[i]+1;j<=maxW;j++)
			F[i][j]=F[max(i-1,0)][j]+F[i][max(j-c[i],(ull)0)];
	}
	F[3][0]=1;
	/*
	for (int i=0;i<4;i++)
	{
		for (int j=1;j<=20;j++)
			cout<<F[i][j]<<" ";
		cout<<endl;
	}
	//*/
	int Q;cin>>Q;
	while (Q--)
	{
		ull s;
		cin>>d[0]>>d[1]>>d[2]>>d[3]>>s;
		ull Ans=0;
		for (int S=0;S<(1<<4);S++)
		{
			int w=s;int opt=1;
			for (int i=0;i<4;i++) if ((S&(1<<i))!=0) w-=c[i]*(d[i]+1),opt=-opt;
			if (w<0) continue;
			//cout<<S<<" "<<w<<" "<<F[3][w]<<endl;
			Ans=Ans+opt*F[3][w];
		}
		cout<<Ans<<endl;
	}
	return 0;
}
