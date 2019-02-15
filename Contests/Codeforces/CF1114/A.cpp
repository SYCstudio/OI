#include<bits/stdc++.h>
using namespace std;

int main(){
    int x,y,z,G,P,B;scanf("%d%d%d%d%d%d",&x,&y,&z,&G,&P,&B);
    G-=x;if (G<0){puts("NO");return 0;}
    int mn=min(G,y);y-=mn;G-=mn;
    P-=y;
    if (P<0||G+P+B<z) puts("NO");
    else puts("YES");return 0;
}