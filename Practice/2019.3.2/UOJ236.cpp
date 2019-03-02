#include "railroad.h"
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

#define Dct(x) (lower_bound(&Num[1],&Num[num+1],x)-Num)
const int maxN=202000*2;
class Edge{
    public:
    int u,v;long long w;
};
int n,ufs[maxN],num,Num[maxN],Sm[maxN];
Edge E[maxN];

int find(int x);
bool cmp(Edge A,Edge B);
long long plan_roller_coaster(vector<int> S,vector<int> T){
    n=S.size();
    for (int i=0;i<n;i++) Num[++num]=S[i],Num[++num]=T[i];
    sort(&Num[1],&Num[num+1]);num=unique(&Num[1],&Num[num+1])-Num-1;
    for (int i=1;i<=num;i++) ufs[i]=i;
    for (int i=0;i<n;i++) S[i]=Dct(S[i]),T[i]=Dct(T[i]),--Sm[S[i]],++Sm[T[i]],ufs[find(S[i])]=find(T[i]);
    ++Sm[1];--Sm[num];ufs[find(1)]=find(num);
    for (int i=1;i<=num;i++) Sm[i]+=Sm[i-1];
    long long Ans=0;int ecnt=0;
    for (int i=1;i<num;i++){
        if (Sm[i]){
            if (Sm[i]<0) Ans=Ans+1ll*(Num[i+1]-Num[i])*(-Sm[i]);
            ufs[find(i)]=find(i+1);
        }
        E[++ecnt]=((Edge){i,i+1,Num[i+1]-Num[i]});
    }
    //for (int i=1;i<=num;i++) cout<<find(i)<<" ";cout<<endl;
    sort(&E[1],&E[ecnt+1],cmp);
    for (int i=1;i<=ecnt;i++) if (find(E[i].u)!=find(E[i].v)) Ans+=E[i].w,ufs[find(E[i].u)]=find(E[i].v);
    //for (int i=1;i<=ecnt;i++) cout<<find(i)<<" ";cout<<endl;
    return Ans;
}
int find(int x){
    if (ufs[x]!=x) ufs[x]=find(ufs[x]);
    return ufs[x];
}
bool cmp(Edge A,Edge B){
    return A.w<B.w;
}