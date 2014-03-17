// -*- C++ -*-

/* myparser.cc
 *
 * Copyright (C) 2002 The libxml++ development team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "myparser.h"
#include <glibmm/convert.h> //For Glib::ConvertError
#include<cstring>
#include<stdio.h>
#include<fstream>
#include<stdlib.h>
#include<vector>
#include<boost/algorithm/string.hpp>
#include <boost/foreach.hpp>
#include <iostream>
#include<map>
#include<set>
#include <unordered_set>
#include<stack>
 

using namespace std;
string docid = "";
string st_temp = "";
char lastChar=' ',presentChar=' ';
int infoBox=0;
int bracesCount=0,bracesPresent=0;
string tagFlag="";

extern string indexMaker;
// Alphabet size (# of symbols)
#define ALPHABET_SIZE (26)
// Converts key current character into index
// use only 'a' through 'z' and lower case
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')
//using namespace boost;

#define tr 1
#define fa 0

stack<string> taglist;
map <string,set<string> > wordlist;
string title="";
vector <string> titlevector;
string delimiters = " }{]['|/:.\"-!,=<>\n\t\r1234567890%()#$&*^@~";
using namespace std;




char* toLowerCase(char* str)
{	
	int differ = 'A'-'a';
	char ch;
	int ii = strlen(str);
	for (int i=0; i <ii;i++)
	{
		strncpy(&ch,str+i,1);
		if (ch>='A' && ch<='Z')
		{
			ch = ch-differ;
			memcpy(str+i,&ch,1);
		}
	}
	return str;
}







char filename[][27]={"file0","file1","file2","file3","file4","file5","file6","file7","file8","file9","file10",
		      "file11","file12","file13","file14","file15","file16","file17","file18","file19","file20",
		      "file21","file22","file23","file24","file25","file26"};
//map <string,int> keymap;
int identify(string tmp)
{
	int alpha = (int)tmp.at(0) - 97;
	if(alpha >=0 && alpha <26)return alpha;
	else return 26;
}



void writing()
{
	ofstream pf0(filename[0],ios::app);
	/*ofstream pf1(filename[1],ios::app);
	ofstream pf2(filename[2],ios::app);
	ofstream pf3(filename[3],ios::app);
	ofstream pf4(filename[4],ios::app);
	ofstream pf5(filename[5],ios::app);	ofstream pf6(filename[6],ios::app);
	ofstream pf7(filename[7],ios::app);
	ofstream pf8(filename[8],ios::app);
	ofstream pf9(filename[9],ios::app);
	ofstream pf10(filename[10],ios::app);
	ofstream pf11(filename[11],ios::app);
	ofstream pf12(filename[12],ios::app);
	ofstream pf13(filename[13],ios::app);
	ofstream pf14(filename[14],ios::app);
	ofstream pf15(filename[15],ios::app);
	ofstream pf16(filename[16],ios::app);
	ofstream pf17(filename[17],ios::app);
	ofstream pf18(filename[18],ios::app);
	ofstream pf19(filename[19],ios::app);
	ofstream pf20(filename[20],ios::app);
	ofstream pf21(filename[21],ios::app);
	ofstream pf22(filename[22],ios::app);
	ofstream pf23(filename[23],ios::app);
	ofstream pf24(filename[24],ios::app);
	ofstream pf25(filename[25],ios::app);
	ofstream pf26(filename[26],ios::app);
	*/
	  typedef map<string, set<string> >::iterator it_type;
	  std::set<string>::iterator it;
	  set <string> setTemp;
	//  cout << wordlist.size() << " word " << endl;
	  for(it_type iterator = wordlist.begin(); iterator != wordlist.end(); iterator++) {

		 
		  setTemp = iterator->second;
		  int setSize = setTemp.size();
		  pf0 << iterator->first << " ";
		/*  int alpha = identify(iterator->first);
		  if(alpha==0)pf0 << iterator->first << " ";
		  else if(alpha==1)pf1 << iterator->first << " ";
		  else if(alpha==2)pf2 << iterator->first << " ";
		  else if(alpha==3)pf3 << iterator->first << " ";
		  else if(alpha==4)pf4 << iterator->first << " ";
		  else if(alpha==5)pf5 << iterator->first << " ";
		  else if(alpha==6)pf6 << iterator->first << " ";
		  else if(alpha==7)pf7 << iterator->first << " ";
		  else if(alpha==8)pf8 << iterator->first << " ";
		  else if(alpha==9)pf9 << iterator->first << " ";
		  else if(alpha==10)pf10 << iterator->first << " ";
		  else if(alpha==11)pf11 << iterator->first << " ";
		  else if(alpha==12)pf12 << iterator->first << " ";
		  else if(alpha==13)pf13 << iterator->first << " ";
		  else if(alpha==14)pf14 << iterator->first << " ";
		  else if(alpha==15)pf15 << iterator->first << " ";
		  else if(alpha==16)pf16 << iterator->first << " ";
		  else if(alpha==17)pf17 << iterator->first << " ";
		  else if(alpha==18)pf18 << iterator->first << " ";
		  else if(alpha==19)pf19 << iterator->first << " ";
		  else if(alpha==20)pf20 << iterator->first << " " ;
		  else if(alpha==21)pf21 << iterator->first << " ";
		  else if(alpha==22)pf22 << iterator->first << " ";
		  else if(alpha==23)pf23 << iterator->first << " ";
		  else if(alpha==24)pf24 << iterator->first << " ";
		  else if(alpha==25)pf25 << iterator->first << " ";
		  else pf26 << iterator->first << " ";
		  */
		  int tpointer = 0;
		  
		  for (it=setTemp.begin(); it!=setTemp.end(); it++)
		  {
	//	  cout << iterator->first << " " << alpha << " " << iterator->second << endl;
	//	  fprintf(pf0,"%s %s\n",iterator->first,iterator->second);
		  //if(iterator->second!='\0')
		  //{
		  tpointer++;
		  if(tpointer < setSize)pf0 << *it << " ";
		  else pf0 << *it << endl;
		  /*if(alpha==0)pf0 << iterator->first << " " << iterator->second << endl;
		  else if(alpha==1)pf1 << iterator->first << " " << iterator->second << endl;
		  else if(alpha==2)pf2 << iterator->first << " " << iterator->second << endl;
		  else if(alpha==3)pf3 << iterator->first << " " << iterator->second << endl;
		  else if(alpha==4)pf4 << iterator->first << " " << iterator->second << endl;
		  else if(alpha==5)pf5 << iterator->first << " " << iterator->second << endl;
		  else if(alpha==6)pf6 << iterator->first << " " << iterator->second << endl;
		  else if(alpha==7)pf7 << iterator->first << " " << iterator->second << endl;
		  else if(alpha==8)pf8 << iterator->first << " " << iterator->second << endl;
		  else if(alpha==9)pf9 << iterator->first << " " << iterator->second << endl;
		  else if(alpha==10)pf10 << iterator->first << " " << iterator->second << endl;
		  else if(alpha==11)pf11 << iterator->first << " " << iterator->second << endl;
		  else if(alpha==12)pf12 << iterator->first << " " << iterator->second << endl;
		  else if(alpha==13)pf13 << iterator->first << " " << iterator->second << endl;
		  else if(alpha==14)pf14 << iterator->first << " " << iterator->second << endl;
		  else if(alpha==15)pf15 << iterator->first << " " << iterator->second << endl;
		  else if(alpha==16)pf16 << iterator->first << " " << iterator->second << endl;
		  else if(alpha==17)pf17 << iterator->first << " " << iterator->second << endl;
		  else if(alpha==18)pf18 << iterator->first << " " << iterator->second << endl;
		  else if(alpha==19)pf19 << iterator->first << " " << iterator->second << endl;
		  else if(alpha==20)pf20 << iterator->first << " " << iterator->second << endl;
		  else if(alpha==21)pf21 << iterator->first << " " << iterator->second << endl;
		  else if(alpha==22)pf22 << iterator->first << " " << iterator->second << endl;
		  else if(alpha==23)pf23 << iterator->first << " " << iterator->second << endl;
		  else if(alpha==24)pf24 << iterator->first << " " << iterator->second << endl;
		  else if(alpha==25)pf25 << iterator->first << " " << iterator->second << endl;
		  else pf26 << iterator->first << " " << iterator->second << endl;*/
		  }
		  //}
	  }
	//  wordlist.clear();
	 pf0.close();
	/* pf1.close();
	 pf2.close();
	 pf3.close();
	 pf4.close();
	 pf5.close();
	 pf6.close();
	 pf7.close();
	 pf8.close();
	 pf9.close();
	 pf10.close();
	 pf11.close();
	 pf12.close();
	 pf13.close();
	 pf14.close();
	 pf15.close();
	 pf16.close();
	 pf17.close();
	 pf18.close();
	 pf19.close();
	 pf20.close();
	 pf21.close();
	 pf22.close();
	 pf23.close();
	 pf24.close();
	 pf25.close();
	 pf26.close();*/

}

