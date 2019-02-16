#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define lowbit(x) (x)&(-(x))

const int maxN=100010;
const int maxNum=200010;
const int inf=2147483647;

class Data
{
public:
	int a,b,c,ans,cnt;
};

int n;
Data D[maxN],Backup[maxN];
int Bit[maxNum];
int histcnt=0,Hist[maxNum];
int Ans[maxN],Cnt[maxN];

bool cmp(Data A,Data B);
void Solve(int l,int r);
void Add(int pos,int key);
int Sum(int pos);

int main()
{
	ios::sync_with_stdio(false);

	int K;
	cin>>n>>K;
	for (int i=1;i<=n;i++){
		cin>>D[i].a>>D[i].b>>D[i].c;
	}
	sort(&D[1],&D[n+1],cmp);
	int p=0;
	for (int i=1,j=0;i<=n;i++)
	{
		j++;
		if ((D[i].a!=D[i+1].a)||(D[i].b!=D[i+1].b)||(D[i].c!=D[i+1].c)){
			D[++p]=D[i];D[p].cnt=j;j=0;
		}
	}
	//for (int i=1;i<=p;i++) cout<<D[i].a<<" "<<D[i].b<<" "<<D[i].c<<" "<<D[i].cnt<<endl;
	//for (int i=1;i<=n;i++) cout<<D[i].a<<" "<<D[i].b<<" "<<D[i].c<<" "<<D[i].id<<endl;
	Solve(1,p);
	//for (int i=1;i<=n;i++) cout<<Ans[i]<<endl;
	//for (int i=1;i<=n;i++) cout<<D[i].a<<" "<<D[i].b<<" "<<D[i].c<<" "<<D[i].ans<<endl;
	for (int i=1;i<=p;i++) Cnt[D[i].ans]+=D[i].cnt;
	for (int i=0;i<n;i++) cout<<Cnt[i]<<endl;
	return 0;
}

bool cmp(Data A,Data B)
{
	if (A.a!=B.a) return A.a<B.a;
	if (A.b!=B.b) return A.b<B.b;
	return A.c<B.c;
}

void Solve(int l,int r)
{
	if (l==r){
		D[l].ans=D[l].cnt-1;
		return;
	}
	int mid=(l+r)>>1;
	Solve(l,mid);Solve(mid+1,r);
	histcnt++;//mem(Bit,0);
	int p1=l,p2=mid+1;
	//cout<<"["<<l<<","<<r<<"] mid:"<<mid<<endl;
	//for (int i=l;i<=r;i++) cout<<D[i].a<<" "<<D[i].b<<" "<<D[i].c<<" "<<D[i].id<<endl;cout<<endl;
	for (int i=l;i<=r;i++)
		if ((p1<=mid)&&((p2>r)||(D[p1].b<=D[p2].b))){
			Backup[i]=D[p1];Add(D[p1].c,D[p1].cnt);p1++;
		}
		else{
			//cout<<D[p2].a<<" "<<D[p2].b<<" "<<D[p2].c<<" "<<" "<<Sum(D[p2].c)<<endl;
			D[p2].ans+=Sum(D[p2].c);Backup[i]=D[p2];p2++;
		}
	for (int i=l;i<=r;i++) D[i]=Backup[i];
	return;
}

void Add(int pos,int key)
{
	while (pos<maxNum)
	{
		if (Hist[pos]!=histcnt) Bit[pos]=key,Hist[pos]=histcnt;
		else Bit[pos]+=key;
		//Bit[pos]+=key;
		pos+=lowbit(pos);
	}
	return;
}

int Sum(int pos)
{
	int ret=0;
	while (pos)
	{
		if (Hist[pos]==histcnt) ret+=Bit[pos];
		//ret+=Bit[pos];
		pos-=lowbit(pos);
	}
	return ret;
}
