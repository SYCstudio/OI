#include<bits/stdc++.h>
using namespace std;

const int maxN=100000;

int make(int l,int r);
int main(){
    srand(time(0));
    int n=100000/2,Q=100000/2,m=100000;
    int Sk[120];for (int i=1;i<=100;i++) Sk[i]=make(1,m);
    cout<<n<<" "<<m<<" "<<Q<<endl;
    for (int i=1;i<=n;i++) cout<<make(1,m)<<" ";cout<<endl;
    for (int i=1;i<=Q;i++){
	int l=make(1,n),r=make(1,n);if (l>r) swap(l,r);
	cout<<l<<" "<<r<<" "<<Sk[make(1,100)]<<endl;
    }
    fclose(stdout);return 0;
}
int make(int l,int r){
    double dou=1.0*rand()/RAND_MAX;
    return min(r,(int)(dou*(r-l+1)+l));
}