/* Open Souce Code for Stemming : Taken from
 * http://www.cs.cmu.edu/~callan/Teaching/porter.c
 */
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

/* vowelinstem() is tr <=> k0,...j contains a vowel */

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
string tagnm1="",tagnm2="",tagnm3="";
  std::unordered_set<std::string> keys = {"able","about","above","according","accordingly","across","actually","after","afterwards","again","against","all","allow","allows","almost","alone","along","already","also","although","always","am","among","amongst","an","and","another","any","anybody","anyhow","anyone","anything","anyway","anyways","anywhere","apart","appear","appreciate","appropriate","are","around","as","aside","ask","asking","associated","at","available","away","awfully","b","be","became","because","become","becomes","becoming","been","before","beforehand","behind","being","believe","below","beside","besides","best","better","between","beyond","both","brief","but","by","c","came","can","cannot","cant","cause","causes","certain","certainly","changes","clearly","co","com","come","comes","concerning","consequently","consider","considering","contain","containing","contains","corresponding","could","course","currently","d","definitely","described","despite","did","different","do","does","doing","done","down","downwards","during","e","each","edu","eg","eight","either","else","elsewhere","enough","entirely","especially","et","etc","even","ever","every","everybody","everyone","everything","everywhere","ex","exactly","example","except","f","far","few","fifth","first","five","followed","following","follows","for","former","formerly","forth","four","from","further","furthermore","g","get","gets","getting","given","gives","go","goes","going","gone","got","gotten","greetings","h","had","happens","hardly","has","have","having","he","hello","help","hence","her","here","hereafter","hereby","herein","hereupon","hers","herself","hi","him","himself","his","hither","hopefully","how","howbeit","however","i","ie","if","ignored","immediate","in","inasmuch","inc","indeed","indicate","indicated","indicates","inner","insofar","instead","into","inward","is","it","its","itself","j","just","k","keep","keeps","kept","know","knows","known","l","last","lately","later","latter","latterly","least","less","lest","let","like","liked","likely","little","look","looking","looks","ltd","m","mainly","many","may","maybe","me","mean","meanwhile","merely","might","more","moreover","most","mostly","much","must","my","myself","n","name","namely","nd","near","nearly","necessary","need","needs","neither","never","nevertheless","new","next","nine","no","nobody","non","none","noone","nor","normally","not","nothing","novel","now","nowhere","o","obviously","of","off","often","oh","ok","okay","old","on","once","one","ones","only","onto","or","other","others","otherwise","ought","our","ours","ourselves","out","outside","over","overall","own","p","particular","particularly","per","perhaps","placed","please","plus","possible","presumably","probably","provides","q","que","quite","qv","r","rather","rd","re","really","reasonably","regarding","regardless","regards","relatively","respectively","right","s","said","same","saw","say","saying","says","second","secondly","see","seeing","seem","seemed","seeming","seems","seen","self","selves","sensible","sent","serious","seriously","seven","several","shall","she","should","since","six","so","some","somebody","somehow","someone","something","sometime","sometimes","somewhat","somewhere","soon","sorry","specified","specify","specifying","still","sub","such","sup","sure","t","take","taken","tell","tends","th","than","thank","thanks","thanx","that","thats","the","their","theirs","them","themselves","then","thence","there","thereafter","thereby","therefore","therein","theres","thereupon","these","they","think","third","this","thorough","thoroughly","those","though","three","through","throughout","thru","thus","to","together","too","took","toward","towards","tried","tries","truly","try","trying","twice","two","u","un","under","unfortunately","unless","unlikely","until","unto","up","upon","us","use","used","useful","uses","using","usually","uucp","v","value","various","very","via","viz","vs","w","want","wants","was","way","we","welcome","well","went","were","what","whatever","when","whence","whenever","where","whereafter","whereas","whereby","wherein","whereupon","wherever","whether","which","while","whither","who","whoever","whole","whom","whose","why","will","willing","wish","with","within","without","wonder","would","would","x","y","yes","yet","you","your","yours","yourself","yourselves","z","zero"};

	
