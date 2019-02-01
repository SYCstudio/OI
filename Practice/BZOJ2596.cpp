#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>
#include<queue>
#include<iostream>
using namespace std;

#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define sqr(x) ((x)*(x))
#define mp make_pair
#define pb push_back
#define ft first
#define sd second

const int maxN=1010;
const int maxNode=maxN*maxN;
const int maxM=maxNode*8;
const ld eps=1e-6;
const ld INF=1e18;

class Point{
public:
    ld x,y;
    ld len(){
	return sqrt(sqr(x)+sqr(y));
    }
};

int n,m;ld va,vb,nodecnt=0;
int edgecnt=0,Head[maxNode],Next[maxM],V[maxM];
Point P[maxN];
vector<pair<Point,int> > St[maxN];
ld Dist[maxNode],W[maxM];
priority_queue<pair<ld,int> > H;
bool vis[maxNode];

ld crs(Point A,Point B);
ld dst(Point A,Point B);
Point operator + (Point A,Point B);
Point operator - (Point A,Point B);
bool operator < (Point A,Point B);
ostream & operator << (ostream & os,Point A);
void Calc(int p,int q1,int q2);
void Add_Edge(int u,int v,ld w);

int main(){
    freopen("in","r",stdin);
    scanf("%d",&n);scanf("%LF%LF",&va,&vb);
    P[0].x=P[0].y=0;
    for (int i=1;i<=n;i++) scanf("%LF%LF",&P[i].x,&P[i].y);
    for (int i=0;i<n;i++) St[i].push_back(mp(P[i],i)),St[i].push_back(mp(P[i+1],i+1));
    nodecnt=n;mem(Head,-1);
    for (int i=0;i<=n;i++)
	for (int j=0;j<n;j++)
	    if (i!=j&&i!=j+1){
		Calc(i,j,j+1);
		Calc(i,j+1,j);
	    }
    cout<<"nodecnt:"<<nodecnt<<endl;

    for (int i=0;i<n;i++){
	sort(St[i].begin(),St[i].end());
	for (int j=1,sz=St[i].size();j<sz;j++)
	    Add_Edge(St[i][j-1].sd,St[i][j].sd,(St[i][j].ft-St[i][j-1].ft).len()/va);
    }

    
    for (int i=0;i<n;i++){
	cout<<i<<":";
	for (int j=0,sz=St[i].size();j<sz;j++)
	    cout<<St[i][j].ft<<" ";
	cout<<endl;
    }
    //*/

    for (int i=0;i<=nodecnt;i++) Dist[i]=INF;
    Dist[0]=0;H.push(mp(0,0));
    while (!H.empty()){
	int u=H.top().second;H.pop();
	if (vis[u]) continue;vis[u]=1;
	//cout<<u<<" "<<Dist[u]<<endl;
	for (int i=Head[u];i!=-1;i=Next[i]){
	    if (Dist[V[i]]>Dist[u]+W[i]){
		//cout<<u<<" -> "<<V[i]<<" "<<W[i]<<endl;
		Dist[V[i]]=Dist[u]+W[i];
		H.push(mp(-Dist[V[i]],V[i]));
	    }
	}
    }
    printf("%.6LF\n",Dist[n]);return 0;
}
ld crs(Point A,Point B){
    return A.x*B.y-A.y*B.x;
}
ld dst(Point A,Point B){
    return sqrt(sqr(A.x-B.x)+sqr(A.y-B.y));
}
Point operator + (Point A,Point B){
    return ((Point){A.x+B.x,A.y+B.y});
}
Point operator - (Point A,Point B){
    return ((Point){A.x-B.x,A.y-B.y});
}
bool operator < (Point A,Point B){
    if (fabs(A.x-B.x)>eps) return A.x<B.x;
    else return A.y<B.y;
}
ostream & operator << (ostream & os,Point A){
    os<<"("<<A.x<<","<<A.y<<")";
    return os;
}
void Calc(int p,int q1,int q2){
    //cout<<"Calc:"<<p<<" "<<q1<<" "<<q2<<endl;
    ld dis=(P[q1]-P[q2]).len();
    ld h=fabs(crs(P[p]-P[q1],P[p]-P[q2]))/dis;
    if (sqr((P[p]-P[q1]).len())<h*h) return;
    ld L=sqrt(sqr((P[p]-P[q1]).len())-h*h);
    //cout<<dis<<" "<<h<<" "<<L<<endl;
    ld l=0,r=L;
    while (l+eps<r){
	ld ql=l+(r-l)/3,qr=r-(r-l)/3;
	ld lk=ql/va+sqrt(sqr(L-ql)+h*h)/vb,rk=qr/va+sqrt(sqr(L-qr)+h*h)/vb;
	if (lk<rk) r=qr;
	else l=ql;
    }
    //cout<<"after dv:"<<l<<endl;
    if (fabs(l)<eps){
	Add_Edge(p,q1,sqrt(h*h+L*L)/vb);
	return;
    }
    //cout<<(P[q2].x-P[q1].x)/dis*l<<" "<<(P[q2].y-P[q1].y)/dis*l<<endl;
    ld px=P[q1].x+(P[q2].x-P[q1].x)/dis*l,py=P[q1].y+(P[q2].y-P[q1].y)/dis*l;
    cout<<"Calc:"<<p<<" "<<q1<<" "<<q2<<endl;
    cout<<dis<<" "<<h<<" "<<L<<endl;
    cout<<P[q2].x-P[q1].x<<" "<<P[q2].y-P[q1].y<<endl;
    cout<<px<<" "<<py<<endl<<endl;
    St[min(q1,q2)].push_back(make_pair((Point){px,py},++nodecnt));
    //cout<<"w:"<<sqrt(sqr(L-l)+h*h)/vb<<" "<<vb<<endl;
    Add_Edge(p,nodecnt,sqrt(sqr(L-l)+h*h)/vb);
    return;
}
void Add_Edge(int u,int v,ld w){
    //cout<<"Add Edge:"<<u<<" "<<v<<" "<<w<<endl;
    Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;W[edgecnt]=w;
    Next[++edgecnt]=Head[v];Head[v]=edgecnt;V[edgecnt]=u;W[edgecnt]=w;
    return;
}
