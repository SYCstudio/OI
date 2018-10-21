#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define RG register
#define IL inline

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

/*
void Input(int &x){
	scanf("%d",&x);return;
}
//*/

const int maxN=4010;
const int inf=2147483647;

class QueueData
{
public:
	int id,l,r;
};

int n,K;
int Val[maxN][maxN],Sum[maxN][maxN];
int F[maxN],G[maxN];
QueueData Q[maxN];

void Calc(RG int C);
IL bool Better(RG int u,RG int v,RG int tim);
IL int Beyond(RG int u,RG int v);

int main(){
	RG int i,j,L,R,pos,mid;
	Input(n);Input(K);
	for (i=1;i<=n;++i) for (j=1;j<=n;++j) Input(Val[i][j]);
	for (j=1;j<=n;++j) for (i=j-1;i>=1;--i) Val[i][j]+=Val[i+1][j];
	for (i=1;i<=n;++i) for (j=i;j<=n;++j) Sum[i][j]=Sum[i][j-1]+Val[i][j];

	L=0;R=Sum[1][n];pos;
	do{
		mid=(L+R)>>1;
		Calc(mid);
		if (G[n]>=K) pos=mid,L=mid+1;
		else R=mid-1;
	}
	while (L<=R);
	Calc(pos);
	IO::Print(F[n]-K*pos);
	IO::Flush();
	return 0;
}

void Calc(RG int C){
	RG int L=1,R=1,i,pos;Q[1]=((QueueData){0,0,n});
	for (i=1;i<=n;++i){
		++Q[L].l;if (Q[L].l>Q[L].r) ++L;
		F[i]=F[Q[L].id]+Sum[Q[L].id+1][i]+C;G[i]=G[Q[L].id]+1;
		if ((L>R)||(Better(i,Q[R].id,n))){
			while ((L<=R)&&(Better(i,Q[R].id,Q[R].l))) --R;
			if (L>R) Q[++R]=((QueueData){i,i,n});
			else{
				pos=Beyond(i,Q[R].id);
				Q[R].r=pos-1;Q[++R]=((QueueData){i,pos,n});
			}
		}
	}
	return;
}

IL bool Better(RG int u,RG int v,RG int tim){
	RG int key1=F[u]+Sum[u+1][tim],key2=F[v]+Sum[v+1][tim];
	return ((key1<key2)||((key1==key2)&&(G[u]>=G[v])));
}

IL int Beyond(RG int u,RG int v){
	RG int L=v,R=n,ret=0,mid;
	do{
		mid=(L+R)>>1;
		if (Better(u,v,mid)) ret=mid,R=mid-1;
		else L=mid+1;
	}
	while (L<=R);
	return ret;
}
