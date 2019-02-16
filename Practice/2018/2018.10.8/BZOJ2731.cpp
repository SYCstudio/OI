#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int maxNum=1010000;
const int inf=2147483647;

class Tgl
{
public:
	int x,y,d;
	int l,r;
};

int n;
ll Ans,sum;
Tgl T[maxN];
int Cnt[maxNum],head=0,Nxt[maxN],Pre[maxN];
vector<int> Dt[maxNum];

bool cmp(Tgl A,Tgl B);
void Insert(int id);
void Delete(int id);

int main(){
	scanf("%d",&n);
	int down=inf,up=-inf;
	for (int i=1;i<=n;i++){
		scanf("%d%d%d",&T[i].x,&T[i].y,&T[i].d);
		if (T[i].d==0) --i,--n;
		T[i].l=T[i].x;T[i].r=T[i].x+T[i].d-1;
		down=min(down,T[i].y);up=max(up,T[i].y+T[i].d);
	}
	sort(&T[1],&T[n+1],cmp);

	for (int i=1;i<=n;i++) Dt[T[i].y].push_back(i);

	for (int i=0,sz=Dt[down].size();i<sz;i++)
		Insert(Dt[down][i]);

	//cout<<down<<":"<<sum<<endl;
	//for (int i=1;i<=6;i++) cout<<Cnt[i]<<" ";cout<<endl;
	for (int d=down+1;d<=up;d++){
		int lastsum=sum;
		for (int i=head;i;i=Nxt[i]){
			if ((--Cnt[T[i].r])==0) sum--;
			if ((--T[i].r)<T[i].x) Delete(i);
		}
		Ans=Ans+lastsum+sum;
		for (int i=0,sz=Dt[d].size();i<sz;i++)
		{
			bool flag=1;int id=Dt[d][i];
			for (int j=head;j;j=Nxt[j])
				if ((T[j].x<=T[id].x)&&(T[j].r>=T[id].r)){
					flag=0;break;
				}
				else if ((T[j].x>=T[id].x)&&(T[j].r<=T[id].r)) Delete(j);
			if (flag) Insert(id);
		}
		//cout<<d<<":"<<sum<<endl;
		//for (int i=1;i<=6;i++) cout<<Cnt[i]<<" ";cout<<endl;
	}
	printf("%.1lf\n",(double)Ans/2.0);return 0;
}

bool cmp(Tgl A,Tgl B){
	return A.y<B.y;
}

void Insert(int id){
	if (head) Pre[head]=id;
	Nxt[id]=head;Pre[id]=0;head=id;
	for (int i=T[id].x;i<=T[id].r;i++) if ((++Cnt[i])==1) sum++;
	return;
}

void Delete(int id){
	if (Pre[id]) Nxt[Pre[id]]=Nxt[id];
	if (Nxt[id]) Pre[Nxt[id]]=Pre[id];
	if (head==id) head=Nxt[id];
	for (int i=T[id].x;i<=T[id].r;i++) if ((--Cnt[i])==0) sum--;
	return;
}
