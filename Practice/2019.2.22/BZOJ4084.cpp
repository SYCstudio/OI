#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

typedef unsigned long long ull;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
const int maxN=101000;
const int maxL=4040000;
const ull base=998244353;
const int Mod=100003;

class HashTable{
    int edgecnt,Head[maxN],Next[maxL],tim,Tim[maxN];
    pair<ull,int> W[maxL];
    public:
    void clear(){
        edgecnt=0;++tim;return;
    }
    void Insert(ull key){
        int p=key%Mod;if (Tim[p]!=tim) Head[p]=-1,Tim[p]=tim;
        for (int i=Head[p];i!=-1;i=Next[i]) if (W[i].first==key) {++W[i].second;return;}
        Next[++edgecnt]=Head[p];Head[p]=edgecnt;W[edgecnt]=make_pair(key,1);return;
    }
    int Query(ull key){
        int p=key%Mod;if (Tim[p]!=tim) Head[p]=-1,Tim[p]=tim;
        for (int i=Head[p];i!=-1;i=Next[i]) if (W[i].first==key) return W[i].second;
        return 0;
    }
};

int n,m,LS,LT;
vector<int> S[maxN];
char In[maxL];
HashTable H1,H2;
ull H[maxL],Pw[maxL];

ull Get(int l,int r);
int main(){
    Pw[0]=1;
    scanf("%d%d%d%d",&n,&m,&LS,&LT);
    for (int i=1;i<=LS;i++) Pw[i]=Pw[i-1]*base;
    if ((LS+LT)&1){
        printf("0\n");return 0;
    }
    for (int i=1;i<=n;i++){
        scanf("%s",In+1);S[i].resize(LS+1);
        for (int j=1;j<=LS;j++) S[i][j]=In[j]-'a'+1;
    }
    H1.clear();
    for (int i=1;i<=m;i++){
        scanf("%s",In+1);ull h=0;
        for (int j=1;j<=LT;j++) h=h*base+In[j]-'a'+1;
        //cout<<i<<" "<<h<<endl;
        H1.Insert(h);
    }
    int Ans=0,len=(LS+LT)/2,rs=LS-len;
    //cout<<len<<" "<<rs<<endl;
    for (int i=1;i<=n;i++){
        ull suf=0;H2.clear();
        for (int j=len+1;j<=LS;j++) suf=suf*base+S[i][j];
        //cout<<i<<":"<<suf<<endl;
        H[0]=0;
        for (int j=1;j<=len;j++) H[j]=H[j-1]*base+S[i][j];
        for (int j=len+1;j<=len+len;j++) H[j]=H[j-1]*base+S[i][j-len];
        for (int j=1;j<=len;j++)
            if (Get(j,j+rs-1)==suf){
                ull h=Get(j+rs,j+len-1);
                if (H2.Query(h)==0){
                    Ans=Ans+H1.Query(h);H2.Insert(h);
                }
            }
    }
    printf("%d\n",Ans);return 0;
}
ull Get(int l,int r){
    //cout<<"["<<l<<","<<r<<"] "<<H[r]-H[l-1]*Pw[r-l+1]<<endl;
    return H[r]-H[l-1]*Pw[r-l+1];
}