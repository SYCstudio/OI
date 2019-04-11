#include<bits/stdc++.h>
using namespace std;

const int maxN=502000;
const int inf=2000000000;

int n,m;
char S[maxN],T[maxN];
int Ans;
pair<int,int> Opr[maxN];

void Work(char x,char y);
int main(){
    scanf("%s",S+1);scanf("%s",T+1);
    n=strlen(S+1);m=strlen(T+1);Ans=inf;
    Work('a','b');Work('b','a');
    printf("%d\n",Ans);for (int i=1;i<=Ans;i++) printf("%d %d\n",Opr[i].first,Opr[i].second);
    return 0;
}
void Work(char x,char y){
    static int cnt;static pair<int,int> O[maxN];
    cnt=0;
    int p1=1,p2=1,opt=0;
    while (p1<=n&&S[p1]==x) ++p1;while (p2<=m&&T[p2]==y) ++p2;
    while (p1<=n||p2<=m){
	if (opt==0){
	    O[++cnt]=make_pair(p1-1,p2-1);
	    opt^=1;
	    while (p1<=n&&S[p1]==y) ++p1;while (p2<=m&&T[p2]==x) ++p2;
	}
	else{
	    O[++cnt]=make_pair(p2-1,p1-1);
	    opt^=1;
	    while (p1<=n&&S[p1]==x) ++p1;while (p2<=m&&T[p2]==y) ++p2;
	}
    }
    if (cnt<=Ans){
	Ans=cnt;for (int i=1;i<=Ans;i++) Opr[i]=O[i];
    }
    return;
}
