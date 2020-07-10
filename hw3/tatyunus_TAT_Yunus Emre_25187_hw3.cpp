#include <iostream>
#include<sstream>
#include<string>
#include<vector>
#include<fstream>
#include<climits>
using namespace std;
struct Point
{
	int x;
	int y;
};
struct StackNode
{
	Point value;
	StackNode *next;
};
class Mazestack
{
private:
	StackNode *top;
	int size;
public:
	Mazestack();
	Mazestack(const Mazestack & s);
	~Mazestack();
	bool isEmpty();
	void push(int x,int y);
	void pop(int &x,int &y);
	const Mazestack &operator =(const Mazestack &rhs);
	const Mazestack& operator >>(Point &);
	const Mazestack & operator <<(Point );
	int& takingsize();
	string promptingstring()const;

};
Mazestack::Mazestack(const Mazestack &rhs) //The copy constructor is a constructor which creates an object by initializing it with an object of the same class.
{
	size=rhs.size;
	StackNode *a=rhs.top;// which has been created previously.
	int x,y;
	Point p;
	while(a!=NULL)
		{
			p.x=a->value.x;
			p.y=a->value.y;
			this->push(p.x,p.y);//initializing process
			a=a->next;
		}
}
string Mazestack::promptingstring() const
{//creating a string add to stack meembers to string and printing 
	StackNode *temp=top;
	string nameofthestring="";
	string different="";
	while(temp!=NULL)
	{
		int x=temp->value.x;
		int y=temp->value.y;
		nameofthestring+=to_string(x);
		nameofthestring+=",";
		nameofthestring+=to_string(y);
		nameofthestring+="\n";
		temp=temp->next;
	}

	return nameofthestring;



}

Mazestack::Mazestack()
{//default constructor which can be called with no arguments 
	top=NULL;
	size=0;
}
int& Mazestack::takingsize()
{//returning size to compare each other
	return size;
}
const Mazestack& Mazestack::operator=(const Mazestack &Mazestacks)
{//assignment operator is a special case of assignment operator where the source (right-hand side) and destination (left-hand side) are of the same class type.
	StackNode *taker=Mazestacks.top;
	StackNode copied;
	if(Mazestacks.top==NULL)
	{
		return *this;
	}
	//first clear left-hand side becaue aim is creating completely same 
	while(!(this->isEmpty()))
	{
		StackNode* ptr=this->top;
		this->top=this->top->next;
		delete ptr;
	}
	int x,y;
	// pushing the lhs stack
	while(taker !=NULL)
	{
		int x=taker->value.x;
		int y =taker->value.y;
		this->push(x,y);
		taker=taker->next;
	}

	this->size=Mazestacks.size;
	return *this;

}

Mazestack::~Mazestack()
{//The memory is allocated before the constructor is called, and it is freed only after the last destructor has finished.
	StackNode *head;
	StackNode *toptemplate=top;
	while(toptemplate!=NULL)
	{
		head=toptemplate->next;
		delete toptemplate;
		toptemplate=head;
	}



}
ostream &operator<<(ostream &os,const Mazestack&complex)
{//it is implemented with using normal pushing funciton
	os<<complex.promptingstring();
	return os;
}


void Mazestack::pop(int &numx,int &numy)
{// removes top element from the stack and reduces size of stack by one.
	StackNode *temp;

	if (isEmpty())
	{
		cout << "The stack is empty.\n";
	}
	else	// pop value off top of stack
	{
		numx = top->value.x;
		numy=top->value.y;
		temp = top->next;
		delete top;
		top = temp;
	}
	size=size-1;
}

void Mazestack::push(int x,int y)
{
	StackNode *newNode;

	// Allocate a new node & store Num
	newNode = new StackNode;
	newNode->value.x = x;
	newNode->value.y=y;

	// If there are no nodes in the list
	// make newNode the first node
	if (isEmpty())
	{
		top = newNode;
		newNode->next = NULL;
	}
	else	// Otherwise, insert NewNode before top
	{
		newNode->next = top;
		top = newNode;
	}
	size++;
}// insert new elements in the stack. The elements are inserted at the top of the stack.

