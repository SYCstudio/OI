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

const int maxN=201000;
const int inf=2147483647;

class Point
{
public:
	ld x,y;
	Point(){}
	Point(ld _x,ld _y){
		x=_x,y=_y;return;
	}
};

class Line
{
public:
	Point p,d;ld agl;int id;
	Line(){}
	Line(Point A,Point B,int idid){
		p=A;d=B;id=idid;agl=atan2(d.y,d.x);return;
	}
};

int n,lcnt;
Line L[maxN],A[maxN],Q1[maxN];
Point Q2[maxN];

Point operator + (Point A,Point B);
Point operator - (Point A,Point B);
Point operator * (Point A,ld t);
bool operator < (Line A,Line B);
ld Cross(Point A,Point B);
Point GetP(Line A,Line B);
bool Isleft(Line A,Point B);
bool check(int limit);

int main(){
	L[++lcnt]=(Line){(Point){0,-1e-15},(Point){1,0},0};L[++lcnt]=(Line){(Point){-1e-15,0},(Point){0,1},0};
	L[++lcnt]=(Line){(Point){1e-15,1e15},(Point){-1,0},0};L[++lcnt]=(Line){(Point){-1e15,1e15},(Point){0,-1},0};
	
	scanf("%d",&n);
	for (int i=1;i<=n;i++){
		ld x,y1,y2;scanf("%LF%LF%LF",&x,&y1,&y2);y1-=1e-15;y2+=1e-15;
		L[++lcnt]=(Line){(Point){0,y1/x},(Point){1.0/x,-1},i};
		L[++lcnt]=(Line){(Point){0,y2/x},(Point){-1.0/x,1},i};
	}
	sort(&L[1],&L[lcnt+1]);

	int Ans=0,L=1,R=n;
	do{
		int mid=(L+R)>>1;
		if (check(mid)) Ans=mid,L=mid+1;
		else R=mid-1;
	}
	while (L<=R);
	printf("%d\n",Ans);return 0;
}

Point operator + (Point A,Point B){
	return ((Point){A.x+B.x,A.y+B.y});
}

Point operator - (Point A,Point B){
	return ((Point){A.x-B.x,A.y-B.y});
}

Point operator * (Point A,ld t){
	return ((Point){A.x*t,A.y*t});
}

bool operator < (Line A,Line B){
	return A.agl<B.agl;
}

ld Cross(Point A,Point B){
	return A.x*B.y-A.y*B.x;
}

Point GetP(Line A,Line B){
	Point dx=A.p-B.p;
	ld t=Cross(B.d,dx)/Cross(A.d,B.d);
	return A.p+A.d*t;
}

bool Isleft(Line A,Point B){
	return Cross(A.d,B-A.p)>0;
}

bool check(int limit){
	int scnt=0;
	for (int i=1;i<=lcnt;i++) if (L[i].id<=limit) A[++scnt]=L[i];
	int L=1,R=1;Q1[1]=A[1];
	for (int i=2;i<=scnt;i++){
		while ((L<R)&&(!Isleft(A[i],Q2[R-1]))) R--;
		while ((L<R)&&(!Isleft(A[i],Q2[L]))) L++;
		Q1[++R]=A[i];
		if (fabs(Cross(Q1[R].d,Q1[R-1].d))<1e-15){
			--R;
			if (Isleft(Q1[R],A[i].p)) Q1[R]=A[i];
		}
		if (L<R) Q2[R-1]=GetP(Q1[R-1],Q1[R]);
	}
	while ((L<R)&&(!Isleft(Q1[L],Q2[R-1]))) R--;
	return R-L>1;
}
