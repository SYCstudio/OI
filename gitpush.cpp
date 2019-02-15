#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;

int main(){
	string message;getline(cin,message);
	chdir("./OI");
	system("ls");
	system("git add *");
	system(("git commit -m \""+message+"\"").c_str());
	system("git push origin master");
	chdir("../文档/vnote_notebooks/");
	system("ls");
	system("git add *");
	system(("git commit -m \""+message+"\"").c_str());
	system("git push origin master");
	return 0;
}
