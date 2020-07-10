#ifndef _HEADER_H
#define _HEADER_H

#include<string>
using namespace std;
class Container//base class
{
protected:
	struct node//it is inherited struct from our base class to sub classes
	{
		int id;
		node *next;
		node(const int &i,node *ne)
			:id(i),next(ne){}
	};
	node *top;

public:
	virtual ~Container() {}
	virtual void insertElement(int a)=0;
	virtual void deleteElement(int &num)=0;
	virtual void print()=0;


};
class LinkedList: public Container//sub classes
{
private :
	int size;
public:
	LinkedList();
	~LinkedList();
	virtual void insertElement(int a);
	virtual void deleteElement(int &num);
	virtual void print();
	void sorted();
	int getsize() const;

};
class Stack:public Container//subclasses
{

public:
	Stack();
	~Stack();
	virtual void insertElement(int a);
	virtual void print();
	virtual void deleteElement(int &num);


};
class Queue:public Container//sub classes
{
protected:
	node *rear;
public:
	Queue();
	~Queue();
	virtual void insertElement(int a);
	virtual void deleteElement(int &a);
	virtual void print();
};
#endif