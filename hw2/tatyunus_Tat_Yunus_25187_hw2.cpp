#include<iostream>
#include <string>
#include <fstream>
#include<sstream>
#include "2dlinkedlist.h"
string reverse(string str) //reversing for the only using 2 function for searcing and other 2 function for deleting.If ýt is not used I need 8 function
{ 
	string a="";
	for (int i=str.length()-1; i>=0; i--) 
		a +=str[i]; 
	return a;
} 


using namespace std;


int main()
{

	string filename;
	ifstream f;
	cout<<"Welcome to a mixture of Candy Crush and Sunday Morning Puzzle."<<endl;
	cout<<"Please enter a filename for the puzzle: ";
	cin>>filename;
	f.open(filename.c_str());
	while(f.fail())//it is fail condition
	{
		cout<<"Failed.."<<endl;
		cout<<"Please enter another filename for the puzzle: ";
		cin>>filename;
		f.open(filename.c_str());
	}
	cout<<"Success!";
	cout<<endl;
	string line,name;
	int rowcounter=0,colcounter=0;
	linkedlist myfourthlylinkedlist;
	getline(f,line);
	stringstream ss(line);
	int x;
	int y;
	ss>>x;
	ss>>y;
	getline(f,line);
	stringstream sk(line);
	char a;
	while(sk >>a)
	{
		myfourthlylinkedlist.addtoend(a);//creating the doublylinkedlist
	}

	while(getline(f,line))//it is used to first linking the doubly linked list's first nodes
	{
		stringstream ss(line);
		ss>>a;
		myfourthlylinkedlist.movetodownline(a);
		while(ss>>a)
		{
			myfourthlylinkedlist.addtoend1(a);
		}
	}
	myfourthlylinkedlist.baglayici(x);// as it explained,it is used to link doubly linked list lines
	int totalpoint=0;
		myfourthlylinkedlist.realprintlist(totalpoint);
	;
	while(myfourthlylinkedlist.emre()!=NULL)//looking all the conditions with if else firstly left to right then right to left then top to down then down to top
	{
		cout<<"Please enter a word: ";
		cin>>name;
		string reversedstring=reverse(name);
		if(name.length()<3)
		{
			cout<<"Game has ended."<<endl;
			cout<<"Total points: "<<totalpoint<<"."<<endl;
			break;//if a word length is smaller than 3 it is broken
		}
		else
		{
			bool p1=myfourthlylinkedlist.lefttorightsearch(name,rowcounter);
			if(p1)
			{
				myfourthlylinkedlist.deletelefttoright(rowcounter);
				cout<<"Word "<<name<<" is found."<<endl;
				cout<<name.length()<<" points are earned."<<endl;
				totalpoint+=name.length();
				cout<<"Total points: "<<totalpoint<<"."<<endl;
				myfourthlylinkedlist.realprintlist(totalpoint);

			}
			else
			{
				bool p2=myfourthlylinkedlist.lefttorightsearch(reversedstring,rowcounter);
				if(p2)
				{
					myfourthlylinkedlist.deletelefttoright(rowcounter);
					cout<<"Word "<<name<<" is found."<<endl;
					cout<<name.length()*2<<" points are earned."<<endl;
					totalpoint+=name.length()*2;
					cout<<"Total points: "<<totalpoint<<"."<<endl;
					myfourthlylinkedlist.realprintlist(totalpoint);
				}
				else
				{
					bool p3=myfourthlylinkedlist.toptobottomsearch(name,rowcounter);
					if(p3)
					{
						myfourthlylinkedlist.deletetoptobottom(rowcounter);
						cout<<"Word "<<name<<" is found."<<endl;
						cout<<name.length()+2<<" points are earned."<<endl;
						totalpoint +=name.length()+2;
						cout<<"Total points: "<<totalpoint<<"."<<endl;
						myfourthlylinkedlist.realprintlist(totalpoint);
					}
					else
					{
						bool p4=myfourthlylinkedlist.toptobottomsearch(reversedstring,rowcounter);
						if(p4)
						{
							myfourthlylinkedlist.deletetoptobottom(rowcounter);
							cout<<"Word "<<name<<" is found."<<endl;			
							cout<<(name.length()*2)+2<<" points are earned."<<endl;
							totalpoint+=(name.length()*2)+2;
							cout<<"Total points: "<<totalpoint<<"."<<endl;
							myfourthlylinkedlist.realprintlist(totalpoint);
						}
						else
						{
							cout<<"The word cannot be found in the puzzle."<<endl;
							cout<<"5 points are deducted."<<endl;
							totalpoint-=5;
							cout<<"Total points: "<<totalpoint<<"."<<endl;
						}
					}

				}
			}
		}
	}







	return 0;

}












