#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

const int maxN=1200;

int n;
int D[maxN][maxN],Seq[maxN],Fa[maxN],Bp[maxN];

void Get(int u,int v);
void Solve(int left,int l,int r,int fa);

int main()
{
	scanf("%d",&n);
	int mxd=0,left,right;
	for (int i=1; i<=n; i++) {
		Get(1,i);
		if (D[1][i]>mxd) mxd=D[1][i],left=i;
	}
	for (int i=1; i<=n; i++) Seq[i]=i;
	Solve(left,1,n,0);
	printf("! ");
	for (int i=1; i<=n; i++) printf("%d ",Fa[i]);
	printf("\n");
	return 0;
}
void Get(int u,int v)
{
	if (D[u][v]||u==v) return;
	printf("? %d %d\n",u,v);
	fflush(stdout);
	scanf("%d",&D[u][v]);
	D[v][u]=D[u][v];
	return;
}
void Solve(int left,int l,int r,int fa)
{
	if (l==r||l>r) {
		if (l==r) Fa[Seq[l]]=fa;
		return;
	}
	//cout<<"Solve:"<<left<<" "<<l<<" "<<r<<" "<<fa<<":";for (int i=l;i<=r;i++) cout<<Seq[i]<<" ";cout<<endl;
	int mxd=0,right;
	for (int i=l; i<=r; i++) {
		Get(left,Seq[i]);
		if (D[left][Seq[i]]>mxd) mxd=D[left][Seq[i]],right=Seq[i];
	}
	for (int i=l; i<=r; i++) Get(right,Seq[i]);
	int ql=l-1,qr=r+1,mid;
	for (int i=l; i<=r; i++)
		if (D[left][Seq[i]]<D[right][Seq[i]]) Bp[++ql]=Seq[i];
		else if (D[right][Seq[i]]<D[left][Seq[i]]) Bp[--qr]=Seq[i];
		else mid=Seq[i];
	//cout<<left<<" "<<mid<<" "<<right<<endl;
	Fa[mid]=fa;
	for (int i=l; i<=r; i++) Seq[i]=Bp[i];
	Solve(left,l,ql,mid);
	Solve(right,qr,r,mid);
	return;
}