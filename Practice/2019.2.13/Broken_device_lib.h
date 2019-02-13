#include<bits/stdc++.h>
using namespace std;

void Anna(int N,long long X,int K,int P[]);
long long Bruno(int N,int P[]);

namespace lib{
    #define mem(Arr,x) memset(Arr,x,sizeof(Arr))
    const int maxNN=150;
    int vis[maxNN],Fob[maxNN],Rc[maxNN];
}

long long make(long long l,long long r);
void Set(int p,int k);
int main(){
    using namespace lib;
    int Q=10000;srand(time(0));
    for (int qi=1;qi<=Q;qi++){
        mem(vis,0);
        long long X=make(0,1ll<<60);int K=make(0,40);
        for (int i=0;i<K;i++) Fob[i]=make(0,150);
        sort(&Fob[0],&Fob[K]);K=unique(&Fob[0],&Fob[K])-Fob-1;
        Anna(150,X,K,Fob);
        for (int i=0;i<150;i++) if (vis[i]==0) cout<<"There some bits havn't set value!"<<endl,exit(0);
        for (int i=0;i<K;i++) if (Rc[Fob[i]]) cout<<"Invalid sequeue!"<<endl,exit(0);
        long long ret=Bruno(150,Rc);
        //cout<<"X:"<<X<<" ret:"<<ret<<endl;
        //for (int i=0;i<150;i+=3) cout<<Rc[i]<<Rc[i+1]<<Rc[i+2]<<" ";cout<<endl;
        if (ret!=X) cout<<"Wrong Answer!"<<endl,exit(0);
        cout<<"Accepted at "<<qi<<endl;
    }
    return 0;
}
long long make(long long l,long long r){
    double dou=1.0*rand()/RAND_MAX;
    return min(r,(long long)(dou*(r-l+1))+l);
}
void Set(int p,int k){
    using namespace lib;
    if (p<0||p>=150) cout<<"Invalid position!"<<endl,exit(0);
    if (k!=0&&k!=1) cout<<"Invalid set key!"<<endl,exit(0);
    vis[p]=1;Rc[p]=k;return;
}