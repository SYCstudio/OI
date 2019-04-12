#include<bits/stdc++.h>
using namespace std;

#define pw(x) (1<<(x))
const int maxN=22;
const int inf=2000000000;

int n,P;
int Srt[maxN],Len[maxN],Nt[maxN];
int Is[maxN],It[maxN];
int F[pw(maxN)+10],From[pw(maxN)+10];
pair<int,int> Ans[maxN];

bool cmps(int a,int b);
bool cmpt(int a,int b);
int main(){
    scanf("%d%d",&n,&P);int N=1<<n;for (int i=1;i<N;i++) F[i]=inf;
    F[0]=1;
    for (int i=0;i<n;i++) scanf("%d%d%d",&Srt[i],&Len[i],&Nt[i]),Is[i]=It[i]=i;
    sort(&Is[0],&Is[n],cmps);sort(&It[0],&It[n],cmpt);
    for (int S=0;S<N;S++){
	if (F[S]==inf) continue;
	int lip=0,limt=F[S],above=0;
	//cout<<"S:"<<S<<" "<<F[S]<<endl;
	for (int i=0;i<n;i++)
	    if (!(S&pw(It[i]))){
		//cout<<limt+Nt[It[i]]<<" "<<Srt[Is[lip]]<<endl;
		while (lip<n&&limt+Nt[It[i]]>=Srt[Is[lip]]){
		    //cout<<"Arr:"<<Is[lip]<<endl;
		    if (!(S&pw(Is[lip]))) if (limt>=Srt[Is[lip]]&&limt<Srt[Is[lip]]+Len[Is[lip]]) limt=Srt[Is[lip]]+Len[Is[lip]];else;
		    else limt=max(limt,Srt[Is[lip]]+Len[Is[lip]]);
		    above|=pw(Is[lip]);++lip;
		}
		//cout<<"fail at:"<<(above&pw(It[i]))<<" "<<(limt+Nt[It[i]]>=Srt[It[i]])<<endl;
		if ((above&pw(It[i]))||(limt+Nt[It[i]]>=Srt[It[i]])) continue;
		if (F[S|pw(It[i])]>limt+Nt[It[i]]) F[S|pw(It[i])]=limt+Nt[It[i]],From[S|pw(It[i])]=It[i];
	    }
    }
    if (P==1){
	if (F[N-1]==inf) puts("NO");
	else{
	    int S=N-1;while (S) Ans[From[S]].second=F[S]-Nt[From[S]],S^=pw(From[S]);
	    puts("YES");
	    for (int i=0;i<n;i++) printf("1 %d\n",Ans[i].second);
	}
    }
    else{
	for (int S=0;S<N;S++)
	    if (F[S]!=inf&&F[S^(N-1)]!=inf){
		int T=S;while (T) Ans[From[T]]=make_pair(1,F[T]-Nt[From[T]]),T^=pw(From[T]);
		T=S^(N-1);while (T) Ans[From[T]]=make_pair(2,F[T]-Nt[From[T]]),T^=pw(From[T]);
		puts("YES");
		for (int i=0;i<n;i++) printf("%d %d\n",Ans[i].first,Ans[i].second);
		return 0;
	    }
	puts("NO");
    }
    return 0;
}
bool cmps(int a,int b){
    return Srt[a]<Srt[b];
}
bool cmpt(int a,int b){
    return Nt[a]<Nt[b];
}
