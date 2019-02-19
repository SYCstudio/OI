#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
const int maxN=510;

int n,H,St[maxN];
vector<int> T[maxN];
int vis[maxN];

void Ask(int id);
int main(){
    int Case;scanf("%d",&Case);
    while (Case--){
        scanf("%d",&H);n=(1<<H)-1;mem(vis,0);mem(St,0);
        if (H==0) exit(0);
        for (int i=1;i<maxN;i++) T[i].clear();
        int now=1,cnt=0,gr=0;
        while (1){
            Ask(now);St[++cnt]=now;
            if (T[now].size()==2){
                cout<<"! "<<now<<endl;fflush(stdout);gr=1;break;
            }
            bool flag=0;
            for (int i=0;i<T[now].size();i++) if (T[T[now][i]].size()==0) {flag=1;now=T[now][i];break;}
            if (flag==0) break;
        }
        if (gr) continue;
        if (T[1].size()==3){
            for (int i=0;i<T[1].size();i++) if (T[T[1][i]].size()==0) {now=T[1][i];break;}
            reverse(&St[1],&St[cnt+1]);
            while (1){
                Ask(now);St[++cnt]=now;
                if (T[now].size()==2){
                    cout<<"! "<<now<<endl;fflush(stdout);gr=1;break;
                }
                bool flag=0;
                for (int i=0;i<T[now].size();i++) if (T[T[now][i]].size()==0) {flag=1;now=T[now][i];break;}
                if (flag==0) break;
            }
        }
        if (gr) continue;

        now=St[cnt/2+1];int h=H-cnt/2-1,lst=St[cnt/2+1];
        if (T[now].size()==2){
            cout<<"! "<<now<<endl;fflush(stdout);continue;
        }
        for (int i=0;i<T[now].size();i++) if (T[now][i]!=St[cnt/2]&&T[now][i]!=St[cnt/2+2]) {now=T[now][i];break;}
        if (h==1){
            cout<<"! "<<now<<endl;fflush(stdout);continue;
        }
        if (h==2){
            int u=-1,v=-1;Ask(now);
            //cout<<now<<" "<<lst<<endl;
            for (int i=0;i<T[now].size();i++) if (T[now][i]!=lst) (u==-1)?(u=T[now][i]):(v=T[now][i]);
            Ask(u);
            if (T[u].size()==2) cout<<"! "<<u<<endl;
            else cout<<"! "<<v<<endl;
            fflush(stdout);continue;
        }
        while (h>3){
            //cout<<"running on:"<<now<<" "<<h<<endl;
            int limit=H-h,u=now;int top=0;St[0]=lst;
            for (int i=1;i<=limit;i++){
                Ask(u);St[++top]=u;
                if (T[u].size()==2){
                    cout<<"! "<<u<<endl;fflush(stdout);gr=1;break;
                }
                for (int j=0;j<T[u].size();j++) if (T[u][j]!=St[top-1]) {u=T[u][j];break;}
            }
            if (gr==1) break;
            Ask(u);St[++top]=u;
            //cout<<"u:"<<u<<endl;
            if (T[u].size()==2){
                cout<<"! "<<u<<endl;fflush(stdout);gr=1;break;
            }
            //cout<<"usz:"<<T[u].size()<<endl;
            //for (int i=0;i<T[now].size();i++) cout<<T[now][i]<<" "<<T[T[now][i]].size()<<endl;
            if (T[u].size()==1){
                for (int i=0;i<T[now].size();i++) if (T[now][i]!=lst&&T[now][i]!=St[2]) {lst=now;now=T[now][i];break;}
            }
            else lst=now,now=St[2];
            --h;
        }
        if (gr) continue;
        //cout<<"after skip:"<<now<<endl;
        Ask(now);
        int u=-1,v=-1;
        for (int i=0;i<T[now].size();i++) if (T[now][i]!=lst) (u==-1)?(u=T[now][i]):(v=T[now][i]);
        //cout<<"Getuv:"<<u<<" "<<v<<endl;
        Ask(u);Ask(v);
        vector<int> L;
        for (int i=0;i<T[u].size();i++) if (T[u][i]!=now) L.push_back(T[u][i]);
        for (int i=0;i<T[v].size();i++) if (T[v][i]!=now) L.push_back(T[v][i]);
        //cout<<L[0]<<" "<<L[1]<<" "<<L[2]<<" "<<L[3]<<endl;
        Ask(L[0]);Ask(L[1]);Ask(L[2]);
        if (T[L[0]].size()==2) cout<<"! "<<L[0]<<endl;
        else if (T[L[1]].size()==2) cout<<"! "<<L[1]<<endl;
        else if (T[L[2]].size()==2) cout<<"! "<<L[2]<<endl;
        else cout<<"! "<<L[3]<<endl;
        fflush(stdout);
    }
    return 0;
}
void Ask(int id){
    if (vis[id]) return;
    cout<<"? "<<id<<endl;fflush(stdout);
    int cnt,x;cin>>cnt;if (cnt==0) exit(0);
    while (cnt--){
        cin>>x;T[id].push_back(x);
    }
    vis[id]=1;
    return;
}