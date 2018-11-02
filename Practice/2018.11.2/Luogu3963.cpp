#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<set>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=202000;
const int inf=2147483647;

int n,m;

class DataStruct
{
	multiset<int> S1,S2;
	ll sum;int size;
public:
	void insert(int key){
		//cout<<"Insert:"<<key<<endl;
		if (size<m) S1.insert(key),++size,sum+=key;
		else if (*(--S1.end())>key){
			sum-=(*(--S1.end()));S2.insert(*(--S1.end()));
			S1.erase(--S1.end());sum+=key;S1.insert(key);
		}
		else S2.insert(key);return;
	}
	void erase(int key){
		if (S2.count(key)) S2.erase(S2.find(key));
		else{
			sum-=key;S1.erase(S1.find(key));
			if (!S2.empty()){
				sum+=*S2.begin();S1.insert(*S2.begin());
				S2.erase(S2.begin());
			}
			else --size;
		}
	}
	bool full(){
		return size==m;
	}
	ll mink(){
		return sum;
	}
	void outp(){
		cout<<"S1:";for (multiset<int>::iterator it=S1.begin();it!=S1.end();it++) cout<<(*it)<<" ";cout<<endl;
		cout<<"S2:";for (multiset<int>::iterator it=S2.begin();it!=S2.end();it++) cout<<(*it)<<" ";cout<<endl;
		return;
	}
};

ll limit;
pair<int,int> P[maxN];
DataStruct D1,D2;

int main(){
	scanf("%d%d%lld",&m,&n,&limit);m/=2;
	for (int i=1;i<=n;i++) scanf("%d%d",&P[i].first,&P[i].second);
	sort(&P[1],&P[n+1]);
	for (int i=2;i<=n;i++) D2.insert(P[i].second);
	ll Ans=-1;
	//D2.outp();cout<<endl;
	for (int i=1;i<n;i++){
		if (D1.full()&&D2.full()&&(D1.mink()+D2.mink()+P[i].second<=limit)) Ans=P[i].first;
		D2.erase(P[i+1].second);D1.insert(P[i].second);
		//cout<<"i:"<<i<<endl;
		//cout<<"D1:"<<endl;D1.outp();
		//cout<<"D2:"<<endl;D2.outp();
	}
	printf("%lld\n",Ans);return 0;
}
