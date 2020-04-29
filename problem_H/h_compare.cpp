#include<bits/stdc++.h> 
using namespace std;
int main(int argc,char* argv[]){
	ifstream ans(argv[1]),test(argv[2]);
	int a,b,cnt=1;bool good = true;
	while(ans&&test){
		ans>>a;test>>b;
		if(a!=b){cout<<cnt <<"  "; good =false;}
		cnt++;
	}
	if(good)cout<<"good game\n";
	return 0;
}