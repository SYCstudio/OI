#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int inf=2147483647;

class Heap
{
public:
	int key,wth;
	int ls,rs,dis;
	void init(){
			ls=rs=dis=0;return;
		}
};

int n;
Heap H[maxN];

int Merge(int r1,int r2);

int main()
{
	int cas=0;
	ios::sync_with_stdio(false);
	while (scanf("%d",&n))
	{
		if (n==0) break;
		printf("Case #%d:\n",++cas);
		int rt[3],nodecnt=0,tim=0;
		rt[1]=rt[2]=0;
		char opt[20];
		while (n--)
		{
			cin>>opt;
			if ((opt[0]=='p')&&(opt[1]=='u'))
			{
				char hp;int key;cin>>hp>>key;hp=hp-'A'+1;
				tim++;nodecnt++;
				H[nodecnt].init();
				H[nodecnt].key=key;H[nodecnt].wth=tim;
				rt[hp]=Merge(rt[hp],nodecnt);
			}
			if ((opt[0]=='p')&&(opt[1]=='o'))
			{
				char hp;cin>>hp;hp=hp-'A'+1;
				printf("%d\n",H[rt[hp]].key);
				rt[hp]=Merge(H[rt[hp]].ls,H[rt[hp]].rs);
			}
			if (opt[0]=='m')
			{
				char hp1,hp2;cin>>hp1>>hp2;
				hp1=hp1-'A'+1;hp2=hp2-'A'+1;
				rt[hp1]=Merge(rt[hp1],rt[hp2]);
				rt[hp2]=0;
			}
		}
	}
	return 0;
}

int Merge(int r1,int r2)
{
	if (r1==0) return r2;
	if (r2==0) return r1;
	if (H[r1].wth<H[r2].wth) swap(r1,r2);
	H[r1].rs=Merge(H[r1].rs,r2);
	if (H[H[r1].ls].dis<H[H[r1].rs].dis) swap(H[r1].ls,H[r1].rs);
	if (H[r1].rs) H[r1].dis=H[H[r1].rs].dis+1;
	else H[r1].dis=0;
	return r1;
}
