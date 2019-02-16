#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=100100;
const int maxMap=18;
const int Mod=1000000001;
const int inf=2147483647;

int n;
bool Used[maxN];
int Len[maxMap];
int Map[maxMap][maxMap];
int F[maxMap][1<<maxMap];

ll Calc(int st);

int main()
{
	ios::sync_with_stdio(false);

	ll Ans=1;
	cin>>n;
	for (int i=1;i<=n;i++) if (Used[i]==0) Ans=Ans*Calc(i)%Mod;
	cout<<Ans<<endl;

	return 0;
}

ll Calc(int st)
{
	Used[Map[1][1]=st]=1;
	for (int i=2;;i++)
	{
		if (Map[1][i-1]*3ll>n){
			Len[1]=i-1;break;
		}
		Used[Map[1][i]=Map[1][i-1]*3ll]=1;
	}
	int line;
	for (int i=2;;i++)
	{
		if (Map[i-1][1]*2ll>n){
			line=i-1;break;
		}
		Used[Map[i][1]=Map[i-1][1]*2ll]=1;
		for (int j=2;;j++)
		{
			if (Map[i][j-1]*3ll>n){
				Len[i]=j-1;break;
			}
			Used[Map[i][j]=Map[i][j-1]*3]=1;
		}
	}
	/*
	for (int i=1;i<=line;i++)
	{
		for (int j=1;j<=Len[i];j++)
			cout<<Map[i][j]<<" ";
		cout<<endl;
	}
	cout<<endl;
	//*/
	//mem(F,0);
	for (int i=1;i<=line;i++) for (int S=0;S<(1<<Len[i]);S++) F[i][S]=0;
	F[0][0]=1;
	for (int S=0;S<(1<<Len[1]);S++)
		if ((S&(S<<1))==0) F[1][S]=1;
	for (int i=2;i<=line;i++)
	{
		for (int S1=0;S1<(1<<Len[i-1]);S1++)
			if ((S1&(S1<<1))==0)
				for (int S2=0;S2<(1<<Len[i]);S2++)
					if (((S2&(S2<<1))==0) && ((S1&S2)==0))
						F[i][S2]=(F[i][S2]+F[i-1][S1])%Mod;
	}
	ll Ret=0;
	for (int S=0;S<(1<<Len[line]);S++)
		if ((S&(S<<1))==0) Ret=(Ret+F[line][S])%Mod;
	return Ret;
}
