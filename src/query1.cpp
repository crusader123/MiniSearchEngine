#include<stdio.h>
#include<iostream>
#include<cstring>
#include<vector>
#include<fstream>
#include<stdlib.h>
#include<vector>
#include <iostream>
#include<map>
#include<stack>
#include <unordered_set>
#include<algorithm>
#include<boost/algorithm/string.hpp>
#include <boost/foreach.hpp>
#include<set>
#include<sstream>
#include<utility>
#include<cmath>

using namespace std;



#define tr 1
#define fa 0
using namespace std;
#define ALPHABET_SIZE (26)
// Converts key current character into index
// use only 'a' through 'z' and lower case
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')
//using namespace boost;


string pwd = "index_folder/";

static char * b;       /* buffer for word to be stemmed */
static int k,k0,j;     /* j is a general offset into the string */

/* cons(i) is tr <=> b[i] is a consonant. */

	int cons(int i)
{  switch (b[i])
	{  case 'a': case 'e': case 'i': case 'o': case 'u': return fa;
		case 'y': return (i==k0) ? tr : !cons(i-1);
		default: return tr;
	}
}

/* m() measures the number of consonant sequences between k0 and j. if c is
 *    a consonant sequence and v a vowel sequence, and <..> indicates arbitrary
 *       presence,
 *
 *             <c><v>       gives 0
 *                   <c>vc<v>     gives 1
 *                         <c>vcvc<v>   gives 2
 *                               <c>vcvcvc<v> gives 3
 *                                     ....
 *                                     */

int m()
{  int n = 0;
	int i = k0;
	while(tr)
	{  if (i > j) return n;
		if (! cons(i)) break; i++;
	}
	i++;
	while(tr)
	{  while(tr)
		{  if (i > j) return n;
			if (cons(i)) break;
			i++;
		}
		i++;
		n++;
		while(tr)
		{  if (i > j) return n;
			if (! cons(i)) break;
			i++;
		}
		i++;
	}
}

/* vowelinstem() is tr <=> k01,...j contains a vowel */

int vowelinstem()
{  int i; for (i = k0; i <= j; i++) if (! cons(i)) return tr;
	return fa;
}

/* doublec(j) is tr <=> j,(j-1) contain a double consonant. */

int doublec(int j)
{  if (j < k0+1) return fa;
	if (b[j] != b[j-1]) return fa;
	return cons(j);
}

/* cvc(i) is tr <=> i-2,i-1,i has the form consonant - vowel - consonant
 *    and also if the second c is not w,x or y. this is used when trying to
 *       restore an e at the end of a short word. e.g.
 *
 *             cav(e), lov(e), hop(e), crim(e), but
 *                   snow, box, tray.
 *
 *                   */

int cvc(int i)
{  if (i < k0+2 || !cons(i) || cons(i-1) || !cons(i-2)) return fa;
	{  int ch = b[i];
		if (ch == 'w' || ch == 'x' || ch == 'y') return fa;
	}
	return tr;
}

/* ends(s) is tr <=> k0,...k ends with the string s. */

int ends(char * s)
{  int length = s[0];
	if (s[length] != b[k]) return fa; /* tiny speed-up */
	if (length > k-k0+1) return fa;
	if (memcmp(b+k-length+1,s+1,length) != 0) return fa;
	j = k-length;
	return tr;
}

/* setto(s) sets (j+1),...k to the characters in the string s, readjusting
 *    k. */

void setto(char * s)
{  int length = s[0];
	memmove(b+j+1,s+1,length);
	k = j+length;
}

/* r(s) is used further down. */

void r(char * s) { if (m() > 0) setto(s); }

/* step1ab() gets rid of plurals and -ed or -ing. e.g.
 *
 *        caresses  ->  caress
 *               ponies    ->  poni
 *                      ties      ->  ti
 *                             caress    ->  caress
 *                                    cats      ->  cat
 *
 *                                           feed      ->  feed
 *                                                  agreed    ->  agree
 *                                                         disabled  ->  disable
 *
 *                                                                matting   ->  mat
 *                                                                       mating    ->  mate
 *                                                                              meeting   ->  meet
 *                                                                                     milling   ->  mill
 *                                                                                            messing   ->  mess
 *
 *                                                                                                   meetings  ->  meet
 *
 *                                                                                                   */

