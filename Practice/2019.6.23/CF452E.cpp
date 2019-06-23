#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define ft first
#define sd second

const int maxN=303000*2;
const int maxAlpha=26;
const int Mod=1e9+7;

class SAM{
public:
    int son[maxAlpha],fail,len;
};

char A[maxN],B[maxN],C[maxN];
int lst=1,scnt=1;
SAM S[maxN];
vector<int> Pt[maxN];
int Ea[maxN],Eb[maxN],Ec[maxN];
vector<int> Pb[maxN],Pc[maxN];
int Ans[maxN];

void Extend(int c);
void dfs(int u);
int main(){
    scanf("%s",A+1);scanf("%s",B+1);scanf("%s",C+1);
    int la=strlen(A+1),lb=strlen(B+1),lc=strlen(C+1);

    for (int i=1;i<=la;i++) Extend(A[i]-'a'),++Ea[lst];
    for (int i=2;i<=scnt;i++) Pt[S[i].fail].pb(i);
    
    for (int i=1,now=1,len=0;i<=lb;i++){
	int c=B[i]-'a';
	while (now&&S[now].son[c]==0) now=S[now].fail,len=S[now].len;
	if (now==0){
	    now=1;len=0;continue;
	}
	now=S[now].son[c];++len;
	Pb[now].pb(len);
    }
    for (int i=1,now=1,len=0;i<=lc;i++){
	int c=C[i]-'a';
	while (now&&S[now].son[c]==0) now=S[now].fail,len=S[now].len;
	if (now==0){
	    now=1;len=0;continue;
	}
	now=S[now].son[c];++len;
	Pc[now].pb(len);
    }

    /*
    for (int i=1;i<=scnt;i++) for (int j=0;j<maxAlpha;j++) if (S[i].son[j]) cout<<i<<" "<<S[i].son[j]<<" "<<((char)(j+'a'))<<endl;
    for (int i=1;i<=scnt;i++) cout<<S[i].fail<<" "<<i<<endl;
    //*/

    dfs(1);

    for (int i=1;i<=min(la,min(lb,lc));i++) Ans[i]=(Ans[i]+Ans[i-1])%Mod;
    for (int i=1;i<=min(la,min(lb,lc));i++) printf("%d ",Ans[i]);
    
    return 0;
}
void Extend(int c){
    int np=++scnt,p=lst;lst=np;S[np].len=S[p].len+1;
    while (p&&S[p].son[c]==0) S[p].son[c]=np,p=S[p].fail;
    if (p==0) S[np].fail=1;
    else{
	int q=S[p].son[c];
	if (S[q].len==S[p].len+1) S[np].fail=q;
	else{
	    int nq=++scnt;S[nq]=S[q];S[nq].len=S[p].len+1;S[q].fail=S[np].fail=nq;
	    while (p&&S[p].son[c]==q) S[p].son[c]=nq,p=S[p].fail;
	}
    }
    return;
}
void dfs(int u){
    for (int i=0;i<Pt[u].size();i++){
	int v=Pt[u][i];dfs(v);
	Ea[u]+=Ea[v];Eb[u]+=Eb[v];Ec[u]+=Ec[v];
    }
    sort(Pb[u].begin(),Pb[u].end());sort(Pc[u].begin(),Pc[u].end());
    //cout<<"u:"<<u<<endl;
    //for (int i=0;i<Pb[u].size();i++) cout<<Pb[u][i]<<" ";cout<<endl;
    //for (int i=0;i<Pc[u].size();i++) cout<<Pc[u][i]<<" ";cout<<endl;
    int sb=Pb[u].size()-1,sc=Pc[u].size()-1;
    int lst=S[u].len;
    while (sb>=0||sc>=0){
	int mx=0;
	if (sb>=0) mx=max(mx,Pb[u][sb]);
	if (sc>=0) mx=max(mx,Pc[u][sc]);
	
	int plus=1ll*Ea[u]*Eb[u]*Ec[u]%Mod;
	Ans[mx+1]=(Ans[mx+1]+plus)%Mod;
	Ans[lst+1]=(Ans[lst+1]-plus+Mod)%Mod;
	
	while (sb>=0&&Pb[u][sb]==mx) ++Eb[u],--sb;
	while (sc>=0&&Pc[u][sc]==mx) ++Ec[u],--sc;
	lst=mx;
    }

    int falen=S[S[u].fail].len,plus=1ll*Ea[u]*Eb[u]%Mod*Ec[u]%Mod;
    Ans[falen+1]=(Ans[falen+1]+plus)%Mod;
    Ans[lst+1]=(Ans[lst+1]-plus+Mod)%Mod;
    return;
}
