#include <bits/stdc++.h>

using namespace std;

vector<int> v[2000000];

int main() {
	int a,b,c;
	while(scanf("%d,%d,%d",&a,&b,&c)>0){
		v[b].push_back(c);
	}
	double maxsd=0;
	int maxid = 0;
	for(int i = 0 ; i < 2000000 ; ++ i ) {
		if(v[i].size()>=10) {
			double sum = 0 ;
			for(auto x : v[i]) sum+=x;
			sum/=v[i].size();
			double rmq = 0;
			for(auto x : v[i]) {
				rmq+= (x-sum)*(x-sum);
			}
			rmq/=(v[i].size());
			rmq=sqrt(rmq);	
			if(rmq>maxsd) {
				maxsd=rmq;
				maxid=i;
			}
		}
	}
	cout << maxid << endl << maxsd << endl;
	return 0;
}
