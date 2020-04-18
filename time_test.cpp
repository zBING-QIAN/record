#include<bits/stdc++.h>
using namespace std;

/*  測試map的時間消耗  */


int main(){
	
	map<int,int> tree;
	for(int i=0;i<500000;i++){
		tree[rand()] = rand();tree[rand()] = rand();
		tree.find(rand());
	}
	clock_t start = clock();
	for(int i=0;i<10;i++){
		int k=0;map<int,int>::iterator it = tree.begin();
		for(;it!=tree.end();)it++;
	}
	clock_t end = clock();
	cout<<(double(end)-double(start))/CLOCKS_PER_SEC;


	return 0;

}