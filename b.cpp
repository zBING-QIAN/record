#include<bits/stdc++.h>
using namespace std;
long long  a,b,n,h,x[10005],y[10005];
long long  dp[10005];
inline bool incircle(double cx,double cy,int p){
	double xp=double(x[p]),yp=double(y[p]),dh = double(h);
	return (cx-xp)*(cx-xp)+(cy-yp)*(cy-yp)<=(dh-cy)*(dh-cy);
}
bool ok(double cx,double cy,int rp,int lp){
	return (cy>=y[rp]||incircle(cx,cy,rp))&&(cy>=y[lp]||incircle(cx,cy,lp));
}
int main(){
	cin>>n>>h>>a>>b;
	for(int i=0;i<10005;i++)dp[i]=LLONG_MAX;
	for(int i=0;i<n;i++){
		cin>>x[i]>>y[i];
	}
	dp[0]=a*(h-y[0]);
	for(int i=1;i<n;i++){
		double leftp=x[i]-(h-y[i]),rightp=x[i];
		int lp=i,rp=i;
		for(int j=i-1;j>=0&&leftp<=rightp;j--){
			double cx = double(x[i]+x[j])/2.0,cy = double(h)-double(x[i]-x[j])/2.0;
			double tmp1 = double(x[i]+h-x[j]-y[j]),tmp2 = sqrt(double(2*(x[i]-x[j])*(h-y[j])));
			double r1 = double(tmp1+tmp2),r2=double(tmp1-tmp2);
			double x1 = double(x[i]-r1),x2 = double(x[i]-r2); 
			
			if(dp[j]!=LLONG_MAX&&h-y[j]>=h-cy){
				if(ok(cx,cy,rp,lp)){
				
					long long cost = a*(h-y[i])+
						b*(x[i]-x[j])*(x[i]-x[j]);
					if(dp[i]>cost+dp[j]){
						dp[i]=cost+dp[j];
					}
				}
			}
			if(x2<rightp&&y[j]+r2>=h){
				rightp = x2;
				rp=j;
			}
			if(x1>leftp){
				leftp=x1;
				lp=j;
			}
			
			
		}
	}
	if(dp[n-1]!=LLONG_MAX)cout<<dp[n-1];
	else cout<<"impossible";
	return 0;
}