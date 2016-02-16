#include <bits/stdc++.h>

using namespace std;

map<string,string> mp;

int main() {

	mp["ควย"]="#]!";
	mp["เหี้ย"]="#]!(&";
	mp["ห้วดอ"]="#]!(&";
	mp["หมาไม่แดก"]="#]!(&@%?#";
	mp["ส้นตีน"]="#]!(&@";
	mp["อีโง่"]="#]!(&";
	mp["ไอ้โง่"]="#]!(&@";
	mp["เย็ดแม่"]="#]!(&@%";
	mp["แม่ตาย"]="#]!(&@";
	mp["โคตรพ่อโคตรแม่"]="#]!(&@%?#]!(&@";
	mp["จัญไร"]="#]!(&";
		
	for(auto x : mp ) {
		if(x.first.size() != x.second.size() )
		cout << x.first << " " << x.second << endl;
	}
	for (int i = 801 ; i <= 991 ; ++ i ){
		char tmp[20];
		sprintf(tmp,"review/%d.txt",i);
		string in(tmp);
		sprintf(tmp,"ans/censored-%d.txt",i);
		string out(tmp);
		cout << in << endl;
		char c;
		FILE *fin = fopen(in.c_str(),"r");
		string fcon;
		while(true){
			if(fscanf(fin,"%c",&c)>0)
				fcon.push_back(c);
			else break;
		}
		cout <<"________\n\n\n\n\n\n" << fcon << "_________\n\n\n\n\n\n";
		string fcout;
		int cur = 0 ;
		while(cur<fcon.size()) {
			bool found=false;
			string daword;
			for(auto x : mp ) {
				bool yes=true;
				for(int i = 0 ; i < x.first.size() ; ++ i) {
					if(cur+i>=fcon.size() || x.first[i]!=fcon[cur+i]) {
						yes=false;
					}
				}
				if(yes){
					found=true;
					daword = x.first;
					break;
				}
			}
			if(found) {
				fcout.append(mp[daword]);
				cur+=daword.size();
			} else {
				fcout.push_back(fcon[cur++]);
			}
		}
		if(fcon!=fcout){
			FILE *fout = fopen(out.c_str(),"w");
			fprintf(fout,"%s",fcout.c_str());
		}
	}
	return 0;
}
