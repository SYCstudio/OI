#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=301000;
const int maxAlpha=26;
const int inf=2147483647;

class AhoCorasick
{
private:
	int root[maxN],top,Size[maxN];
	int nodecnt;
	int son[maxAlpha][maxN],trans[maxAlpha][maxN],fail[maxN],end[maxN],cnt[maxN];
	bool rebuild[maxN];
	queue<int> Q;

	void GetFail(int rt){
		//cout<<"GetFail:"<<rt<<endl;
		while (!Q.empty()) Q.pop();
		for (int i=0;i<maxAlpha;i++) trans[i][rt]=son[i][rt];
		for (int i=0;i<maxAlpha;i++)
			if (trans[i][rt]){
				fail[trans[i][rt]]=rt;cnt[trans[i][rt]]=end[trans[i][rt]];
				Q.push(trans[i][rt]);
			}
			else trans[i][rt]=rt;
		while (!Q.empty()){
			int u=Q.front();Q.pop();
			//cout<<u<<":"<<fail[u]<<endl;
			for (int i=0;i<maxAlpha;i++) trans[i][u]=son[i][u];
			for (int i=0;i<maxAlpha;i++)
				if (trans[i][u]){
					fail[trans[i][u]]=trans[i][fail[u]];
					cnt[trans[i][u]]=cnt[fail[trans[i][u]]]+end[trans[i][u]];
					Q.push(trans[i][u]);
				}
				else trans[i][u]=trans[i][fail[u]];
		}
		//cout<<"End"<<endl;
		return;
	}

	int Merge(int r1,int r2){
		if ((r1==0)||(r2==0)) return r1+r2;
		end[r1]+=end[r2];
		for (int i=0;i<maxAlpha;i++) son[i][r1]=Merge(son[i][r1],son[i][r2]);
		return r1;
	}
	
public:
	AhoCorasick(){
		nodecnt=0;top=0;return;
	}
	
	void Insert(char *str){
		//cout<<"Insert:"<<(str+1)<<endl;
		root[++top]=++nodecnt;Size[top]=1;
		int len=strlen(str+1);
		int now=root[top];
		for (int i=1;i<=len;i++){
			if (son[str[i]-'a'][now]==0) son[str[i]-'a'][now]=++nodecnt;
			now=son[str[i]-'a'][now];
		}
		//cout<<"finish"<<endl;
		end[now]++;cnt[now]++;
		while ((top!=1)&&(Size[top]==Size[top-1])){
			//cout<<"Merge:"<<root[top]<<" "<<root[top-1]<<endl;
			root[top-1]=Merge(root[top],root[top-1]);Size[top-1]+=Size[top];
			top--;rebuild[top]=0;
		}
		return;
	}

	int Query(char *str){
		//cout<<"Query:"<<(str+1)<<endl;
		int ret=0,len=strlen(str+1);
		for (int id=1;id<=top;id++){
			if (rebuild[id]==0){
				GetFail(root[id]);rebuild[id]=1;
			}
			int now=root[id];
			for (int i=1;i<=len;i++){
				now=trans[str[i]-'a'][now];
				ret=ret+cnt[now];
			}
		}
		return ret;
	}
};

AhoCorasick T1,T2;
char Input[maxN];

int main(){
	int Q;scanf("%d",&Q);
	while (Q--){
		int opt;scanf("%d",&opt);
		scanf("%s",Input+1);
		if (opt==1) T1.Insert(Input);
		if (opt==2) T2.Insert(Input);
		if (opt==3){
			printf("%d\n",T1.Query(Input)-T2.Query(Input));
			fflush(stdout);
		}
	}
	return 0;
}
