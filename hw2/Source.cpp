#include<iostream>
#include<string>
#include "2dlinkedlist.h"

using namespace std;

linkedlist::linkedlist()
{
	head=NULL;
	tail=NULL;
}
node* linkedlist::emre()
{
	return head;
}

void linkedlist::addtoend(char n)
{
	node *ptr=head;

	if(tail==NULL)
	{
		node *temp=new node(n,NULL,NULL,NULL,NULL);
		tail=temp;
		head=tail;
	}
	else
	{
		node *temp=new node(n,NULL,tail,NULL,NULL);
		tail->right=temp;
		tail=temp;
	}	
}//IT IS BASED ON LINKEDLIST
void linkedlist::movetodownline(char n)
{//THÝS FUNCTION IS WRITTEN BECAUSE OF WHEN GETTÝNG  CHARACAHTER WE HAVE TO GET NEW LINE IF WE WRÝTE A NEW LÝNE WE HAVE TO GO DOWN LINE
	node *ptr=tail;
	while(ptr->left !=NULL)
	{
		ptr=ptr->left;
	}
	ptr->south=new node(n,NULL,NULL,NULL,ptr);
	tail=ptr->south;

}
void linkedlist::addtoend1(char n)
{//WHEN WE MOVE TO DOWN LINE WE HAVE TO BUILD NEW NODE 
	node *ptr=tail->north;
	node *temp=new node(n,NULL,tail,NULL,NULL);
	tail->right=temp;
	tail=temp;

}
void linkedlist::baglayici(int a)
{//WHEN ALL THE DOUBLY LINES ARE CREATED.WE HAVE TO LINK THEM.THIS FUNCTÝON HAS 2 POINTER FOR LINK SENTENCES.SEQUENCE IS (1-2,2-3,3-4....)
	node *ptr=head;
	node *temp=ptr->south;
	int x=0;
	while(x<a-1)
	{
		while(ptr->right !=NULL && temp->right !=NULL)
		{
			ptr->south=temp;
			temp->north=ptr;
			ptr=ptr->right;
			temp=temp->right;
		}	
		ptr->south=temp;
		temp->north=ptr;
		while(ptr->left!=NULL && temp->left!=NULL)
		{
			ptr =ptr->left;
			temp=temp->left;
		}
		ptr=ptr->south;
		temp=temp->south;
		x++;
	}
}
void linkedlist::controlprintlist()
{//IT IS WRÝTTEN BECAUSE CONTROLÝNG THE LÝNKED POINTER IN THE NODE BODY.ALL THE POINTERS ARE USED TO CONTROL
	node *ptr=head;
	while(ptr->south!=NULL)
	{
		while(ptr->right!=NULL)
		{
			cout<<ptr->ch<<" ";
			ptr=ptr->right;
		}
		cout<<ptr->ch;
		cout<<endl;
		cout<<ptr->ch<<" ";	
		ptr=ptr->left;
		while(ptr->left !=NULL)
		{
			cout<<ptr->ch<<" " ;
			ptr=ptr->left;
		}
		cout<<ptr->ch;
		cout<<endl;
		ptr=ptr->south;
	}
	while(ptr->right!=NULL)
	{
		cout<<ptr->ch<<" ";
		ptr=ptr->right;
	}
	cout<<ptr->ch;
	cout<<endl;
	cout<<ptr->ch<<" ";	
	ptr=ptr->left;
	while(ptr->left !=NULL)
	{
		cout<<ptr->ch<<" " ;
		ptr=ptr->left;
	}
	cout<<ptr->ch;
	cout<<endl;
}
void linkedlist::realprintlist(int totalpoints)
{	if(head!=NULL)//IF HEAD IS NULL ALL THE PUZZLE IS DELETED.BUT IF HEAD ÝS NOT NULL THERE ARE NODES.
{
	cout<<"Puzzle:"<<endl;
	node *ptr=head;
	while(ptr->south !=NULL)
	{
		while(ptr->right!=NULL)
		{
			cout<<ptr->ch<<" ";
			ptr=ptr->right;
		}
		cout<<ptr->ch;
		while(ptr->left!=NULL)
		{
			ptr=ptr->left;
		}
		ptr=ptr->south;
		cout<<endl;
	}
	while(ptr->right!=NULL)
	{
		cout<<ptr->ch<<" ";
		ptr=ptr->right;
	}
	cout <<ptr->ch;
	while(ptr->left!=NULL)
	{
		ptr=ptr->left;
	}
	ptr=ptr->south;

}
else
{
	cout<<"Puzzle is cleared. 20 extra points are earned."<<endl;
	totalpoints +=20;
	cout<<"Total points: "<<totalpoints<<"."<<endl;
	cout<<"Game has ended."<<endl;
	cout<<"Total points: "<<totalpoints<<".";
}
cout<<endl;

}
bool linkedlist::lefttorightsearch(string name,int &rowcounter)
{//IT IS WRÝTTEN FOR SEARCING LEFT TO RIGHT AND RIGHT TO LEFT REVERSELY.IT'S FIRST CHARACHTER IS FIRST LINE CHARACTER THEN 
	//IT ADD NEW CHARACHTER UNTIL FINDING WORD THEN ITS NEW CHARACHTER SECOND LÝNE CHARACHTER.
	int y=0;
	rowcounter=0;
	node *t=head;
	while(t->south!=NULL)
	{
		y++;
		t=t->south;
	}
	if(y==1 || y==0)
	{
		rowcounter=1;
	}


	node *ptr=head;
	node *temp;
	int a=0;
	string namem="";
	while(a==0 && ptr!=tail)
	{
		temp=ptr;
		while(ptr->right!=NULL && a==0)
		{
			while(temp->right !=NULL&&a==0)
			{
				namem+=temp->ch;
				temp=temp->right;
				if(namem==name)
				{
					a=1;
				}
			}
			if(a==0)
			{
				namem+=temp->ch;
				if(namem==name)
				{
					a=1;
				}
				else
				{
					ptr=ptr->right;
					temp=ptr;
					namem="";
				}

			}
		}
		while(ptr->left!=NULL&& a==0&&ptr->south !=NULL)
		{
			ptr=ptr->left;
		}
		if(ptr->south !=NULL)
		{
			ptr=ptr->south;
			rowcounter++;
		}
	}
	if (a==1)
	{
		return true;
	}
	else
	{
		return false;
	}


}
bool linkedlist::rigthtoleftsearch(string name,int &rowcounter)
{//IT IS NOT USED IN PROJECT.FIRSTLY IT IS USED BUT I REVERSED WORDS THEN I IMPLEMENTED TO LEFT TO RÝGHT SEARCH
	rowcounter =0;
	int a=0;
	node *ptr=head;
	while(ptr->right !=NULL)
	{
		ptr=ptr->right;
	}
	node *temp;
	string namem="";
	while(a==0)
	{
		temp=ptr;
		while(ptr->left!=NULL&&a==0)
		{

			while(temp->left!=NULL&&a==0)
			{
				namem+=temp->ch;
				temp=temp->left;
				if(name==namem)
				{
					a=1;

				}
			}
			if(a==0)
			{
				namem+=temp->ch;
				if(name==namem)
				{
					a=1;
				}
				else
				{
					namem="";
					ptr=ptr->left;
					temp=ptr;
				}
			}
		}
		while(ptr->right!=NULL&&a==0)
		{
			ptr=ptr->right;
		}
		if(ptr->south!=NULL)
		{
			ptr=ptr->south;
			rowcounter++;
		}
	}
	if(a==1)
	{
		return true;
	}
	else
	{
		return false;
	}



}
bool linkedlist::toptobottomsearch(string name,int &rowcounter)
{//IT IS AS SAME AS LEFT TO RIGHT WORKING METHOD.FIRSTLY IT TAKES FIRST COL WORD THEN IT ADD OTHER CHARACTERS AND IT CHECKS THEM SUCH AS (1,1-2,1-2-3...)
	//(2,2-3,2-3-4.....)
	node *ptr=head;
	node *temp;
	rowcounter=1;
	string namem="";
	int a=0;
	while (a==0 && ptr!=tail)
	{
		temp=ptr;
		while(ptr->right !=NULL && a==0)
		{
			while(temp->south !=NULL && a==0)
			{
				namem +=temp->ch;
				temp=temp->south;
				if(namem ==name)
				{
					a=1;
				}
			}
			if(a==0)
			{
				namem +=temp->ch;
				if(namem==name)
				{
					a=1;
				}
				else
				{

					rowcounter ++;
					ptr=ptr->right;
					temp=ptr;
					namem="";
				}
			}
		}
		while(temp->south !=NULL && a==0)
		{
			namem +=temp->ch;
			temp=temp->south;
			if(namem ==name)
			{
				a=1;
			}
		}
		if(a==0)
		{
			namem +=temp->ch;
			if(namem==name)
			{
				a=1;
			}
		}
		while(ptr->left!=NULL && a==0 && ptr->south !=NULL)
		{
			ptr=ptr->left;
		}
		if(ptr->south !=NULL&&a==0)
		{
			ptr=ptr->south;
			rowcounter=1;
		}
		namem ="";
	}
	if(a==1)
	{
		return true;
	}
	else
	{
		return false;
	}


}
bool linkedlist::bottomtoupsearch(string name,int &colcounter)
{//IT IS NOT USED IN THE MAIN PART ,TOP TO BOTTOM IS USED WITH REVERSELY FOR FINDING THE BOTTOM TO UP SEARCH
	colcounter=0;
	node *ptr=head;
	node *temp;
	int a=0;
	string namem="";
	ptr=ptr->south;
	while(a==0)
	{
		temp=ptr;
		while(ptr->right !=NULL &&a==0)
		{
			while(temp->north!=NULL && a==0)
			{
				namem+=temp->ch;
				temp=temp->north;
				if(name==namem)
				{
					a=1;
				}
			}
			if(a==0)
			{
				namem+=temp->ch;
				if(namem==name)
				{
					a=1;
				}
				else
				{
					ptr=ptr->right;
					colcounter ++;
					temp=ptr;
					namem="";
				}
			}
		}
		while(temp->north!=NULL && a==0)
		{
			namem+=temp->ch;
			temp=temp->north;
			if(name==namem)
			{
				a=1;
			}
		}
		if(a==0)
		{
			namem+=temp->ch;
			if(namem==name)
			{
				a=1;
			}
			else
			{
				ptr=ptr->right;
				colcounter ++;
				temp=ptr;
				namem="";
			}


		}


		while(ptr->left !=NULL &&a==0)
		{
			ptr=ptr->left;
		}
		if(ptr->south!=NULL)
		{
			ptr=ptr->south;
			colcounter=0;
		}
	}
	if(a==1)
	{
		return true;
	}
	else
	{
		return false;
	}



}

