#include<bits/stdc++.h>
using namespace std;

int main(){
    int cas=0;
    while (1){
	system("./gen >in && ./L >o1 && ./brute >o2");
	FILE *f1=fopen("o1","r"),*f2=fopen("o2","r");
	double a1,a2;
	while (fscanf(f1,"%lf",&a1)!=EOF){
	    fscanf(f2,"%lf",&a2);
	    if (fabs(a1-a2)>1e-5){
		cout<<"Wrong"<<endl;return 0;
	    }
	}
	fclose(f1);fclose(f2);
	cout<<"OK "<<++cas<<endl;
    }
    return 0;
}
