#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
#include<iostream>
using namespace std;

typedef long long ll;
#define mp make_pair
#define ft first
#define sd second
const int maxN=202000;
const ll INF=1e18;

class MyHeap
{
	priority_queue<pair<ll,int> > H,Del;
public:
	void maintain()
	{
		while (!H.empty()&&!Del.empty()&&H.top().sd==Del.top().sd) H.pop(),Del.pop();
		return;
	}
	void push(pair<ll,int> key)
	{
		H.push(key);
		return;
	}
	void pop()
	{
		maintain();
		H.pop();
		return;
	}
	pair<ll,int> top()
	{
		maintain();
		return H.top();
	}
	void delet(pair<ll,int> key)
	{
		Del.push(key);
		return;
	}
	void outp()
	{
		static priority_queue<pair<ll,int> > Dq;
		while (!Dq.empty()) Dq.pop();
		cout<<"H:";
		while (!H.empty()) cout<<"("<<H.top().ft<<" "<<H.top().sd<<")",Dq.push(H.top()),H.pop();
		cout<<endl;
		while (!Dq.empty()) H.push(Dq.top()),Dq.pop();
		cout<<"Del:";
		while (!Del.empty()) cout<<"("<<Del.top().ft<<" "<<Del.top().sd<<")",Dq.push(Del.top()),Del.pop();
		cout<<endl;
		while (!Dq.empty()) Del.push(Dq.top()),Dq.pop();
		return;
	}
};

int n,Nxt[maxN],Pre[maxN];//,Mark[maxN];
ll A[maxN];
MyHeap H;

int main()
{
	scanf("%d",&n);
	for (int i=1; i<=n; i++) scanf("%lld",&A[i]),H.push(mp(A[i],i));
	for (int i=1; i<n; i++) Nxt[i]=i+1,Pre[i+1]=i;
	int K=n/2+(n&1);
	ll Ans=0;
	for (int i=1; i<=K; i++) {
		pair<ll,int> k=H.top();
		H.pop();
		Ans+=k.ft;
		//cout<<"Get:"<<k.ft<<" "<<k.sd<<endl;
		int u=k.sd,pre=Pre[u],nxt=Nxt[u];
		if (pre) H.delet(mp(A[pre],pre));//,Mark[pre]=1;
		if (nxt) H.delet(mp(A[nxt],nxt));//,Mark[nxt]=1;
		if (pre&&nxt) {
			A[u]=A[pre]+A[nxt]-A[u];
			H.push(mp(A[u],u));
		} else A[u]=-INF,H.push(mp(A[u],u));
		if (pre&&Pre[pre]) Nxt[Pre[pre]]=u;
		if (nxt&&Nxt[nxt]) Pre[Nxt[nxt]]=u;
		if (pre) Pre[u]=Pre[pre];
		if (nxt) Nxt[u]=Nxt[nxt];
		//for (int j=1;j<=n;j++) cout<<Pre[j]<<" ";cout<<endl;
		//for (int j=1;j<=n;j++) cout<<Nxt[j]<<" ";cout<<endl;
		//for (int i=1;i<=n;i++) cout<<Mark[i]<<" ";cout<<endl;
		//H.outp();
		printf("%lld\n",Ans);
	}
	return 0;
}
