#include<bits/stdc++.h>
using namespace std;

int make(int l,int r);
int main(){
    freopen("rand","r",stdin);int seed;cin>>seed;srand(seed^time(0));fclose(stdout);
    freopen("in","w",stdout);
    int n=10;
    cout<<n<<endl;
    for (int i=2;i<=n;i++) cout<<make(1,i-1)<<" "<<i<<endl;
    fclose(stdout);
    freopen("rand","w",stdout);cout<<make(1,10000000)<<endl;fclose(stdout);
    return 0;
}
int make(int l,int r){
    double dou=1.0*rand()/RAND_MAX;
    return min(r,(int)(dou*(r-l+1))+l);
}