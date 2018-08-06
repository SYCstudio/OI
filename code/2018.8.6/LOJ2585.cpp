#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<set>
#include<queue>
#include<map>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define GetNum(x) (lower_bound(&P[1],&P[poscnt+1],x)-P)
#define lson (now<<1)
#define rson (lson|1)

const int maxN=300100*2;
const int inf=1e9+10;

class Question
{
public:
	int pos,tim,id;
};

class Shop
{
public:
	int pos,kind,tim,opt;
};

class ShopInput
{
public:
	int pos,kind,l,r;
};

class Heap
{
private:
	priority_queue<int,vector<int>,greater<int> > Q,Del;
public:
	void MainTain(){
		while ((!Q.empty())&&(!Del.empty())){
			if (Q.top()==Del.top()) Q.pop(),Del.pop();
			else if (Q.top()>Del.top()) Del.pop();
			else break;
		}
		return;
	}
	void push(int key){
		Q.push(key);return;
	}
	void del(int key){
		Del.push(key);return;
	}
	int top(){
		MainTain();
		if (Q.empty()) return inf;
		else return Q.top();
	}
};

int n,K,Q;
Question Qn[maxN];
Shop Sn[maxN];
ShopInput In[maxN];
int poscnt,P[maxN];
Heap H[maxN];
map<int,int> Mp[maxN];
set<int> S[maxN];
int Mn[maxN<<2];
int emptycnt,Ans[maxN];

bool cmp1(Shop A,Shop B);
bool cmp2(Question A,Question B);
void Add(int pos,int kind);
void Del(int pos,int kind);
void Build(int now,int l,int r);
void Replace(int now,int l,int r,int pos,int k1,int k2);
void Extend(int now,int l,int r,int pos,int key);
void Remove(int now,int l,int r,int pos,int key);
int Query(int now,int l,int r,int ql,int qr);

int main(){
	//freopen("68.in","r",stdin);freopen("out.out","w",stdout);
	scanf("%d%d%d",&n,&K,&Q);emptycnt=K;
	for (int i=1;i<=n;i++) scanf("%d%d%d%d",&In[i].pos,&In[i].kind,&In[i].l,&In[i].r),P[++poscnt]=In[i].pos;
	for (int i=1;i<=Q;i++) scanf("%d%d",&Qn[i].pos,&Qn[i].tim),Qn[i].id=i;

	P[++poscnt]=-inf;P[++poscnt]=inf;
	sort(&P[1],&P[poscnt+1]);poscnt=unique(&P[1],&P[poscnt+1])-P-1;
	
	int scnt=0;
	for (int i=1;i<=n;i++) Sn[++scnt]=((Shop){In[i].pos,In[i].kind,In[i].l,1}),Sn[++scnt]=((Shop){In[i].pos,In[i].kind,In[i].r+1,-1});
	sort(&Sn[1],&Sn[scnt+1],cmp1);

	for (int i=1;i<=K;i++) S[i].insert(inf),S[i].insert(-inf),Mp[i][inf]=1,Mp[i][-inf]=1,H[poscnt].push(-inf);

	Build(1,1,poscnt);

	sort(&Qn[1],&Qn[Q+1],cmp2);

	/*
	for (int i=1;i<=scnt;i++) cout<<Sn[i].tim<<" "<<Sn[i].pos<<" "<<Sn[i].kind<<" "<<Sn[i].opt<<endl;
	cout<<"Pos:"<<poscnt<<endl;
	for (int i=1;i<=poscnt;i++) cout<<P[i]<<" ";cout<<endl;
	//*/
	
	for (int i=1,j=0;i<=Q;i++){
		while ((j!=scnt)&&(Sn[j+1].tim<=Qn[i].tim)){
			j++;
			if (Sn[j].opt==1) Add(Sn[j].pos,Sn[j].kind);
			if (Sn[j].opt==-1) Del(Sn[j].pos,Sn[j].kind);
		}
		/*
		cout<<"Query:"<<Qn[i].pos<<" "<<Qn[i].tim<<endl;
		cout<<"NowSet:"<<endl;
		for (int j=1;j<=K;j++){
			cout<<j<<":";
			for (set<int>::iterator it=S[j].begin();it!=S[j].end();it++)
				cout<<(*it)<<" ";
			cout<<endl;
		}
		cout<<"NowSeg:"<<endl;
		for (int j=1;j<=poscnt;j++) cout<<Query(1,1,poscnt,j,j)<<" ";cout<<endl;
		cout<<"empty:"<<emptycnt<<endl;
		//*/
		if (emptycnt>0){
			Ans[Qn[i].id]=-1;continue;
		}
		int L=0,R=inf,ans=-1;
		do
		{
			int mid=(L+R)>>1;
			//cout<<"("<<L<<","<<R<<") "<<mid<<endl;
			//cout<<"GetMin:"<<Qn[i].pos+mid+1<<" ["<<GetNum(Qn[i].pos+mid+1)<<"] "<<poscnt<<":"<<Query(1,1,poscnt,min(poscnt,(int)GetNum(Qn[i].pos+mid+1)),poscnt)<<" "<<Qn[i].pos-mid<<endl;
			if (Query(1,1,poscnt,min(poscnt,(int)GetNum(Qn[i].pos+mid+1)),poscnt)>=Qn[i].pos-mid) ans=mid,R=mid-1;
			else L=mid+1;
		}
		while (L<=R);
		Ans[Qn[i].id]=ans;
		//cout<<endl;
	}

	for (int i=1;i<=Q;i++) printf("%d\n",Ans[i]);
	return 0;
}

