#include<iostream>
#include<map>
#include<cstring>
#include<fstream>
using namespace std;

int main()
{
	map<string,string> mymap;
	ifstream infile;
	infile.open("../bin/so.txt");
	ofstream outfile;
	outfile.open("../bin/indexTitle");
	string line;
	int count=0;
	long long int sum=0;
	while(getline(infile,line))
	{
		//count++;
		unsigned pos = line.find(":");
		string key = line.substr(0,pos);
		string value = line.substr(pos+1);
		if(count%1000==0)outfile <<key<<" " << sum << endl;
		count++;
		sum = sum+line.size()+1;
		//mymap[key]=value;
		//cout << count << endl;
	}
	infile.close();
	outfile.close();
	return 0;

}