void inflateDicitionary(vector <string> &parts)
{

	  unordered_set<std::string>::const_iterator got;
	  unsigned int i;
	  for(i=0;i<parts.size();i++)
	  {

		  //cout << parts[i] << endl;
		  //char tmp[1024];
		  //strcpy(tmp,parts[i].c_str());
		  //tmp[sizeof(parts[i])-1]='\0';
		  //if(parts[i].length()!=0 && search(&trie,tmp)==0)
		  if(parts[i].length()!=0 )
		  {
			  got = keys.find(parts[i]);
			  if(got==keys.end())
			  {

				  char tmp[1024];
				  strcpy(tmp,parts[i].c_str());
				  int si = parts[i].size();
				  tmp[si]='\0';

				  tmp[stem(tmp,0,si-1)+1]=0;
				  string ss(tmp);
				  //		Porter2Stemmer::stem(parts[i]);
				  wordlist[ss].insert(docid);
				  if(ss=="sympathis")cout << parts[i] << " " << ss << " " << docid << endl;
				  //cout << parts[i] << endl;
				  //cout << tmp << endl;
			  }
		  }
	  }
}

MySaxParser::MySaxParser()
  : xmlpp::SaxParser()
{
}

MySaxParser::~MySaxParser()
{
}

void MySaxParser::on_start_document()
{
 // std::cout << "************************Start Document********************************" << std::endl;
// cout << "indx making " << indexMaker << endl;
 int i,size2=indexMaker.size();
if(indexMaker[size2-1]!='/')indexMaker = indexMaker + "/";
 for(i=0;i<27;i++)
 {
	 string tmpfile(filename[i]);
	 tmpfile = indexMaker + tmpfile;
	 size2 = tmpfile.size();
	 char tmp2[1024];
	 strcpy(tmp2,tmpfile.c_str());
	 tmp2[size2]='\0';
	 strcpy(filename[i],tmp2);
//	 cout << filename[i] << endl;
	 
 }

}
void MySaxParser::on_end_document()
{
	writing();
  //std::cout << "**********************End Document**********************************" << std::endl;
}