const Mazestack& Mazestack::operator<<(Point p)
{//pushing operations implemented by push
	this->push(p.x,p.y);
	return *this;
}
const Mazestack& Mazestack::operator>>(Point& p)
{//poping function implemented by pop function
	this->pop(p.x,p.y);
	return *this;

};

void PrintMatrix(int **matrix, int rowsize,int colsize)
{//prinint function to show how the work is going 
	for(int i=0; i<rowsize; i++)
	{
		for(int j=0; j<colsize; j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}
void DeleteMatrix(int ** matrix, int rowsize)
{//delete function to remove the matrix (refresh allocated memory)
	for(int i=0; i<rowsize; i++)
	{
		delete [] matrix[i];
	}
	delete matrix;
}
bool Mazestack::isEmpty(void)
{//isempty function to controlling the top private data
	bool status;

	if (top == NULL)
		status = true;
	else
		status = false;

	return status;
}

int main()
{
	ifstream f;
	string filename;
	cout<<"Welcome to the homework "<<char(34)<<"A Great Day for Freedom"<<char(34)<<"."<<endl;
	cout<<"Please enter a file name for the maze: ";
	cin>>filename;
	f.open(filename.c_str());
	if(f.fail())
	{
		cout<<"File name is incorrect. Program exiting..."<<endl;
		return 0;
	}
	int arraysize,row,column,number,columnbas,rowbas;
	string line;
	getline(f,line);//it is not in the loop because only aim to getting the first two line
	istringstream ss(line);
	ss>>number;
	column=number;
	ss>>number;
	row=number;
	getline(f,line);
	istringstream st(line);
	st>>number;
	columnbas=number;
	st>>number;
	rowbas=number;
	int **matrix=new int*[row];
	for(int i=0;i<row;i++)
	{
		matrix[i]=new int[column];
	}
	int i=0,k=0;
	while(getline(f,line))//getting line to create matrix
	{
		stringstream sk(line);
		while(sk>>number)
		{
			matrix[i][k]=number;
			k++;
		}
		k=0;
		i++;
	}
	Mazestack s;//the first stack to store data
	s.takingsize()=INT_MAX;//determining the size biggest number for compare
	if(columnbas!=0 &&rowbas==0)
	{	
		
		while(matrix[rowbas+1][columnbas]!=1)
		{
		int nextpathx=rowbas+1;//our aim is to scan all the available Stacknode
		int nextpathy=columnbas;
		Mazestack tempstack;
		    Point p;
		    p.x=rowbas;
		    p.y=columnbas;
			tempstack<<p;//first place is contained by stack
			bool flag=false;
			while(!(nextpathx==0||nextpathy==0||nextpathx==row-1||nextpathy==column-1||flag==true))//our condition it is not located in entry point conditions(located in edges)
			{
					if((matrix[nextpathx-1][nextpathy]==0) && !(p.x==nextpathx-1 &&p.y==nextpathy))//looking up and condition is it must not be past location
					{
						p.x=nextpathx;
						p.y=nextpathy;
						tempstack<<p;
						nextpathx-=1;
						

					}
					else if((matrix[nextpathx+1][nextpathy]==0) && !(p.x==nextpathx+1 &&p.y==nextpathy))//looking down and condition is it must not be past location
					{
						p.x=nextpathx;
						p.y=nextpathy;
						tempstack<<p;
						nextpathx+=1;
					}
					else if((matrix[nextpathx][nextpathy+1]==0) && !(p.x==nextpathx &&p.y==nextpathy+1))//looking right and condition is it must not be past location
					{
						p.x=nextpathx;
						p.y=nextpathy;
						tempstack<<p;
						nextpathy+=1;
					}


					else if((matrix[nextpathx][nextpathy-1]==0) && !(p.x==nextpathx &&p.y==nextpathy-1))//looking left and condition is it must not be past location
					{
						p.x=nextpathx;
						p.y=nextpathy;
						tempstack<<p;
						nextpathy-=1;

					}

					else
					{
						matrix[nextpathx][nextpathy]=1;//it is locked point between 1 number
						flag=true;

					}
				}
				if(flag==false)//if it is located in out of the second while that means a condition in while is not provided means it can reach the out point
				{
					p.x=nextpathx;
					p.y=nextpathy;
					tempstack<<p;
					matrix[nextpathx][nextpathy]=1;
		
					 if(s.takingsize()>tempstack.takingsize()){//if s size bigger number than temp(new path) means assign it as s 
						s=tempstack;
					
					}

				}

		}

	}
	if(columnbas==0 &&rowbas!=0)// condition assume the it is located in column 0 edge
	{	
		
		while(matrix[rowbas][columnbas+1]!=1)
		{
		int nextpathx=rowbas;
		int nextpathy=columnbas+1;
		int k=0;
		Mazestack tempstack;
		    Point p;
		    p.x=rowbas;
		    p.y=columnbas;
			tempstack<<p;
			bool flag=false;
			while(!(nextpathx==0||nextpathy==0||nextpathx==row-1||nextpathy==column-1||flag==true))//our condition it is not located in entry point conditions(located in edges)
			{
					if((matrix[nextpathx-1][nextpathy]==0) && !(p.x==nextpathx-1 &&p.y==nextpathy))//looking up and condition is it must not be past location
					{
						p.x=nextpathx;
						p.y=nextpathy;
						tempstack<<p;
						nextpathx-=1;
						

					}
					else if((matrix[nextpathx+1][nextpathy]==0) && !(p.x==nextpathx+1 &&p.y==nextpathy))//looking down and condition is it must not be past location
					{
						p.x=nextpathx;
						p.y=nextpathy;
						tempstack<<p;
						nextpathx+=1;
					}
					else if((matrix[nextpathx][nextpathy+1]==0) && !(p.x==nextpathx &&p.y==nextpathy+1))//looking right and condition is it must not be past location
					{
						p.x=nextpathx;
						p.y=nextpathy;
						tempstack<<p;
						nextpathy+=1;
					}


					else if((matrix[nextpathx][nextpathy-1]==0) && !(p.x==nextpathx &&p.y==nextpathy-1))//looking left and condition is it must not be past location
					{
						p.x=nextpathx;
						p.y=nextpathy;
						tempstack<<p;
						nextpathy-=1;

					}

					else//it is locked point between 1 number
					{
						matrix[nextpathx][nextpathy]=1;
						flag=true;

					}
				}
				if(flag==false)//if it is located in out of the second while that means a condition in while is not provided means it can reach the out point
				{
					p.x=nextpathx;
					p.y=nextpathy;
					tempstack<<p;
	
					matrix[nextpathx][nextpathy]=1;
					nextpathx=rowbas;
					nextpathy=columnbas;
				
					 if(s.takingsize()>tempstack.takingsize()){//if s size bigger number than temp(new path) means assign it as s
						s=tempstack;
					}

				}

		}

	}
	if(columnbas==column-1 &&rowbas!=0)
	{	
		
		while(matrix[rowbas][columnbas-1]!=1)
		{
		int nextpathx=rowbas;
		int nextpathy=columnbas-1;
		int k=0;
		Mazestack tempstack;
		    Point p;
		    p.x=rowbas;
		    p.y=columnbas;
			tempstack<<p;
			bool flag=false;
			while(!(nextpathx==0||nextpathy==0||nextpathx==row-1||nextpathy==column-1||flag==true))//our condition it is not located in entry point conditions(located in edges)
			{
					if((matrix[nextpathx-1][nextpathy]==0) && !(p.x==nextpathx-1 &&p.y==nextpathy))//looking up and condition is it must not be past location
					{
						p.x=nextpathx;
						p.y=nextpathy;
						tempstack<<p;
						nextpathx-=1;
						

					}
					else if((matrix[nextpathx+1][nextpathy]==0) && !(p.x==nextpathx+1 &&p.y==nextpathy))//looking down and condition is it must not be past location
					{
						p.x=nextpathx;
						p.y=nextpathy;
						tempstack<<p;
						nextpathx+=1;
					}
					else if((matrix[nextpathx][nextpathy+1]==0) && !(p.x==nextpathx &&p.y==nextpathy+1))//looking right and condition is it must not be past location
					{
						p.x=nextpathx;
						p.y=nextpathy;
						tempstack<<p;
						nextpathy+=1;
					}


					else if((matrix[nextpathx][nextpathy-1]==0) && !(p.x==nextpathx &&p.y==nextpathy-1))//looking left and condition is it must not be past location
					{
						p.x=nextpathx;
						p.y=nextpathy;
						tempstack<<p;
						nextpathy-=1;

					}

					else
					{
						matrix[nextpathx][nextpathy]=1;//it is locked point between 1 number
						flag=true;

					}
				}
				if(flag==false)//if it is located in out of the second while that means a condition in while is not provided means it can reach the out point
				{
					p.x=nextpathx;
					p.y=nextpathy;
					tempstack<<p;
					matrix[nextpathx][nextpathy]=1;
					nextpathx=rowbas;
					nextpathy=columnbas;
					
					if(s.takingsize()>tempstack.takingsize()){
						s=tempstack;
				
					}

				}

		}

	}
	if(columnbas!=0 &&rowbas==row-1)
	{	
		
		while(matrix[rowbas-1][columnbas]!=1)
		{
		int nextpathx=rowbas-1;
		int nextpathy=columnbas;
		int k=0;
		Mazestack tempstack;
		    Point p;
		    p.x=rowbas;
		    p.y=columnbas;
			tempstack<<p;
			bool flag=false;
			while(!(nextpathx==0||nextpathy==0||nextpathx==row-1||nextpathy==column-1||flag==true))//our condition it is not located in entry point conditions(located in edges)
			{
					if((matrix[nextpathx-1][nextpathy]==0) && !(p.x==nextpathx-1 &&p.y==nextpathy))//looking up and condition is it must not be past location
					{
						p.x=nextpathx;
						p.y=nextpathy;
						tempstack<<p;
						nextpathx-=1;
						

					}
					else if((matrix[nextpathx+1][nextpathy]==0) && !(p.x==nextpathx+1 &&p.y==nextpathy))//looking down and condition is it must not be past location
					{
						p.x=nextpathx;
						p.y=nextpathy;
						tempstack<<p;
						nextpathx+=1;
					}
					else if((matrix[nextpathx][nextpathy+1]==0) && !(p.x==nextpathx &&p.y==nextpathy+1))//looking right and condition is it must not be past location
					{
						p.x=nextpathx;
						p.y=nextpathy;
						tempstack<<p;
						nextpathy+=1;
					}


					else if((matrix[nextpathx][nextpathy-1]==0) && !(p.x==nextpathx &&p.y==nextpathy-1))//looking left and condition is it must not be past location
					{
						p.x=nextpathx;
						p.y=nextpathy;
						tempstack<<p;
						nextpathy-=1;

					}

					else
					{
						matrix[nextpathx][nextpathy]=1;
						flag=true;

					}
				}
				if(flag==false)
				{//it is locked point between 1 number
					p.x=nextpathx;
					p.y=nextpathy;
					tempstack<<p;
					matrix[nextpathx][nextpathy]=1;
				
					 if(s.takingsize()>tempstack.takingsize())
					 {
						s=tempstack;
					}


				}

		}
	}
	cout<<"Printing the shortest exit path, with the length of "<<s.takingsize()<<endl;
	cout<<s;
	DeleteMatrix(matrix,row);

}
