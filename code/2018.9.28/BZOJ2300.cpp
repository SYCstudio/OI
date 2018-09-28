#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<set>
#include<cmath>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int inf=2147483647;

class Point
{
public:
	int x,y;
};

int n,cx,cy,m,Q;
Point P[maxN];
set<Point> S;
pair<int,int> Opt[maxN];
bool fob[maxN];
ld Ans=0,Outp[maxN];

void Insert(Point A);
Point operator + (Point A,Point B);
Point operator - (Point A,Point B);
bool operator < (Point A,Point B);
int Cross(Point A,Point B);
ld Dist(Point A,Point B);

int main(){
	scanf("%d%d%d",&n,&cx,&cy);
	scanf("%d",&m);
	for (int i=1;i<=m;i++) scanf("%d%d",&P[i].x,&P[i].y);
	scanf("%d",&Q);
	for (int i=1;i<=Q;i++){
		scanf("%d",&Opt[i].first);
		if (Opt[i].first==1){
			scanf("%d",&Opt[i].second);
			fob[Opt[i].second]=1;
		}
	}

	Ans=Dist(((Point){0,0}),((Point){cx,cy}))+Dist(((Point){cx,cy}),((Point){n,0}));
	S.insert((Point){0,0});S.insert((Point){n,0});S.insert((Point){cx,cy});
	for (int i=1;i<=m;i++) if (fob[i]==0) Insert(P[i]);

	for (int i=Q;i>=1;i--)
		if (Opt[i].first==1) Insert(P[Opt[i].second]);
		else Outp[i]=Ans;
	
	for (int i=1;i<=Q;i++)
		if (Opt[i].first==2) printf("%.2LF\n",Outp[i]);

	return 0;
}

void Insert(Point A){
	set<Point>::iterator p=S.lower_bound(A),p2,p3;
	if (A.x==(*p).x){
		if (A.y<=(*p).y) return;
		p2=p;p2--;p3=p;p3++;
		Ans-=Dist((*p),(*p2));Ans-=Dist((*p),(*p3));
		Ans+=Dist(A,(*p2));Ans+=Dist(A,(*p3));
		S.erase(p);S.insert(A);
	}
	else{
		p2=p;p--;
		if (Cross(A-(*p),(*p2)-(*p))>=0) return;
		Ans-=Dist(*p,*p2);
		Ans+=Dist(*p,A)+Dist(*p2,A);
		S.insert(A);
	}
	do{
		p=S.find(A);
		if ((p==S.begin())||(p==++S.begin())) break;
		p2=p;p2--;p3=p2;p3--;
		if (Cross(A-(*p3),(*p2)-(*p3))>=0) break;
		Ans-=Dist(*p,*p2);Ans-=Dist(*p2,*p3);
		Ans+=Dist(*p3,*p);S.erase(p2);
	}
	while (1);
	do{
		p=S.find(A);
		if ((p==S.end())||(p==--S.end())||(p==--(--S.end()))) break;
		p2=p;p2++;p3=p2;p3++;
		if (Cross(A-(*p3),A-(*p2))>=0) break;
		Ans-=Dist(*p,*p2);Ans-=Dist(*p2,*p3);
		Ans+=Dist(*p,*p3);S.erase(p2);
	}
	while (1);
	return;
}

Point operator + (Point A,Point B){
	return ((Point){A.x+B.x,A.y+B.y});
}

Point operator - (Point A,Point B){
	return ((Point){A.x-B.x,A.y-B.y});
}

bool operator < (Point A,Point B){
	return A.x<B.x;
}

int Cross(Point A,Point B){
	return A.x*B.y-A.y*B.x;
}

ld Dist(Point A,Point B){
	return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y));
}
