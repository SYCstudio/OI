#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<set>
#include<iostream>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
const int maxN=101000;
const int Block=350;

int n,Seq[maxN],St[maxN],Stp[maxN],From[maxN];
bool vis[maxN];
vector<int> Ans[maxN];
set<pair<int,int> > S;

int main(){
    //freopen("in","r",stdin);
    int Case;scanf("%d",&Case);
    while (Case--){
        scanf("%d",&n);for (int i=1;i<=n;i++) scanf("%d",&Seq[i]);
        int cnt=0,res=n;
        while (1){
            int top=0,K=0;while ((K+2)*(K+1)/2<=res) ++K;
            //cout<<K<<endl;
            for (int i=1;i<=n;i++)
                if (vis[i]==0){
                    int p=lower_bound(&St[1],&St[top+1],Seq[i])-St;
                    From[i]=Stp[p-1];Stp[p]=i;St[p]=Seq[i];
                    top=max(top,p);
                }
            //cout<<"GetLIS:["<<top<<"] ";for (int i=1;i<=top;i++) cout<<St[i]<<" ";cout<<endl;
            //for (int i=1;i<=top;i++) cout<<Stp[i]<<" ";cout<<endl;
            //for (int i=1;i<=n;i++) cout<<From[i]<<" ";cout<<endl;
            if (top>K){
                int now=Stp[top];++cnt;res-=top;
                while (now){
                    Ans[cnt].push_back(Seq[now]);vis[now]=1;now=From[now];
                }
                reverse(Ans[cnt].begin(),Ans[cnt].end());
                for (int i=1;i<=top;i++) St[i]=Stp[i]=0;
                continue;
            }
            else{
                S.clear();
                for (int i=1;i<=n;i++)
                    if (vis[i]==0){
                        set<pair<int,int> >::iterator p=S.lower_bound(make_pair(Seq[i],0));
                        if (p==S.end()){
                            ++cnt;Ans[cnt].push_back(Seq[i]);S.insert(make_pair(Seq[i],cnt));
                        }
                        else{
                            int lst=(*p).second;S.erase(p);
                            Ans[lst].push_back(Seq[i]);S.insert(make_pair(Seq[i],lst));
                        }
                    }
                break;
            }
        }
        printf("%d\n",cnt);
        for (int i=1;i<=cnt;i++){
            int sz=Ans[i].size();printf("%d ",sz);
            for (int j=0;j<sz;j++) printf("%d ",Ans[i][j]);printf("\n");
            Ans[i].clear();
        }
        for (int i=1;i<=n;i++) vis[i]=0;
    }
    return 0;
}