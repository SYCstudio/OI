#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define RG register

const int maxN=1000010;
const int Mod=1e9+7;
const int maxBit=20;
const int inf=2147483647;

int n;
char str[maxN];
int Next[maxBit+1][maxN],Size[maxBit+1][maxN];
int Num[maxN],Tot[maxN];

int main()
{
	ios::sync_with_stdio(false);
	RG int T;cin>>T;
	while (T--)
	{
		cin>>(str+1);n=strlen(str+1);
		mem(Next[0],0);mem(Size[0],0);
		Next[0][0]=-1;Next[0][1]=0;
		for (RG int i=2;i<=n;++i)
		{
			RG int j=Next[0][i-1];
			while ((j!=0)&&(str[j+1]!=str[i])) j=Next[0][j];
			if (str[j+1]==str[i]) Next[0][i]=j+1;
			else Next[0][i]=0;
			Size[0][i]=1;
		}
		//cout<<"Next:";for (int i=1;i<=n;i++) cout<<Next[0][i]<<" ";cout<<endl;
		for (RG int i=1;i<=maxBit;++i)
			for (RG int j=1;j<=n;++j)
				Next[i][j]=Next[i-1][Next[i-1][j]],Size[i][j]=Size[i-1][j]+Size[i-1][Next[i-1][j]];
		mem(Num,0);mem(Tot,0);Num[0]=-1;
		for (RG int i=1;i<=n;++i)
		{
			RG int now=i;
			for (RG int j=maxBit;j>=0;--j) if (Next[j][now]*2>i) now=Next[j][now],Tot[i]=Tot[i]+Size[j][now];
			now=Next[0][now];
			Tot[i]+=Tot[now]+1;
			Num[i]=Tot[now];
			//cout<<i<<" "<<now<<endl;
		}
		//for (int i=1;i<=n;i++) cout<<Num[i]<<" ";cout<<endl;
		//for (int i=1;i<=n;i++) cout<<Tot[i]<<" ";cout<<endl;
		RG ll Ans=1;
		for (RG int i=1;i<=n;++i) Ans=Ans*(ll)(Num[i]+1)%Mod;
		printf("%lld\n",Ans);
	}
	return 0;
}
