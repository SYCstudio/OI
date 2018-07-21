#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

int main()
{
	int cas=0;
	do
	{
		system("./gen");system("./zsy <in.in >zsy.out");system("./BZOJ4755.exe <in.in >my.out");
		if (system("diff zsy.out my.out"))
		{
			cout<<"Wrong"<<endl;
			break;
		}
		cout<<"Correct "<<++cas<<endl;
	}
	while (1);
	return 0;
}
