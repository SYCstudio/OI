#include<bits/stdc++.h>
using namespace std;

#define double long double
const int maxN=101000;
const double Pi=acos(-1);
const double eps=1e-10;

class Point{
public:
	double x,y;
	double len(){
		return sqrt(x*x+y*y);
	}
	double angle(){
		return atan2(y,x);
	}
};
class Line{
public:
	Point p,f;
};

int n;
Point A[maxN],B[maxN],C[maxN];
int Id[maxN],mxcnt;
double Angle[maxN];
multiset<double> S;

Point operator + (Point A,Point B);
Point operator - (Point A,Point B);
Point operator * (Point A,double B);
ostream & operator << (ostream &os,Point A);
double Cross(Point A,Point B);
Point Cross(Line A,Line B);
bool idcmp(int x,int y);
void Insert(int id);
void Delete(int id);
bool check(double A,double B,bool f);
int main(){
	scanf("%d",&n);
	for (int i=1;i<=n+1;i++){
		Point a,b;scanf("%LF%LF%LF%LF",&a.x,&a.y,&b.x,&b.y);
		A[i]=a;B[i]=b-a;
	}
	for (int i=1;i<=n;i++) C[i]=Cross((Line){A[i],B[i]},(Line){A[n+1],B[n+1]}),Id[i]=i;

	sort(&Id[1],&Id[n+1],idcmp);

	for (int i=1;i<=n;i++){
		if (Cross(B[i],B[n+1])>=0) Angle[i]=B[i].angle();
		else Angle[i]=B[i].angle()+Pi;
		while (Angle[i]<0) Angle[i]+=Pi+Pi;
		while (Angle[i]>=Pi+Pi) Angle[i]-=Pi+Pi;
		Insert(i);
	}

	printf("%d",(mxcnt==0));
	for (int i=1;i<=n;i++){
		Delete(Id[i]);Angle[Id[i]]=Angle[Id[i]]+Pi;
		while (Angle[Id[i]]<0) Angle[Id[i]]+=Pi+Pi;
		while (Angle[Id[i]]>=Pi+Pi) Angle[Id[i]]-=Pi+Pi;
		Insert(Id[i]);
		printf("%d",(mxcnt==0));
	}
	puts("");
	return 0;
}
Point operator + (Point A,Point B){
	return ((Point){A.x+B.x,A.y+B.y});
}
Point operator - (Point A,Point B){
	return ((Point){A.x-B.x,A.y-B.y});
}
Point operator * (Point A,double B){
	return ((Point){A.x*B,A.y*B});
}
ostream & operator << (ostream &os,Point A){
	os<<"("<<A.x<<","<<A.y<<")";return os;
}
double Cross(Point A,Point B){
	return A.x*B.y-A.y*B.x;
}
Point Cross(Line A,Line B){
	double rate=Cross(B.f,A.p-B.p)/Cross(A.f,B.f);
	return A.p+A.f*rate;
}
bool idcmp(int x,int y){
	return C[x].x<C[y].x;
}
void Insert(int id){
	S.insert(Angle[id]);
	if (S.size()==1) return;
	if (S.size()==2){
		multiset<double>::iterator i1=S.begin(),i2=--S.end();
		mxcnt+=check(*i1,*i2,0);
		mxcnt+=check(*i2,*i1,1);
		return;
	}
	multiset<double>::iterator it=S.find(Angle[id]),pre,nxt;
	pre=nxt=it;bool f1=0,f2=0;
	if (it==S.begin()) pre=--S.end(),f1=1;else --pre;
	if (it==--S.end()) nxt=S.begin(),f2=1;else ++nxt;
	mxcnt-=check(*pre,*nxt,f1|f2);
	mxcnt+=check(*pre,*it,f1);
	mxcnt+=check(*it,*nxt,f2);
	return;
}
void Delete(int id){
	multiset<double>::iterator it=S.find(Angle[id]),pre,nxt;
	pre=nxt=it;bool f1=0,f2=0;
	if (it==S.begin()) pre=--S.end(),f1=1;else --pre;
	if (it==--S.end()) nxt=S.begin(),f2=1;else ++nxt;
	mxcnt+=check(*pre,*nxt,f1|f2);
	mxcnt-=check(*pre,*it,f1);
	mxcnt-=check(*it,*nxt,f2);
	S.erase(it);
	return;
}
bool check(double l,double r,bool f){
	if (f) r+=Pi+Pi;
	return r-l+eps>=Pi;
}
