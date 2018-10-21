#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cmath>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define ld long double

const int maxN=10001;
const int F1[5]={0,0,0,1,-1};
const int F2[5]={0,1,-1,0,0};
const int inf=2147483647;

class Pos
{
public:
	int x,y;
};

int n,m,R,K;
ld midn,midm;
int lx,ly,rx,ry;
ld midnn,midmm;
priority_queue<Pos> Q;

bool operator < (Pos A,Pos B)
{
	return fabs((ld)A.x+0.5-midn)+fabs((ld)A.y+0.5-midm)>fabs((ld)B.x+0.5-midn)+fabs((ld)B.y+0.5-midm);
}

ld GetAns(Pos u);

int main()
{
	int h=0,t=0;
	cin>>n>>m>>R>>K;
	lx=(n+1)/2;ly=(m+1)/2;
	rx=(n+1)/2+(n%2==0);ry=(m+1)/2+(m%2==0);
	midn=(ld)1.0*(lx+rx+1)/2;
	midm=(ld)1.0*(ly+ry+1)/2;
	cout<<midn<<" "<<midm<<endl;
	for (int i=lx;i<=rx;i++) for (int j=ly;j<=ry;j++) Q.push((Pos){i,j});
	for (int i=1;i<=K;i++)
	{
		Pos u=Q.top();Q.pop();
		cout<<u.x<<" "<<u.y<<endl;
		if (Q.empty())
		{
			lx--;ly--;rx++;ry++;
			cout<<lx<<" "<<ly<<" "<<rx<<" "<<ry<<endl;
			for (int j=max(lx,1);j<=min(rx,n);j++)
			{
				if (ly>=1) Q.push((Pos){j,ly});
				if (ry<=m) Q.push((Pos){j,ry});
			}
			for (int j=max(ly,1);j<=min(ry,m);j++)
			{
				if (lx>=1) Q.push((Pos){lx,j});
				if (rx<=n) Q.push((Pos){rx,j});
			}
		}
	}
	return 0;
}

ld GetAns(Pos u)
{
	int l=u.x
}
