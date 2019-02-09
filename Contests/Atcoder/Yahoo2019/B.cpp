#include<bits/stdc++.h>
using namespace std;

int D[5];

int main(){
    for (int i=1;i<=6;i++){
        int x;scanf("%d",&x);++D[x];
    }
    sort(&D[1],&D[5]);
    if (D[1]==1&&D[2]==1&&D[3]==2&&D[4]==2) puts("YES");
    else puts("NO");return 0;
}