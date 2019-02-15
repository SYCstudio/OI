#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#include<iostream>
using namespace std;

const int maxN=1010000;

int n,m,Q;
queue<int> Qu;
int Input[maxN],lft[maxN],rht[maxN],Key[maxN],idcnt=0,Id[maxN],D[maxN],Pos[maxN];
vector<int> T[maxN];

int main(){
    //freopen("game10.in","r",stdin);freopen("out","w",stdout);
    scanf("%d%d%d",&n,&m,&Q);
    for (int i=1;i<=m;i++){
        int x,y;scanf("%d%d",&x,&y);Key[x]=y;
    }
    for (int i=1,j;i<=n;i=j+1){
        j=i;while (j<n&&!Key[j]) ++j;++idcnt;
        for (int k=i;k<=j;k++) Id[k]=idcnt;
    }
    for (int i=1;i<=n;i++) Pos[Id[i]]=Id[Key[i]];
    for (int i=1;i<n;i++)
        if (Key[i]){
            if (Key[i]<=i) T[Id[i+1]].push_back(Id[i]),++D[Id[i]];
            else T[Id[i]].push_back(Id[i+1]),++D[Id[i+1]];
        }
    for (int i=1;i<=idcnt;i++) if (D[i]==0) Qu.push(i);
    while (!Qu.empty()){
        int u=Qu.front();Qu.pop();
        //cerr<<"running on :"<<u<<endl;
        lft[u]=rht[u]=u;
        while ((Pos[lft[u]-1]>=lft[u]&&Pos[lft[u]-1]<=rht[u])||(Pos[rht[u]]>=lft[u]&&Pos[rht[u]]<=rht[u])||lft[u]!=lft[lft[u]]||rht[u]!=rht[rht[u]]){
            //cerr<<"("<<lft[u]<<","<<rht[u]<<")"<<" "<<Pos[lft[u]-1]<<" "<<Pos[rht[u]]<<" "<<lft[lft[u]]<<" "<<rht[rht[u]]<<endl;
            if (lft[u]!=lft[lft[u]]) lft[u]=lft[lft[u]];
            else if (rht[u]!=rht[rht[u]]) rht[u]=rht[rht[u]];
            else if (Pos[lft[u]-1]>=lft[u]&&Pos[lft[u]-1]<=rht[u]) --lft[u];
            else if (Pos[rht[u]]>=lft[u]&&Pos[rht[u]]<=rht[u]) ++rht[u];
        }
        for (int i=0,sz=T[u].size();i<sz;i++) if ((--D[T[u][i]])==0) Qu.push(T[u][i]);
    }
    //for (int i=1;i<=n;i++) cout<<Id[i]<<" ";cout<<endl;
    //for (int i=1;i<=idcnt;i++) cout<<lft[i]<<" "<<rht[i]<<endl;
    while (Q--){
        int s,t;scanf("%d%d",&s,&t);s=Id[s];t=Id[t];
        if (lft[s]<=t&&rht[s]>=t) puts("YES");
        else puts("NO");
    }
    return 0;
}