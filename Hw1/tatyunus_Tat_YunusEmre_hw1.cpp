//Created by Yunus Emre TAT on 6.7.2019
//Copright 2019 Yunus Emre TAT.All rights reserved.

#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>
#include<iomanip>
#include<stdlib.h>
using namespace std;
void print(const vector<vector<int> >&x)//printing the matrix
{
	cout<<"The matrix is being printed:"<<endl;
	for(int i=0;i<x.size();i++)
	{
		for(int k=0;k<x[0].size();k++)
		{
			cout<<x[i][k]<<" ";
		}
		cout<<endl;

	}

}
void printingtemp(const vector<vector<int> >&x)//printing the temp matrix(temp matrix is end of the function writing different sentences)
{
	cout<<"Printing the main matrix: "<<endl;
	for(int i=0;i<x.size();i++)
	{
		for(int k=0;k<x[0].size();k++)
		{
			cout<<x[i][k]<<" ";
		}
		cout<<endl;

	}

}
void copyanelement(vector<vector<int> >&x,int a,int b,int c,int d)
{
	x[c][d]=x[a][b];
	cout<<"The element at Row "<<a<<", Column "<<b<<" is being copied to Row "<<c<<", Column "<<d<<"."<<endl;
}

void swappedelement(vector<vector<int> >&x,int a,int b,int f,int g)//swapping element
{
	int temp=x[a][b];
	x[a][b]=x[f][g];
	x[f][g]=temp;
	cout<<"The element at Row "<<a<<", Column "<<b<<" is being swapped with the element at Row "<<f<<", Column "<<g<<"."<<endl;
}
void onerowprint(const vector<vector<int> >&x,int a)//getting a row and printing
{
	cout<<"Row "<<a<<" is being printed:"<<endl;
	for(int i=0;i<x[0].size();i++)
	{
		cout<<x[a][i]<<" ";
	}
	cout<<endl;
}
void swappedrow(vector<vector<int> >&x,int a,int b)//getting row number and swapping each other
{
	for(int i=0;i<x[0].size();i++)
	{
		int temp=x[a][i];
		x[a][i]=x[b][i];
		x[b][i]=temp;
	}
	cout<<"Row "<<a<<" is being swapped with Row "<<b<<"."<<endl;
}
void copyrow(vector<vector<int> >&x,int a,int b)//copy to row
{
	for(int i=0;i<x[0].size();i++)
	{
		x[b][i]=x[a][i];
	}
	cout<<"Row "<<a<<" is being copied to Row "<<b<<"."<<endl;
}
void swappedcol (vector<vector<int> >&x,int a ,int b)//we have columns to swapping eachother
{
	for(int i=0;i<x.size();i++)
	{
		int temp=x[i][a];
		x[i][a]=x[i][b];
		x[i][b]=temp;
	}
	cout<<"Column "<<a<<" is being swapped with Column "<<b<<"."<<endl;
}
void copycol(vector<vector<int> >&x,int a,int b)//copying to column
{
	for(int i=0;i<x.size();i++)
	{
		x[i][b]=x[i][a];
	}
	cout<<"Column "<<a<<" is being copied to Column "<<b<<"."<<endl;
}
void colprinter(const vector<vector<int> >&x,int a)
{
	cout<<"Column "<<a<<" is being printed:"<<endl;
	for(int i=0;i<x.size();i++)
	{
		cout<<x[i][a]<<" ";
	}
	cout<<endl;
}//we have a prompt to print
void gettingdat(vector<vector<int> >&x,int a,int b)
{
	int number;
	cout<<"Please enter an input for the element at Row "<<a<<", Column "<<b<<": ";
	cin>>number;
	x[a][b]=number;
}//getting a number to put our matrix with coordinates
void printingdata(const vector<vector<int> >&x,int a ,int b)//we want print only a elemnt from matrix w
{
	cout<<"The element at Row "<<a<<", Column "<<b<<" is being printed: "<<endl;
	cout<<x[a][b]<<endl;
}
void printingdatrow(vector<vector<int> >&p,int a)//gettig a number to writing a row
{
	int number;
	cout<<"Please enter an input for Row "<<a<<": ";
	cin>>number;
	for(int i=0;i<p[0].size();i++)
	{
		p[a][i]=number;
	}
}
void printingdatcol(vector<vector<int> >&p,int a)//getting a number to writing a column
{
	int number;
	cout<<"Please enter an input for Column "<<a<<": ";
	cin>>number;
	for(int i=0;i<p.size();i++)
	{
		p[i][a]=number;
	}

}

