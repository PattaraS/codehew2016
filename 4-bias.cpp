#include <bits/stdc++.h>

using namespace std;

map<int,int> users;
vector<int> reviews[3000000];
char buff[101000];
map<int,bool> isFake;
int main() {
	FILE *f = fopen("users.csv","r");
	int a,b;
	while(fscanf(f,"%d,%d",&a,&b)>0) {
		users[a]=b;
	}

	for(auto x : users ) {
		cout << x.first << " " << x.second << endl;
	}
	
	FILE *f2 = fopen("reviews.csv","r");
	int c;
	while(fscanf(f2,"%d,%d,%d,%[^\r]\n",&a,&b,&c,buff) > 0) {
		int len = strlen(buff);
		reviews[b].push_back(a);
		if(c==5 && users[b] < 100 && strlen(buff) <= 100 ) {isFake[a]=true;
		cout << a << " " << b << " " << c << " " << string(buff) << endl;
		cout << "\n\n\n\n\n\n\n\__________________\n\n\n\n\n\n\n\n\n" ;
		}
	}
	vector<int> ans;
	for(int i = 0 ; i < 3000000 ; ++ i ) {
		if(reviews[i].size()) {
			sort(reviews[i].begin(),reviews[i].end());
			if(isFake[reviews[i][0]]) {
				ans.push_back(reviews[i][0]);
			}
		}
	}
	sort(ans.begin(),ans.end());
	for(auto x : ans ) {
		cout << x << endl;
	}
	return 0;
}
