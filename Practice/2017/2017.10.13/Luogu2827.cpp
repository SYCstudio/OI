#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define ld long double

const int maxN=8*1e6;
const int inf=2147483647;

class QUEUE
{
private:
	int h,t;
	ll Q[maxN];
public:
	QUEUE()
		{
			h=1;
			t=1;
			memset(Q,0,sizeof(Q));
		}
	void Insert(ll x)
		{
			Q[h]=x;
			h++;
		}
	ll Top()
		{
			if (t!=h)
				return Q[t];
			else
				return -inf;
		}
	void Pop()
		{
			t++;
		}
};

ll n,m,q,t;
int Arr[maxN];
QUEUE Q[4];

ll getmax();
bool cmp(int a,int b);

int main()
{
	int u,v;
	scanf("%lld%lld%lld%d%d%lld",&n,&m,&q,&u,&v,&t);
	for (int i=1;i<=n;i++)
		scanf("%d",&Arr[i]);
	sort(&Arr[1],&Arr[n+1],cmp);
	for (int i=1;i<=n;i++)
		Q[1].Insert(Arr[i]);
	ll addlen=0;
	for (int i=1;i<=m;i++)
	{
		ll now=getmax()+addlen;
		ll l1,l2;
		l1=(ld)now*u/v;
		l2=now-l1;
		//cout<<now<<" "<<l1<<" "<<l2<<endl;
		Q[2].Insert(l1-addlen-(ll)q);
		Q[3].Insert(l2-addlen-q);
		addlen+=q;
		if (i%t==0)
			printf("%lld ",now);
	}
	printf("\n");
	for (int i=1;i<=n+m;i++)
	{
		ll now=getmax()+(ll)m*(ll)q;
		if (i%t==0)
			printf("%lld ",now);
	}
	printf("\n");
	return 0;
}

ll getmax()
{
	ll now=max(Q[1].Top(),max(Q[2].Top(),Q[3].Top()));
	if (now==Q[1].Top())
		Q[1].Pop();
	else if (now==Q[2].Top())
		Q[2].Pop();
	else if (now==Q[3].Top())
		Q[3].Pop();
	return now;
}

bool cmp(int a,int b)
{
	return a>b;
}