void step1ab()
{  if (b[k] == 's')
	{  if (ends("\04" "sses")) k -= 2; else
		if (ends("\03" "ies")) setto("\01" "i"); else
			if (b[k-1] != 's') k--;
	}
	if (ends("\03" "eed")) { if (m() > 0) k--; } else
		if ((ends("\02" "ed") || ends("\03" "ing")) && vowelinstem())
		{  k = j;
			if (ends("\02" "at")) setto("\03" "ate"); else
				if (ends("\02" "bl")) setto("\03" "ble"); else
					if (ends("\02" "iz")) setto("\03" "ize"); else
						if (doublec(k))
						{  k--;
							{  int ch = b[k];
								if (ch == 'l' || ch == 's' || ch == 'z') k++;
							}
						}
						else if (m() == 1 && cvc(k)) setto("\01" "e");
		}
}

/* step1c() turns terminal y to i when there is another vowel in the stem. */

void step1c() { if (ends("\01" "y") && vowelinstem()) b[k] = 'i'; }


/* step2() maps double suffices to single ones. so -ization ( = -ize plus
 *    -ation) maps to -ize etc. note that the string before the suffix must give
 *       m() > 0. */

void step2() { switch (b[k-1])
	{
		case 'a': if (ends("\07" "ational")) { r("\03" "ate"); break; }
				  if (ends("\06" "tional")) { r("\04" "tion"); break; }
			  break;
		case 'c': if (ends("\04" "enci")) { r("\04" "ence"); break; }
				  if (ends("\04" "anci")) { r("\04" "ance"); break; }
			  break;
		case 'e': if (ends("\04" "izer")) { r("\03" "ize"); break; }
				  break;
		case 'l': if (ends("\03" "bli")) { r("\03" "ble"); break; } /*-DEPARTURE-*/

				  /* To match the published algorithm, replace this line with
				   *     case 'l': if (ends("\04" "abli")) { r("\04" "able"); break; } */

				  if (ends("\04" "alli")) { r("\02" "al"); break; }
			  if (ends("\05" "entli")) { r("\03" "ent"); break; }
			  if (ends("\03" "eli")) { r("\01" "e"); break; }
			  if (ends("\05" "ousli")) { r("\03" "ous"); break; }
			  break;
		case 'o': if (ends("\07" "ization")) { r("\03" "ize"); break; }
				  if (ends("\05" "ation")) { r("\03" "ate"); break; }
			  if (ends("\04" "ator")) { r("\03" "ate"); break; }
			  break;
		case 's': if (ends("\05" "alism")) { r("\02" "al"); break; }
				  if (ends("\07" "iveness")) { r("\03" "ive"); break; }
			  if (ends("\07" "fulness")) { r("\03" "ful"); break; }
			  if (ends("\07" "ousness")) { r("\03" "ous"); break; }
			  break;
		case 't': if (ends("\05" "aliti")) { r("\02" "al"); break; }
				  if (ends("\05" "iviti")) { r("\03" "ive"); break; }
			  if (ends("\06" "biliti")) { r("\03" "ble"); break; }
			  break;
		case 'g': if (ends("\04" "logi")) { r("\03" "log"); break; } /*-DEPARTURE-*/

				  /* To match the published algorithm, delete this line */

	} }

/* step3() deals with -ic-, -full, -ness etc. similar strategy to step2. */

void step3() { switch (b[k])
	{
		case 'e': if (ends("\05" "icate")) { r("\02" "ic"); break; }
				  if (ends("\05" "ative")) { r("\00" ""); break; }
			  if (ends("\05" "alize")) { r("\02" "al"); break; }
			  break;
		case 'i': if (ends("\05" "iciti")) { r("\02" "ic"); break; }
				  break;
		case 'l': if (ends("\04" "ical")) { r("\02" "ic"); break; }
				  if (ends("\03" "ful")) { r("\00" ""); break; }
			  break;
		case 's': if (ends("\04" "ness")) { r("\00" ""); break; }
				  break;
	} }

