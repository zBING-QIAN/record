#include<bits/stdc++.h>
using namespace std;
// . = 1000 , - = 2000


int oboard[64],fboard[64],bw[2],*op[8],*fp[8];
inline int fx(int i){return (i-1)/4;}
inline int fy(int i){return 2*((i-1)%4)+1-((i-1)%8)/4;}
inline int remap(int i){
	return fx(i)*8+fy[i];
}
inline int mid(int p1,int p2){
	if(p1>p2)swap(p1,p2);
	if(p2-p1==9){
		return (((p2-1)/4)%2==1)?p2-5:p2-4;
	}
	else{
		return (((p2-1)/4)%2==1)?p2-4:p2-3;
	}
}
vector<char> chesslist;
void process(char *s,int time){
	int len = strlen(s);
	bool isjump = true;
	vector<int> plist;plist.push_back(0);
	for(int i=0;i<len;i++){
		if(s[i]=='x'){
			plist.push_back(0);
		}
		else if(s[i]=='-'){
			plist.push_back(0);
			isjump=false;
		}
		else{
			plist.back()= plist.back()*10+s[i]-'0';
		}
	}
	int pos1 = remap(plist[0]);
	if(fboard[pos1]==1000){
		if(oboard[pos1]==1000){
			//jump point check!!
			oboard[pos1]=chesslist.size();
			chesslist.push_back(bw[time%2]);
		}
		else cerr<<"error occur!";
		fboard[pos1]=oboard[pos1];
	}
	if(isjump){
		
		for(int i=0;i<plist.size()-1;i++){
			
		}
		
	}
	else{
		int pos2 = remap(plist[1]);	
		if(fboard[pos2]==1000){
			fboard[pos2]=fboard[pos1];
			fboard[pos1]=1000;
		}
		else cerr<<"error occur!";
		if(pos1>pos2&&chesslist[fboard[pos2]]=='b')chesslist[fboard[pos2]]='B';
		else if(pos2>pos1&&chesslist[fboard[pos2]]=='w')chesslist[fboard[pos2]]='W';
	}
}
int main(){
	int n;
	for(int i=0;i<8;i++){
		op[i]=&oboard[i*8];
		for(int j=0;j<8;j++){
			op[i][j]=((j+i)%2==0)?2000:1000;
		}
		fp[i]=&fboard[i*8];
		for(int j=0;j<8;j++){
			fp[i][j]=((j+i)%2==0)?2000:1000;
		}
	}
	cin>>bw[0]>>n;
	if(bw[0]=='W'){
		bw[1]='b';
		bw[0]='w';
	}
	else{
		bw[0]='b';
		bw[1]='w';
	}
	char s[1000];
	for(int i=0;i<n;i++){
		cin>>s;
		process(s,i)
	}
	
	return 0;
}