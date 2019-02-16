#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define lowbit(x) ((x)&(-(x)))

const int maxN=101000;
const int inf=2147483647;

class Data
{
public:
	ll tim,id,key;
	ll ans;
};

int n,m;
int Pos[maxN];
Data Q[maxN],Q2[maxN];
ll BIT[maxN],histcnt=0,Hist[maxN];
ll Ans[maxN];

bool operator < (Data A,Data B);
void Add(int pos,ll key);
ll Sum(int pos);
ll Query(int l,int r);
void Divide(int l,int r);

int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for (int i=1;i<=n;i++)
	{
		cin>>Q[i].key;Pos[Q[i].key]=i;
		Q[i].id=i;Q[i].tim=0;
	}
	int cnt=n;
	for (int i=m;i>=1;i--)
	{
		int pos;cin>>pos;pos=Pos[pos];
		Q[pos].tim=cnt--;
	}
	//cnt=0;
	for (int i=1;i<=n;i++) if (Q[i].tim==0) Q[i].tim=cnt--;
	sort(&Q[1],&Q[n+1]);
	//for (int i=1;i<=n;i++) cout<<Q[i].id<<" "<<Q[i].tim<<" "<<Q[i].key<<" "<<Q[i].ans<<endl;
	//cout<<endl;
	Divide(1,n);
	//for (int i=1;i<=n;i++) cout<<"id:"<<Q[i].id<<" tim:"<<Q[i].tim<<" key:"<<Q[i].key<<" ans:"<<Q[i].ans<<endl;
	for (int i=1;i<=n;i++) Ans[Q[i].tim]=Q[i].ans;
	for (int i=1;i<=n;i++) Ans[i]+=Ans[i-1];
	for (int i=1,j=n;i<=m;i++,j--) cout<<Ans[j]<<endl;
	return 0;
}

bool operator < (Data A,Data B)
{
	if (A.tim!=B.tim) return A.tim<B.tim;
	return A.id<B.id;
}

void Add(int pos,ll key)
{
	while (pos<=n)
	{
		if (Hist[pos]!=histcnt) BIT[pos]=key,Hist[pos]=histcnt;
		else BIT[pos]+=key;
		pos+=lowbit(pos);
	}
	return;
}

ll Sum(int pos)
{
	int ret=0;
	while (pos)
	{
		if (Hist[pos]==histcnt) ret+=BIT[pos];
		pos-=lowbit(pos);
	}
	return ret;
}

ll Query(int l,int r)
{
	if (l>r) return 0;
	return Sum(r)-Sum(l-1);
}

void Divide(int l,int r)
{
	if (l==r) return;
	int mid=(l+r)>>1;
	Divide(l,mid);Divide(mid+1,r);
	//cout<<"["<<l<<","<<r<<"]"<<endl;
	//for (int i=l;i<=r;i++) cout<<"id:"<<Q[i].id<<" tim:"<<Q[i].tim<<" key:"<<Q[i].key<<" ans:"<<Q[i].ans<<endl;cout<<endl;
	int p1=l,p2=mid+1;
	histcnt++;
	for (int i=l;i<=r;i++)
		if ((p1<=mid)&&((p2>r)||(Q[p1].id<Q[p2].id))){
			Add(Q[p1].key,1);p1++;
		}
		else{
			Q[p2].ans+=Query(Q[p2].key,n);p2++;
		}
	p1=mid,p2=r;histcnt++;
	for (int i=r;i>=l;i--)
		if ((p1>=l)&&((p2<mid+1)||(Q[p1].id>Q[p2].id))){
			Add(Q[p1].key,1);p1--;
		}
		else {
			Q[p2].ans+=Query(1,Q[p2].key);p2--;
		}
	
	p1=l;p2=mid+1;
	for (int i=l;i<=r;i++)
		if ((p1<=mid)&&((p2>r)||(Q[p1].id<Q[p2].id))) Q2[i]=Q[p1++];
		else Q2[i]=Q[p2++];
	for (int i=l;i<=r;i++) Q[i]=Q2[i];
	//for (int i=l;i<=r;i++) cout<<"id:"<<Q[i].id<<" tim:"<<Q[i].tim<<" key:"<<Q[i].key<<" ans:"<<Q[i].ans<<endl;cout<<endl;
	return;
}
