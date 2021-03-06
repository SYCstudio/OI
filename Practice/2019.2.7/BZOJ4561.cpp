#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<set>
#include<cmath>
#include<iostream>
using namespace std;

typedef long long ll;
#define sqr(x) ((double)(x))*((double)(x))
class Data
{
public:
	int x,id,opt;
};
class SetData
{
public:
	int id,opt;
};
class Circle
{
public:
	int x,y,r;
};

const int maxN=202000*2;
const double eps=1e-10;

int n;
Data D[maxN];
Circle C[maxN];
set<SetData> S;
int nowx,Mark[maxN];

bool dcmp(Data A,Data B);
bool operator < (SetData A,SetData B);

int main()
{
	scanf("%d",&n);
	for (int i=1; i<=n; i++) {
		int x,y,r;
		scanf("%d%d%d",&x,&y,&r);
		C[i]=((Circle) {
			x,y,r
		});
		D[i]=((Data) {
			x-r,i,1
		});
		D[i+n]=((Data) {
			x+r,i,-1
		});
	}
	sort(&D[1],&D[n+n+1],dcmp);
	//for (int i=1;i<=n+n;i++) cout<<D[i].id<<" "<<D[i].opt<<" "<<D[i].x<<endl;
	ll Ans=0;
	for (int i=1; i<=n+n; i++) {
		nowx=D[i].x;
		if (D[i].opt==1) {
			set<SetData>::iterator p=S.lower_bound((SetData) {
				D[i].id,1
			});
			if (p==S.end()) Mark[D[i].id]=1;
			else if ((*p).opt==1) Mark[D[i].id]=-Mark[(*p).id];
			else Mark[D[i].id]=Mark[(*p).id];
			Ans=Ans+Mark[D[i].id]*sqr((ll)C[D[i].id].r);
			S.insert((SetData) {
				D[i].id,1
			});
			S.insert((SetData) {
				D[i].id,-1
			});
		} else {
			S.erase((SetData) {
				D[i].id,1
			});
			S.erase((SetData) {
				D[i].id,-1
			});
		}
	}
	printf("%lld\n",Ans);
	return 0;
}
bool dcmp(Data A,Data B)
{
	if (A.x!=B.x) return A.x<B.x;
	return A.opt>B.opt;
}
bool operator < (SetData A,SetData B)
{
	//cout<<"Compare:"<<A.id<<"["<<A.opt<<"] "<<B.id<<"["<<B.opt<<"]"<<endl;
	double da=C[A.id].y+A.opt*sqrt(sqr(C[A.id].r)-sqr(C[A.id].x-nowx));
	double db=C[B.id].y+B.opt*sqrt(sqr(C[B.id].r)-sqr(C[B.id].x-nowx));
	//cout<<nowx<<" "<<da<<" "<<db<<endl;
	if (fabs(da-db)<eps) return A.opt<B.opt;
	return da<db;
}