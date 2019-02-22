#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
using namespace std;

typedef unsigned long long ull;

const int maxN=110;
const int maxL=4040000;
const ull base=20150822;

int n,m,LS,LT;
vector<int> S[maxN];
char In[maxL];
map<ull,int> Hst;
set<ull> Use;
ull H[maxL],Pw[maxL];

ull Get(int l,int r);
int main(){
    Pw[0]=1;for (int i=1;i<maxN;i++) Pw[i]=Pw[i-1]*base;
    scanf("%d%d%d%d",&n,&m,&LS,&LT);
    if ((LS+LT)&1){
        printf("0\n");return 0;
    }
    for (int i=1;i<=n;i++){
        scanf("%s",In+1);S[i].resize(LS+1);
        for (int j=1;j<=LS;j++) S[i][j]=In[i]-'a'+1;
    }
    for (int i=1;i<=m;i++){
        scanf("%s",In+1);ull h=0;
        for (int i=1;i<=LT;i++) h=h*base+In[i]-'a'+1;
        ++Hst[h];
    }
    int Ans=0,len=(LS+LT)/2,rs=LS-len;
    for (int i=1;i<=n;i++){
        ull suf=0;Use.clear();
        for (int j=len+1;j<=LS;j++) suf=suf*base+S[i][j];
        H[0]=0;
        for (int j=1;j<=len;j++) H[i]=H[i-1]*base+S[i][j];
        for (int j=len+1;j<=len+len;j++) H[i]=H[i-1]*base+S[i][j-len];
        for (int j=1;j<=len;j++)
            if (Get(j,j+rs-1)==suf){
                ull h=Get(j+rs,j+LS);
                if (Use.count(h)==0){
                    Ans=Ans+Hst[h];Use.insert(h);
                }
            }
    }
    printf("%d\n",Ans);return 0;
}
ull Get(int l,int r){
    return H[r]-H[l-1]*Pw[r-l+1];
}