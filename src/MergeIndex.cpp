#include<stdio.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<map>
#include<vector>
#include<string>
#include<boost/algorithm/string.hpp>
#include <boost/foreach.hpp>


using namespace std;

int main(int argc,char **argv)
{

	int j;
	string s2(argv[1]);
	int sizeIndex = s2.size();
	if(s2.at(sizeIndex-1)!='/')
	{   
		s2=s2+"/";

	}   

	for(j=0;j<677;j++)
	{
	stringstream ss;
	ss << j;
	string num = ss.str();
	string inputFile = s2+"file" + num;
	ifstream infile;
	infile.open(inputFile.c_str());
	string lines;
	map <string,vector<string> > mymap;
	//cout << " Reading " << j << endl;
	vector<std::string> parts;
	long long int cnt =0;
	while(getline(infile,lines))
	{
		boost::split(parts,lines, boost::is_any_of("|"), boost::token_compress_on);
		string first = parts[0];
		parts.erase (parts.begin(),parts.begin()+1);
		if(mymap.count(first)<=0)
		{
			mymap[first]=parts;
		}
		else
		{
			int i;
			for(i=0;i<parts.size();i++)
			{
				mymap[first].push_back(parts[i]);
			}
		}
		parts.clear();
		//cout << " done " << cnt++ << endl;

	
	}
	string outputFile = s2+"FinalIndex/out"+num;
	ofstream pf(outputFile.c_str(),ios::app);
	 map<string, vector<string> >::iterator it;
	 string key;
	 vector <string> value;
	 //cout << " Writng " << j << endl;
	 for(it=mymap.begin();it!=mymap.end();++it)
	 {
		 key = it->first;
		 value = it->second;
		 pf << key << "|";
		 int i;
		 for(i=0;i<value.size();i++)pf << value[i] << "|";
		 pf << endl;
		 value.clear();
	 
	 }

	 pf.close();
	 infile.close();

	}

}
