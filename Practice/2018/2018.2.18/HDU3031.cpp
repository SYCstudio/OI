#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=100*10000+100;
const int inf=2147483647;

class Heap
{
public:
	int key;
	int ls,rs,dis;
	void init(){
			ls=rs=dis=0;return;
		}
};

int R;
int n,m,Pile[maxN],Pnum[maxN];
Heap H[maxN];

int Merge(int r1,int r2);

int main()
{
	ios::sync_with_stdio(false);
	while (cin>>R)
	{
		int hap=0,wof=0;
		while (R--)
		{
			int nodecnt=0;mem(Pile,0);
			cin>>n>>m;
			for (int i=1;i<=m;i++) cin>>Pnum[i];
			for (int i=1;i<=m;i++)
				for (int j=1;j<=Pnum[i];j++)
				{
					++nodecnt;H[nodecnt].init();
					cin>>H[nodecnt].key;
					Pile[i]=Merge(Pile[i],nodecnt);
				}
			int Id[3];Id[1]=Id[2]=0;
			int Size[3];Size[1]=Size[2]=0;
			for (int now=1;now<=n;now++)
			{
				int pl=(now-1)%2+1;
				char opt;cin>>opt;
				if (opt=='T')//Take-card
				{
					int kth;cin>>kth;
					Id[pl]=Merge(Id[pl],Pile[kth]);
					Size[pl]+=Pnum[kth];
				}
				if (opt=='C')//Challenge-card
				{
					//++nodecnt;H[nodecnt].init();H[nodecnt].key=H[Id[1]].key;Id[1]=Merge(Id[1],nodecnt);
					//++nodecnt;H[nodecnt].init();H[nodecnt].key=H[Id[2]].key;Id[2]=Merge(Id[2],nodecnt);
					//Size[1]++;Size[2]++;
					if (H[Id[2]].key>H[Id[1]].key){
						Id[2]=Merge(Id[1],Id[2]);Id[1]=0;
						Size[2]+=Size[1];Size[1]=0;
					}
					else if (H[Id[1]].key>H[Id[2]].key){
						Id[1]=Merge(Id[1],Id[2]);Id[2]=0;
						Size[1]+=Size[2];Size[2]=0;
					}
				}
				if (opt=='L'){//Lost-card
					Id[pl]=Merge(H[Id[pl]].ls,H[Id[pl]].rs);Size[pl]--;
				}
				if (opt=='A'){
					int key;cin>>key;H[Id[pl]].key+=key;
				}
				if (opt=='E')
				{
					int key;cin>>key;
					int id=Id[pl];Id[pl]=Merge(H[Id[pl]].ls,H[Id[pl]].rs);
					H[id].key=key;Id[pl]=Merge(Id[pl],id);
				}
			}
			printf("%d:%d\n",Size[1],Size[2]);
			if (Size[1]>=Size[2]) wof++;
			else hap++;
		}
		if (wof>hap) printf("Hahaha...I win!!\n");
		else printf("I will be back!!\n");
	}
	return 0;
}

int Merge(int r1,int r2)
{
	if (r1==0) return r2;
	if (r2==0) return r1;
	if (H[r1].key<H[r2].key) swap(r1,r2);
	H[r1].rs=Merge(H[r1].rs,r2);
	if (H[H[r1].ls].dis<H[H[r1].rs].dis) swap(H[r1].ls,H[r1].rs);
	if (H[r1].rs) H[r1].dis=H[H[r1].rs].dis+1;
	else H[r1].dis=0;
	return r1;
}
