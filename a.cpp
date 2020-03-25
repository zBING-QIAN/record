#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<set>
#include<vector>
using namespace std;
struct obj{
	int id,p,h;
	bool operator<(const obj& T)const{
		return this->h<T.h;
	}
	
}mlist[600000],jlist[600000];
bool compp(const obj &a,const obj &b){
	return a.p<b.p;
}
multiset<obj> treem,treej;
vector<int> ansm,ansj;

bool process(multiset<obj> &t1,multiset<obj> &t2){
	if(t1.size()>=t2.size()){
		while(!t2.empty()){
			multiset<obj>::iterator it2 = t2.begin();
			multiset<obj>::iterator it1 = t1.upper_bound(*it2);
			if(it1==t1.end())return false;
			ansm.push_back(it1->id);ansj.push_back(it2->id);
			t2.erase(it2);t1.erase(it1);
		}
	}
	else{
		while(!t1.empty()){
			multiset<obj>::iterator it1 = t1.begin();
			multiset<obj>::iterator it2 = t2.lower_bound(*it1);
			if(it2==t2.begin())return false;
			it2--;
			ansm.push_back(it1->id);ansj.push_back(it2->id);
			t2.erase(it2);t1.erase(it1);
		}
	}
	return true;
}

int main(){
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		mlist[i].id=i;
		jlist[i].id=i;
	}
	for(int i=0;i<n;i++){
		scanf("%d",&mlist[i].p);
	}
	for(int i=0;i<n;i++){
		scanf("%d",&mlist[i].h);
	}
	for(int i=0;i<n;i++){
		scanf("%d",&jlist[i].p);
	}
	for(int i=0;i<n;i++){
		scanf("%d",&jlist[i].h);
	}
	sort(mlist,mlist+n,compp);
	sort(jlist,jlist+n,compp);
	mlist[n].p=-1;
	jlist[n].p=-1;
	/*
	sort(mlist,mlist+n,[](const obj& a,const obj& b){return a.p<b.p;});
	sort(jlist,jlist+n,[](const obj& a,const obj& b){return a.p<b.p;});
	*/
/*
for(int i=0;i<n+1;i++)cout<<mlist[i].p<<" ";
cout<<"\n";
for(int i=0;i<n+1;i++)cout<<jlist[i].p<<" ";
cout<<"\n";
*/
	int flag = 0;
	for (int s=0,t=0;s<n;s++){
		treem.insert(mlist[s]);
		if(mlist[s].p!=mlist[s+1].p){
			while(!treem.empty()){
				if(treej.empty()){
					for(;t<n;t++){
						treej.insert(jlist[t]);
						if(jlist[t].p!=jlist[t+1].p)break;
					}
					t++;
				}
				if (!process(treem,treej)){
					cout<<"impossible\n";
					return 0;
				}
			}
			
		}
		
	}
	
	
	for(int i=0;i<n;i++){
		printf("%d ",ansm[i]+1);
	}
	printf("\n");
	for(int i=0;i<n;i++){
		printf("%d ",ansj[i]+1);
	}
	printf("\n");
	return 0;
}