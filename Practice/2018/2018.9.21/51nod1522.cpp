#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define Trans(a,b,c,d) a//cout<<"("<<a<<","<<b<<") -> ("<<c<<","<<d<<")"<<endl

const int maxN=75;
const int maxM=510;
const int inf=2147483647;

class Limit
{
public:
	int opt,v;
};

int n,K;
int edgecnt=0,Head[maxN],Next[maxM];
Limit E[maxM];
ll F[maxN][maxN];

void Add_Edge(int u,int v,int opt);
bool check(int u,int v,int l,int r,int pl,int pr);

int main(){
	mem(Head,-1);
	scanf("%d%d",&n,&K);
	for (int i=1;i<=K;i++){
		int u,v;char s[5];scanf("%d %s %d",&u,s,&v);
		
		if (u==v){
			if ( ((s[0]=='<')||(s[0]=='>')) && (s[1]!='=')){
				printf("0\n");return 0;
			}
			continue;
		}
		//*/
		if (s[0]=='=') Add_Edge(u,v,1),Add_Edge(v,u,1);
		if (s[0]=='<'){
			if (s[1]=='=') Add_Edge(u,v,4),Add_Edge(v,u,5);
			else Add_Edge(u,v,2),Add_Edge(v,u,3);
		}
		if (s[0]=='>'){
			if (s[1]=='=') Add_Edge(u,v,5),Add_Edge(v,u,4);
			else Add_Edge(u,v,3),Add_Edge(v,u,2);
		}
	}
	/*
	for (int i=1;i<=n+n;i++)
		for (int j=Head[i];j!=-1;j=Next[j])
			cout<<i<<" -> "<<E[j].v<<" "<<E[j].opt<<endl;
	//*/
	mem(F,0);F[0][n+n+1]=1;
	for (int i=1;i<=n;i++)
		for (int l=0;l<=i*2;l++){
			int r=n+n-(i*2-l)+1;
			if (check(l,r,l,r,l-1,r+1)) F[l][r]+=F[l-1][r+1],Trans(l-1,r+1,l,r);
			if (l==r-1) continue;
			if (check(l-1,l,l,r,l-2,r)) F[l][r]+=F[l-2][r],Trans(l-2,r,l,r);
			if (check(r,r+1,l,r,l,r+2)) F[l][r]+=F[l][r+2],Trans(l,r+2,l,r);
		}
	/*
	for (int i=0;i<n;i++)
		for (int l=0;l<=i*2;l++){
			int r=n+n-(i*2-l)+1;
			if (check(l+1,l+2,l+1,r,l,r)) F[l+2][r]+=F[l][r],Trans(l,r,l+2,r);
			if (r-l-1==2) continue;
			if (check(l+1,r-1,l+1,r-1,l,r)) F[l+1][r-1]+=F[l][r],Trans(l,r,l+1,r-1);
			if (check(r-2,r-1,l,r-1,l,r)) F[l][r-2]+=F[l][r],Trans(l,r,l,r-2);
		}
	//*/
	/*
	for (int i=1;i<=n+n;i++)
		for (int j=i;j<=n+n;j++)
			cout<<"("<<i<<","<<j<<") "<<F[i][j]<<endl;
	//*/

	ll Ans=0;
	for (int i=0;i<=n+n;i++) Ans+=F[i][i+1];
	printf("%lld\n",Ans);return 0;
}

void Add_Edge(int u,int v,int opt){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;E[edgecnt]=((Limit){opt,v});
	return;
}

bool check(int u,int v,int l,int r,int pl,int pr){
	if ((u>=v)||(u<=0)||(v>=n+n+1)) return 0;
	if ((l>r)||(pl>pr)||(pl<0)||(pr>n+n+1)) return 0;
	//.cout<<"check:"<<u<<" "<<v<<" ["<<l<<","<<r<<"] ["<<pl<<","<<pr<<"]"<<endl;
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((E[i].opt==1)&&(E[i].v!=v)) return 0;
		else if ((E[i].opt==2)&&((E[i].v<=l)||(E[i].v>=r))) return 0;
		else if ((E[i].opt==3)&&(E[i].v<pr)&&(E[i].v>pl)) return 0;
		else if ((E[i].opt==4)&&((E[i].v<=pl)||(E[i].v>=pr))) return 0;
		else if ((E[i].opt==5)&&(E[i].v<r)&&(E[i].v>l)) return 0;
	for (int i=Head[v];i!=-1;i=Next[i])
		if ((E[i].opt==1)&&(E[i].v!=u)) return 0;
		else if ((E[i].opt==2)&&((E[i].v<=l)||(E[i].v>=r))) return 0;
		else if ((E[i].opt==3)&&(E[i].v<pr)&&(E[i].v>pl)) return 0;
		else if ((E[i].opt==4)&&((E[i].v<=pl)||(E[i].v>=pr))) return 0;
		else if ((E[i].opt==5)&&(E[i].v<r)&&(E[i].v>l)) return 0;
	return 1;
}