void allchange(vector<vector<int> >&x)//writing the matrix again with number which was given from user
{
	int number;
	cout <<"Please enter an input for the matrix: ";
	cin>>number;
	for(int i=0;i<x[0].size();i++)
	{
		for(int k=0;k<x.size();k++)
		{
			x[k][i]=number;
		}

	}

}
void kestimbictim(vector<int>ct,const vector<vector<int> >&y,vector<vector<int> >&kesik)//cutting matrix to creating new matrix
{
	int p;
	for(int i=0;i<ct[0];i++)
	{
		vector<int>a;
		for(int k=0;k<ct[1];k++)
		{
			 p=y[i][k];
			 a.push_back(p);
		}
		kesik.push_back(a);
	}
}
void hadidikelim(vector<vector<int> >&y,vector<vector<int> >&kesik)//to getting new matrix after getting coordinates it is a function
{
	for(int i=0;i<kesik.size();i++)
	{
		for(int k=0;k<kesik[0].size();k++)
		{
			y[i][k]=kesik[i][k];
		}
	}

}

bool controlboundriesforcutting(vector<int>x,vector<int>y)//we have some rules to implement boundries
{
	int matrixrow=x[0];
	int matrixcol=x[1];
	int comrow=y[0];
	int comcol=y[1];
	if(matrixrow >comrow || matrixcol>comcol)
	{
		return false;
	}
	return true;

}
bool controlboundries(vector<int>x,vector<int>y)//we have some rules to implement boundries
{
	int matrixrow=x[0];
	int matrixcol=x[1];
	int comrow=y[0];
	int comcol=y[1];
	if(comrow >matrixrow || comcol > matrixcol)
	{
		return false;
	}
	return true;

}
string promptsettinger(string s)//promptsettinger is a very meaningful function to creating super algoritm function's aim is to create new string which only consists symbols
{
	char ch;
	string husnu="";
	for(int i=0;i<s.size();i++)
	{
		if(!isdigit(s[i]) && s[i] !=' ')
		{
			husnu+=tolower(s[i]);
		}

	}
	return husnu;

}
string settingerdigit(string s)//settingerdigit is a function which creates string which is only consisted with digit.It is a key role 
{
	char ch;
	string suat="";
	for(int i=0;i<s.size();i++)
	{
		if(isdigit(s[i]))
		{
			suat +=tolower(s[i]);
		}

	}
	return suat;

}
//first class function which is the cornerstone of my code.We have some compiler prompts to do commands.We are getting commands and operating them
void commandsislev(const vector<string>& x,const vector<string>&t,vector<vector<int> >&y)//x commands,t commandsnumbers
{
	for(int i=0;i<x.size();i++)
	{
		if(x[i]==".<>.")
		{
			string s=t[i];
			int a=s[0]-48;int b=s[1]-48;int c=s[2]-48;int d=s[3]-48;
			swappedelement(y,a,b,c,d);
		}
		else if(x[i]=="o.x")
		{
			string e=t[i];
			int f=e[0]-48;
			onerowprint(y,f);
		}
		else if(x[i]==".x<>.x")
		{
			string g=t[i];
			int q=g[0]-48;int w=g[1]-48;
			swappedrow(y,q,w);
		}
		else if(x[i]==".x>.x")
		{
			string r=t[i];
			int h=r[0]-48;int j=r[1]-48;
			copyrow(y,h,j);
		}
		else if(x[i]=="o")
		{
			print(y);
		}
		else if(x[i]=="x.<>x.")
		{
			string a=t[i];
			int b=a[0]-48;int c=a[1]-48;
			swappedcol(y,b,c);
		}
		else if(x[i]=="x.>x.")
		{
			string a=t[i];
			int b=a[0]-48;int c=a[1]-48;
			copycol(y,b,c);
		}
		else if(x[i]=="ox.")
		{
			string a=t[i];
			int b=a[0]-48;
			colprinter(y,b);
		}
		else if(x[i]=="i.")
		{
			string a=t[i];
			int b=a[0]-48;int c=a[1]-48;
			gettingdat(y,b,c);
		}
		else if(x[i]=="o.")
		{
			string a=t[i];
			int b=a[0]-48;int c=a[1]-48;
			printingdata(y,b,c);
		}
		else if(x[i]==".x>.x")
		{
			string a=t[i];
			int b=a[0]-48;int c=a[0]-48;
			copyrow(y,b,c);
		}
		else if(x[i]=="i.x")
		{
			string a=t[i];
			int b=a[0]-48;
			printingdatrow(y,b);
		}
		else if(x[i]=="i")
		{
			allchange(y);
		}
		else if(x[i] ==".>.")
		{
			string a=t[i];
			int b=a[0]-48;int c=a[1]-48;int d=a[2]-48;int e=a[3]-48;
			copyanelement(y,b,c,d,e);
		}
		else if(x[i]=="ix.")
		{
			string a=t[i];
			int b=a[0]-48;
			printingdatcol(y,b);
		}


	}
	cout<<"Commands are completed."<<endl;

}
vector<string> settingerprompt(vector<string>x)
{
	string a;
	vector<string> y;
	for(int i=0;i<x.size();i++)
	{
		a=promptsettinger(x[i]);
		y.push_back(a);
	}
	return y;
}
// this function will provide us pure vector to directly use
vector<string> purevectoring(vector<string>x)
{   
	vector<string>y;
	string a;
	for(int i=0;i<x.size();i++)
	{
		a=settingerdigit(x[i]);
		y.push_back(a);
	}
	return y;

}








