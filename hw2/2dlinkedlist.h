#ifndef _2DLINKEDLqIST_H
#define _2DLINKEDLIST_H
#include<string>
#include<iostream>
using namespace std;
struct node
{
	char ch;
	node *right;
	node *left;
	node *south;
	node *north;
	node()
	{}
	node(const  char&ch,node *linkright,node *linkleft,node *linksouth,node *linknorth)
		:ch(ch),right(linkright),left(linkleft),south(linksouth),north(linknorth)
	{}
	 
};
class linkedlist
{
private:
	node *head;
	node *tail;
	//int rowcounter,colcounter;
public:
	linkedlist();
	void birlestirm();
	void realprintlist(int totalpoints);
	void controlprintlist();
	void controlprintlist2();
	
	node *emre();
	bool lefttorightsearch(string name,int &rowcounter);
	bool rigthtoleftsearch(string name,int &rowcounter);
	bool toptobottomsearch(string name,int &rowcounter);
	bool bottomtoupsearch(string name,int &rowcounter);
	void deletelefttoright(int rowcounter);
	void deleterighttoleft(int rowcounter);
	void deletetoptobottom(int rowcounter);
	void deletebottomtoup(int rowcounter);
	void baglayici(int a);
	void addtoend(char chh);
	void addtoend1(char chhh);
	void movetodownline(char n);


};
























#endif