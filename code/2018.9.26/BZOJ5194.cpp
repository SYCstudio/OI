#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<set>
using namespace std;

class Boot
{
public:
	int s,d,id;
};

const int maxN=101000;
const int inf=2147483647;

int n,B;
Boot Bt[maxN];
pair<int,int> Block[maxN];
set<int> Pos;
multiset<int> H;
int Ans[maxN];

bool cmp(Boot P,Boot Q);

int main(){
	scanf("%d%d",&n,&B);
	for (int i=1;i<=n;i++) scanf("%d",&Block[i].first),Block[i].second=i;
	for (int i=1;i<=B;i++) scanf("%d%d",&Bt[i].s,&Bt[i].d),Bt[i].id=i;
	Block[1].first=Block[n].first=-1;

	sort(&Block[1],&Block[n+1]);
	sort(&Bt[1],&Bt[B+1],cmp);

	//for (int i=1;i<=n;i++) cout<<Block[i].second<<" "<<Block[i].first<<endl;
	
	Pos.insert(1);Pos.insert(n);
	H.insert(n-1-1);
	for (int i=1,j=3;i<=B;i++){
		while ((j<=n)&&(Block[j].first<=Bt[i].s)){
			int pos=Block[j].second;
			Pos.insert(pos);
			int lst=*(--Pos.find(pos)),nxt=*(++Pos.find(pos));
			//cout<<j<<":"<<lst<<" "<<nxt<<" "<<nxt-lst-1<<endl;
			H.erase(H.find(nxt-lst-1));
			H.insert(pos-lst-1);H.insert(nxt-pos-1);
			j++;
		}
		if ((*(--H.end()))>=Bt[i].d) Ans[Bt[i].id]=0;
		else Ans[Bt[i].id]=1;
		//cout<<"now heap:";
		//for (multiset<int>::iterator it=H.begin();it!=H.end();it++) cout<<(*it)<<" ";cout<<endl;
	}
	for (int i=1;i<=B;i++) printf("%d\n",Ans[i]);return 0;
}

bool cmp(Boot P,Boot Q){
	return P.s<Q.s;
}
