#include<bits/stdc++.h>
using namespace std;

int main(){
    srand(20020729);
    int n;scanf("%d",&n);int cnt=40;
    int l=0,r=1e9,mx;
    while (l<=r){
        int mid=(l+r)>>1;
        cout<<"> "<<mid<<endl<<flush;
        int b;cin>>b;--cnt;
        if (b) mx=mid+1,l=mid+1;
        else r=mid-1;
    }
    int d=0;
    while (cnt--){
        int p=rand()%n+1;
        cout<<"? "<<p<<endl<<flush;
        int key;cin>>key;
        if (d==0) d=mx-key;
        else d=__gcd(d,mx-key);
    }
    printf("%d %d\n",mx-(n-1)*d,d);return 0;
}