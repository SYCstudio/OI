#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=300100;
const int inf=2147483647;

class Heap
{
public:
	int key;
	int ls,rs,dis,fa,lazy;
};

int n;
Heap H[maxN];
priority_queue<int> Q1,Q2;

int Merge(int r1,int r2);
void PushDown(int r);
void Mark(int r,int lazy);
int GetRt(int x);
void PushLazy(int x);
void QPush(int x);
void QDel(int x);
int QTop();

int main()
{
	freopen("in.in","r",stdin);freopen("out.out","w",stdout);
	ios::sync_with_stdio(false);
	cin>>n;
	for (int i=1;i<=n;i++){
		cin>>H[i].key;QPush(H[i].key);
	}
	int Q;cin>>Q;
	char opt[5];
	int allsum=0;
	while (Q--)
	{
		cin>>opt;
		if (opt[0]=='U')
		{
			int x,y;cin>>x>>y;
			x=GetRt(x);y=GetRt(y);
			if (x!=y){
				int t=Merge(x,y);
				if (t==x) QDel(H[y].key);
				else QDel(H[x].key);
			}
		}
		if (opt[0]=='A')
		{
			if (opt[1]=='1')
			{
				int x,v;cin>>x>>v;
				PushLazy(x);QDel(H[GetRt(x)].key);
				
				int nrt=Merge(H[x].ls,H[x].rs),fa=H[x].fa;
				
				if (H[fa].ls==x) H[fa].ls=nrt;
				else if (H[fa].rs==x) H[fa].rs=nrt;
				H[x].fa=H[x].ls=H[x].rs=0;H[x].key+=v;
				H[nrt].fa=fa;
				//cout<<"nrt:"<<nrt<<endl;
				
				nrt=GetRt(nrt);
				nrt=Merge(x,nrt);
				QPush(H[nrt].key);
			}
			if (opt[1]=='2')
			{
				int x,v;cin>>x>>v;
				x=GetRt(x);QDel(H[x].key);
				Mark(x,v);QPush(H[x].key);
			}
			if (opt[1]=='3')
			{
				int v;cin>>v;allsum+=v;
			}
		}
		if (opt[0]=='F')
		{
			if (opt[1]=='1')
			{
				int x;cin>>x;
				PushLazy(x);
				printf("%d\n",H[x].key+allsum);
			}
			if (opt[1]=='2')
			{
				int x;cin>>x;
				x=GetRt(x);
				printf("%d\n",H[x].key+allsum);
			}
			if (opt[1]=='3')
			{
				printf("%d\n",QTop()+allsum);
			}
		}
	}
	return 0;
}

int Merge(int r1,int r2)
{
	if (r1==0) return r2;
	if (r2==0) return r1;
	PushDown(r1);PushDown(r2);
	if (H[r1].key<H[r2].key) swap(r1,r2);
	H[r1].rs=Merge(H[r1].rs,r2);
	H[H[r1].rs].fa=r1;
	if (H[H[r1].ls].dis<H[H[r1].rs].dis) swap(H[r1].ls,H[r1].rs);
	if (H[r1].rs) H[r1].dis=H[H[r1].rs].dis+1;
	else H[r1].dis=0;
	return r1;
}

void PushDown(int r)
{
	if (H[r].lazy==0) return;
	if (H[r].ls) Mark(H[r].ls,H[r].lazy);
	if (H[r].rs) Mark(H[r].rs,H[r].lazy);
	H[r].lazy=0;return;
}

void Mark(int r,int lazy)
{
	H[r].key+=lazy;H[r].lazy+=lazy;
	return;
}

int GetRt(int x)
{
	while (H[x].fa) x=H[x].fa;
	return x;
}

int Stack[maxN];

void PushLazy(int x)
{
	int stacktop=0;
	while (x){
		Stack[++stacktop]=x;x=H[x].fa;
	}
	while (stacktop) PushDown(Stack[stacktop--]);
	return;
}

void QPush(int x)
{
	Q1.push(x);return;
}

void QDel(int x)
{
	Q2.push(x);
	while ((!Q1.empty())&&(!Q2.empty())&&(Q1.top()==Q2.top())) Q1.pop(),Q2.pop();
	return;
}

int QTop()
{
	while ((!Q1.empty())&&(!Q2.empty())&&(Q1.top()==Q2.top())) Q1.pop(),Q2.pop();
	return Q1.top();
}