void MySaxParser::on_start_element(const Glib::ustring& name,
                                   const AttributeList& attributes)
{
	//tagnm1 = tagnm2;
	//tagnm2 = tagnm3;
	tagnm3 = name;
	
	taglist.push(tagnm3);
 //std::cout << "node name=" << name << tagnm1 << " " << tagnm2 << " " << tagnm3 << std::endl;


  // Print attributes:
  for(xmlpp::SaxParser::AttributeList::const_iterator iter = attributes.begin(); iter != attributes.end(); ++iter)
  {
	  try
	  {
		  //char str[] ="- This, a sample string.";
		  //char *pch = iter->name;
//		  string s = iter->name.lowercase();
		  //printf ("Splitting string \"%s\" into tokens:\n",str);
		  /*pch = strtok (iter->name," }{[]><|=");
		 char *s = toLowerCase(pch);		
		  while (pch != NULL)
		  {
			  printf ("%s\n",pch);
			  pch = strtok (NULL, " }{[]><|=");
			 s = toLowerCase(pch);
		  }*/
      //std::cout << "  Attribute name=" << iter->name << std::endl;
	
    }
    catch(const Glib::ConvertError& ex)
    {
      std::cerr << "MySaxParser::on_start_element(): Exception caught while converting name for std::cout: " << ex.what() << std::endl;
    }

    try
    {
      //std::cout << "    , value= " << iter->value << std::endl;
    }
    catch(const Glib::ConvertError& ex)
    {
      std::cerr << "MySaxParser::on_start_element(): Exception caught while converting value for std::cout: " << ex.what() << std::endl;
    }
  }
}

void MySaxParser::on_end_element(const Glib::ustring& /* name */)
{
  //std::cout << "on_end_element()" << std::endl;
  if(!taglist.empty())
  {
	  string checkTag = taglist.top();
  taglist.pop();
  if(checkTag=="page")
  {
	//  writing();
	  boost::split(titlevector, title, boost::is_any_of(delimiters), boost::token_compress_on);
	  int i;
	  for(i=0;i<titlevector.size();i++)cout << titlevector[i] << " title " << docid << endl;
	  inflateDicitionary(titlevector);
	  titlevector.clear();
	  title="";
	  

  }

  }
  bracesPresent=0,bracesCount=0,infoBox=0;
  presentChar=' ',lastChar=' ';
}

