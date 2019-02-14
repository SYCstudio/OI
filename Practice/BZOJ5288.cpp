#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

const int maxN=1010000;

int n,m,Q;
int Input[maxN],lft[maxN],rht[maxN],Key[maxN],idcnt=0,nId[maxN],D[maxN];
vector<int> T[maxN],Id[maxN];

int main(){
    scanf("%d%d%d",&n,&m,&Q);
    for (int i=1;i<=m;i++){
        int x,y;scanf("%d%d",&x,&y);Key[x]=y;
    }
    for (int i=1;i<n;i++)
        if (Key[i]){
            if (Key[i]<=i) T[i+1].push_back(i),++D[i];
            else T[i].push_back(i+1),++D[i+1];
        }
    for (int i=1,j;i<=n;i=j+1){
        j=i;while (j<n&&!Key[j]) ++j;++idcnt;
        for (int k=i;k<=j;k++) Id[idcnt].push_back(k),nId[k]=idcnt;
    }
}