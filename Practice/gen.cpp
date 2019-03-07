#include<bits/stdc++.h>
using namespace std;

int make(int l,int r);
int main(){
    srand(time(0));
    freopen("in","w",stdout);
    int n=100000,m=make(1,50000);cout<<n<<" "<<m<<endl;
    for (int i=1;i<=n;i++) cout<<make(1,1000000)<<" ";cout<<endl;
    int Q=10000;cout<<Q<<endl;
    for (int i=1;i<=Q;i++){
        int l=make(1,n-m+1),r=make(1,n-m+1);
        if (l>r) swap(l,r);
        cout<<l<<" "<<r<<" "<<make(1,100000)<<endl;
    }
    fclose(stdout);return 0;
}
int make(int l,int r){
    double dou=1.0*rand()/RAND_MAX;
    return min(r,(int)(dou*(r-l+1)+l));
}