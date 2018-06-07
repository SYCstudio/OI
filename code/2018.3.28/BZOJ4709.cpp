#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=100100;
const int maxNum=maxN;
const int inf=2147483647;

int n;
int Num[maxN],Last[maxN];
vector<int> Queue[maxNum];
ll F[maxN],S[maxN];

int Beyond(int u,int v);
ll Calc(int p,ll key);

int main()
{
	//ios::sync_with_stdio(false);

	cin>>n;
	for (int i=1;i<=n;i++) cin>>Num[i];
	for (int i=1;i<=n;i++){
		S[i]=S[Last[Num[i]]]+1;Last[Num[i]]=i;
	}
	ll Ans=0;
	for (int i=1;i<=n;i++)
	{
		int id=Num[i];
		while ((Queue[id].size()>=2)&&(Beyond(Queue[id][Queue[id].size()-2],Queue[id][Queue[id].size()-1])<=Beyond(Queue[id][Queue[id].size()-1],i))) Queue[id].pop_back();
		Queue[id].push_back(i);
		while ((Queue[id].size()>=2)&&(Beyond(Queue[id][Queue[id].size()-2],Queue[id][Queue[id].size()-1])<=S[i])) Queue[id].pop_back();
		F[i]=Calc(Queue[id][Queue[id].size()-1],S[i]-S[Queue[id][Queue[id].size()-1]]+1ll);
		//cout<<F[i]<<" ";
		Ans=max(Ans,F[i]);
	}
	//cout<<endl;
	cout<<Ans<<endl;
	return 0;
}

int Beyond(int u,int v)
{
	int l=1,r=n;
	int Ret=n+1;
	//cout<<"Beyond:"<<u<<" "<<v<<endl;
	do
	{
		int mid=(l+r)>>1;
		if (Calc(u,mid-S[u]+1ll)>=Calc(v,mid-S[v]+1ll)) Ret=mid,r=mid-1;
		else l=mid+1;
	}
	while (l<=r);
	//cout<<"End:"<<u<<" "<<v<<" "<<Ret<<endl;
	return Ret;
}

ll Calc(int p,ll key)
{
	return F[p-1]+(ll)Num[p]*key*key;
}
