#include<iostream>
#include<fstream>
#include<sstream>
#include<cstdio>
#include<cstring>
#include<boost/algorithm/string.hpp>
#include <boost/foreach.hpp>


using namespace std;

int main(int argc,char **argv)
{
	string s2(argv[1]);
	int sizeIndex = s2.size();
	if(s2.at(sizeIndex-1)!='/')
	{   
		s2=s2+"/";

	}   

	int i;
	for(i=0;i<677;i++)
	{
		stringstream ss;
		ss << i;
		string num = ss.str();
		string inputfile = s2+"FinalIndex/out"+num;
		string outputfile = s2+"FinalIndex/secondary"+num;
		ifstream infile;
		infile.open(inputfile.c_str());
		ofstream outfile;
		outfile.open(outputfile.c_str());
		string line;
		long long int sum=0,cnt=0;
		while(getline(infile,line))
		{
			string first="";
			long long int k;
			long long int length = line.size(); 
			for(k=0;k<length;k++)
			{
				if(line.at(k)!='|')first=first+line.at(k);
				else break;
			}

			if(cnt%100==0)outfile << first << " " << sum << endl;
			//int length = line.size();
			sum = sum+length+1;
			cnt++;
		}
		outfile.close();
		infile.close();
		//cout << sum << endl;
	}
}
