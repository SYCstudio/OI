#include<bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
#define pb push_back
#define mp make_pair
#define ft first
#define sd second

const int maxN=2020000;
const ull base=20020729;
const int maxT=1000000;

int n,nodecnt,Extend[maxN],Dg[maxN],Sum[maxN];
char S[maxN],Y[maxN];
ull Hp[maxN],Hs[maxN];
vector<int> T[maxN];
vector<pair<ull,int> > HashTable[maxT];
vector<ull> FULLHASH;

ull ExpendQ(int l,int r);
ull Query(int l,int r);
int GetId(ull key);
int main()
{
	Hp[0]=1;
	for (int i=1; i<maxN; i++) Hp[i]=Hp[i-1]*base;
	int Case;
	scanf("%d",&Case);
	while (Case--) {
		scanf("%s",S+1);
		n=strlen(S+1);
		for (int i=1; i<=n; i++) Hs[i]=Hs[i-1]*base+S[i]-'a'+1;
		Y[0]=0;
		for (int i=1; i<=n; i++) Y[i+i-1]=S[i],Y[i+i]=0;

		//for (int i=0;i<=n+n;i++) cout<<(int)Y[i]<<" ";cout<<endl;

		int mxpos=-1,right=-1;
		for (int i=0; i<=n+n; i++) {
			int len,lst;
			if (right>=i) len=min(Extend[mxpos+mxpos-i],right-i+1);
			else len=0;

			if (((i&1)&&len>=2)||((~i&1)&&len>=3)) {
				ull nowh=ExpendQ(i-len+2,i+len-2);
				lst=GetId(nowh);
			} else lst=0;

			//cout<<"running on:"<<i<<" l="<<len<<endl;
			while (len<=i&&i+len<=n+n&&Y[i+len]==Y[i-len]) {
				++len;
				if (Y[i+len-1]!=0) {
					ull nowh=ExpendQ(i-len+1,i+len-1);
					int u=GetId(nowh);
					if (lst) T[u].pb(lst);//,cout<<Mp[nowh]<<"->"<<lst<<" "<<len<<endl;
					lst=u;
				}
			}
			Extend[i]=len;
			if (i+len-1>=right) mxpos=i,right=i+Extend[i]-1;

			if (lst) Sum[lst]^=((i+1)/2-1);//,cout<<"final:"<<lst<<" "<<(i+1)/2<<endl;
		}

		//for (int i=0;i<=n+n;i++) cout<<Extend[i]<<" ";cout<<endl;

		for (int i=1; i<=nodecnt; i++) {
			sort(T[i].begin(),T[i].end());
			T[i].erase(unique(T[i].begin(),T[i].end()),T[i].end());
			for (int j=0; j<T[i].size(); j++) ++Dg[T[i][j]];
		}
		queue<int> Qu;
		for (int i=1; i<=nodecnt; i++) if (!Dg[i]) Qu.push(i);
		int Ans=0;
		while (!Qu.empty()) {
			int u=Qu.front();
			Qu.pop();
			Ans=max(Ans,Sum[u]);
			for (int i=0; i<T[u].size(); i++) {
				int v=T[u][i];
				Sum[v]^=Sum[u];
				if ((--Dg[v])==0) Qu.push(v);
			}
		}
		printf("%d\n",Ans);
		//for (int i=1;i<=nodecnt;i++) cout<<Sum[i]<<" ";cout<<endl;

		for (int i=1; i<=nodecnt; i++) T[i].clear(),Dg[i]=0,Sum[i]=0,Extend[i]=0;
		for (int i=0; i<FULLHASH.size(); i++) HashTable[FULLHASH[i]%maxT].clear();
		FULLHASH.clear();
	}
	return 0;
}
ull ExpendQ(int l,int r)
{
	return Query(l/2+1,r/2+1);
}
ull Query(int l,int r)
{
	return Hs[r]-Hs[l-1]*Hp[r-l+1];
}
int GetId(ull key)
{
	int mnkey=key%maxT;
	for (int i=0; i<HashTable[mnkey].size(); i++)
		if (HashTable[mnkey][i].ft==key) return HashTable[mnkey][i].sd;
	HashTable[mnkey].pb(mp(key,++nodecnt));
	FULLHASH.pb(key);
	return nodecnt;
}
