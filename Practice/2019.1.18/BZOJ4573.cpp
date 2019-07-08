#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=403000;

class SplayData
{
public:
	int ch[2],fa,sz,k;
};
class Question
{
public:
	int u,v;
};
int n,Q,Ans[maxN],grcnt=0,qcnt=0,ncnt=0;
int Rgl[maxN],Rgr[maxN];
SplayData S[maxN];
vector<pair<int,int> > Gr[maxN];
vector<int> Qr[maxN];
Question Qu[maxN];

bool Isroot(int x);
void Update(int x);
void Rotate(int x);
void Splay(int x);
int Access(int x);
void outp();

int main()
{
	scanf("%d%d",&n,&Q);
	grcnt=Q+2;
	S[grcnt].k=0;
	ncnt=1;
	S[ncnt].k=S[ncnt].sz=1;
	S[grcnt].fa=ncnt;
	Rgl[1]=1;
	Rgr[1]=n;
	for (int i=1; i<=Q; i++) {
		int opt;
		scanf("%d",&opt);
		if (opt==0) {
			int l,r;
			scanf("%d%d",&l,&r);
			++ncnt;
			S[ncnt].k=S[ncnt].sz=1;
			S[ncnt].fa=grcnt;
			Rgl[ncnt]=l;
			Rgr[ncnt]=r;
		}
		if (opt==1) {
			int l,r,x;
			scanf("%d%d%d",&l,&r,&x);
			l=max(Rgl[x],l);
			r=min(Rgr[x],r);
			if (l>r) continue;
			++grcnt;
			S[grcnt].k=0;
			S[grcnt].fa=grcnt-1;
			Gr[l].push_back(make_pair(grcnt,x));
			Gr[r+1].push_back(make_pair(-grcnt,x));
		}
		if (opt==2) {
			++qcnt;
			int x;
			scanf("%d%d%d",&x,&Qu[qcnt].u,&Qu[qcnt].v);
			Qr[x].push_back(qcnt);
		}
	}

	for (int i=1; i<=n; i++) {
		//cout<<"running on:"<<i<<endl;
		sort(Gr[i].begin(),Gr[i].end());
		reverse(Gr[i].begin(),Gr[i].end());
		for (int j=0,sz=Gr[i].size(); j<sz; j++)
			if (Gr[i][j].first>0) {
				int gr=Gr[i][j].first,to=Gr[i][j].second;
				//cout<<"gr:"<<gr<<" "<<to<<endl;
				Access(gr);
				Splay(gr);
				if (S[gr].ch[0]) S[S[gr].ch[0]].fa=0;
				S[gr].ch[0]=0;
				Update(gr);
				S[gr].fa=to;
			} else {
				int gr=-Gr[i][j].first;
				Access(gr);
				Splay(gr);
				if (S[gr].ch[0]) S[S[gr].ch[0]].fa=0;
				S[gr].ch[0]=0;
				Update(gr);
				S[gr].fa=gr-1;
			}
		for (int j=0,sz=Qr[i].size(); j<sz; j++) {
			int id=Qr[i][j],u=Qu[id].u,v=Qu[id].v,szu=0,szv=0,szlca=0;
			Access(u);
			Splay(u);
			szu=S[u].sz;
			int lca=Access(v);
			Splay(v);
			szv=S[v].sz;
			Access(lca);
			Splay(lca);
			szlca=S[lca].sz;
			//cout<<szu<<" "<<szv<<" "<<szlca<<endl;
			//cout<<u<<" "<<v<<" lca:"<<lca<<endl;
			Ans[id]=szu+szv-szlca*2;
		}
	}
	for (int i=1; i<=qcnt; i++) printf("%d\n",Ans[i]);
	return 0;
}
bool Isroot(int x)
{
	return !((S[S[x].fa].ch[0]==x)||(S[S[x].fa].ch[1]==x));
}
void Update(int x)
{
	S[x].sz=S[S[x].ch[0]].sz+S[S[x].ch[1]].sz+S[x].k;
	return;
}
void Rotate(int x)
{
	int y=S[x].fa,z=S[y].fa,sx=(x==S[y].ch[1]),sy=(y==S[z].ch[1]);
	S[x].fa=z;
	if (!Isroot(y)) S[z].ch[sy]=x;
	S[y].ch[sx]=S[x].ch[sx^1];
	if (S[x].ch[sx^1]) S[S[x].ch[sx^1]].fa=y;
	S[y].fa=x;
	S[x].ch[sx^1]=y;
	Update(y);
	return;
}
void Splay(int x)
{
	while (!Isroot(x)) {
		int y=S[x].fa,z=S[y].fa;
		if (!Isroot(y))
			((x==S[y].ch[0])^(y==S[z].ch[0]))?Rotate(x):Rotate(y);
		Rotate(x);
	}
	Update(x);
	return;
}
int Access(int x)
{
	int lstx=0;
	while (x) {
		Splay(x);
		S[x].ch[1]=lstx;
		Update(x);
		lstx=x;
		x=S[x].fa;
	}
	return lstx;
}
void outp()
{
	printf("id fa ls rs sz\n");
	for (int j=1; j<=grcnt; j++)
		printf("%2d%3d%3d%3d%3d\n",j,S[j].fa,S[j].ch[0],S[j].ch[1],S[j].sz);
	return;
}
