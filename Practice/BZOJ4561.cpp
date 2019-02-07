#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<set>
using namespace std;

typedef long long ll;
#define sqr(x) (x)*(x)
class Data{
public:
    int x,l,r,id;
};
class SetData{
public:
    int p,id;
};
const int maxN=202000*2;

int n;
Data D[maxN];
set<SetData> S;
int Dep[maxN],R[maxN];

bool dcmp(Data A,Data B);
bool operator < (SetData A,SetData B);

int main(){
    scanf("%d",&n);
    for (int i=1;i<=n;i++){
        int x,y,r;scanf("%d%d%d",&x,&y,&r);R[i]=r;
        D[i]=((Data){x-r,y-r,y+r,i});
        D[i+n]=((Data){x+r,y-r,y+r,-i});
    }
    sort(&D[1],&D[n+n+1],dcmp);
    for (int i=1;i<=n;i++)
        if (D[i].id>0){
            set<SetData>::iterator p1,p2;
            p1=S.lower_bound((SetData){})
        }
        else{
        }
}