#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<iostream>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

double X,Y;

namespace brute{
    const int maxN=40400;
    double F[2][maxN];
    int main();
}

int main(){
    freopen("in","r",stdin);freopen("out","w",stdout);
    int Case;scanf("%d",&Case);
    while (Case--){
        scanf("%lf%lf",&X,&Y);
        if (Y<=1600) brute::main();
    }
    return 0;
}

namespace brute{
    int main(){
        cerr<<X<<" "<<Y<<endl;
        mem(F,0);X--;
        int now=1;F[now][0]=1;
        for (int i=1;i<=Y;i++){
            now^=1;mem(F[now],sizeof(int)*(i*X));
            for (int j=0;j<=(i-1)*X;j++)
                for (int k=0;k<=X;k++)
                    F[now][j+k]+=F[now^1][j]/(X+1);
            //for (int j=0;j<=i*X;j++) cout<<F[now][j]<<" ";cout<<endl;
        }
        for (int i=1;i<=Y*X;i++) F[now][i]+=F[now][i-1];
        for (int ti=1;ti<=10;ti++){
            int A,B;scanf("%d%d",&A,&B);
            printf("%.12lf\n",F[now][B]-((A>=1)?F[now][A-1]:0));
        }
        return 0;
    }
}