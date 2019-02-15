#include<bits/stdc++.h>
using namespace std;

const int maxN=4010;
const int Mod=998244353;

char Input[maxN];
int n;
int Sum[maxN][2];
int F[maxN][maxN];

void Plus(int &x,int y);

int main(){
    scanf("%s",Input+1);n=strlen(Input+1);
    for (int i=1;i<=n;i++){
        Sum[i][0]=Sum[i-1][0];Sum[i][1]=Sum[i-1][1];
        if (Input[i]=='0') Sum[i][0]+=2;
        if (Input[i]=='1') Sum[i][0]++,Sum[i][1]++;
        if (Input[i]=='2') Sum[i][1]+=2;
    }
    for (int i=n+1;i<=n+n;i++) Sum[i][0]=Sum[i-1][0],Sum[i][1]=Sum[i-1][1];
    //for (int i=1;i<=n+n;i++) cout<<"("<<Sum[i][0]<<" "<<Sum[i][1]<<") ";cout<<endl;
    F[0][0]=1;
    for (int i=0;i<n+n;i++)
        for (int j=0;j<=min(i,Sum[i][0]);j++){
            if (Sum[i+1][0]>j) Plus(F[i+1][j+1],F[i][j]);//,cout<<"("<<i<<" "<<j<<")->("<<i+1<<","<<j+1<<")"<<endl;
            if (Sum[i+1][1]>i-j) Plus(F[i+1][j],F[i][j]);//,cout<<"("<<i<<" "<<j<<")->("<<i+1<<","<<j<<")"<<endl;
        }
        /*
    for (int i=1;i<=n+n;i++){
        for (int j=0;j<=i;j++) cout<<F[i][j]<<" ";cout<<endl;
    }
    //*/
    int Ans=0;
    for (int i=0;i<=n+n;i++) Plus(Ans,F[n+n][i]);
    printf("%d\n",Ans);return 0;
}
void Plus(int &x,int y){
    x+=y;if (x>=Mod) x-=Mod;return;
}