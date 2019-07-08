#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;

class Item
{
public:
	int value,cost;
	Item()
	{
		value=cost=-1;
	}
	void init(int a,int b)
	{
		value=a;
		cost=b;
	}
};

class MainItem
{
public:
	Item Main;
	Item A[3];
};

const int maxN=33000;
const int maxM=70;
const int inf=2147483647;

int n,m;
int Map[maxM];
MainItem I[maxM];
int F[maxM][maxN];

int main()
{
	int N=0;
	cin>>n>>m;
	for (int i=1; i<=m; i++) {
		int v,p,q;
		cin>>v>>p>>q;
		if (q==0) {
			N++;
			Map[i]=N;
			I[N].Main.init(v*p,v);
		} else {
			int vv=Map[q];
			if (I[vv].A[1].value==-1)
				I[vv].A[1].init(v*p,v);
			else
				I[vv].A[2].init(v*p,v);
		}
	}
	memset(F,0,sizeof(F));
	int Ans=0;
	for (int i=1; i<=N; i++)
		for (int j=0; j<=n; j++) {
			F[i][j]=F[i-1][j];
			int c=I[i].Main.cost;
			int v=I[i].Main.value;
			int c1=I[i].A[1].cost;
			int c2=I[i].A[2].cost;
			int v1=I[i].A[1].value;
			int v2=I[i].A[2].value;
			if (j>=c) {
				F[i][j]=max(F[i][j],F[i-1][j-c]+v);
			}
			if ((v1!=-1)&&(j>=c1+c))
				F[i][j]=max(F[i][j],F[i-1][j-c1-c]+v+v1);
			if ((v2!=-1)) {
				if (j>=c2+c)
					F[i][j]=max(F[i][j],F[i-1][j-c2-c]+v+v2);
				if (j>=c+c1+c2)
					F[i][j]=max(F[i][j],F[i-1][j-c-c1-c2]+v+v1+v2);
			}
			Ans=max(Ans,F[i][j]);
		}
	/*for (int i=1;i<=N;i++)
	{
	    for (int j=0;j<=n;j++)
	        cout<<F[i][j]<<' ';
	    cout<<endl;
	}*/
	cout<<Ans<<endl;
	return 0;
}
