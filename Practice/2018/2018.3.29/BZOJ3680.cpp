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

const int maxN=10010;
const int maxM=1;
const ld dt=0.9;
const ld Pi=acos(-1);
const ld eps=1e-4;
const ld inf=1e30;
//const int inf=2147483647;

class Pos
{
public:
	ld x,y;
};

int n;
Pos P[maxN];
ld W[maxN];
Pos Ans[maxN];
ld Dis[maxN];
Pos Outp;
ld ww=inf;

ld Make(ld l,ld r);
ld Calc(Pos P);
ld Dist(Pos A,Pos B);

int main()
{
	//srand(170524^141404);
	ios::sync_with_stdio(false);

	cin>>n;
	ld mxx=-inf,mxy=-inf,mnx=inf,mny=inf;
	for (int i=1;i<=n;i++) cin>>P[i].x>>P[i].y>>W[i];
	ld x0=0,y0=0;
	for (int i=1;i<=n;i++)
	{
		x0+=P[i].x;y0+=P[i].y;
		mxx=max(mxx,P[i].x);mxy=max(mxy,P[i].y);
		mnx=min(mnx,P[i].x);mny=min(mny,P[i].y);
	}
	x0=x0/n;y0=y0/n;Calc((Pos){x0,y0});
	ld dx=mxx-mnx,dy=mxy-mny;
	Ans[1].x=x0;Ans[1].y=y0;
	Dis[1]=Calc(Ans[1]);
	//cout<<x0<<" "<<y0<<endl;
	for (int i=2;i<=maxM;i++)
	{
		Ans[i].x=x0+Make(-dx*i/maxM,dx*i/maxM)/100;
		Ans[i].y=y0+Make(-dy*i/maxM,dy*i/maxM)/100;
		Dis[i]=Calc(Ans[i]);
	}
	ld T=1000;
	while (T>eps)
	{
		for (int i=1;i<=maxM;i++)
			for (int tim=1;tim<=20;tim++)
			{
				Pos now;
				now.x=Ans[i].x+T*Make(-1.0,1.0);
				now.y=Ans[i].y+T*Make(-1.0,1.0);
				ld d=Dis[i]-Calc(now);
				//if (d<0) cout<<d<<" "<<d/T<<" "<<exp(d/T)<<" "<<Make(0.0,1.0)<<endl;
				if ((d>eps)/*||(exp(d/T)<Make(0.0,1.0))*/) Ans[i]=now,Dis[i]=Calc(now);
			}
		T=T*dt;
		//printf("%.7lf\n",T);
	}
	/*
	for (int tim=1;tim<=5000;tim++)
		for (int i=1;i<=maxM;i++)
		{
			//ld theta=Make(0,Pi*2);
			Pos now;
			now.x=Ans[i].x+T*Make(-1.0,1.0);
			now.y=Ans[i].y+T*Make(-1.0,1.0);
			ld d=Calc(now);
			if ((d<Dis[i])/*||(exp((Dis[i]-d)/T)>Make(0,1))*///) Ans[i]=now,Dis[i]=d;
	//}
	//*/
	int id=1;
//for (int i=2;i<=maxM;i++) if (Dis[i]<Dis[id]) id=i;
	for(int tim=1;tim<=1000;tim++)
	{
		//ld theta=Make(0,Pi*2);
		Pos now;
		now.x=Ans[id].x+T*Make(-1.0,1.0);
		now.y=Ans[id].y+T*Make(-1.0,1.0);
		//cout<<now.x<<" "<<now.y<<endl;
		//printf("%.6lf %.6lf\n",now.x,now.y);
		ld d=Calc(now);
		if (d<Dis[id]) Ans[id]=now,Dis[id]=d;
		//cout<<Ans[id].x<<" "<<Ans[id].y<<endl;
		//printf("%.6lf %.6lf\n",Ans[id].x,Ans[id].y);
	}
	//printf("%.3lf %.3lf\n",Ans[id].x,Ans[id].y);
	printf("%.3lf %.3lf\n",Outp.x,Outp.y);
	return 0;
}

ld Make(ld l,ld r)
{
	ld dou=(ld)(rand())/RAND_MAX;
	return dou*(r-l)+l;
}

ld Calc(Pos H)
{
	//ld dx=0,dy=0;
	ld sd=0;
	for (int i=1;i<=n;i++)
	{
		ld d=Dist(H,P[i]);
		//dx=dx+W[i]*(P[i].x-H.x)/d;
		//dy=dy+W[i]*(P[i].y-H.y)/d;
		sd=sd+W[i]*d;
	}
	//return sqrt(dx*dx+dy*dy);
	if (sd<ww) Outp=H,ww=sd;
	return sd;
}

ld Dist(Pos A,Pos B)
{
	return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y));
}
