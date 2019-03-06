#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<iostream>
#include<vector>
using namespace std;

#define NAME "C"
#define sqr(x) ((x)*(x))
class Point{
public:
    double x,y,agl;
    Point(){}
    Point(double _x,double _y){
	x=_x;y=_y;return;
    }
    int len(){
	return sqrt(sqr(x)+sqr(y));
    }
    void I(){
	agl=atan2(y,x);return;
    }
};

const int maxN=110;
const int inf=2000000000;
const int meminf=1061109567;

int n,m;
Point W[maxN],B[maxN],Up[maxN],Down[maxN];

bool cmp(Point A,Point B);
Point operator + (Point A,Point B);
Point operator - (Point A,Point B);
ostream & operator << (ostream &os,Point A);
double Cross(Point A,Point B);
namespace brute{
    Point Up[maxN],Down[maxN];
    int main();
}
namespace dp{
    Point Up[maxN],Down[maxN],Nb[maxN];
    int Mp[maxN][maxN];
    int main();
    void Convex(Point *P,int n,Point *U,Point *D,int &t1,int &t2);
    bool cmpa(Point A,Point B);
    bool check(Point A,Point B,Point *P,int t);
    bool CrossSection(Point A,Point B,Point C,Point D);
}
int main(){
    scanf("%d%d",&n,&m);
    for (int i=0;i<n;i++) scanf("%lf%lf",&W[i].x,&W[i].y);
    for (int i=0;i<m;i++) scanf("%lf%lf",&B[i].x,&B[i].y);
    sort(&W[0],&W[n],cmp);sort(&B[0],&B[m],cmp);
    if (m<=15) brute::main();
    else dp::main();
    return 0;
}
bool cmp(Point A,Point B){
    if (A.x!=B.x) return A.x<B.x;
    return A.y<B.y;
}
Point operator + (Point A,Point B){
    return ((Point){A.x+B.x,A.y+B.y});
}
Point operator - (Point A,Point B){
    return ((Point){A.x-B.x,A.y-B.y});
}
ostream & operator << (ostream & os,Point A){
    os<<"("<<A.x<<","<<A.y<<")";return os;
}
double Cross(Point A,Point B){
    return A.x*B.y-A.y*B.x;
}
namespace brute{
    int main(){
	int Ans=inf;
	for (int S=0,N=1<<n;S<N;S++){
	    int t1=0,t2=0,sum=0;
	    for (int i=0;i<n;i++)
		if ((S>>i)&1){
		    sum+=20;
		    if (t1==0) Up[++t1]=W[i];
		    else{
			while (t1>=2&&Cross(Up[t1]-Up[t1-1],W[i]-Up[t1-1])>0) --t1;
			Up[++t1]=W[i];
		    }
		    if (t2==0) Down[++t2]=W[i];
		    else{
			while (t2>=2&&Cross(W[i]-Down[t2-1],Down[t2]-Down[t2-1])>0) --t2;
			Down[++t2]=W[i];
		    }
		}
	    int p1=0,p2=0;
	    for (int i=0;i<m;i++){
		while (p1+1<=t1&&Up[p1+1].x<B[i].x) ++p1;
		while (p2+1<=t2&&Down[p2+1].x<B[i].x) ++p2;
		if (p1==t1||p2==t2){
		    sum+=111;continue;
		}
		if (p1==0||p2==0||Cross(B[i]-Down[p2],Down[p2+1]-Down[p2])>0||Cross(Up[p1+1]-Up[p1],B[i]-Up[p1])>0) sum+=111;
	    }
	    Ans=min(Ans,sum);
	}
	printf("%d\n",Ans);return 0;
    }
}
namespace dp{
    int main(){
	int t1=0,t2=0;
	Convex(W,n,Up,Down,t1,t2);
	int Ans=0,p1=0,p2=0,bcnt=0;
	for (int i=0;i<m;i++){
	    while (p1+1<=t1&&Up[p1+1].x<B[i].x) ++p1;
	    while (p2+1<=t2&&Down[p2+1].x<B[i].x) ++p2;
	    if (p1==t1||p2==t2||p1==0||p2==0||Cross(B[i]-Down[p2],Down[p2+1]-Down[p2])>0||Cross(Up[p1+1]-Up[p1],B[i]-Up[p1])>0) Ans+=111;
	    else Nb[bcnt++]=B[i];
	}

	t1=t2=0;
	Convex(Nb,bcnt,Up,Down,t1,t2);
    //for (int i=1;i<=t1;i++) cout<<Up[i]<<" ";cout<<endl;
    //for (int i=1;i<=t2;i++) cout<<Down[i]<<" ";cout<<endl;
	Point MID=Up[1]+Up[t1];MID.x/=2;MID.y/=2;
	//cout<<"MID:"<<MID<<endl;
	int wcnt=0;p1=p2=0;
	for (int i=0;i<n;i++){
	    while (p1+1<=t1&&Up[p1+1].x<W[i].x) ++p1;
	    while (p2+1<=t2&&Down[p2+1].x<W[i].x) ++p2;
	    if (p1==t1||p2==t2||p1==0||p2==0||Cross(W[i]-Down[p2],Down[p2+1]-Down[p2])>0||Cross(Up[p1+1]-Up[p1],W[i]-Up[p1])>0){
		W[wcnt++]=W[i]-MID;continue;
	    }
	}
	for (int i=wcnt;i>=1;i--) W[i]=W[i-1];
	for (int i=1;i<=wcnt;i++) W[i].I();
	sort(&W[1],&W[wcnt+1],cmpa);
	//for (int i=1;i<=wcnt;i++) cout<<W[i]<<" ";cout<<endl;
	memset(Mp,63,sizeof(Mp));
	for (int i=1;i<=wcnt;i++)
	    for (int j=i+1;j<=wcnt;j++)
		if (check(W[i]+MID,W[j]+MID,Up,t1)&&check(W[i]+MID,W[j]+MID,Down,t2)){
		    if (Cross(W[i],W[j])>0) Mp[i][j]=1;
		    else Mp[j][i]=1;
		}
	/*
	for (int i=1;i<=wcnt;i++){
	    for (int j=1;j<=wcnt;j++) cout<<Mp[i][j]<<" ";
	    cout<<endl;
	}
	//*/
	int mnring=inf;
	for (int k=1;k<=wcnt;k++){
	    //for (int i=1;i<=wcnt;i++) for (int j=1;j<=wcnt;j++) if (i!=k&&j!=k&&Mp[i][j]!=meminf&&Mp[j][k]!=meminf&&Mp[k][i]!=meminf) mnring=min(mnring,Mp[i][j]+Mp[j][k]+Mp[k][i]);
	    for (int i=1;i<=wcnt;i++) for (int j=1;j<=wcnt;j++) Mp[i][j]=min(Mp[i][j],Mp[i][k]+Mp[k][j]);
	}
    for (int i=1;i<=wcnt;i++) mnring=min(mnring,Mp[i][i]);
    /*
    for (int i=1;i<=wcnt;i++){
        for (int j=1;j<=wcnt;j++) cout<<Mp[i][j]<<" ";
        cout<<endl;
    }
    //*/
	//cout<<mnring<<endl;
	if (mnring<meminf) mnring*=20;
	printf("%d\n",min(mnring+Ans,m*111));return 0;
    }
    void Convex(Point *P,int n,Point *U,Point *D,int &t1,int &t2){
	for (int i=0;i<n;i++){
	    if (t1==0) U[++t1]=P[i];
	    else{
		while (t1>=2&&Cross(U[t1]-U[t1-1],P[i]-U[t1-1])>0) --t1;
		U[++t1]=P[i];
	    }
	    if (t2==0) D[++t2]=P[i];
	    else{
		while (t2>=2&&Cross(P[i]-D[t2-1],D[t2]-D[t2-1])>0) --t2;
		D[++t2]=P[i];
	    }
	}
	return;
    }
    bool cmpa(Point A,Point B){
	return A.agl<B.agl;
    }
    bool check(Point A,Point B,Point *P,int t){
	for (int i=1;i<t;i++) if (CrossSection(A,B,P[i],P[i+1])) return 0;
	return 1;
    }
    bool CrossSection(Point A,Point B,Point C,Point D){
	return ((Cross(A-C,D-C)>0)^(Cross(B-C,D-C)>0))
	    &&((Cross(C-A,B-A)>0)^(Cross(D-A,B-A)>0));
    }
}
