#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=100100;
const ld eps=1e-9;
const ld inf=1e9;

class Data
{
public:
	ld a,b,r,k;
	int id;
};

class Pos
{
public:
	ld x,y;
};

int n;
ld F[maxN];
Data Query[maxN],Q2[maxN];
Pos P[maxN],P2[maxN];
int Stack[maxN];

bool operator < (Pos A,Pos B);
bool operator < (Data A,Data B);
void Divide(int l,int r);
ld Slope(int u,int v);

int main()
{
	//ios::sync_with_stdio(false);
	int S;
	//cin>>n>>S;
	scanf("%d%d",&n,&S);
	F[0]=S;
	for (int i=1;i<=n;i++)
	{
		//cin>>Query[i].a>>Query[i].b>>Query[i].r;
		scanf("%LF%LF%LF",&Query[i].a,&Query[i].b,&Query[i].r);
		Query[i].k=-Query[i].a/Query[i].b;Query[i].id=i;
	}
	sort(&Query[1],&Query[n+1]);
	Divide(1,n);
	printf("%.3LF\n",F[n]);
	return 0;
}

bool operator < (Pos A,Pos B){
	if (fabs(A.x-B.x)<=eps) return A.y<B.y+eps;
	else return A.x<B.x+eps;
}

bool operator < (Data A,Data B){
	return A.k<B.k;
}

void Divide(int l,int r)
{
	if (l==r)
	{
		F[l]=max(F[l],F[l-1]);
		P[l].y=F[l]/(Query[l].r*Query[l].a+Query[l].b);
		P[l].x=P[l].y*Query[l].r;
		return;
	}
	int mid=(l+r)>>1;
	int p1=l,p2=mid+1;
	for (int i=l;i<=r;i++)
		if (Query[i].id<=mid) Q2[p1++]=Query[i];
		else Q2[p2++]=Query[i];
	for (int i=l;i<=r;i++) Query[i]=Q2[i];
	
	Divide(l,mid);

	int top=0;
	for (int i=l;i<=mid;i++)
	{
		while ((top>=2)&&(Slope(Stack[top],Stack[top-1])<Slope(i,Stack[top])+eps)) top--;
		Stack[++top]=i;
	}

	for (int i=r,j=1;i>=mid+1;i--)
	{
		while ((j<top)&&(Query[i].k<Slope(Stack[j],Stack[j+1])+eps)) j++;
		F[Query[i].id]=max(F[Query[i].id],P[Stack[j]].x*Query[i].a+P[Stack[j]].y*Query[i].b);
	}

	Divide(mid+1,r);
	p1=l;p2=mid+1;
	for (int i=l;i<=r;i++)
		if ((p1<=mid)&&((p2>r)||(P[p1]<P[p2]))) P2[i]=P[p1++];
		else P2[i]=P[p2++];
	for (int i=l;i<=r;i++) P[i]=P2[i];
	return;
}

ld Slope(int u,int v)
{
	if (u==0) return -inf;
	if (v==0) return inf;
	if (fabs(P[u].x-P[v].x)<=eps) return -inf;
	return (P[u].y-P[v].y)/(P[u].x-P[v].x);
}
