#include<bits/stdc++.h>
using namespace std;
#define MAXN 10000000

struct tarp{
	static int x;
	int x1,x2,y1,y2,id;
	tarp(int X1,int X2,int Y1,int Y2){
		if(X1>X2){
			x1=X2;y1=Y2;
			x2=X1;y2=Y1;
		}else{
			x1=X1;y1=Y1;
			x2=X2;y2=Y2;
		}
	}
	double h_in_x()const{
		return double(y1)+(double(x-x1)/double(x2-x1))*double(y2-y1);
	}
	bool operator< (const tarp& T)const{
		return this->h_in_x()>T.h_in_x();
	}
};
int tarp::x = 0;
bool cmp(const tarp& t1,const tarp &t2){
	return t1.x1<t2.x1;
}
bool cmph(const pair<int,int>& a,const pair<int,int> &b){
	return a>b;
}
struct link{
	int next,to;
	link(int n,int t){next=n;to=t;}
};

struct node{
	int first;
	bool second;
	map<int,node>::iterator n,p;
	node(){first=(1<<30),second=0;}
	node(int f,bool s){first=f,second=s;}
};


struct line_tree{
	map<int,node> neg_tree,pos_tree;
	int base = (1<<30),left,right,d_l,d_r;
	line_tree(int l,int r){
		left=l;right=r;d_l=l,d_r=r;
		neg_tree[l]=node(-base,0);pos_tree[r]=node(base,0);
		neg_tree[(1<<30)]=node(0,0);pos_tree[(1<<30)+1]=node(0,0);
		neg_tree[-2]=node(0,0);pos_tree[-1]=node(0,0);
		map<int,node>::iterator it_n=neg_tree.begin();
		map<int,node>::iterator it_p=pos_tree.begin();
		for(;it_n!=neg_tree.end()&&it_p!=pos_tree.end();){
			if(it_n->first>it_p->first){
				it_n->second.p = it_p;it_p->second.n = it_n;
				it_p++;
			}else {
				it_p->second.p = it_n;it_n->second.n = it_p;
				it_n++;
			}
		}
		
	}
	int find_min(){
		int now=base,ans=base;
		map<int,node>::iterator it=neg_tree.begin();
		for(;it->first<=right;it=it->second.n){
			if(it->first>=left){
				ans=(ans>now)?now:ans;
			}
			now += it->second.first;
		}
		if(it->first>right){
				ans=(ans>now)?now:ans;
		}
		return ans;
	}
	
	void process_tarp(tarp &T){
		if(T.y1<T.y2){   //minus
			map<int,node> ::iterator it_n,it_p,it;
			int min_val,now;node tmp ;
			it_n=  neg_tree.upper_bound(T.x2);
			it_p= pos_tree.upper_bound(T.x2);
			it = ((it_n->first<it_p->first)||(it_n->first==it_p->first&&it_p->second.second))?it_n:it_p;
			tmp = node(-1,0);tmp.n = it;tmp.p = it->second.p;
			neg_tree[T.x2]=tmp;it_n--;
			it_n->second.p->second.n=it_n;it_n->second.n->second.p=it_n;
			it = --it_n;
			now =0;
			while(it->first>T.x1){
				if(now+it->second.first>0){it->second.first+=now;now=0;it = it_n;}
				else{
					now+=(it->second.first);
					it_p=it;it=it->second.p;
					it_p->second.p->second.n=it_p->second.n;
					it_p->second.n->second.p=it_p->second.p;
					if(it_p->second.first<0){
						it_n--;neg_tree.erase(it_p);
					}else {
						pos_tree.erase(it_p);
					}
				}
			}
			it_n=  neg_tree.upper_bound(T.x1);
			it_p= pos_tree.upper_bound(T.x1);
			it = ((it_n->first<it_p->first)||(it_n->first==it_p->first&&it_p->second.second))?it_n:it_p;
			tmp = node(1,1);tmp.n = it;tmp.p = it->second.p;
			pos_tree[T.x1]=tmp;it_p--;
			it_p->second.p->second.n=it_p;it_p->second.n->second.p=it_p;
			if(now<0){
				tmp = node(now,0);tmp.n = it_p;tmp.p = it_p->second.p;
				neg_tree[T.x1]=tmp;it_n--;
				it_n->second.p->second.n=it_n;it_n->second.n->second.p=it_n;
			}
		}
		else {    //add
			map<int,node> ::iterator it_n,it_p,it;
			int min_val,now;node tmp ;
			it_n=  neg_tree.upper_bound(T.x1);
			it_p= pos_tree.upper_bound(T.x1);
			it = ((it_n->first<it_p->first)||(it_n->first==it_p->first&&it_p->second.second))?it_n:it_p;
			tmp = node(1,0);tmp.n = it;tmp.p = it->second.p;
			pos_tree[T.x1]=tmp;it_p--;                                   
			it_p->second.p->second.n=it_p;it_p->second.n->second.p=it_p;
			it = ++it_p;
			now =0;
			while(it->first<T.x2){
				if(now+it->second.first<0){it->second.first+=now;now=0;it = it_p;}
				else{
					now+=(it->second.first);
					it_n=it;it=it->second.n;
					it_n->second.p->second.n=it_n->second.n;
					it_n->second.n->second.p=it_n->second.p;
					if(it_n->second.first>0){
						it_p++;pos_tree.erase(it_n);
					}else {
						neg_tree.erase(it_n);
					}
				}
			}
			it_n=  neg_tree.upper_bound(T.x2);
			it_p= pos_tree.upper_bound(T.x2);
			it = ((it_n->first<it_p->first)||(it_n->first==it_p->first&&it_p->second.second))?it_n:it_p;
			tmp = node(-1,0);tmp.n = it;tmp.p = it->second.p;
			neg_tree[T.x2]=tmp;it_n--;
			it_n->second.p->second.n=it_n;it_n->second.n->second.p=it_n;
			if(now>0){
				tmp = node(now,1);tmp.n = it_n->second.n;tmp.p = it_n;
				pos_tree[T.x2]=tmp;it_p--;
				it_p->second.p->second.n=it_p;it_p->second.n->second.p=it_p;
			}
		}
	}
	
};


