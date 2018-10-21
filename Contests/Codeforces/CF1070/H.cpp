#include<bits/stdc++.h>
using namespace std;

const int maxN=101000;
const int inf=2147483647;

class Trie
{
public:
	int ch[40];
	int lst,cnt;
};

int n;
char Input[maxN][10],str[maxN];
int Mp[200];
int nodecnt=1,root=1;
Trie T[maxN*8];

void Insert(char *S,int l,int r,int id);

int main(){
	for (int i='a';i<='z';i++) Mp[i]=i-'a';
	for (int i='0';i<='9';i++) Mp[i]=i-'0'+26;
	Mp['.']=26+10;
	scanf("%d",&n);
	for (int i=1;i<=n;i++){
		scanf("%s",Input[i]+1);
		int len=strlen(Input[i]+1);
		for (int j=1;j<=len;j++) Insert(Input[i],j,len,i);
	}
	int Q;scanf("%d",&Q);
	while (Q--){
		scanf("%s",str+1);
		int len=strlen(str+1);
		int now=1;
		for (int i=1;i<=len;i++) now=T[now].ch[Mp[str[i]]];
		if (now==0) printf("0 -\n");
		else printf("%d %s\n",T[now].cnt,Input[T[now].lst]+1);
	}
	return 0;
}

void Insert(char *S,int l,int r,int id){
	int now=1;
	for (int i=l;i<=r;i++){
		if (T[now].ch[Mp[S[i]]]==0) T[now].ch[Mp[S[i]]]=++nodecnt;
		now=T[now].ch[Mp[S[i]]];
		if (T[now].lst!=id) T[now].lst=id,T[now].cnt++;
	}
	return;
}
