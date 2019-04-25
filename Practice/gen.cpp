#include<bits/stdc++.h>
using namespace std;

int make(int l,int r);
int main(){
    srand(time(0));
    int n=1000,m=1000;
    cout<<n<<" "<<m<<endl;
    for (int i=1;i<=n;i++) cout<<make(-10,10)<<" ";cout<<endl;
    for (int i=1;i<=n;i++) cout<<make(-10,10)<<" ";cout<<endl;
    while (m--){
	int opt=make(1,3),l=make(1,n),r=make(1,n);if (l>r) swap(l,r);
	int s=make(-10,10),t=make(-10,10);
	if (opt>=2) cout<<opt<<" "<<l<<" "<<r<<" "<<s<<" "<<t<<endl;
	else cout<<opt<<" "<<l<<" "<<r<<endl;
    }
    return 0;
}
int make(int l,int r){
    double dou=1.0*rand()/RAND_MAX;
    return min(r,(int)(dou*(r-l+1))+l);
}