void MySaxParser::on_characters(const Glib::ustring& text)
{
  try
  {
    //std::cout << "on_characters(): " << text << std::endl;
	  string str = text.lowercase();
    	//cout << text.size() << "*******size*******************\n";

	if ( taglist.size()>=2)
	{
	tagnm1 = taglist.top();
	taglist.pop();
	tagnm2 = taglist.top();
	taglist.pop();
	  if(tagnm1=="id" && tagnm2=="page")
	  {
	  docid = str;
	  //cout << "***************doc id**************** " << docid << " " << str.size() << endl;
	  }
	  taglist.push(tagnm2);
	  taglist.push(tagnm1);
	}
	if(tagnm1=="title")title = title + str;
	else
	{
	
	//cout << str ;
	  //unsigned int i;
	  vector<std::string> parts;
	  //boost::split(parts, str, boost::is_any_of(delimiters), boost::token_compress_on);
	  int posin1 = 0,posin2 = 0;
	  int si2 = str.size();
	  unsigned int i;
	  int differ = 'A' - 'a';
	 // string st_temp;
	  for(i=0;i<si2;i++)
	  {
		  lastChar = presentChar;
		  presentChar=str.at(i);
		  if(lastChar=='{' && presentChar=='{' && infoBox==0)
		  {
			  bracesPresent++;
			  presentChar=' ';
		  }
		  if(lastChar=='{' && presentChar=='{' && infoBox==1 && bracesPresent>=1)
		  {
			  bracesCount++;
			  presentChar=' ';
		  }
		  if(lastChar=='}' && presentChar=='}' && infoBox==1 && bracesCount>=1)
		  {
			  bracesCount--;
			  presentChar=' ';
			  if(bracesCount==0)infoBox=0;
		  }

		  if(!(str.at(i)>='a' && str.at(i)<='z'))
		  {
			  if(str.at(i)=='\n')
			  {
				  tagFlag="";
			  }
			  st_temp = st_temp + str.substr(posin1,i-posin1);
			  if(st_temp.size()!=0)parts.push_back(st_temp);
			  posin1 = i+1;
			  if(st_temp=="infobox")
			  {
				  infoBox=1;
				  if(bracesPresent>=1)bracesCount=1;
			  }

			  if(st_temp=="http")
			  {
				  tagFlag="http";
			  }
			  else if(st_temp=="category")
			  {
				  tagFlag="category";
			  }

			  if(bracesCount>=1 && st_temp.size()>0 && infoBox==1)cout << st_temp << " " << " infoBox " << docid << endl;
			  if(tagFlag=="http" && st_temp.size()>0)cout << st_temp << " http " << docid << endl;
			  if(tagFlag=="category" && st_temp.size()>0)cout << st_temp << " category " << docid << endl;
			  if(tagFlag=="" && st_temp.size()>0 && bracesCount==0 && infoBox==0)cout << st_temp << " body " << docid << endl;

			  st_temp = "";


		  }
		  
	  }
	  if(posin1 != si2)
	  {
		  st_temp = st_temp + str.substr(posin1);
	  }
	  inflateDicitionary(parts);
	}
	 // for(i=0;i<parts.size();i++)
	 // cout << parts[i] << endl;

	  //parts.clear();
	  /*BOOST_FOREACH(string t, parts)
	    {
	    cout << t << "." << endl;
	    }*/

  }
  catch(const Glib::ConvertError& ex)
  {
    std::cerr << "MySaxParser::on_characters(): Exception caught while converting text for std::cout: " << ex.what() << std::endl;
  }
}

void MySaxParser::on_comment(const Glib::ustring& text)
{
  try
  {
    std::cout << "on_comment(): " << text << std::endl;
  }
  catch(const Glib::ConvertError& ex)
  {
    std::cerr << "MySaxParser::on_comment(): Exception caught while converting text for std::cout: " << ex.what() << std::endl;
  }
}

void MySaxParser::on_warning(const Glib::ustring& text)
{
  try
  {
    std::cout << "on_warning(): " << text << std::endl;
  }
  catch(const Glib::ConvertError& ex)
  {
    std::cerr << "MySaxParser::on_warning(): Exception caught while converting text for std::cout: " << ex.what() << std::endl;
  }
}

void MySaxParser::on_error(const Glib::ustring& text)
{
  try
  {
    std::cout << "on_error(): " << text << std::endl;
  }
  catch(const Glib::ConvertError& ex)
  {
    std::cerr << "MySaxParser::on_error(): Exception caught while converting text for std::cout: " << ex.what() << std::endl;
  }
}

void MySaxParser::on_fatal_error(const Glib::ustring& text)
{
  try
  {
    std::cout << "on_fatal_error(): " << text << std::endl;
  }
  catch(const Glib::ConvertError& ex)
  {
    std::cerr << "MySaxParser::on_characters(): Exception caught while converting value for std::cout: " << ex.what() << std::endl;
  }
}

