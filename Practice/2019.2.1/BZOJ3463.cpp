#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<queue>
#include<iostream>
#include<cstring>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define mp make_pair
#define ft first
#define sd second

namespace IO{
    const int maxn((1 << 21) + 1);

    char ibuf[maxn], *iS, *iT, obuf[maxn], *oS = obuf, *oT = obuf + maxn - 1, c, st[55];
    int f, tp;
    char Getc() {
        return (iS == iT ? (iT = (iS = ibuf) + fread(ibuf, 1, maxn, stdin), (iS == iT ? EOF : *iS++)) : *iS++);
    }

    void Flush() {
        fwrite(obuf, 1, oS - obuf, stdout);
        oS = obuf;
    }

    void Putc(char x) {
        *oS++ = x;
        if (oS == oT) Flush();
    }
    
    template <class Int> void Input(Int &x) {
        for (f = 1, c = Getc(); c < '0' || c > '9'; c = Getc()) f = c == '-' ? -1 : 1;
        for (x = 0; c <= '9' && c >= '0'; c = Getc()) x = (x << 3) + (x << 1) + (c ^ 48);
        x *= f;
    }
    
    template <class Int> void Print(Int x) {
        if (!x) Putc('0');
        if (x < 0) Putc('-'), x = -x;
        while (x) st[++tp] = x % 10 + '0', x /= 10;
        while (tp) Putc(st[tp--]);
    }

    void Getstr(char *s, int &l) {
        for (c = Getc(); c < 'a' || c > 'z'; c = Getc());
        for (l = 0; c <= 'z' && c >= 'a'; c = Getc()) s[l++] = c;
        s[l] = 0;
    }
    
    void Putstr(const char *s) {
        for (int i = 0, n = strlen(s); i < n; ++i) Putc(s[i]);
    }
}

using namespace IO;

const int maxN=101000;
const int Block=110;
const ll INF=1e18;

ld GetC(ll k1,ll b1,ll k2,ll b2);

class Convex{
public:
    int sz;
    deque<pair<ll,ll> > C;
    Convex(){
	sz=-1;return;
    }
    void clear(){
	sz=-1;C.clear();return;
    }
    void push_back(ll k,ll b){
	while (sz>=0){
	    if (C[sz].ft==k){
		if (C[sz].sd>=b) return;
		C.pop_back();--sz;continue;
	    }
	    else if (sz>=1&&GetC(C[sz-1].ft,C[sz-1].sd,k,b)<=GetC(C[sz-1].ft,C[sz-1].sd,C[sz].ft,C[sz].sd)){
		C.pop_back();--sz;continue;
	    }
	    break;
	}
	C.push_back(mp(k,b));++sz;return;
    }
    bool empty(){
	return sz==-1;
    }
    ll top(ll t){
	if (empty()) return -INF;
	while (sz>=1&&GetC(C[0].ft,C[0].sd,C[1].ft,C[1].sd)<=t) C.pop_front(),--sz;
	return t*C[0].ft+C[0].sd;
    }
};

int n,m;
int L[maxN],R[maxN],Bl[maxN];
bool nrb[maxN];
ll K[maxN],B[maxN];
pair<ll,ll> Sorter[maxN];
Convex Cnx[1000],Bp;

void rebuild(int id);

int main(){
    //freopen("9.in","r",stdin);freopen("out","w",stdout);
    Input(n);Input(m);//n=Input();m=Input();//scanf("%d%d",&n,&m);
    
    for (int i=1;i<=n;i++){
	Bl[i]=i/Block+1;R[Bl[i]]=i;
	if (L[Bl[i]]==0) L[Bl[i]]=i;
    }
    for (int i=1;i<=n;i++) K[i]=0,B[i]=-INF;
    while (m--){
	//if (m%10000==0) cerr<<m<<endl;
	int opt;Input(opt);//scanf("%d",&opt);
	if (opt==1){
	    ll t,p,k,b;//scanf("%lld%lld%lld%lld",&t,&p,&k,&b);
	    Input(t);Input(p);Input(k);Input(b);
	    K[p]=k;B[p]=b-k*t;
	    nrb[Bl[p]]=1;
	}
	if (opt==2){
	    int t,l,r;//scanf("%d%d%d",&t,&l,&r);
	    Input(t);Input(l);Input(r);
	    ll Ans=-INF;if (l>r) swap(l,r);
	    if (Bl[l]==Bl[r]) for (int i=l;i<=r;i++) Ans=max(Ans,K[i]*t+B[i]);
	    else{
		for (int i=l;i<=R[Bl[l]];i++) Ans=max(Ans,K[i]*t+B[i]);
		for (int i=L[Bl[r]];i<=r;i++) Ans=max(Ans,K[i]*t+B[i]);
		for (int i=Bl[l]+1;i<Bl[r];i++) if (nrb[i]) rebuild(i);
		for (int i=Bl[l]+1;i<Bl[r];i++) Ans=max(Ans,Cnx[i].top(t));
	    }
	    if (Ans==-INF) Putstr("nema\n");//printf("nema\n");
	    else Print(Ans),Putc('\n');//printf("%lld\n",Ans);
	}
    }
    Flush();
    return 0;
}

ld GetC(ll k1,ll b1,ll k2,ll b2){
    return (ld)(b1-b2)/(ld)(k2-k1);
}
int Input(){
    char ch=getchar();int x=0,k=1;
    while (!isdigit(ch)&&(ch!='-')) ch=getchar();
    if (ch=='-') k=-1,ch=getchar();
    while (isdigit(ch)) x=x*10+ch-48,ch=getchar();
    return x*k;
}
void rebuild(int id){
    int scnt=0;for (int i=L[id];i<=R[id];i++) if (B[i]!=-INF) Sorter[++scnt]=mp(K[i],B[i]);
    sort(&Sorter[1],&Sorter[scnt+1]);
    Cnx[id].clear();
    for (int i=1;i<=scnt;i++) Cnx[id].push_back(Sorter[i].ft,Sorter[i].sd);
    nrb[id]=0;return;
}
