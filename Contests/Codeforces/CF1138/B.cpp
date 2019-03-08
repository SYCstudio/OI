#include<bits/stdc++.h>
using namespace std;

const int maxN=5010;

int n;
char I1[maxN],I2[maxN];

int main(){
    scanf("%d",&n);scanf("%s",I1+1);scanf("%s",I2+1);
    int c[2][2];memset(c,0,sizeof(c));
    for (int i=1;i<=n;i++) ++c[I1[i]-'0'][I2[i]-'0'];
    for (int i=0;i<=c[1][1];i++)
        for (int j=0;j<=c[1][0];j++)
            if (i+j<=n/2&&c[1][1]-i+c[0][1]<=n/2&&n/2-i-j<=c[0][0]&&i+j==c[1][1]-i+c[0][1]){
                int a=i,b=j,c=n/2-i-j;
                //cout<<a<<" "<<b<<endl;
                for (int k=1;k<=n;k++){
                    if (I1[k]=='1'&&I2[k]=='1'&&a) printf("%d ",k),--a;
                    if (I1[k]=='1'&&I2[k]=='0'&&b) printf("%d ",k),--b;
                    if (I1[k]=='0'&&I2[k]=='0'&&c) printf("%d ",k),--c;
                }
                //cout<<a<<" "<<b<<" "<<c<<endl;
                return 0;
            }
    puts("-1");return 0;
}