/* step4() takes off -ant, -ence etc., in context <c>vcvc<v>. */

	void step4()
{  switch (b[k-1])
	{  case 'a': if (ends("\02" "al")) break; return;
		case 'c': if (ends("\04" "ance")) break;
				  if (ends("\04" "ence")) break; return;
		case 'e': if (ends("\02" "er")) break; return;
		case 'i': if (ends("\02" "ic")) break; return;
		case 'l': if (ends("\04" "able")) break;
				  if (ends("\04" "ible")) break; return;
		case 'n': if (ends("\03" "ant")) break;
				  if (ends("\05" "ement")) break;
			  if (ends("\04" "ment")) break;
			  if (ends("\03" "ent")) break; return;
		case 'o': if (ends("\03" "ion") && (b[j] == 's' || b[j] == 't')) break;
				  if (ends("\02" "ou")) break; return;
			  /* takes care of -ous */
		case 's': if (ends("\03" "ism")) break; return;
		case 't': if (ends("\03" "ate")) break;
				  if (ends("\03" "iti")) break; return;
		case 'u': if (ends("\03" "ous")) break; return;
		case 'v': if (ends("\03" "ive")) break; return;
		case 'z': if (ends("\03" "ize")) break; return;
		default: return;
	}
	if (m() > 1) k = j;
}

/* step5() removes a final -e if m() > 1, and changes -ll to -l if
 *    m() > 1. */

void step5()
{  j = k;
	if (b[k] == 'e')
	{  int a = m();
		if (a > 1 || a == 1 && !cvc(k-1)) k--;
	}
	if (b[k] == 'l' && doublec(k) && m() > 1) k--;
}

/* In stem(p,i,j), p is a char pointer, and the string to be stemmed is from
 *    p[i] to p[j] inclusive. Typically i is zero and j is the offset to the last
 *       character of a string, (p[j+1] == '\0'). The stemmer adjusts the
 *          characters p[i] ... p[j] and returns the new end-point of the string, k.
 *             Stemming never increases word length, so i <= k <= j. To turn the stemmer
 *                into a module, declare 'stem' as extern, and delete the remainder of this
 *                   file.
 *                   */

int stem(char * p, int i, int j)
{  b = p; k = j; k0 = i; /* copy the parameters into statics */
	if (k <= k0+1) return k; /*-DEPARTURE-*/

	/* With this line, strings of length 1 or 2 don't go through the
	 *       stemming process, although no mention is made of this in the
	 *             published algorithm. Remove the line to match the published
	 *                   algorithm. */

	step1ab(); step1c(); step2(); step3(); step4(); step5();
	return k;
}

/*--------------------stemmer definition ends here------------------------*/

static char * s;         /* a char * (=string) pointer; passed into b above */

#define INC 50           /* size units in which s is increased */
static int i_max = INC;  /* maximum offset in s */

void increase_s()
{  i_max += INC;
	{  char * new_s = (char *) malloc(i_max+1);
		{ int i; for (i = 0; i < i_max; i++) new_s[i] = s[i]; } /* copy across */
		free(s); s = new_s;
	}
}

#define UC(ch) (ch <= 'Z' && ch >= 'A')
#define LC(ch) (ch <= 'z' && ch >= 'a')
#define LETTER(ch) (UC(ch) || LC(ch))
#define FORCELC(ch) (ch-('A'-'a'))

int identify(string tmp)
{
	int alpha = ((int)tmp.at(0) - 97)*26 + ((int)tmp.at(1) - 97);
	if(alpha >=0 && alpha <676)return alpha;
	else return 676;
}




ifstream inF;

