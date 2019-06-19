#include<bits/stdc++.h>
using namespace std;

const int maxN=3030000;

int n,Nxt[maxN];
char S[maxN];

int equal(int pos,int len);
int main(){
    scanf("%s",S+1);n=strlen(S+1);

    Nxt[1]=n;int pos=2,p=0;
    while (p+2<=n&&S[p+2]==S[p+1]) ++p;
    Nxt[2]=p;

    for (int i=3;i<=n;i++){
	int len=Nxt[i-pos+1];
	if (i+len<p) Nxt[i]=len;
	else{
	    int j=max(0,p-i);
	    while (i+j<=n&&S[i+j]==S[1+j]) ++j;
	    p=i+(Nxt[pos=i]=j)-1;
	}
    }

    //for (int i=1;i<=n;i++) cout<<Nxt[i]<<" ";cout<<endl;

    vector<int> f;
    for (int i=1;i<=n;i++){
	vector<int> g;f.push_back(i);
	for (int j=0;j<f.size();j++){
	    int q=f[j];
	    while (!g.empty()&&S[i]<S[g.back()+i-q]) g.pop_back();
	    if (g.empty()||(S[i]==S[g.back()+i-q]&&i-q+1<=q-g.back()))
		g.push_back(q);
	}
	f=g;
	int ans=f[0];
	for (int j=1;j<f.size();j++){
	    int q=f[j],e=equal(i-q+ans+1,q-ans);
	    if (e==1) ans=q;
	    else if (e==0&&equal(q-ans+1,ans-1)==-1) ans=q;
	}
	//for (int j=0;j<f.size();j++) cout<<f[j]<<" ";cout<<endl;
	//printf("ans %d = %d ",i,ans);
	printf("%d ",ans);
    }

    return 0;
}
int equal(int pos,int len){
    if (Nxt[pos]>=len) return 0;
    if (S[pos+Nxt[pos]]<S[1+Nxt[pos]]) return -1;
    return 1;
}
