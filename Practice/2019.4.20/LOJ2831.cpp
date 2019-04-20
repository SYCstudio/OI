#include<cstdio>
#include<algorithm>
#include<iostream>
using namespace std;

typedef long long ll;
const int maxN=101000;

class SplayData{
public:
    int ch[2],fa,cov,siz;
};

int n;
int Val[maxN],num,Num[maxN];
int BIT[maxN],tim,Tim[maxN];
SplayData S[maxN];

bool Isroot(int x);
void PushDown(int x);
void Update(int x);
void Rotate(int x);
void Splay(int x);
void Access(int x);
void Add(int p,int key);
int Sum(int p);

int main(){
    scanf("%d",&n);for (int i=1;i<=n;i++) scanf("%d",&Val[i]),Num[i]=Val[i];
    sort(&Num[1],&Num[n+1]);num=unique(&Num[1],&Num[n+1])-Num-1;
    for (int i=1;i<=n;i++) S[i].cov=Val[i]=lower_bound(&Num[1],&Num[num+1],Val[i])-Num,S[i].siz=1;
    for (int i=1;i<n;i++){
	int a,b;scanf("%d%d",&a,&b);
	S[b].fa=a;Access(b);
    }
    return 0;
}
bool Isroot(int x){
    int fa=S[x].fa;if (S[fa].ch[0]==x||S[fa].ch[1]==x) return 0;return 1;
}
void Update(int x){
    S[x].siz=S[S[x].ch[0]].siz+S[S[x].ch[1]].siz+1;
    return;
}
void PushDown(int x){
    if (S[x].ch[0]) S[S[x].ch[0]].cov=S[x].cov;
    if (S[x].ch[1]) S[S[x].ch[1]].cov=S[x].cov;
    return;
}
void Rotate(int x){
    int y=S[x].fa,z=S[y].fa,sx=(x==S[y].ch[1]),sy=(y==S[z].ch[1]);
    S[x].fa=z;if (!Isroot(y)) S[z].ch[sy]=x;
    S[y].ch[sx]=S[x].ch[sx^1];if (S[x].ch[sx^1]) S[S[x].ch[sx^1]].fa=y;
    S[y].fa=x;S[x].ch[sx^1]=y;
    Update(y);return;
}
void Splay(int x){
    static int St[maxN],top,now;now=x;top=1;St[1]=now;
    while (!Isroot(now)) St[++top]=now=S[now].fa;
    
    while (top) PushDown(St[top--]);
    while (!Isroot(x)){
	int y=S[x].fa,z=S[y].fa;
	if (!Isroot(y)) ((x==S[y].ch[0])^(y==S[z].ch[0]))?Rotate(x):Rotate(y);
	Rotate(x);
    }
    Update(x);return;
}
void Access(int x){
    ++tim;ll Ans=0;int key=Val[x],lstx=x,skp=0,mxs=0,prex=x;x=S[x].fa;
    while (x){
	++skp;mxs=max(mxs,S[x].siz);
	Splay(x);Ans=Ans+1ll*(S[S[x].ch[0]].siz+1)*Sum(S[x].cov-1);
	Add(S[x].cov,S[S[x].ch[0]].siz+1);S[x].cov=key;
	S[x].ch[1]=lstx;lstx=x;Update(x);x=S[x].fa;
    }
    printf("%lld\n",Ans);return;
}
void Add(int p,int key){
    while (p<=num){
	if (Tim[p]!=tim) Tim[p]=tim,BIT[p]=0;
	BIT[p]+=key;p+=(p)&(-p);
    }
    return;
}
int Sum(int p){
    int ret=0;
    while (p){
	if (Tim[p]==tim) ret+=BIT[p];
	p-=(p)&(-p);
    }
    return ret;
}