void linkedlist::controlprintlist2()
{//It is other contoling the control list
	while(tail->north!=NULL)
	{
		cout<<tail->ch<<" ";
		tail=tail->north;
	}

}
/*void linkedlist::toptobottomsearch(string name)
{
node *ptr=head;
int a=0;
node *temp=ptr;
string names="";
while(a==0)
{
while(ptr->right!=NULL)
{
while(temp->south!=NULL)
{
names+=temp->ch;
temp=temp->south;
}
names+=temp->ch;
if(names==name)
{
a=1;
}
else
{
ptr=ptr->right;;
names="";
a=0;
temp=ptr;
}
}
while(temp->south!=NULL)
{
names+=temp->ch;
temp=temp->south;
}
names+=temp->ch;
if(names==name)
{
a=1;
}
else
{
ptr=ptr->right;;
names="";
a=0;
temp=ptr;
}
while(ptr->left!=NULL)
{
ptr=ptr->left;
}
ptr=ptr->south;
temp=ptr;
}

}*/
void linkedlist::deletelefttoright(int rowcounter)
{ //ýt is other cornerstone function which clearing the left to right.It begins from the head north or south and deleting the all row
	node *ptr=head;
	node *k;
	int counter=1;
	/*	while(ptr->left !=NULL)
	{
	ptr=ptr->left;
	}*/
	while(counter!=rowcounter)
	{
		ptr=ptr->south;
		counter ++;
	}
	if(ptr->north==NULL)
	{	head=ptr->south;
	}
	else
	{
		k=ptr;
		while(k->north!=NULL)
		{
			k=k->north;
		}
		head=k;

	}
	if(ptr->north !=NULL&&ptr->south!=NULL)
	{
	node *ust,*alt;
	ust=ptr->north;
	alt=ptr->south;
	while(ust->right!=NULL && alt->right !=NULL)
	{
		ust->south=alt;
		alt->north=ust;
		ust=ust->right;
		alt=alt->right;
	}
	ust->south=alt;
	alt->north=ust;
	}
	else if(ptr->south !=NULL && ptr->north ==NULL)
	{
		node *ust =ptr->south;
		while(ust->right !=NULL)
		{
			ust->north=NULL;
			ust=ust->right;
		}
		ust->north=NULL;

	}
	else if(ptr->south ==NULL && ptr->north !=NULL)
	{
		node *alt=ptr->north;
		while(alt->right !=NULL)
		{
			alt->south =NULL;
			alt=alt->right;
		}
		alt->south ==NULL;

	}


	while(ptr->right!=NULL)
	{
		k=ptr;
		ptr=ptr->right;
		delete k;
	}
	
	k=ptr;
	if(k==tail&&tail->north!=NULL)
	{
		tail=tail->north;
		delete k;
	}
	else
	{
		delete k;
	}

}
void linkedlist::deleterighttoleft(int rowcounter)
{//it is not used in main because only left to right is enough.
	node *k;
	node *ptr=head;
	int counter =1;
	while(counter !=rowcounter)
	{
		ptr=ptr->south;
		counter ++;
	}

	if(ptr->north==NULL)
	{
		head=ptr->south;
	}
	else
	{
		k=ptr;
		while(k->north!=NULL)
		{
			k=k->north;
		}
		while(k->left !=NULL)
		{
			k=k->left;
		}

		head=k;

	}

	while(ptr->right !=NULL)
	{
		ptr=ptr->right;
	}
	node*ust,*alt;
	ust=ptr->north;
	alt=ptr->south;
	while(ust->left!=NULL && alt ->left !=NULL)
	{
		ust->south=alt;
		alt->north=ust;
		ust=ust->left;
		alt=alt->left;
	}
	ust->south=alt;
	alt->north=ust;
	while(ptr->left!=NULL)
	{
		k=ptr;
		ptr=ptr->left;
		delete k;
	}
	k=ptr;
	delete k;
}
void linkedlist::deletetoptobottom(int rowcounter)
{//It is used in the coloumn deleting.Firstly it is employed the first row then its direction is south to deleting the nodes
	node *k;
	node *ptr=head;
	int counter =1;
	while(counter !=rowcounter)
	{
		ptr=ptr->right;
		counter ++;
	}
	/*
	while(ptr->north!=NULL)
	{
	ptr=ptr->north;
	}*/
	k=ptr;
	while(k->left !=NULL)
	{
		k=k->left;
	}
	head=k;
	if(ptr->right!=NULL&&ptr->left !=NULL)
	{
		node *sol=ptr->left;
		node *sag=ptr->right;
		while(sol->south !=NULL && sag->south !=NULL)
		{
			sol->right=sag;
			sag->left=sol;
			sol=sol->south;
			sag=sag->south;
		}
		sol->right=sag;
		sag->left =sol;
	}
	else if(ptr->right==NULL && ptr ->left==NULL)
	{
		while(head->south!=NULL)
		{
		k=head;
		head=head->south;
		delete k;

		}
		k=head;
		delete k;
		head=NULL;

	}

	else if (ptr->right ==NULL)
	{
	
		node *ust=ptr->left;
		while(ust->south!=NULL)
		{
			ust->right=NULL;
			ust=ust->south;
		}
		ust->right=NULL;

	}
	else if(ptr->left ==NULL)
	{
		node *ust=ptr->right;
		head=head->right;
		while(ust->south!=NULL)
		{
			ust->left=NULL;
			ust=ust->south;
		}
		ust->left=NULL;
	}
	


	
	while(ptr->south!=NULL && head!=NULL)
	{
		k=ptr;
		ptr=ptr->south;
		delete k;
	}
	k=ptr;
	if(k==tail&&tail->left !=NULL&&head!=NULL)
	{
		tail=tail->left;
	
		delete k;
	}
	else if(head!=NULL)
	{
		delete k;
	}

	


}





















