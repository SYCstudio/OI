#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<map>
#include<vector>
using namespace std;

#define pw(x) (1<<(x))
class Edge{
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
void Minus(int &x,int y);

int main(){
    scanf("%d%d",&n,&m);
    for (int i=1;i<=m;i++){
        int opt;scanf("%d",&opt);
        if (opt==1){
            int u,v;scanf("%d%d",&u,&v);--u;--v;Mp[u][v]=1;
        }
        else{
            int a,b,c,d;scanf("%d%d%d%d",&a,&b,&c,&d);--a;--b;--c;--d;
            if (a>c) swap(a,c),swap(b,d);
            To[a].push_back((Edge){a,b,c,d,opt});
        }
    }
    printf("%d\n",dfs(pw(n)-1,pw(n)-1));
    return 0;
}
int dfs(int S,int T){
    if (Rc.count((S<<15)|T)) return Rc[(S<<15)|T];
    int left=S&(-S),ret=0;
    for (int i=0;i<n;i++) if (Mp[left][i]&&(!(T&pw(i)))) Plus(ret,1ll*(dfs(S|pw(left),T|pw(i))+1)*inv2%Mod);
    for (int i=0,sz=To[left].size();i<sz;i++)
        if (!(S&pw(To[left][i].c))&&!(T&pw(To[left][i].b))&&!(T&pw(To[left][i].d)))
            To[left][i].opt-1?Plus(ret,1ll*(dfs(S|pw(left)|pw(To[left][i].c),T|pw(To[left][i].b)|pw(To[left][i].d))+2)*inv4%Mod):
                              Minus(ret,1ll*(dfs(S|pw(left)|pw(To[left][i].c),T|pw(To[left][i].b)|pw(To[left][i].d))+2)*inv4%Mod);
    return Rc[(S<<15)|T]=ret;
}
void Plus(int &x,int y){
    x+=y;if (x>=Mod) x-=Mod;return;
}
void Minus(int &x,int y){
    x-=y;if (x<0) x+=Mod;return;
}