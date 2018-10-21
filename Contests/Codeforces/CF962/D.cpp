#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=151000;
const int inf=2147483647;

class Heap_Data
{
public:
	ll key,pos;
};

int n;
ll Ans[maxN];
priority_queue<Heap_Data> H;

bool operator < (Heap_Data A,Heap_Data B);

int main()
{
	//ios::sync_with_stdio(false);
	mem(Ans,-1);
	scanf("%d",&n);//cin>>n;
	for (int i=1;i<=n;i++)
	{
		ll num;scanf("%lld",&num);//cin>>num;
		H.push((Heap_Data){num,i});
	}
	int tot=n;
	while (!H.empty())
	{
		Heap_Data u=H.top();H.pop();
		if ((H.empty())||(H.top().key!=u.key))
		{
			Ans[u.pos]=u.key;
			continue;
		}
		Heap_Data v=H.top();H.pop();
		H.push((Heap_Data){u.key*2ll,v.pos});
		tot--;
	}
	printf("%d\n",tot);
	for (int i=1;i<=n;i++) if (Ans[i]!=-1) printf("%lld ",Ans[i]);///cout<<Ans[i]<<" ";
	return 0;
}

bool operator < (Heap_Data A,Heap_Data B)
{
	if (A.key!=B.key) return A.key>B.key;
	return A.pos>B.pos;
}
