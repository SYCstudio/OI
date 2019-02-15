#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#include<iostream>
using namespace std;

typedef long long ll;
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
const int maxN=202000;

int n,m;
ll A[maxN],B[maxN],C[maxN],Seq[maxN],Pls[maxN],Res[maxN];
vector<int> T[maxN];
priority_queue<pair<int,int> > H;

bool check(int pos,ll limit,ll rev);
int main(){
    //freopen("05-01.in","r",stdin);
    scanf("%d%d",&n,&m);
    for (int i=1;i<=m;i++){
        scanf("%lld%lld%lld",&A[i],&B[i],&C[i]);
        if (A[i]>B[i]) swap(A[i],B[i]);
        Seq[A[i]]+=C[i];Seq[B[i]]-=C[i];
    }
    int mxl=1,mxr=1;
    for (int i=2;i<=n;i++){
        Seq[i]+=Seq[i-1];
        if (Seq[i]>Seq[mxl]) mxl=i;
        if (Seq[i]==Seq[mxl]) mxr=i;
    }
    //cout<<mxl<<" "<<mxr<<endl;
    ll l=0,r=Seq[mxl],mx=Seq[mxl],mid,Ans;
    while (l<=r){
        mid=(l+r)>>1;
        if (check(mxl,mid,mx-mid)||check(mxl,mid,mx-mid+1)
            ||check(mxr,mid,mx-mid)||check(mxr,mid,mx-mid+1)) 
                Ans=mid,r=mid-1;else l=mid+1;
    }
    printf("%lld\n",Ans);return 0;
}
bool check(int pos,ll limit,ll rev){
    if (rev>limit) return 0;
    //cout<<"check:"<<pos<<" "<<limit<<" "<<rev<<endl;
    for (int i=1;i<=n;i++) T[i].clear();
    for (int i=1;i<=m;i++) if (A[i]<=pos&&B[i]>pos) T[A[i]].push_back(i),Res[i]=C[i];
    while (!H.empty()) H.pop();mem(Pls,0);
    for (int i=1;i<=pos;i++){
        //cout<<"running on :"<<i<<endl;
        for (int j=0,sz=T[i].size();j<sz;j++) H.push(make_pair(B[T[i][j]],T[i][j]));
        ll mt=(max(0ll,Seq[i]+rev-limit)+1)/2;
        while (mt&&!H.empty()){
            int id=H.top().second;H.pop();
            //cout<<id<<" "<<Res[id]<<" | "<<mt<<endl;
            if (Res[id]<=mt){
                rev-=Res[id]*2;mt-=Res[id];
                Pls[A[id]]-=Res[id];Pls[B[id]]+=Res[id]*2;Res[id]=0;
            }
            else{
                rev-=mt*2;Res[id]-=mt;H.push(make_pair(B[id],id));
                Pls[A[id]]-=mt;Pls[B[id]]+=mt*2;mt=0;
            }
        }
        if (mt) return 0;
    }
    //cout<<"Fn"<<endl;
    //for (int i=1,sum=0;i<=n;i++) sum+=Pls[i],cout<<sum<<" ";cout<<endl;
    for (int i=1;i<=n;i++){
        Pls[i]+=Pls[i-1];
        if (Pls[i]+Seq[i]>limit) return 0;
    }
    return 1;
}