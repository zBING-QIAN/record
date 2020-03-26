#include<bits/stdc++.h>
using namespace std;
struct node{
	vector<int> to;
	int size;
};

int main(){
	int n,m,n1,n2;
	vector<node> list;
	cin>>n>>m;
	list.resize(n+5);
	for(int i=0;i<m;i++){
		cin>>n1>>n2;
		list[n1].to.push_back(n2);
		list[n2].to.push_back(n1);
	}
	vector<int> que;
	for(int i=1;i<=n;i++){
		list[i].size=list[i].to.size();
		if(list[i].size==1){
			que.push_back(i);
		}
	}
	int flag = 0;
	while(que.size()>flag){
		for(int i=0;i<list[que[flag]].to.size();i++){
			if(--(list[list[que[flag]].to[i]].size)==1)que.push_back(list[que[flag]].to[i]);
		}
		flag++;
	}
	vector<pair<int,int> > ans;
	flag=0;que.clear();
	for(int i=1;i<=n;i++){
		if(list[i].size==1){
			for(int j=0;j<list[i].to.size();j++){
				if(list[list[i].to[j]].size>0){
					ans.push_back(make_pair(list[i].to[j],i));
				}
				else{
					que.push_back(list[i].to[j]);
					list[list[i].to[j]].size=-1;
					while(que.size()>flag){
						for(int k=0;k<list[que[flag]].to.size();k++){
							if(list[list[que[flag]].to[k]].size==0){
								list[list[que[flag]].to[k]].size=-1;
								que.push_back(list[que[flag]].to[k]);
							}
						}
						flag++;
					}
				}
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(list[i].size==0&&list[i].to.size()==1){
			ans.push_back(make_pair(i,list[i].to[0]));
		}
	}
	sort(ans.begin(),ans.end());
	cout<<ans.size()<<endl;
	for(int i=0;i<ans.size();i++){
		cout<<ans[i].first<<" "<<ans[i].second<<endl;
	}
	return 0;
}