std::unordered_set<std::string> keys = {"able","about","above","according","accordingly","across","actually","after","afterwards","again","against","all","allow","allows","almost","alone","along","already","also","although","always","am","among","amongst","an","and","another","any","anybody","anyhow","anyone","anything","anyway","anyways","anywhere","apart","appear","appreciate","appropriate","are","around","as","aside","ask","asking","associated","at","available","away","awfully","b","be","became","because","become","becomes","becoming","been","before","beforehand","behind","being","believe","below","beside","besides","best","better","between","beyond","both","brief","but","by","c","came","can","cannot","cant","cause","causes","certain","certainly","changes","clearly","co","com","come","comes","concerning","consequently","consider","considering","contain","containing","contains","corresponding","could","course","currently","d","definitely","described","despite","did","different","do","does","doing","done","down","downwards","during","e","each","edu","eg","eight","either","else","elsewhere","enough","entirely","especially","et","etc","even","ever","every","everybody","everyone","everything","everywhere","ex","exactly","example","except","f","far","few","fifth","first","five","followed","following","follows","for","former","formerly","forth","four","from","further","furthermore","g","get","gets","getting","given","gives","go","goes","going","gone","got","gotten","greetings","h","had","happens","hardly","has","have","having","he","hello","help","hence","her","here","hereafter","hereby","herein","hereupon","hers","herself","hi","him","himself","his","hither","hopefully","how","howbeit","however","i","ie","if","ignored","immediate","in","inasmuch","inc","indeed","indicate","indicated","indicates","inner","insofar","instead","into","inward","is","it","its","itself","j","just","k","keep","keeps","kept","know","knows","known","l","last","lately","later","latter","latterly","least","less","lest","let","like","liked","likely","little","look","looking","looks","ltd","m","mainly","many","may","maybe","me","mean","meanwhile","merely","might","more","moreover","most","mostly","much","must","my","myself","n","name","namely","nd","near","nearly","necessary","need","needs","neither","never","nevertheless","new","next","nine","no","nobody","non","none","noone","nor","normally","not","nothing","novel","now","nowhere","o","obviously","of","off","often","oh","ok","okay","old","on","once","one","ones","only","onto","or","other","others","otherwise","ought","our","ours","ourselves","out","outside","over","overall","own","p","particular","particularly","per","perhaps","placed","please","plus","possible","presumably","probably","provides","q","que","quite","qv","r","rather","rd","re","really","reasonably","regarding","regardless","regards","relatively","respectively","right","s","said","same","saw","say","saying","says","second","secondly","see","seeing","seem","seemed","seeming","seems","seen","self","selves","sensible","sent","serious","seriously","seven","several","shall","she","should","since","six","so","some","somebody","somehow","someone","something","sometime","sometimes","somewhat","somewhere","soon","sorry","specified","specify","specifying","still","sub","such","sup","sure","t","take","taken","tell","tends","th","than","thank","thanks","thanx","that","thats","the","their","theirs","them","themselves","then","thence","there","thereafter","thereby","therefore","therein","theres","thereupon","these","they","think","third","this","thorough","thoroughly","those","though","three","through","throughout","thru","thus","to","together","too","took","toward","towards","tried","tries","truly","try","trying","twice","two","u","un","under","unfortunately","unless","unlikely","until","unto","up","upon","us","use","used","useful","uses","using","usually","uucp","v","value","various","very","via","viz","vs","w","want","wants","was","way","we","welcome","well","went","were","what","whatever","when","whence","whenever","where","whereafter","whereas","whereby","wherein","whereupon","wherever","whether","which","while","whither","who","whoever","whole","whom","whose","why","will","willing","wish","with","within","without","wonder","would","would","x","y","yes","yet","you","your","yours","yourself","yourselves","z","zero"};


