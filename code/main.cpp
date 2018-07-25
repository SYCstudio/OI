#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

int main()
{
	int cas=0;
	do
	{
		system("./gen");
		system("./HDU5030.exe <in.in >1.out");
		system("./std <in.in >2.out");
		if (system("diff 1.out 2.out")){
			cout<<"Wrong"<<endl;break;
		}
		cout<<"OK "<<++cas<<endl;
	}
	while (1);
	return 0;
}
