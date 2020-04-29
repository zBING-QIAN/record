#include<bits/stdc++.h>
using namespace std;

int main(){
	srand(time(NULL));
	int n = rand()%1000,k = rand()%n;
	cout<<n<<" "<<k<<endl;
	for(int i=1;i<=n;i++){
		int tmp = rand()%n;
		if(tmp==n)tmp++;
		cout<<tmp<<" ";
	}
	return 0;
}