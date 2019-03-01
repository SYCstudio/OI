#include<bits/stdc++.h>
using namespace std;

int main(){
    int cas=0;
    while (1){
        system("./gen");system("./C <in >out");system("./sss <in >sout");
        if (system("diff out sout")){
            cout<<"Wrong"<<endl;break;
        }
        cout<<"OK "<<++cas<<endl;
    }
    return 0;
}