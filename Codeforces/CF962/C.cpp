#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=11;
const int inf=2147483647;

int num;
int Queue[5000000];
int Depth[5000000];

int GetSize(int k);
bool Check(int k);

int main()
{
	ios::sync_with_stdio(false);
	cin>>num;
	if (Check(num))
	{
		cout<<0<<endl;
		return 0;
	}
	int h=1,t=0;
	Queue[1]=num;Depth[1]=0;
	do
	{
		int u=Queue[++t];
		if (Check(u))
		{
			cout<<Depth[t]<<endl;
			return 0;
		}
		int siz=GetSize(u);
		if (siz==1) continue;
		for (int i=1,wei=1;i<=siz;i++,wei*=10)
		{
			int v=u%wei+u/(wei*10)*wei;
			if (GetSize(v)==siz-1)
			{
				//cout<<u<<"->"<<v<<endl;
				Queue[++h]=v;
				Depth[h]=Depth[t]+1;
			}
		}
	}
	while (t!=h);
	cout<<-1<<endl;
	return 0;
}

int GetSize(int k)
{
	int Ret=0;
	while (k) Ret++,k/=10;
	return Ret;
}

bool Check(int k)
{
	int q=sqrt(k);
	return q*q==k;
}
