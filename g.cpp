#include<bits/stdc++.h>
using namespace std;
#define MAXN 1000006
vector<char> arr;
vector<int> link,to,root;
vector<int> ans;
struct AC{
	int tr[MAXN][26],fp[MAXN],id[MAXN],count[MAXN],cnt,id_c;
	vector<int> q;
	AC(){
		memset(fp,0,sizeof(fp));
		memset(count,0,sizeof(count));
		memset(id,0,sizeof(id));
		id_c = cnt=1;
		for(int i=0;i<MAXN;i++)memset(tr[i],0,sizeof(tr[i]));
	}
	int insert(string &s){
		int len = s.length(),now = 0;
		for(int i=len-1;i>=0;i--){
			if(!tr[now][s[i]-'A']){
				tr[now][s[i]-'A']=cnt++;
			}
			if(!id[now])id[now] = 0;
			now = tr[now][s[i]-'A'];
		}
		id[now] = id_c++;
		return now;
	}
	void build(){
		for(int i=0;i<26;i++){if(tr[0][i])q.push_back(tr[0][i]);}
		int now ,flag = 0;
		while(q.size()>flag){
			now = q[flag];
			for(int i=0;i<26;i++){
				if(tr[now][i])fp[tr[now][i]]=tr[fp[now]][i],q.push_back(tr[now][i]);
				else tr[now][i] = tr[fp[now]][i];
			}flag++;
		}
	}
	
	void dfs(int pos,int now){
		count[now]++;
		int go = root[pos],v;
		while(go){
			v = arr[to[go]];
			dfs(to[go],tr[now][v-'A']);
			go = link[go];
		}
	}
	void bfs(){   //from end to start
		while(q.size()){
			if(fp[q.back()]){
				count[fp[q.back()]]+=count[q.back()];
			}
			q.pop_back();
		}
	}
};



int main(){
	int m,n,p;
	char c;
	cin>>m>>n;
	ans.reserve(m+5);
	arr.reserve(m+5);link.reserve(m+5);to.reserve(m+5);root.resize(m+5,0);
	arr.push_back(0);link.push_back(0);to.push_back(0);
	for(int i=1;i<=m;i++){
		cin>>c>>p;
		arr.push_back(c);link.push_back(root[p]);to.push_back(i);root[p]=i;
	}
	string stmp;
	vector<string> list;
	AC trie = AC();
	for(int i=0;i<n;i++){
		cin>>stmp;
		list.push_back(stmp);
		ans.push_back(trie.insert(stmp));
	}
	trie.build();
	trie.dfs(1,trie.tr[0][arr[1]-'A']);
	trie.bfs();
	for(int i=0;i<n;i++)cout<<trie.count[ans[i]]<<endl;
	return 0;
}