
#include<bits/stdc++.h>
using namespace std;

int main(){
	int n,ans=0,maxans=0;
	vector<int> num,sign,remap(1000005,0),s(1000005,0),e(1000005,0);
	
	char mark[100];
	cin>>n;
	int index = n-1;
	for(int i=0;i<n;i++){
		scanf("%s",mark);
		sign.push_back((mark[0]=='s')?0:1);
		num.push_back(0);
		for(int j=1;j<strlen(mark);j++){
			num.back()=num.back()*10+mark[j]-'0';
		}
		remap[num.back()]=1;
	}
	for(int i=0;i<n;i++){
		if(sign[i]==0){			
			s[num[i]]++;
		}else{
			if(s[num[i]]>0)s[num[i]]--;
			else e[num[i]]++;
		}
	}
	for(int i=0;i<1000001;i++){
		if(remap[i]==1&&s[i]-e[i]!=0)remap[i]=0;
		else if(remap[i]==1&&s[i]==0&&e[i]==0)ans++;
	}
	maxans=ans;
	for(int i=0;i<n;i++){
		if(remap[num[i]]==1){
			if(sign[i]==1){
				s[num[i]]--;e[num[i]]--;
				if(s[num[i]]==0&&e[num[i]]==0)ans++;
			}
			else{
				if(s[num[i]]==0&&e[num[i]]==0)ans--;
				s[num[i]]++;e[num[i]]++;
			}
		}
		if(maxans<ans){
			maxans=ans;
			index=i;
		}
	}
	cout<<(index+1)%n+1<<" "<<maxans;
	return 0;
}