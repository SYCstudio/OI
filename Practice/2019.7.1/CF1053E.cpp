#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define pw(x) (1<<(x))
const int maxN=505000*2;
const int maxB=22;
const int inf=2000000000;

int n,N,seq[maxN];
int Cnt[maxN];
queue<int> empty;
int ufs[maxN],Lst[maxN],Pre[maxN],Lg[maxN],ST[maxB][maxN];

void NO();
int StMin(int l,int r);
int ufs_find(int x);
void Solve(int l,int r);
int main()
{
	//freopen("input","r",stdin);freopen("out","w",stdout);
	for (int i=2; i<maxN; i++) Lg[i]=Lg[i>>1]+1;
	scanf("%d",&n);
	N=n+n-1;
	for (int i=1; i<=N; i++) scanf("%d",&seq[i]),++Cnt[seq[i]];
	for (int i=1; i<=n; i++) if (!Cnt[i]) empty.push(i);

	if (!seq[1]&&!seq[N]) {
		if (empty.empty()) NO();
		seq[1]=seq[N]=empty.front();
		empty.pop();
	} else if (!seq[1]||!seq[N]) seq[1]=seq[N]=seq[1]+seq[N];
	else if (seq[1]!=seq[N]) NO();

	for (int i=1; i<=N; i++) {
		Pre[i]=inf;
		if (!seq[i]) continue;
		if (Lst[seq[i]]) {
			if ((i&1)!=(Lst[seq[i]]&1)) NO();
			Pre[i]=Lst[seq[i]];
		} else Pre[i]=i;
		Lst[seq[i]]=i;
	}
	for (int i=1; i<=N; i++) ST[0][i]=Pre[i];
	for (int i=1; i<maxB; i++) for (int j=1; j+pw(i)-1<=N; j++) ST[i][j]=min(ST[i-1][j],ST[i-1][j+pw(i-1)]);

	for (int i=1; i<=N; i++) if (seq[i]&&StMin(Pre[i]+1,i-1)<Pre[i]) NO();

	for (int i=1; i<=N; i++) ufs[i]=i;

	//for (int i=1;i<=N;i++) cout<<Pre[i]<<" ";cout<<endl;

	for (int i=1; i<=N; i++) if (Pre[i]<i&&seq[i]) Solve(ufs_find(Pre[i]),i);
	puts("yes");
	for (int i=1; i<=N; i++) printf("%d ",seq[i]);
	puts("");
	return 0;
}
void NO()
{
	puts("no");
	exit(0);
}
int StMin(int l,int r)
{
	if (l>r) return inf;
	int lg=Lg[r-l+1];
	return min(ST[lg][l],ST[lg][r-pw(lg)+1]);
}
int ufs_find(int x)
{
	return ufs[x]==x?ufs[x]:ufs[x]=ufs_find(ufs[x]);
}
void Solve(int l,int r)
{
	//cout<<"Solve:"<<l<<" "<<r<<endl;
	vector<int> vec;
	for (int i=ufs_find(r); i>=l; i=ufs_find(i-1)) {
		int sz=vec.size();
		while (sz>=2&&seq[vec[sz-1]]&&(
		            (!seq[vec[sz-2]]&&seq[i])
		            ||(seq[vec[sz-2]]&&!seq[i])
		            ||(seq[vec[sz-2]]==seq[i]&&seq[i]))) {
			//cout<<"pop:"<<vec[sz-2]<<" "<<vec[sz-1]<<" "<<(seq[vec[sz-2]]==0)<<" "<<(seq[i]==0)<<endl;
			if (!seq[vec[sz-2]]||!seq[i])
				seq[vec[sz-2]]=seq[i]=seq[i]+seq[vec[sz-2]];
			vec.pop_back();
			vec.pop_back();
			sz-=2;
		}
		vec.pb(i);
	}
	//cerr<<empty.size()<<endl;
	reverse(vec.begin(),vec.end());
	//cout<<empty.size()<<" vec:";for (int i=0;i<vec.size();i++) cout<<vec[i]<<"["<<seq[vec[i]]<<"] ";cout<<endl;
	for (int i=1; i<vec.size(); i++) if (seq[vec[i]]&&seq[vec[i-1]]) NO();
	//for (int i=1;i<=N;i++) cout<<seq[i]<<" ";cout<<endl;
	int rt=vec[0];
	deque<int> dq;
	for (int i=1; i+1<vec.size(); i++) dq.pb(vec[i]);
	while (!dq.empty()) {
		int u=dq.front(),v=dq.back();
		//cout<<u<<" "<<v<<endl;
		if (dq.size()==1) {
			if (!seq[u]) {
				if (empty.empty()) NO();
				seq[u]=empty.front();
				empty.pop();
			}
			break;
		}
		int zero=(seq[u]==0)+(seq[v]==0);
		if (zero==2) {
			if (empty.empty()) NO();
			seq[u]=seq[v]=rt=empty.front();
			empty.pop();
			dq.pop_front();
			dq.pop_back();
		} else if (zero==1) {
			rt=seq[u]=seq[v]=seq[u]+seq[v];
			dq.pop_front();
			dq.pop_back();
		} else {
			seq[dq[dq.size()-2]]=rt;
			dq.pop_back();
			dq.pop_back();
		}
	}
	ufs[ufs_find(r)]=l;
	return;
}