string TitleCheck(string tit)
{
	inF.open("indexTitle");
	//cout << "tit " << tit << endl;
	long int t = atol(tit.c_str());
	//cout << " given " << t << endl;
	long int key=0;
	long int value=0,pastVal=0;
	while(inF>>value>>key)
	{
		//cout << " key " << key << endl;
		if(value>t)break;
		else
		pastVal=key;

	}
	//cout << value << " past " << pastVal << endl;
	FILE *pfile;
	pfile = fopen("so.txt","rb");
	fseek(pfile,pastVal,SEEK_SET);
	//int Si;
	//if(key>pastVal)Si=key-pastVal;
	int Si=5000;
	char *line=(char*)malloc(Si);;
	int count=0;
	while(fgets(line,Si,pfile)!=NULL)
	{
		string ss(line);
		unsigned pos = ss.find(":");
		string key1 = ss.substr(0,pos);
		long int tt = atol(key1.c_str());
		string value1 = ss.substr(pos+1);
		if(tt==t)
		{
			free(line);
			inF.close();
			fclose(pfile);
			return value1;
		}
		count++;
		if(count==1000)
		{
			free(line);
			inF.close();
			fclose(pfile);
			return "";
		}


	}
	free(line);
	inF.close();
	fclose(pfile);
	return "";

	
}

