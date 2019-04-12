#include<bits/stdc++.h>
using namespace std;

const int maxN=505000;

char In[maxN];
vector<pair<int,int> > A,B,Ans;

void Init(char *S,vector<pair<int,int> > &V);
void PushBack(vector<pair<int,int> > &V,pair<int,int> p);
void Exge(int l);
int main(){
    scanf("%s",In+1);Init(In,A);scanf("%s",In+1);Init(In,B);
    int swp=0;if (A.size()>B.size()) swap(A,B),swp=1;

    if (A.back().first==B.back().first){
	if ((B.size()-A.size())%4==3) Exge((B.size()-A.size()+1)/4*2);
	int l=(B.size()-A.size())/4*2+1;A.push_back(make_pair(B[B.size()-l-1].first,0));
	Exge(l);
    }
    else if (B.size()-A.size()>2) Exge((B.size()-A.size()+1)/4*2+1);

    while (A.size()>1||B.size()>1) Exge(1);
    printf("%d\n",(int)Ans.size());
    for (int i=0,sz=Ans.size();i<sz;i++)
	swp?printf("%d %d\n",Ans[i].second,Ans[i].first):printf("%d %d\n",Ans[i].first,Ans[i].second);
    return 0;
}
void Init(char *S,vector<pair<int,int> > &V){
    for (int i=strlen(S+1);i>=1;i--) PushBack(V,make_pair(S[i],1));return;
}
void PushBack(vector<pair<int,int> > &V,pair<int,int> p){
    if (V.empty()||V.back().first!=p.first) V.push_back(p);else V.back().second+=p.second;
    return;
}
void Exge(int l){
    int tl=0;pair<int,int> la=A.back();A.pop_back();
    for (int i=l,bsz=B.size();i>=1;i--) PushBack(A,B[bsz-i]),tl+=B[bsz-i].second;
    Ans.push_back(make_pair(la.second,tl));
    for (int i=1;i<=l;i++) B.pop_back();PushBack(B,la);
    return;
}
