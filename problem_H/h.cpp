#include<bits/stdc++.h>
using namespace std;
#define MAXN 500005
int n,k,dp[22][MAXN],to[22][MAXN];
vector<int> ans,pass,record,link,go,to_to;
vector<pair<int,int>> cut;
void deloop(int now){
	pass[now]=1;
	if(pass[to[0][now]]==0){
		deloop(to[0][now]);
	}
	else if(pass[to[0][now]]==1){
		cut.push_back(make_pair(now,to[0][now]));
		to[0][now]=0;
	}
	pass[now] = 2;
}



void run_loop(int now,int fin){
	to_to[now] = fin;
	now =fin;
	vector<int> seq;
	do{	
		seq.push_back(now);
		now = to_to[now];
	}while(fin!=now);
	int m = seq.size(),epoch=0,cnt=0,time=0,flag=1,dist;
	queue<int> main_q;
	for(int i=m-1,t=0;i>0;i--,t++){
		flag = main_q.size();
		for(int j=0;j<flag;j++){
			now = record[main_q.front()];main_q.pop();
			while(now){
				main_q.push(go[now]);
				now = link[now];
			}		
		}
		cnt += flag;
		dist = 0,flag = 1,time =0;
		queue<int> q;
		q.push(seq[i]);
		while(q.size()){
			now = record[q.front()];q.pop();
			while(now){
				if(go[now]!=seq[i-1]){
					q.push(go[now]);
				}
				now = link[now];
			}
			if(++time==flag){
				cnt += flag;flag = q.size();time = 0;
				if(dist == ((k>m-1)?k-m+1:0) )  break;
				dist++;
			}
		}
		for(int s = 0;s<flag;s++){main_q.push(q.front());q.pop();}
		if(k>m-1){
			if(m-2-t>=0)ans[seq[m-2-t]]+=cnt;
			else break;
		}
		else{
			if(k-1-t>=0)ans[seq[k-1-t]]+=cnt;
			else break;
		}
	}
}

void total_loop(int now){
	int des = now,m ;
	vector<int>seq;
	do{
		pass[now]=2;
		seq.push_back(now);
		now = to_to[now];
	}while(now!=des);
	m = seq.size();
	for(int i=0;i<m;i++){
		ans[seq[i]] = min(m,k+1);
	}
}

int main(){
	cin>>n>>k;
	pass.resize(n+1,0);
	ans.resize(n+1,0);record.resize(n+5,0);
	to_to.resize(n+1,0);
	link.push_back(0),go.push_back(0);
	dp[0][0]=0;
	for(int i=1;i<=n;i++){
		dp[0][i]=1;
		cin>>to[0][i];to_to[i] = to[0][i];
		link.push_back(record[to[0][i]]);go.push_back(i);
		record[to[0][i]]=i;
	}
	for(int i=1;i<=n;i++)if(record[i]==0)deloop(i);
	
	for(int t = 1;;t++){
		if((1<<t)>k){
			t--;
			int rang = k-(1<<t);
			for(int i=1;i<=n;i++){ans[i]=dp[t][i];}
			for(int h=t-1;;h--){
				if(rang==0){
					for(int i=1;i<=n;i++){
						if(to[t][i]){
							ans[to[t][i]]+=1;
						}
					}break;
				}
				if(rang-(1<<h)>=0){
					rang-=(1<<h);
					for(int i=1;i<=n;i++){
						if(to[t][i]){
							ans[to[t][i]]+=dp[h][i];
						}
						if(to[h][i]&&to[t][to[h][i]]){
							to[h][i]=to[t][to[h][i]];
						}else to[h][i]=0;
					}
					t=h;
				}
			}
			break;
		}
		for(int i=1;i<=n;i++){
			dp[t][i]=dp[t-1][i];
		}
		for(int i=1;i<=n;i++){
			if(to[t-1][i]){
				dp[t][to[t-1][i]]+=dp[t-1][i];
				to[t][i]=to[t-1][to[t-1][i]];
			}
			else to[t][i]=0;
		}
	}
	for(int i=1;i<=n;i++){
		if(pass[i]==0)total_loop(i);
	}
	for(int i=0;i<cut.size();i++){
		run_loop(cut[i].first,cut[i].second);
	}
	for(int i =1;i<=n;i++){
		cout<<ans[i]<<endl;
	}
	
	return 0;
}