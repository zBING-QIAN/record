#include<bits/stdc++.h>
using namespace std;

int main(){
	int n,k;
	cin>>n>>k;
	vector<int> to(n+1),ans(n+1,0);
	vector<bool>pass(n+1,false);
	for(int i=0;i<n;i++){
		cin>>to[i+1];
	}
	
	for(int i=1;i<=n;i++){
		int now = i;
		ans[now]++;
		pass[now]=true;
		for(int j=0;j<k;j++){
			now = to[now];
			if(pass[now])break;
			ans[now]++;pass[now]=true;
		}
		now=i;pass[now]=false;
		for(int j=0;j<k;j++){
			now = to[now];
			if(pass[now])pass[now]=false;
			else break;
		}
	}
	
	for(int i=1;i<=n;i++)cout<<ans[i]<<endl;
	
	return 0;
}