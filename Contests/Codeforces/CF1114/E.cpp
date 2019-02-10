#include<bits/stdc++.h>
using namespace std;

int main(){
    srand(20020622);
    int n;scanf("%d",&n);int cnt=60;
    int l=0,r=1e9,mx=0;
    while (l<=r){
        int mid=(l+r)>>1;
        cout<<"> "<<mid<<endl;fflush(stdout);
        int b;cin>>b;--cnt;
        if (b) mx=mid+1,l=mid+1;
        else r=mid-1;
    }
    int d=0;
    int Seq[50];Seq[0]=mx;
    for (int i=1;i<=cnt;i++){
        int p=rand()%n+1;
        cout<<"? "<<p<<endl;fflush(stdout);
        cin>>Seq[i];
        for (int j=0;j<i;j++) d=__gcd(d,abs(Seq[i]-Seq[j]));
    }
    printf("! %d %d\n",mx-(n-1)*d,d);return 0;
}