bool cmp1(Shop A,Shop B){
	return A.tim<B.tim;
}

bool cmp2(Question A,Question B){
	return A.tim<B.tim;
}
	
void Add(int pos,int kind){
	//cout<<"Add:"<<pos<<" "<<kind<<endl;
	if (Mp[kind].size()==2) emptycnt--;
	if (Mp[kind].count(pos)==0){
		S[kind].insert(pos);
		set<int>::iterator p1,p2;
		p1=p2=S[kind].find(pos);p1--;
		//cout<<"Extend:"<<GetNum(pos)<<" "<<(*p1)<<endl;
		Extend(1,1,poscnt,GetNum(pos),(*p1));p2++;
		//cout<<"Replace:"<<GetNum(*p2)<<" "<<(*p1)<<" "<<pos<<endl;
		Replace(1,1,poscnt,GetNum(*p2),(*p1),pos);
	}
	Mp[kind][pos]++;
	return;
}

void Del(int pos,int kind){
	//cout<<"Delete:"<<pos<<" "<<kind<<endl;
	if (Mp[kind][pos]==1){
		set<int>::iterator p1,p2;
		p1=p2=S[kind].find(pos);p1--;p2++;
		Remove(1,1,poscnt,GetNum(pos),(*p1));
		Replace(1,1,poscnt,GetNum(*p2),pos,(*p1));
		S[kind].erase(pos);
	}
	Mp[kind][pos]--;
	if (Mp[kind][pos]==0) Mp[kind].erase(Mp[kind].find(pos));
	if (Mp[kind].size()==2) emptycnt++;
	return;
}

void Build(int now,int l,int r){
	if (l==r){
		Mn[now]=H[l].top();return;
	}
	int mid=(l+r)>>1;
	Build(lson,l,mid);Build(rson,mid+1,r);
	Mn[now]=min(Mn[lson],Mn[rson]);return;
}

void Replace(int now,int l,int r,int pos,int k1,int k2){
	if (l==r){
		H[l].del(k1);H[l].push(k2);
		Mn[now]=H[l].top();return;
	}
	int mid=(l+r)>>1;
	if (pos<=mid) Replace(lson,l,mid,pos,k1,k2);
	else Replace(rson,mid+1,r,pos,k1,k2);
	Mn[now]=min(Mn[lson],Mn[rson]);return;
}

void Extend(int now,int l,int r,int pos,int key){
	if (l==r){
		H[l].push(key);Mn[now]=H[l].top();
		return;
	}
	int mid=(l+r)>>1;
	if (pos<=mid) Extend(lson,l,mid,pos,key);
	else Extend(rson,mid+1,r,pos,key);
	Mn[now]=min(Mn[lson],Mn[rson]);return;
}

void Remove(int now,int l,int r,int pos,int key){
	if (l==r){
		H[l].del(key);Mn[now]=H[l].top();
		return;
	}
	int mid=(l+r)>>1;
	if (pos<=mid) Remove(lson,l,mid,pos,key);
	else Remove(rson,mid+1,r,pos,key);
	Mn[now]=min(Mn[lson],Mn[rson]);return;
}

int Query(int now,int l,int r,int ql,int qr){
	if ((l==ql)&&(r==qr)) return Mn[now];
	int mid=(l+r)>>1;
	if (qr<=mid) return Query(lson,l,mid,ql,qr);
	else if (ql>=mid+1) return Query(rson,mid+1,r,ql,qr);
	else return min(Query(lson,l,mid,ql,mid),Query(rson,mid+1,r,mid+1,qr));
}
