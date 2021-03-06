#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;

map<string,int> word_count;
map<string, int>::iterator iter;
vector<pair<int, string> > vec;

int count_ch(char* a);
int count_word(char* a);
int count_line(char* a);
bool cmp(pair<int, string> a, pair<int, string> b);
void MapSortOfValue(vector<pair<int,string> >& vec,map<string,int>& m);
int main(int argc,char* argv[]) 
{   
    ofstream out("result.txt");  
    if(out.is_open())   
    {  
        out<<"characters: "<<count_ch(argv[1])<<endl;  
        out<<"words: "<<count_word(argv[1])<<endl;
        out<<"lines: "<<count_line(argv[1])<<endl;
        MapSortOfValue(vec,word_count);
		for(int i=0;i<vec.size()&&i<10;i++)
			out<<"<"<<vec[i].second.c_str()<<">:"<<vec[i].first<<endl;
        out.close();  
    }
    return 0;  
} 
int count_ch(char* a)
{
	char ch;  
	int num=0;
    ifstream in(a); 
    if(!in.is_open())  
    { 
		cout<<"Error opening file";
		exit (1); 
	}  
    while(!in.eof())  
    {  
    	in.get(ch);  
        num++;
    } 
    in.close();
    return num;
}
int count_word(char* a)
{
	int num=0,flag=0,count=0;
	char ch,word[100];
	
    ifstream in(a);  
    if(!in.is_open())  
    { 
		cout<<"Error opening file";
		exit (1); 
	}  
    while(!in.eof())  
    {  
    	in.get(ch);
    	if(count<4&&((ch>='A'&&ch<='Z')||(ch>='a'&&ch<='z')))
    	{
    		if(ch>='A'&&ch<='Z')ch+=32;
    		word[count++]=ch;
		}
		else if(count>=4&&((ch>='A'&&ch<='Z')||(ch>='a'&&ch<='z')||(ch>='0'&&ch<='9')))
    	{
    		if(ch>='A'&&ch<='Z')ch+=32;
    		word[count++]=ch;
		}
		else
		{
			if(count>=4)
			{
				num++;
				++word_count[word];
			}
			count=0;
			for(int i=0;i<30;i++)
				word[i]='\0';
		}
    }
    if(count>=4)
	{
		word[count-1]='\0';
		num++;
		++word_count[word];
	}
    in.close();
    return num;
}
int count_line(char* a)
{
	char ch[10000];
	int num=0;
    ifstream in(a);  
    if(!in.is_open())  
    { 
		cout<<"Error opening file";
		exit (1); 
	}  
    while(!in.eof())  
    {  
    	in.getline(ch,10000);
    	if(ch[0]!='\0')
        	num++;
    } 
    in.close();
    return num;
}
bool cmp(pair<int, string> a, pair<int, string> b)
{
	return (a.first != b.first) ? a.first > b.first:a.second < b.second;
}
void MapSortOfValue(vector<pair<int, string> >& vec, map<string, int>& m)
{
	for(map<string, int>::iterator it = m.begin(); it != m.end(); it++)
		vec.push_back(make_pair(it->second, it->first));
	sort(vec.begin(),vec.end(),cmp);
}
