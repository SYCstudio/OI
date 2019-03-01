#include<bits/stdc++.h>
using namespace std;

int make(int l,int r);
int main(){
    freopen("in","w",stdout);srand(time(0));
    int m=2,n=5,Q=6;cout<<m<<" "<<n<<" "<<Q<<endl;
    int key=0;
    for (int i=1;i<m;i++) for (int j=1;j<=n;j++) cout<<make(1,10)<<" ";cout<<endl;
    for (int i=1;i<=m;i++) for (int j=1;j<n;j++) cout<<make(1,10)<<" ";cout<<endl;
    while (Q--){
        int opt=make(1,2);
        if (opt==1) cout<<opt<<" "<<make(1,m)<<" "<<make(1,n)<<" "<<make(1,m)<<" "<<make(1,n)<<" "<<make(1,100000)<<endl;
        else cout<<opt<<" "<<make(1,m)<<" "<<make(1,n)<<endl;
    }
    fclose(stdout);return 0;
}
int make(int l,int r){
    double dou=1.0*rand()/RAND_MAX;
    return min(r,(int)(dou*(r-l+1))+l);
}