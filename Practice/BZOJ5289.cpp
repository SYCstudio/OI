#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

typedef long long ll;
const int maxN=505000;

int n,ufs[maxN],A[maxN];
ll W[maxN],Sz[maxN];

int find(int x);
namespace Heap{
    priority_queue<pair<double,int> > H,D;
    void MainTain();
    bool empty();
    void push(pair<double,int> d);
    void pop();
    void del(pair<double,int> d);
    pair<double,int> top();
}
using Heap::push;
using Heap::pop;
using Heap::top;
using Heap::del;
using Heap::empty;

int main(){
    scanf("%d",&n);for (int i=0;i<=n;i++) ufs[i]=i;
    for (int i=1;i<=n;i++){
        scanf("%d",&A[i]);
        if (find(i)==find(A[i])){
            puts("-1");return 0;
        }
        ufs[find(i)]=find(A[i]);
    }
    ll Ans=0;
    for (int i=1;i<=n;i++) scanf("%lld",&W[i]),Sz[i]=1,push(make_pair(-W[i],i)),Ans+=W[i];
    for (int i=0;i<=n;i++) ufs[i]=i;
    while (!empty()){
        int u=top().second;pop();int fa=find(u);
        if (!fa) continue;
        Ans=Ans+W[u]*Sz[fa];
        del(make_pair((double)W[fa]/Sz[fa],fa));
        W[fa]+=W[u];Sz[fa]+=Sz[u];
        push(make_pair((double)W[fa]/Sz[fa],fa));
    }
    printf("%lld\n",Ans);return 0;
}
int find(int x){}
namespace Heap{
    void MainTain(){
        while (!H.empty()&&!D.empty()&&H.top()==D.top()) H.pop(),D.pop();return;
    }
    bool empty(){
        MainTain();return H.empty();
    }
    void push(pair<double,int> d){
        H.push(d);return;
    }
    void pop(){
        MainTain();H.pop();return;
    }
    void del(pair<double,int> d){
        MainTain();D.push(d);return;
    }
    pair<double,int> top(){
        MainTain();return H.top();
    }
}