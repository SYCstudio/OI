#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

const int maxN=101000;
const int Alpha=26;
const int maxB=20;

class SAM{
    public:
    int son[Alpha],len,fail;
};

int n,m,Q,K,lstp=1,scnt=1,Enp[maxN<<1],Fa[maxB][maxN];
char In[maxN];
SAM S[maxN<<1];
vector<int> Ft[maxN<<1];

void Extend(int c);
void dfs_sam(int u);
namespace QMIN{
    int Ml[maxN],Mr[maxN];
    int main();
}
namespace KMIN{
    int main();
}

int main(){
    scanf("%d%d%d%d",&n,&m,&Q,&K);
    scanf("%s",&In);for (int i=1;i<=n;i++) Extend(In[i]-'a');
    for (int i=2;i<=scnt;i++) Ft[S[i].fail].push_back(i),Fa[0][i]=S[i].fail;
    dfs_sam(1);for (int i=1;i<maxB;i++) for (int j=1;j<=scnt;j++) Fa[i][j]=Fa[i-1][Fa[i-1][j]];
    if (Q<=K) QMIN::main();
    else KMIN::main();
}
void Extend(int c){
    int np=++scnt,p=lstp;lstp=np;S[np].len=S[p].len+1;Enp[np]=1;
    while (p&&!S[p].son[c]) S[p].son[c]=np,p=S[p].fail;
    if (!p) S[np].fail=1;
    else{
        int q=S[p].son[c];
        if (S[q].len==S[p].len+1) S[np].fail=q;
        else{
            int nq=++scnt;S[nq]=S[q];S[nq].len=S[p].len+1;
            S[q].fail=S[np].fail=nq;
            while (p&&S[p].son[c]==q) S[p].son[c]=nq,p=S[p].fail;
        }
    }
    return;
}
void dfs_sam(int u){
    for (int i=0,sz=Ft[u].size();i<sz;i++) dfs_sam(Ft[u][i]),Enp[u]+=Enp[Ft[u][i]];
    return;
}
namespace QMIN{
    int main(){
        for (int i=1;i<=m;i++) scanf("%d%d",&Ml[i],&Mr[i]);
    }
}