int main(){
	int l,r,n,x1,x2,y1,y2;
	vector<tarp> list;
	cin>>l>>r>>n;
	if(n==0){cout<<0;return 0;}
	for(int i=0;i<n;i++){
		scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
		list.push_back(tarp(x1,x2,y1,y2));
	}
	sort(list.begin(),list.end(),cmp);
	for(int i=0;i<n;i++){list[i].id=i;}
	set<tarp> aux;
	vector<pair<int,int> > heap;
	int counter=0,flag=0x7FFFFFFF;
	vector<int> graph_record;graph_record.resize(n,-1);
	vector<int> is_root;is_root.resize(n,0);
	vector<link> graph_link;
	tarp::x=list[0].x1;
	
	clock_t start = clock();
	
	do{ 
		if(counter<n&&list[counter].x1<flag){
			tarp::x=list[counter].x1;
			heap.push_back(make_pair(list[counter].x2,counter));push_heap(heap.begin(),heap.end(),cmph);
			flag=heap.front().first;
			aux.insert(list[counter]);
			counter++;
		}
		while(heap.size()>0&&(counter>=n||list[counter].x1>flag)){
			tarp::x = heap.front().first;
			set<tarp>::iterator it = aux.upper_bound(list[heap.front().second]);
			
			if(it!=aux.end()){
				graph_link.push_back(link(graph_record[heap.front().second],it->id));
				graph_record[heap.front().second]=graph_link.size()-1;
				is_root[it->id]++;
			}
			it--;
			if(it!=aux.begin()){
				set<tarp>::iterator itp = it;itp--;
				is_root[it->id]++;
				graph_link.push_back(link(graph_record[(itp)->id],it->id));
				graph_record[(itp)->id]=graph_link.size()-1;
			}
			aux.erase(it);
			pop_heap(heap.begin(),heap.end(),cmph);heap.pop_back();
			if(heap.size()>0)flag=heap.front().first;
			else flag = 0x7FFFFFFF;
		}	
	
	}while(heap.size()>0||counter<n);
	
	

	vector<int> q;flag=0;
	for(int i=0;i<n;i++){
		if(is_root[i]==0){
			q.push_back(i);
		}
	}
	int nex;
	line_tree tree = line_tree(l,r);
	while(flag<q.size()){
		tree.process_tarp(list[q[flag]]);
		while(graph_record[q[flag]]!=-1){
			nex = graph_record[q[flag]];
			graph_record[q[flag]]=graph_link[nex].next;
			if(--(is_root[graph_link[nex].to])==0){
				q.push_back(graph_link[nex].to);
			}
		}
		/*clock_t end = clock();
		if(((double(end)-double(start))/CLOCKS_PER_SEC)>11)assert(flag>n/2);*/
		flag++;
	}
	cout<<tree.find_min();
	return 0;
}