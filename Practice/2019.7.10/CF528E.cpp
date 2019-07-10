#include<bits/stdc++.h>
using namespace std;

#define mp make_pair
#define ft first
#define sd second

const double INF=1e18;
class Line{
public:
	double a,b,c,k;
	void Init(double _a,double _b,double _c){
		a=_a;b=_b;c=_c;
		if (b==0) k=INF;
		else k=-a/b;
	}
};

const int maxN=3010;
const double Pi=acos(-1);

int n;
Line L[maxN];

bool lcmp(Line A,Line B);
pair<double,double> Cross(Line A,Line B);
int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++){
		int a,b,c;scanf("%d%d%d",&a,&b,&c);
		L[i].Init(a,b,c);
	}
	sort(&L[1],&L[n+1],lcmp);

	//for (int i=1;i<=n;i++) cout<<L[i].a<<" "<<L[i].b<<" "<<L[i].c<<endl;
	double sumarea=0;
	for (int i=1;i<=n;i++){
		double sx=0,sy=0;
		for (int j=i+1;j<=n;j++){
			pair<double,double> r=Cross(L[i],L[j]);
			//cout<<i<<" "<<j<<":"<<r.ft<<" "<<r.sd<<endl;
			sumarea+=r.ft*sy-r.sd*sx;
			sx+=r.ft;sy+=r.sd;
		}
		for (int j=1;j<i;j++){
			pair<double,double> r=Cross(L[i],L[j]);
			//cout<<i<<" "<<j<<" "<<r.ft<<" "<<r.sd<<endl;
			sumarea+=r.ft*sy-r.sd*sx;
			sx+=r.ft;sy+=r.sd;
		}
	}
	//cout<<sumarea<<endl;

	sumarea=fabs(sumarea);sumarea=sumarea/n/(n-1)/(n-2)*3.0;
	printf("%.9lf\n",sumarea);
	return 0;
}
bool lcmp(Line A,Line B){
	return A.k<B.k;
}
pair<double,double> Cross(Line L1,Line L2){
	double x=(L1.c*L2.b-L2.c*L1.b)/(L1.a*L2.b-L2.a*L1.b);
	double y=(L1.c*L2.a-L2.c*L1.a)/(L1.a*L2.b-L2.a*L1.b);
	//cout<<L1.a*x+L1.b*y<<" "<<L1.c<<"|"<<L2.a*x+L2.b*y<<" "<<L2.c<<endl;
	return mp(x,y);
}
