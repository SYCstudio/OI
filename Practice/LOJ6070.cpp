#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=101000;
const int Alpha=26;

class PAM{
public:
    int son[Alpha],fail,len,diff,nxt;
};

int n,Q;
char Input[maxN];
int nodecnt=1,lst=1,Pos[maxN];
PAM P[maxN];
int dfncnt,dfn[maxN],lst[maxN];

void Extend(int pos,int c);

int main(){
    int type;scanf("%d",&type);
    scanf("%d%d",&n,&Q);scanf("%s",Input+1);
    
    P[0].fail=0;P[0].len=-1;P[1].len=0;P[1].fail=0;
    for (int i=1;i<=n;i++) Extend(i,Input[i]-'a');
}

void Extent(int pos,int c){
    while (Input[pos-P[lst].len+1]!=Input[pos]) 
}