int main(int argc,char **argv)
{
	int tc;
	scanf("%d\n",&tc);
	string s2(argv[1]);
	int sizeIndex = s2.size();
	if(s2.at(sizeIndex-1)!='/')
	{
		s2=s2+"/";

	}
	string fnm1 = "FinalIndex/secondary";
	string fnm2 = "FinalIndex/out";
	string str;
	//int p11=1;
	while(tc>0)
	{
	//	cout << p11 << endl;
	//	p11++;
		map <string,double> mymap;
		pair <double,string> p1;
		set < pair<double,string> > myset;
		string str;
		int len,i,flag=0;
		getline(cin,str);
		//cout << str << endl;
		vector<std::string> Queryparts;
		boost::split(Queryparts,str, boost::is_any_of(" "), boost::token_compress_on);
		int j;
		unordered_set<std::string>::const_iterator got;
		
		for(j=0;j<Queryparts.size();j++)
		{
			int fieldQuery=0;
			int tagIndex=-1;
			flag=0;

			string queryWord = Queryparts[j];
			int diff = 'A'-'a';
			len = queryWord.size();
			if(len>2 && len<40)
			{
				if((queryWord.at(0)=='t'||queryWord.at(0)=='b'||queryWord.at(0)=='i'||queryWord.at(0)=='l'||queryWord.at(0)=='c')&& (queryWord.at(1)==':'))
				{
					fieldQuery=1;
					if(queryWord.at(0)=='t')tagIndex=1;
					else if(queryWord.at(0)=='b')tagIndex=3;
					else if(queryWord.at(0)=='i')tagIndex=2;
					else if(queryWord.at(0)=='l')tagIndex=5;
				        else if(queryWord.at(0)=='c')tagIndex=4;
					queryWord.erase(0,2);
					len = len-2;

						 
				}
								
				for(i=0;i<len;i++)
				{
					if(queryWord.at(i)>='A' && queryWord.at(i)<='Z')
					{
						queryWord.at(i)=queryWord.at(i)-diff;
					}
					if(!(queryWord.at(i)>='a' && queryWord.at(i)<='z'))
					{
						flag=1;
						break;
					}
				}
				if(flag==1)continue;
				got = keys.find(queryWord);
				if(got!=keys.end())continue;

				char tmp[1024];
				strcpy(tmp,queryWord.c_str());
				int si = queryWord.size();
				tmp[si]='\0';
				tmp[stem(tmp,0,si-1)+1]=0;
				string queryWordStemmed(tmp);

				int alpha = identify(queryWordStemmed);
			//	cout << queryWordStemmed << " ";
				queryWordStemmed.erase(0,2);
				stringstream ss;
				ss << alpha;
				string num = ss.str();
				string fileName1 = fnm1+num;
				string fileName2 = fnm2+num;
				string s3 = s2+fileName1;
				string s4 = s2+fileName2;
				//cout << queryWordStemmed << " " << s3 << endl;

	


				//ifstream infile;
				ifstream infile0;
				infile0.open(s3.c_str());
				//string lines;
				string key;
				long long int value=0,pastVal=0;
				while(infile0>>key>>value)
				{
					if(key.compare(queryWordStemmed)>0)break;
					pastVal = value;

				}
				infile0.close();
				FILE *pfile;
				pfile = fopen(s4.c_str(),"rb");
				fseek(pfile,pastVal,SEEK_SET);
				int count =0;


				//infile.open(s4.c_str());
				long long int Si;
				if(value!=pastVal)
				Si=value-pastVal;
				else Si=100000;

				char *line = (char*)malloc(Si);
				while(fgets(line,Si,pfile)!=NULL)
				{
					string lines(line);
					//cout << " lines done " << count << endl;
					long int k,lineSize = lines.size();
					string first="";
					for(k=0;k<lineSize;k++)
					{
						if(lines.at(k)!='|')first=first+lines.at(k);
						else break;
					}
					//cout << first << endl;
					vector<std::string> parts;
					//boost::split(parts,lines, boost::is_any_of("|\n"), boost::token_compress_on);
					//string first = parts[0];
					int flag2=0;
					//cout << queryWordStemmed << " " << first << " " << alpha << endl;
					if(first==queryWordStemmed)
					{
						//cout << " found " << endl;
						//boost::split(parts,lines, boost::is_any_of("|,:\n"));
						//long long int pos=0;
						std::size_t prev_pos = 0, pos;
						while ((pos = lines.find_first_of("|,:\n", prev_pos)) != std::string::npos)
						{   
							//if (pos > prev_pos)
							parts.push_back(lines.substr(prev_pos, pos-prev_pos));
							prev_pos= pos+1;
						}   
						if (prev_pos< lines.length())
							parts.push_back(lines.substr(prev_pos, std::string::npos));

						//cout << " calc " << endl;
						//cout << queryWordStemmed << " " << first << " " << alpha << endl;
						int j=0;
						int numDocs=parts.size()/6;
						if(numDocs>0)
						{
							int total = parts.size();
						//	cout << " total " << total << endl;
							string docId="";
							long int fr,p;
							long long int sum=0;
							for(p=1;p<total;p++)
							{

								if(j==0)
								{
									docId=parts[p];
								//	cout << docId << endl;
								}
								if(docId!="")
								{
									if(parts[p]=="")fr=0;
									else fr = atol(parts[p].c_str());
									if((j==1 && fieldQuery==0)|| (j==1 && fieldQuery==1 && tagIndex==1))sum = sum+16*fr;//title
									else if((j==2 && fieldQuery==0)||(j==2 && fieldQuery==1 && tagIndex==2))sum = sum+1*fr;//infobox
									else if((j==3 && fieldQuery==0)||(j==3 && fieldQuery==1 && tagIndex==3))sum = sum+2*fr;//body
									else if((j==4 && fieldQuery==0)||(j==4 && fieldQuery==1 && tagIndex==4))sum = sum+8*fr;//category
									else if((j==5 && fieldQuery==0)||(j==5 && fieldQuery==1 && (tagIndex==5 || tagIndex==2)))sum = sum+4*fr;//link

								}
								j++;
								if(j==6 && docId!="")
								{
									double idf = log(14041179/(double)numDocs);
									double tf_idf = (double)sum*idf;
									p1 = make_pair(mymap[docId],docId);
									myset.erase(p1);
									mymap[docId]=mymap[docId]+tf_idf;
									p1 = make_pair(mymap[docId],docId);
									myset.insert(p1);
									sum=0;
									j=0;
								} //j==6
							} //for p


						}// numdocs
						//cout << " done processing ....." << endl;
						break;
					}//if word matched
					count++;
					if(count==100)break;

				}//end of while getline
				free(line);
				//infile.close();
				fclose(pfile);

			}// if len>2

		}// enf of for
		int count1 = 0;
		pair <double,string> p2;
		//cout << str << endl;
		for (std::set< pair<double,string> >::reverse_iterator it=myset.rbegin(); it!=myset.rend(); ++it)
		{
			//if(it==NULL)break;
			p2 = *it;
			string id=p2.second;
			cout << id << " " << TitleCheck(id);
			//cout << TitleCheck(id) << endl;
			count1++;
			if(count1==10)break;

		}
		cout << "-----------------" << endl;




		tc--;
	}
	return 0;
}
