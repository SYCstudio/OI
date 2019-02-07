#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<iostream>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

int X,Y;

namespace brute{
    const int maxN=40400;
    double F[2][maxN];
    int main();
}

int main(){
    //freopen("in","r",stdin);freopen("out","w",stdout);
    int Case;scanf("%d",&Case);
    while (Case--){
        scanf("%d%d",&X,&Y);
        if (Y<=1600) brute::main();
    }
    return 0;
}

namespace brute{
    int main(){
        mem(F,0);
        int now=1;for (int i=0;i<=(X-1)*Y;i++) F[now][i]=1;
        for (int i=1;i<=Y;i++){
            now^=1;mem(F[now],0);
            for (int j=0;j<=i*(X-1);j++){
                /*
                for (int k=0;k<X;k++)
                    F[now][j+k]+=F[now^1][j]/X;
                //*/

                double f=F[now^1][min(j,(i-1)*(X-1))];
                if (j>=(int)X) f-=F[now^1][min(j-X,(i-1)*(X-1))];
                f=f/X;
                F[now][j]=f+((j>0)?(F[now][j-1]):0);
                //*/
            }
            //for (int j=0;j<=i*(X-1);j++) cout<<F[now][j]<<" ";cout<<endl;
        }
        //for (int i=1;i<=(X-1)*Y;i++) F[now][i]+=F[now][i-1];
        for (int ti=1;ti<=10;ti++){
            int A,B;scanf("%d%d",&A,&B);
            printf("%.12lf\n",F[now][B]-((A>=1)?F[now][A-1]:0));
        }
        return 0;
    }
}