int main()
{
	cout<<"Welcome to the first boring CS204 Homework."<<endl;
	cout<<"This program does matrix operations as instructed by a command file."<<endl;
	cout<<"In order to start, please enter a matrix file name: ";
	string filename,commandname;
	cin>>filename;
	//creating the vectors and pushing the elements to the vector
	ifstream f,c;
	vector<vector<int> >x;
	f.open(filename.c_str());//opening files to implementing vectors
	while(f.fail())
	{
		cout<<"Wrong file name!"<<endl;
		cout<<"Please enter another matrix file name: ";
		cin>>filename;
		f.open(filename);
	}
	cout<<"Success!";

	string line1;
	getline(f,line1);
	int numbers0;
	stringstream ff(line1);
	vector<int> matrixdim;
	while(ff>>numbers0)
	{
		matrixdim.push_back(numbers0);
	}

	string line;
	while(!f.eof())// we first get the dimensions to other vector and then creating vectors to pushing items
	{
		getline(f,line);
		stringstream ss (line);
		int num;
		vector<int>xp;
		while(ss>>num)
		{
			xp.push_back(num);
		}
		x.push_back(xp);

	}
	f.close();
	cout<<endl;
	cout<<"Please enter a command file name: ";
	cin>>commandname;
	c.open(commandname.c_str());
	while(c.fail())//a loop for controling the filename
	{
		cout<<"Wrong file name!"<<endl;
		cout<<"Please enter another command file name: ";
		cin>>commandname;
		c.open(commandname);
	}
	cout<<"Success!"<<endl;
	char ch;
	string str="";
	vector<string>strvec;
	vector<vector<int> >temp;
	string lines;
	int numbers;
	getline(c,lines);
	vector<int> commandstutucu;
	stringstream ss(lines);
	while(ss>>numbers)//creating new vector for dimensions.Not preference to print whole matrix to the a matrix
	{
		commandstutucu.push_back(numbers);
	}


	while(c.get(ch))//when we getting characters we have some rules we only want symbols 
	{
		if(ch != '\t')
		{
			if(ch!='\n' )
			{
				if(ch!='\r')
				{

				if(ch !=';')
				{
					str +=ch;
				}
				
				else
				{
					strvec.push_back(str);
					str="";

				}
			}
		}		
		}	
	}
	bool a=controlboundries(matrixdim,commandstutucu);
	bool b=controlboundriesforcutting(matrixdim,commandstutucu);
	if(!a)//we have some rules and if you dont obey them our program is not efficent for you
	{
		cout<<"Command and matrix dimensions do not work together. Program exiting..."<<endl;
		return 1;
	}	
	if(!b)//if matrix dimensions are bigger than commands dimensions that means we have to go if 
	{
		kestimbictim(commandstutucu,x,temp);
		vector<string> y=settingerprompt(strvec);
		vector<string>purevec=purevectoring(strvec);
		commandsislev(y,purevec,temp);
		hadidikelim(x,temp);
		printingtemp(x);
		return 1;

	}



	vector<string> y=settingerprompt(strvec);
	vector<string>purevec=purevectoring(strvec);//pure vector means last vector for vector process
	commandsislev(y,purevec,x);
	printingtemp(x);
	return 0;
	
	
	


	






}
