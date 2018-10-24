#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cmath>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define sqr(x) ((x)*(x))

const int maxN=610;
const int maxM=maxN*maxN;
const ld eps=1e-10;
const int inf=2147483647;

class Point
{
public:
	ld x,y;
};

class Line
{
public:
	Point p,d;
	int id;ld agl;
	void calcagl(){
		agl=atan2(d.y,d.x);return;
	}
};

int n;
ld W,H;
Point P[maxN],Q1[maxN],start;
Line L[maxN],Q2[maxN];
int edgecnt=0,Head[maxN],Next[maxM],V[maxM],Dph[maxN];
bool vis[maxN];
queue<int> Qu;

bool cmp(Line A,Line B);
ld Cross(Point A,Point B);
Point operator * (Point A,ld B);
Point operator + (Point A,Point B);
Point operator - (Point A,Point B);
Point Py(Line A,Line B);
bool Isleft(Line A,Point B);
void Add_Edge(int u,int v);

int main(){
	//freopen("in","r",stdin);
	int TTT;scanf("%d",&TTT);
	while (TTT--){
		scanf("%d",&n);scanf("%LF%LF%LF%LF",&W,&H,&start.x,&start.y);
		for (int i=1;i<=n;i++) scanf("%LF%LF",&P[i].x,&P[i].y);

		if (n==0){
			printf("0\n");continue;
		}

		edgecnt=0;mem(Head,-1);
		for (int i=1;i<=n;i++){
			int lcnt=0;
			for (int j=1;j<=n;j++)
				if (j!=i){
					Point p1=((Point){(P[i].x+P[j].x)/2.0,(P[i].y+P[j].y)/2.0});
					Point p2=((Point){P[i].y-P[j].y,P[j].x-P[i].x});
					L[++lcnt]=((Line){p1,p2,j});
				}
			L[++lcnt]=((Line){((Point){0,0}),((Point){1,eps}),n+1});
			L[++lcnt]=((Line){((Point){W,0}),((Point){eps,1}),n+1});
			L[++lcnt]=((Line){((Point){W,H}),((Point){-1,eps}),n+1});
			L[++lcnt]=((Line){((Point){0,H}),((Point){eps,-1}),n+1});
			for (int j=1;j<=lcnt;j++) L[j].calcagl();
			sort(&L[1],&L[lcnt+1],cmp);
			int l=1,r=1;Q2[1]=L[1];
			for (int j=2;j<=lcnt;j++){
				while ((l<r)&&(!Isleft(L[j],Q1[r-1]))) --r;
				while ((l<r)&&(!Isleft(L[j],Q1[l]))) ++l;
				Q2[++r]=L[j];
				if (fabs(Cross(Q2[r].d,Q2[r-1].d))<eps){
					--r;
					if (Isleft(Q2[r],L[j].p)) Q2[r]=L[j];
				}
				if (l<r) Q1[r-1]=Py(Q2[r-1],Q2[r]);
			}
			while ((l<r)&&(!Isleft(Q2[l],Q1[r-1]))) --r;
			for (int j=l;j<=r;j++) Add_Edge(i,Q2[j].id);
		}

		int mnid;ld dist=inf;
		for (int i=1;i<=n;i++) if (sqrt(sqr(P[i].x-start.x)+sqr(P[i].y-start.y))<dist) mnid=i,dist=sqrt(sqr(P[i].x-start.x)+sqr(P[i].y-start.y));

		mem(Dph,-1);Dph[mnid]=1;while (!Qu.empty()) Qu.pop();Qu.push(mnid);
		do{
			int u=Qu.front();Qu.pop();
			for (int i=Head[u];i!=-1;i=Next[i])
				if (Dph[V[i]]==-1){
					Dph[V[i]]=Dph[u]+1;
					Qu.push(V[i]);
				}
		}
		while (!Qu.empty());
		printf("%d\n",Dph[n+1]-1);
	}
	return 0;
}

bool cmp(Line A,Line B){
	return A.agl<B.agl;
}

ld Cross(Point A,Point B){
	return A.x*B.y-A.y*B.x;
}

Point operator * (Point A,ld B){
	return ((Point){A.x*B,A.y*B});
}

Point operator + (Point A,Point B){
	return ((Point){A.x+B.x,A.y+B.y});
}

Point operator - (Point A,Point B){
	return ((Point){A.x-B.x,A.y-B.y});
}

Point Py(Line A,Line B){
	Point d=A.p-B.p;
	ld t=Cross(B.d,d)/Cross(A.d,B.d);
	return A.p+A.d*t;
}

bool Isleft(Line A,Point B){
	return Cross(A.d,B-A.p)>0;
}

void Add_Edge(int u,int v){
	//cout<<"Add:"<<u<<" "<<v<<endl;
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}
