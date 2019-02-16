#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=5010;
const int inf=2147483647;

int n,m;
int Seq[maxN*maxN],Id[maxN*maxN];
int Up[maxN],Down[maxN];

int main(){
    int x,a,b,c,d,Q,NN;
    scanf("%d%d%d%d%d",&x,&a,&b,&c,&d);
    scanf("%d%d%d",&n,&m,&Q);NN=n*m;
    for (int i=1;i<=NN;i++) Seq[i]=i;
    for (int i=1;i<=NN;i++){
        x=(1ll*a*x%d*x%d+1ll*b*x%d+c)%d;
        swap(Seq[i],Seq[x%i+1]);
    }
    while (Q--){
        int u,v;scanf("%d%d",&u,&v);
        swap(Seq[u],Seq[v]);
    }

    for (int i=1;i<=NN;i++) Id[Seq[i]]=i;
    for (int i=1;i<=m;i++) Up[i]=1,Down[i]=n;

    for (int i=1;i<=NN;i++){
        int x=(Id[i]-1)/m+1,y=(Id[i]-1)%m+1;
        //cout<<i<<":("<<x<<","<<y<<")"<<endl;
        if ((Up[y]<=x)&&(Down[y]>=x)){
            printf("%d ",i);
            for (int j=y-1;(j>=1)&&(Down[j]>x);j--) Down[j]=x;
            for (int j=y+1;(j<=m)&&(Up[j]<x);j++) Up[j]=x;
            //for (int j=1;j<y;j++) Down[j]=min(Down[j],x);
            //for (int j=y+1;j<=m;j++) Up[j]=max(Up[j],x);
        }
        //for (int j=1;j<=m;j++) cout<<Up[j]<<" ";cout<<endl;
        //for (int j=1;j<=m;j++) cout<<Down[j]<<" ";cout<<endl;
    }
    printf("\n");

    return 0;
}
