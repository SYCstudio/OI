#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define ld double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010;
const int maxM=50;
const ld dt=0.75;
const ld eps=1e-5;
const ld Pi=acos(-1);
const ld INF=1e14;
const int inf=2147483647;

class Pos
{
public:
	ld x,y;
};

int X,Y,N;
Pos Hole[maxN],Ans[maxN];
ld Dis[maxN];

void SA();
ld Rand(ld l,ld r);
ld Dist(Pos A,Pos B);
ld Calc(Pos P);

int main()
{
	//ios::sync_with_stdio(false);
	int T;scanf("%d",&T);
	while (T--)
	{
		scanf("%d%d%d",&X,&Y,&N);
		for (int i=1;i<=N;i++) scanf("%lf%lf",&Hole[i].x,&Hole[i].y);
		SA();
	}
	return 0;
}

ld Rand(ld l,ld r)
{
	ld dou=(ld)rand()/(ld)RAND_MAX;
	return dou*(r-l+1)+l;
}

ld Dist(Pos A,Pos B){
	return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y));
}

ld Calc(Pos P)
{
	ld ret=INF;
	for (int i=1;i<=N;i++) ret=min(ret,Dist(P,Hole[i]));
	return ret;
}

void SA()
{
	ld T=max(X,Y);
	for (int i=1;i<=maxM;i++)
	{
		Ans[i].x=Rand(0.0,X*1.0);
		Ans[i].y=Rand(0.0,Y*1.0);
		Dis[i]=Calc(Ans[i]);
	}
	/*
	for (int i=1;i<=maxM;i++)
		cout<<Ans[i].x<<" "<<Ans[i].y<<endl;
	cout<<endl;
	//*/
	while (T>eps)
	{
		for (int i=1;i<=maxM;i++)
			for (int t=1;t<=50;t++)
			{
				ld theta=Rand(0.0,Pi*2.0);
				Pos now;
				now.x=Ans[i].x+cos(theta)*T;
				now.y=Ans[i].y+sin(theta)*T;
				if ((now.x<0)||(now.y<0)||(now.x>X)||(now.y>Y)) continue;
				ld d=Calc(now);
				if (d>=Dis[i])
				{
					Dis[i]=d;Ans[i]=now;
				}
			}
		T=T*dt;
	}
	/*
	for (int i=1;i<=maxM;i++)
		cout<<"("<<Ans[i].x<<","<<Ans[i].y<<") "<<Dis[i]<<endl;
	//*/
	int id=1;
	for (int i=2;i<=maxM;i++) if (Dis[i]>Dis[id]) id=i;
	printf("The safest point is (%.1lf, %.1lf).\n",Ans[id].x,Ans[id].y);
	//cout<<"mxDis:"<<id<<" "<<Max<<endl;
	return;
}
