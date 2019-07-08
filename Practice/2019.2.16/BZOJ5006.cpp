#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<map>
#include<vector>
#include<iostream>
using namespace std;

#define pw(x) (1<<(x))
class Edge
{
public:
	int a,b,c,d,opt;
};

const int maxN=15;
const int maxM=maxN*maxN;
const int Mod=1e9+7;
const int inv2=500000004;
const int inv4=250000002;

int n,m,Mp[maxN][maxN];
vector<Edge> To[maxN];
map<int,int> Rc;

int dfs(int S,int T);
void Plus(int &x,int y);

int main()
{
	//freopen("in","r",stdin);freopen("out","w",stdout);
	scanf("%d%d",&n,&m);
	for (int i=1; i<=m; i++) {
		int opt;
		scanf("%d",&opt);
		if (opt==0) {
			int u,v;
			scanf("%d%d",&u,&v);
			--u;
			--v;
			Mp[u][v]=1;
		} else {
			int a,b,c,d;
			scanf("%d%d%d%d",&a,&b,&c,&d);
			--a;
			--b;
			--c;
			--d;
			if (a>c) swap(a,c),swap(b,d);
			Mp[a][b]=Mp[c][d]=1;
			if (a==c||b==d) continue;
			To[a].push_back((Edge) {
				a,b,c,d,opt
			});
		}
	}
	int p2=1;
	for (int i=1; i<=n; i++) p2=2ll*p2%Mod;
	Rc[0]=1;
	printf("%lld\n",1ll*dfs(pw(n)-1,pw(n)-1)*p2%Mod);
	return 0;
}
int dfs(int S,int T)
{
	//cout<<"dfs:"<<S<<" "<<T<<endl;
	if (Rc.count((S<<15)|T)) return Rc[(S<<15)|T];
	int left=0,ret=0;
	while (left<=n-1&&!(S&pw(left))) ++left;
	//cout<<"left:"<<left<<endl;
	for (int i=0; i<n; i++) if (Mp[left][i]&&(T&pw(i))) Plus(ret,1ll*dfs(S^pw(left),T^pw(i))*inv2%Mod);
	for (int i=0,sz=To[left].size(); i<sz; i++)
		if ((S&pw(To[left][i].c))&&(T&pw(To[left][i].b))&&(T&pw(To[left][i].d))) {
			//cout<<"pair:"<<left<<":"<<To[left][i].a<<" "<<To[left][i].b<<" "<<To[left][i].c<<" "<<To[left][i].d<<" "<<To[left][i].opt<<endl;
			(To[left][i].opt==1)?Plus(ret,1ll*dfs(S^pw(left)^pw(To[left][i].c),T^pw(To[left][i].b)^pw(To[left][i].d))*inv4%Mod):
			Plus(ret,1ll*dfs(S^pw(left)^pw(To[left][i].c),T^pw(To[left][i].b)^pw(To[left][i].d))*(Mod-inv4)%Mod);
		}
	//cout<<S<<" "<<T<<":"<<ret<<endl;
	return Rc[(S<<15)|T]=ret;
}
void Plus(int &x,int y)
{
	x+=y;
	if (x>=Mod) x-=Mod;
	return;
}