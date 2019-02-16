#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<bitset>
#include<cmath>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define RG register

const int maxN=100001;
const int inf=2147483647;

class Question
{
public:
	int opt,l,r,x;
	int id;
};

int n,m;
int Belong[maxN],Arr[maxN];
Question Q[maxN];
int Ans[maxN],Cnt[maxN];
bitset<maxN> B1,B2;

bool cmp(Question A,Question B);
void Add(RG int key);
void Del(RG int key);

int main()
{
	//freopen("in.in","r",stdin);freopen("out","w",stdout);
	scanf("%d%d",&n,&m);RG int block=sqrt(n);
	for (RG int i=1;i<=n;i++) Belong[i]=i/block;
	for (RG int i=1;i<=n;i++) scanf("%d",&Arr[i]);

	for (RG int i=1;i<=m;i++)
	{
		scanf("%d%d%d%d",&Q[i].opt,&Q[i].l,&Q[i].r,&Q[i].x);
		Q[i].id=i;
	}
	sort(&Q[1],&Q[m+1],cmp);

	RG int l=1,r=0;
	for (RG int i=1;i<=m;i++)
	{
		while (r<Q[i].r) Add(Arr[++r]);
		while (r>Q[i].r) Del(Arr[r--]);
		while (l<Q[i].l) Del(Arr[l++]);
		while (l>Q[i].l) Add(Arr[--l]);

		if (Q[i].opt==1){
			if ((B1&(B1>>Q[i].x)).any()) Ans[Q[i].id]=1;
		}
		else if (Q[i].opt==2){
			if ((B1&(B2>>(100000-Q[i].x))).any()) Ans[Q[i].id]=1;
		}
		else
		{
			RG int up=sqrt(Q[i].x);
			//cout<<"Q:"<<Q[i].l<<" "<<Q[i].r<<" "<<Q[i].x<<endl;
			for (RG int j=1;j<=up;j++)
			{
				//cout<<j<<" "<<Cnt[j]<<" "<<Cnt[Q[i].x/j]<<endl;
				if ((Q[i].x%j==0)&&(Cnt[j])&&(Cnt[Q[i].x/j]))
				{
					Ans[Q[i].id]=1;
					break;
				}
			}
		}
	}
	for (RG int i=1;i<=m;i++) puts((Ans[i])?("hana"):("bi"));
	return 0;
}

bool cmp(Question A,Question B){
	if (Belong[A.l]!=Belong[B.l]) return Belong[A.l]<Belong[B.l];
	else return A.r<B.r;
}

void Add(RG int key)
{
	Cnt[key]++;
	if (Cnt[key]==1) B1[key]=B2[-key+100000]=1;
	return;
}

void Del(RG int key)
{
	Cnt[key]--;
	if (Cnt[key]==0) B1[key]=B2[-key+100000]=0;
	return;
}
