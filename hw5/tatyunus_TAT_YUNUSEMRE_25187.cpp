#include<iostream>
//#include"Header.h"
#include"tatyunus_TAT_YUNUSEMRE_25187.h"
#include<iomanip>
using namespace std;
LinkedList::LinkedList()//linkedlist constructor
{
	top=NULL;//it is the proteceted from the base classes for creating the stack queue and linked list
	size=0;// taking the size because in the sorting function we will use
}
LinkedList::~LinkedList()
{
	 cout<<"Destructing the linked list."<<endl;
	if(top == NULL)
       return;

    if(top->next != 0)
    {   
         delete this->top->next;
    }
	delete this->top;

}
Stack::~Stack()
{
	cout<<"Destructing the stack."<<endl;
	if(top == NULL)
       return;

    if(top->next != 0)
    {   
         delete this->top->next;
    }
	delete this->top;
}

Queue::~Queue()
{
	cout<<"Destructing the queue."<<endl;
	if(top == NULL)
       return;

    if(top->next != 0)
    {   
         delete this->top->next;
    }
	delete this->top;
}


int  LinkedList::getsize() const
{//taking the size
	return size;
}

void LinkedList::insertElement(int num)
{// inserting element but it is not important what ever its sequence because sorted function is different.we increment for all insertelement function
	node *ptr=top;
	node *temp=new node(num,NULL);
	if(top==NULL)
	{
		top=temp;
	}
	else
	{
		while(ptr->next !=NULL)
			ptr=ptr->next;
		ptr->next=temp;
	}
	size++;
	cout<<num<<" is inserted into the linked list."<<endl<<endl;
} 
void LinkedList::sorted()
{
	node* firsttry = top;// bubble sort algoritm is implemented to my linkedlist 
	node* secondtry = top;

	for (int i = 0; i < getsize(); i++) {
		for (int j = 0; j < getsize() - 1; j++) {
			if (firsttry->id < secondtry->id) {
				int temp = firsttry->id;
				firsttry->id = secondtry->id;
				secondtry->id = temp;

			}
			secondtry = secondtry->next;
		}
		secondtry = top;
		firsttry = top->next;
		for (int k = 0; k < i; k++) {
			firsttry = firsttry->next;
		}
	}
}
void LinkedList::deleteElement(int &num)
{
	if(top==NULL)//deleting the element from linkedlist there is no rule like queue and stack only deleting whatever user give
	{
		cout<<num<<" cannot be deleted from the linked list."<<endl<<endl;
	}
	else
	{
		if(top->id == num)
		{
			node *now=top;
			top=top->next;
			size--;
			cout<<num<<" is deleted from the linked list."<<endl;
			cout<<endl;
			delete now;
		}
		else
		{
			node *prev=top;
			node *now=top->next;
			while(now!=NULL)
			{
				if(now->id==num)
				{
					break;
				}

				else
				{
					prev=now;
					now=now->next;
				}
			}
			if(now==NULL)
			{
				cout<<" cannot be deleted from the linked list."<<endl<<endl;
			}
			else
			{
				prev->next=now->next;
				cout<<num<<" is deleted from the linked list."<<endl;
				cout<<endl;
				delete now;
				size--;//if it is deleted private size member will be deleted
			}


		}
	}
	
}
void LinkedList::print()
{//printing the linkedlist with sorted 
	cout<<"Printing the linked list:"<<endl;
	sorted();
	node *ptr =top;
	while(ptr!=NULL)
	{
		cout<<ptr->id<<" ";
		ptr=ptr->next;
	}
	cout <<endl;
	cout<<endl;
}
Stack::Stack()
{
	top=NULL;
}

void Stack::insertElement(int num)
{
	node *ptr;
	ptr=new node(num,NULL);//inserting the element from the taking element by user
	if(top==NULL)
	{
		top=ptr;
	}
	else
	{
		ptr->next=top;
		top=ptr;
	}	
	cout<<num<<" is inserted into the stack."<<endl<<endl;
}
void Stack::deleteElement(int &num)//deleting element with FILO method (first in last out)
{
	if(top==NULL||top->id!=num)
	{
		cout<<num<<" cannot be deleted from the stack."<<endl<<endl;
	}
	else
	{
		if(top->id == num)
		{
			node *current=top;
			top=top->next;
			cout<<num<<" is deleted from the stack."<<endl<<endl;
			delete current;
		}
		
	}
}
void Stack::print()//printing the stack
{
	node *ptr=top;
	cout<<"Printing the stack:"<<endl;
	if(top==NULL)
	{
		cout<<"";
	}
	else
	{
		while(ptr!=NULL)
		{
			cout<<ptr->id<<" ";
			ptr=ptr->next;
		}
	}
			cout<<endl<<endl;

}
Queue::Queue()
{
	top=NULL;
	rear=NULL;
}
void Queue::insertElement(int num)//inserting element to the queue
{
	if(top==NULL)
	{
		top =new node(num,NULL);
		rear=top;
	}
	else
	{
		rear->next=new node(num,NULL);
		rear=rear->next;
	}
	cout<<num<<" is inserted into the queue."<<endl<<endl;
}
void Queue::deleteElement(int &num)//deleting element from the queue with FIFO first in first out
{
	if(top==NULL||top->id !=num )
	{
		cout<<num<<" cannot be deleted from the queue."<<endl<<endl;
	}
	else
	{
		if(top->id == num)
		{
			node *current=top;
			top=top->next;
			cout<<num<<" is deleted from the queue."<<endl<<endl;
			delete current;
		}
	
	}
}
void Queue::print()//printing the element with first in first out
{
	cout<<"Printing the queue:"<<endl;
	node *temp=top;
	if(top==NULL)
	{
		cout<<"";
	}
	else
	{
	while(temp!=NULL)
	{
		cout<<temp->id<<" ";
		temp=temp->next;
	}
	}
		cout<<endl<<endl;
}




















