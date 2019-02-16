#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<map>
#include<vector>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define lson (now<<1)
#define rson (lson|1)

const int maxN=501000;
const int maxBit=32;
const int inf=2147483647;

class Base
{
public:
	int val[maxBit];
	void Insert(int key){
		for (int i=maxBit-1;i>=0;i--)
			if (key&(1<<i)){
				if (val[i]==0){
					val[i]=key;break;
				}
				key^=val[i];
			}
		return;
	}

	int Get(){
		int ret=0;
		for (int i=maxBit-1;i>=0;i--) ret=max(ret,ret^val[i]);
		return ret;
	}
};

int n;
vector<int> S[maxN<<2];
map<int,int> Pos,Cnt;

void Add(int now,int l,int r,int ql,int qr,int key);
void Query(int now,int l,int r,Base B);

int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++){
		int key;scanf("%d",&key);
		if (key>0){
			if (Cnt[key]==0) Pos[key]=i;
			Cnt[key]++;
		}
		else{
			key=-key;
			if (Cnt[key]==1){
				//cout<<Pos[key]<<" "<<i-1<<" "<<key<<endl;
				Add(1,1,n,Pos[key],i-1,key);
			}
			Cnt[key]--;
		}
	}
	for (map<int,int>::iterator it=Pos.begin();it!=Pos.end();it++)
		if (Cnt[it->first]>0) {
		Add(1,1,n,it->second,n,it->first);
		//cout<<it->second<<" "<<n<<" "<<it->first<<endl;
	}

	Base B;mem(B.val,0);
	Query(1,1,n,B);
	return 0;
}

void Add(int now,int l,int r,int ql,int qr,int key){
	if ((l==ql)&&(r==qr)){
		S[now].push_back(key);return;
	}
	int mid=(l+r)>>1;
	if (qr<=mid) Add(lson,l,mid,ql,qr,key);
	else if (ql>=mid+1) Add(rson,mid+1,r,ql,qr,key);
	else{
		Add(lson,l,mid,ql,mid,key);Add(rson,mid+1,r,mid+1,qr,key);
	}
	return;
}

void Query(int now,int l,int r,Base B){
	for (int sz=S[now].size(),i=0;i<sz;i++) B.Insert(S[now][i]);
	if (l==r){
		printf("%d\n",B.Get());return;
	}
	//cout<<"["<<l<<","<<r<<"]"<<endl;
	int mid=(l+r)>>1;
	Query(lson,l,mid,B);Query(rson,mid+1,r,B);
	return;
}
/*
6
1 2 3 4 -2 -3
//*/
