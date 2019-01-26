#include "combo.h"
#include<string>
#include<iostream>
using namespace std;

string C="ABXY";

string guess_sequence(int N){
	string Ans="",Q="";
	Q="AB";
	if (press(Q)){
		Q="A";
		if (press(Q)) ;
		else swap(C[0],C[1]);
	}
	else{
		Q="X";
		if (press(Q)) swap(C[0],C[2]);
		else swap(C[0],C[3]);
	}
	Ans=Ans+C[0];
	if (N==1) return Ans;
	//cout<<Ans<<endl;
	for (int i=2;i<N;i++){
		Q=Ans+C[1]+C[1]+Ans+C[1]+C[2]+Ans+C[1]+C[3]+Ans+C[2];
		//cout<<"Q:"<<Q<<endl;
		int r=press(Q);
		if (r==i-1) Ans=Ans+C[3];
		else if (r==i) Ans=Ans+C[2];
		else Ans=Ans+C[1];
		//cout<<"Ans:"<<Ans<<endl;
	}
	for (int i=1;i<3;i++){
		Q=Ans+C[i];
		if (press(Q)==N) return Ans+C[i];
	}
	return Ans+C[3];
}
