#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

class SegmentTree
{
public:
	int data;
	int lazynum;
	int lazydata;
};

const int maxN=50001;
const int inf=2147483647;

int n;
SegmentTree T[maxN*4];

int read();
void Init();
void Updata(int num,int data);
int Query(int l0,int r0,int l,int r,int num);

int main()
{
	int T;
	T=read();
	for (int ti=1; ti<=T; ti++) {
		printf("Case %d:\n",ti);
		Init();
		n=read();
		for (int i=1; i<=n; i++)
			Updata(i,read());
		char str[7];
		cin>>str;
		while (str[0]!='E') {
			if (str[0]=='A') {
				int a=read(),b=read();
				Updata(a,b);
			} else if (str[0]=='S') {
				int a=read(),b=read();
				//cout<<"AAA"<<endl;
				Updata(a,-b);
			} else {
				int a=read(),b=read();
				cout<<Query(a,b,1,n,1)<<endl;
			}
			cin>>str;
		}
	}
}

int read()
{
	int x=0;
	int k=1;
	char ch=getchar();
	while (((ch<'0')||(ch>'9'))&&(ch!='-'))
		ch=getchar();
	if (ch=='-') {
		k=-1;
		ch=getchar();
	}
	while ((ch<='9')&&(ch>='0')) {
		x=x*10+ch-48;
		ch=getchar();
	}
	//cout<<x<<' '<<k<<endl;
	return x*k;
}

void Init()
{
	memset(T,0,sizeof(T));
	return;
}

void Updata(int num,int data)
{
	int now=1;
	int l=1,r=n;
	do {
		//cout<<l<<' '<<r<<endl;
		int mid=(l+r)/2;
		T[now].data+=data;
		if (l==r)
			break;
		if (num<=mid) {
			r=mid;
			now=now*2;
		} else {
			l=mid+1;
			now=now*2+1;
		}
	} while (1);
	return;
}

int Query(int l0,int r0,int l,int r,int num)
{
	if ((l0==l)&&(r0==r))
		return T[num].data;
	int mid=(l+r)/2;
	if (l0>=mid+1) {
		return Query(l0,r0,mid+1,r,num*2+1);
	} else if (r0<=mid) {
		return Query(l0,r0,l,mid,num*2);
	} else {
		return Query(l0,mid,l,mid,num*2)+Query(mid+1,r0,mid+1,r,num*2+1);
	}
}
