#include<iostream>
#include<thread>
#include<mutex>
#include<sstream>
#include<fstream>
#include<string>
#include<iomanip>
#include<cmath>
using namespace std;
mutex **mutexmatrix;// it is the one of the important parts of the code for creating the mute matrix because of using the numbers without constant
mutex coutmutex;
bool isdone=true;
void DeleteMatrix(int ** matrix, int rowsize)
{//delete function to remove the matrix (refresh allocated memory)
	for(int i=0; i<rowsize; i++)
	{
		delete [] matrix[i];
	}
	delete matrix;
}
void DeleteMatrixthread(thread ** matrix, int rowsize)
{//delete function to remove the matrix (refresh allocated memory)
	for(int i=0; i<rowsize; i++)
	{
		delete [] matrix[i];
	}
	delete matrix;
}
void DeleteMatrixmutex(mutex ** matrix, int rowsize)
{//delete function to remove the matrix (refresh allocated memory)
	for(int i=0; i<rowsize; i++)
	{
		delete [] matrix[i];
	}
	delete matrix;
}
void printingmatrix(int **matrix,int rowsize,int colsize)// printing the matrix
{
	for(int i=0;i<rowsize;i++)
	{
		for(int k=0;k<colsize;k++)
		{
			cout<<setw(5)<<matrix[i][k];
		}
		cout<<endl;
	}
}

void func(int i,int j,int **&matrix,int row,int col)// it is the only function for taking i j(indexes ) and numbers of rows and cols and processing
{
	int max;// max is that finding the biggest value among the neighbor
	bool flag=false;//some conditions are proccesed then it is determined 
	bool a,b,c,d,e;//bool value finding the true false value after the try lock 
	int k,l,m,n;// getting the neighbor values
	double t;//t is the base cell and has many neigbor it is double because it will be divided
	while(true)
	{
	if(i==0 && j==0)// for processing the left above point
	{
		a=mutexmatrix[0][1].try_lock();
		b=mutexmatrix[1][0].try_lock();//finding the neighbor cells and unlock them ýf they are available (if they are not locked)
		c=mutexmatrix[0][0].try_lock();
		if(a==true && b==true && c==true)// if all the neighbor unlocked flag true(beginning of our process)
		{
			flag=true;
		}
		if(flag)
		{
			t=matrix[0][0];
			k=matrix[0][1];
			l=matrix[1][0];
			//finding the maximum value among all the neighbors and firstly lock cout for getting enought time to print and then our base(cell have neighbors) getting value from its neighbor as its value and of the cond.all of the neighbor mutexes unlocked 
			if(k>=l)
			{	max=k;
				if(max>=2*t)
				{
				
				isdone=true;
				coutmutex.lock();
				cout<<"Row-"<<i<<",Col-"<<j<<" ("<<matrix[i][j]<<") is incremented by "<<ceil(t/3)<<" by stealing from the cell to the right ("<<matrix[0][1]<<")."<<endl;
				coutmutex.unlock();
				matrix[0][0]+=ceil(t/3);
				matrix[0][1]-=ceil(t/3);

				}
				mutexmatrix[0][1].unlock();
				mutexmatrix[1][0].unlock();
				mutexmatrix[0][0].unlock();
			}
			else//finding the maximum value among all the neighbors and firstly lock cout for getting enought time to print and then our base(cell have neighbors) getting value from its neighbor as its value and of the cond.all of the neighbor mutexes unlocked 
			{  
				max=l;
				if(max>=2*t)
				{
				//t+=ceil(t/3);
				//max-=ceil(t/3);
				isdone=true;
				coutmutex.lock();
				cout<<"Row-"<<i<<",Col-"<<j<<" ("<<matrix[i][j]<<") is incremented by "<<ceil(t/3)<<" by stealing from the cell below ("<<matrix[1][0]<<")."<<endl;
				coutmutex.unlock();
				matrix[0][0]+=ceil(t/3);
				matrix[1][0]-=ceil(t/3);
		
				}
				mutexmatrix[0][1].unlock();
				mutexmatrix[1][0].unlock();
				mutexmatrix[0][0].unlock();
			}
			break;
		}
		else if(flag==false)
		{// if we locked any of neighbor but not all of them we have to unlocked it because at least one of them was locked before out trying and it is under processessing situation 
			if(a==true)
			{
				mutexmatrix[0][1].unlock();
			}
			if(b==true)
			{
				mutexmatrix[1][0].unlock();
			}
			if(c==true)
			{
				mutexmatrix[0][0].unlock();
			}

			this_thread::yield();

		}



	}
	else if(i==0 && j!=0 && j!=col-1)// processing the above edge without corners
	{
		a=mutexmatrix[i][j-1].try_lock();
		b=mutexmatrix[i+1][j].try_lock();//finding the neighbor cells and unlock them ýf they are available (if they are not locked)
		c=mutexmatrix[i][j+1].try_lock();
		d=mutexmatrix[i][j].try_lock();
		if(a==true&&b==true&&c==true&&d==true)
		{
			flag=true;// if all the neighbor unlocked flag true(beginning of our process)
		}
		if(flag)
		{
			t=matrix[i][j];
			k=matrix[i][j-1];
			l=matrix[i][j+1];
			m=matrix[i+1][j];
			if(k>=l && k>=m)
			{
				max=k;
				if(max>=2*t)
				{
					coutmutex.lock();
					cout<<"Row-"<<i<<",Col-"<<j<<" ("<<matrix[i][j]<<") is incremented by "<<ceil(t/3)<<" by stealing from the cell to the left ("<<matrix[i][j-1]<<")."<<endl;
					coutmutex.unlock();
					matrix[i][j]+=ceil(t/3);
					matrix[i][j-1]-=ceil(t/3);//finding the maximum value among all the neighbors and firstly lock cout for getting enought time to print and then our base(cell have neighbors) getting value from its neighbor as its value and of the cond.all of the neighbor mutexes unlocked 
						isdone=true;
				}
					mutexmatrix[i][j-1].unlock();
					mutexmatrix[i+1][j].unlock();
					mutexmatrix[i][j+1].unlock();
					mutexmatrix[i][j].unlock();
			}
			else if(l>=k && l>=m)
			{
				max=l;
				if(max>=2*t)
				{//finding the maximum value among all the neighbors and firstly lock cout for getting enought time to print and then our base(cell have neighbors) getting value from its neighbor as its value and of the cond.all of the neighbor mutexes unlocked 
					coutmutex.lock();
					cout<<"Row-"<<i<<",Col-"<<j<<" ("<<matrix[i][j]<<") is incremented by "<<ceil(t/3)<<" by stealing from the cell to the right ("<<matrix[i][j+1]<<")."<<endl;
					coutmutex.unlock();
					matrix[i][j]+=ceil(t/3);
					matrix[i][j+1]-=ceil(t/3);
						isdone=true;
		
				}
							mutexmatrix[i][j-1].unlock();
					mutexmatrix[i+1][j].unlock();
					mutexmatrix[i][j+1].unlock();
					mutexmatrix[i][j].unlock();
			}
			else if(m>=k && m>=l)
			{
				max=m;
				if(max>=2*t)
				{//finding the maximum value among all the neighbors and firstly lock cout for getting enought time to print and then our base(cell have neighbors) getting value from its neighbor as its value and of the cond.all of the neighbor mutexes unlocked 
					coutmutex.lock();
					cout<<"Row-"<<i<<",Col-"<<j<<" ("<<matrix[i][j]<<") is incremented by "<<ceil(t/3)<<" by stealing from the cell below ("<<matrix[i+1][j]<<")."<<endl;
					coutmutex.unlock();
					matrix[i][j]+=ceil(t/3);
					matrix[i+1][j]-=ceil(t/3);
						isdone=true;
			
				}
						mutexmatrix[i][j-1].unlock();
					mutexmatrix[i+1][j].unlock();
					mutexmatrix[i][j+1].unlock();
					mutexmatrix[i][j].unlock();
			}
			break;
		}
		else if(flag==false)
		{
			if(a==true)// if we locked any of neighbor but not all of them we have to unlocked it because at least one of them was locked before out trying and it is under processessing situation 
			{
				mutexmatrix[i][j-1].unlock();
			}
			if(b==true)
			{
				mutexmatrix[i+1][j].unlock();
			}
			if(c==true)
			{
				mutexmatrix[i][j+1].unlock();
			}
			if(d==true)
			{
				mutexmatrix[i][j].unlock();
			}
			this_thread::yield();
		}



	}
	else if(i==0 && j==col-1)//finding the neighbor cells and unlock them if they are available (if they are not locked)
	{// processing the right upper corner
		a=mutexmatrix[i+1][j].try_lock();
		b=mutexmatrix[i][j-1].try_lock();
		c=mutexmatrix[i][j].try_lock();
		if(a==true && b==true&&c==true)
		{// if all the neighbor unlocked flag true(beginning of our process)
			flag=true;
		}
		if(flag)
		{
			k=matrix[i+1][j];
			l=matrix[i][j-1];
			t=matrix[i][j];
			if(k>=l)
			{
				max=k;//finding the maximum value among all the neighbors and firstly lock cout for getting enought time to print and then our base(cell have neighbors) getting value from its neighbor as its value and of the cond.all of the neighbor mutexes unlocked 
				if(max>=2*t)
				{
					coutmutex.lock();
					cout<<"Row-"<<i<<",Col-"<<j<<" ("<<matrix[i][j]<<") is incremented by "<<ceil(t/3)<<" by stealing from the cell below ("<<matrix[i+1][j]<<")."<<endl;
					coutmutex.unlock();
					matrix[i][j]+=ceil(t/3);
					matrix[i+1][j]-=ceil(t/3);
						isdone=true;
					
				}
				mutexmatrix[i][j-1].unlock();
					mutexmatrix[i+1][j].unlock();
					mutexmatrix[i][j].unlock();
			}
			else
			{
				max=l;
				if(max>=2*t)// it is the rule for procesisng the matrix 2 times  base cell have to be smaller then max value
				{
					coutmutex.lock();
					cout<<"Row-"<<i<<",Col-"<<j<<" ("<<matrix[i][j]<<") is incremented by "<<ceil(t/3)<<" by stealing from the cell to the left ("<<matrix[i][j-1]<<")."<<endl;
					coutmutex.unlock();
					matrix[i][j]+=ceil(t/3);
					matrix[i][j-1]-=ceil(t/3);			
						isdone=true;
					
				}
				mutexmatrix[i][j-1].unlock();
					mutexmatrix[i+1][j].unlock();
					mutexmatrix[i][j].unlock();
			}

			break;
		}
		else if(flag==false)
		{
			if(a==true)
			{// if we locked any of neighbor but not all of them we have to unlocked it because at least one of them was locked before out trying and it is under processessing situation 
				mutexmatrix[i+1][j].unlock();
			}
			if(b==true)
			{
				mutexmatrix[i][j-1].unlock();
			}
			if(c==true)
			{
				mutexmatrix[i][j].unlock();
			}
			this_thread::yield();

		}




	}
	else if(i==row-1 && j==0)// processing the left down corner
	{//finding the neighbor cells and unlock them if they are available (if they are not locked)
		a=mutexmatrix[i-1][j].try_lock();
		b=mutexmatrix[i][j+1].try_lock();
		c=mutexmatrix[i][j].try_lock();
		if(a==true && b==true&&c==true)
		{// if all the neighbor unlocked flag true(beginning of our process)
			flag=true;
		}
		if(flag)
		{
			k=matrix[i-1][j];
			l=matrix[i][j+1];
			t=matrix[i][j];
			if(k>=l)
			{//finding the maximum value among all the neighbors and firstly lock cout for getting enought time to print and then our base(cell have neighbors) getting value from its neighbor as its value and of the cond.all of the neighbor mutexes unlocked 
				max=k;
				if(max>=2*t)
				{
					coutmutex.lock();
					cout<<"Row-"<<i<<",Col-"<<j<<" ("<<matrix[i][j]<<") is incremented by "<<ceil(t/3)<<" by stealing from the cell above ("<<matrix[i-1][j]<<")."<<endl;
					coutmutex.unlock();
					matrix[i][j]+=ceil(t/3);
					matrix[i-1][j]-=ceil(t/3);
						isdone=true;
		
				}	
					mutexmatrix[i-1][j].unlock();
					mutexmatrix[i][j+1].unlock();
					mutexmatrix[i][j].unlock();

			}
			else
			{
				max=l;
				if(max>=2*t)
				{//finding the maximum value among all the neighbors and firstly lock cout for getting enought time to print and then our base(cell have neighbors) getting value from its neighbor as its value and of the cond.all of the neighbor mutexes unlocked 
					coutmutex.lock();
					cout<<"Row-"<<i<<",Col-"<<j<<" ("<<matrix[i][j]<<") is incremented by "<<ceil(t/3)<<" by stealing from the cell to the right ("<<matrix[i][j+1]<<")."<<endl;
					coutmutex.unlock();
					matrix[i][j]+=ceil(t/3);
					matrix[i][j+1]-=ceil(t/3);
						isdone=true;
					
				}	
				mutexmatrix[i-1][j].unlock();
					mutexmatrix[i][j+1].unlock();
					mutexmatrix[i][j].unlock();

			}
			break;
		}
		else if(flag==false)
		{// if we locked any of neighbor but not all of them we have to unlocked it because at least one of them was locked before out trying and it is under processessing situation 
			if(a==true)
			{
				mutexmatrix[i-1][j].unlock();
			}
			if(b==true)
			{
				mutexmatrix[i][j+1].unlock();
			}
			if(c==true)
			{
				mutexmatrix[i][j].unlock();
			}
			this_thread::yield();
			
		

		}

		
	}
	else if(i==row-1 && j!=0 && j!=col-1)// processing the down edge
	{
		a=mutexmatrix[i-1][j].try_lock();
		b=mutexmatrix[i][j-1].try_lock();//finding the neighbor cells and unlock them if they are available (if they are not locked)
		c=mutexmatrix[i][j+1].try_lock();
		d=mutexmatrix[i][j].try_lock();
		if(a==true&&b==true&&c==true&&d==true)// if all the neighbor unlocked flag true(beginning of our process)
		{
			flag=true;
		}
		if(flag)
		{
			t=matrix[i][j];
			k=matrix[i-1][j];
			l=matrix[i][j-1];
			m=matrix[i][j+1];
			if(k>=l && k>=m)
			{//finding the maximum value among all the neighbors and firstly lock cout for getting enought time to print and then our base(cell have neighbors) getting value from its neighbor as its value and of the cond.all of the neighbor mutexes unlocked 
				max=k;
				if(max>=2*t)
				{
					coutmutex.lock();
					cout<<"Row-"<<i<<",Col-"<<j<<" ("<<matrix[i][j]<<") is incremented by "<<ceil(t/3)<<" by stealing from the cell above ("<<matrix[i-1][j]<<")."<<endl;
					coutmutex.unlock();
					matrix[i][j]+=ceil(t/3);
					matrix[i-1][j]-=ceil(t/3);
						isdone=true;
			
				}
					mutexmatrix[i-1][j].unlock();
					mutexmatrix[i][j+1].unlock();
					mutexmatrix[i][j].unlock();
					mutexmatrix[i][j-1].unlock();
			}
			else if(l>=k && l>=m)
			{//finding the maximum value among all the neighbors and firstly lock cout for getting enought time to print and then our base(cell have neighbors) getting value from its neighbor as its value and of the cond.all of the neighbor mutexes unlocked 
				max=l;
				if(max>=2*t)
				{
					coutmutex.lock();
					cout<<"Row-"<<i<<",Col-"<<j<<" ("<<matrix[i][j]<<") is incremented by "<<ceil(t/3)<<" by stealing from the cell to the left ("<<matrix[i][j-1]<<")."<<endl;
					coutmutex.unlock();
					matrix[i][j]+=ceil(t/3);
					matrix[i][j-1]-=ceil(t/3);
						isdone=true;
				
				}
					mutexmatrix[i-1][j].unlock();
					mutexmatrix[i][j+1].unlock();
					mutexmatrix[i][j].unlock();
					mutexmatrix[i][j-1].unlock();
			}
			else if(m>=k && m>=l)
			{//finding the maximum value among all the neighbors and firstly lock cout for getting enought time to print and then our base(cell have neighbors) getting value from its neighbor as its value and of the cond.all of the neighbor mutexes unlocked 
				max=m;
				if(max>=2*t)
				{
					coutmutex.lock();
					cout<<"Row-"<<i<<",Col-"<<j<<" ("<<matrix[i][j]<<") is incremented by "<<ceil(t/3)<<" by stealing from the cell to the right ("<<matrix[i][j+1]<<")."<<endl;
					coutmutex.unlock();
					matrix[i][j]+=ceil(t/3);
					matrix[i][j+1]-=ceil(t/3);
						isdone=true;
				
				}
					mutexmatrix[i-1][j].unlock();
					mutexmatrix[i][j+1].unlock();
					mutexmatrix[i][j].unlock();
					mutexmatrix[i][j-1].unlock();
			}
			break;
		}
			else if(flag==false)
		{// if we locked any of neighbor but not all of them we have to unlocked it because at least one of them was locked before out trying and it is under processessing situation 
			if(a==true)
			{
				mutexmatrix[i-1][j].unlock();
			}
			if(b==true)
			{
				mutexmatrix[i][j-1].unlock();
			}
			if(c==true)
			{
				mutexmatrix[i][j+1].unlock();
			}
			if(d==true)
			{
				mutexmatrix[i][j].unlock();
			}
			this_thread::yield();


		}

	}

	else if(i==row-1 && j==col-1)// processing the rigth down corner
	{//finding the neighbor cells and unlock them if they are available (if they are not locked)
		a=mutexmatrix[i-1][j].try_lock();
		b=mutexmatrix[i][j-1].try_lock();
		c=mutexmatrix[i][j].try_lock();
		if(a==true&&b==true &&c==true)
		{
			flag=true;// if all the neighbor unlocked flag true(beginning of our process)
		}
		if(flag)
		{
			k=matrix[i-1][j];
			l=matrix[i][j-1];
			t=matrix[i][j];
			if(k>=l)
			{//finding the maximum value among all the neighbors and firstly lock cout for getting enought time to print and then our base(cell have neighbors) getting value from its neighbor as its value and of the cond.all of the neighbor mutexes unlocked 
				max=k;
				if(max>=2*t)
				{
					coutmutex.lock();
					cout<<"Row-"<<i<<",Col-"<<j<<" ("<<matrix[i][j]<<") is incremented by "<<ceil(t/3)<<" by stealing from the above ("<<matrix[i-1][j]<<")."<<endl;
					coutmutex.unlock();
					matrix[i][j]+=ceil(t/3);
					matrix[i-1][j]-=ceil(t/3);
					isdone=true;

				}	
					mutexmatrix[i-1][j].unlock();
					mutexmatrix[i][j-1].unlock();
					mutexmatrix[i][j].unlock();

			}
			else
			{//finding the maximum value among all the neighbors and firstly lock cout for getting enought time to print and then our base(cell have neighbors) getting value from its neighbor as its value and of the cond.all of the neighbor mutexes unlocked 
				max=l;
				if(max>=2*t)
				{
					coutmutex.lock();
					cout<<"Row-"<<i<<",Col-"<<j<<" ("<<matrix[i][j]<<") is incremented by "<<ceil(t/3)<<" by stealing from the cell to the left ("<<matrix[i][j-1]<<")."<<endl;
					coutmutex.unlock();
					matrix[i][j]+=ceil(t/3);
					matrix[i][j-1]-=ceil(t/3);
						isdone=true;
				
				}	
					mutexmatrix[i-1][j].unlock();
					mutexmatrix[i][j-1].unlock();
					mutexmatrix[i][j].unlock();
			}
			break;
		}
		else if(flag==false)
		{// if we locked any of neighbor but not all of them we have to unlocked it because at least one of them was locked before out trying and it is under processessing situation 
			if(a==true)
			{
				mutexmatrix[i-1][j].unlock();
			}
			if(b==true)
			{
				mutexmatrix[i][j-1].unlock();
			}
			if(c==true)
			{
				mutexmatrix[i][j].unlock();
			}
			this_thread::yield();
		}

	}
	else if(i!=0 && i!=row-1 && j==0)// processing the left edge
	{
		a=mutexmatrix[i][j+1].try_lock();//finding the neighbor cells and unlock them if they are available (if they are not locked)
		b=mutexmatrix[i+1][j].try_lock();
		c=mutexmatrix[i-1][j].try_lock();
		d=mutexmatrix[i][j].try_lock();
		if(a==true && b==true && c==true&&d==true)// if all the neighbor unlocked flag true(beginning of our process)
		{
			flag=true;
		}
		if(flag)
		{
			t=matrix[i][j];
			k=matrix[i][j+1];
			l=matrix[i+1][j];
			m=matrix[i-1][j];
			if(k>=l && k>=m)
			{//finding the maximum value among all the neighbors and firstly lock cout for getting enought time to print and then our base(cell have neighbors) getting value from its neighbor as its value and of the cond.all of the neighbor mutexes unlocked 
				max=k;
				if(max>=2*t)
				{
					coutmutex.lock();
					cout<<"Row-"<<i<<",Col-"<<j<<" ("<<matrix[i][j]<<") is incremented by "<<ceil(t/3)<<" by stealing from the cell to the right ("<<matrix[i][j+1]<<")."<<endl;
					coutmutex.unlock();
					matrix[i][j]+=ceil(t/3);
					matrix[i][j+1]-=ceil(t/3);
						isdone=true;

				}
					mutexmatrix[i-1][j].unlock();
					mutexmatrix[i][j+1].unlock();
					mutexmatrix[i][j].unlock();
					mutexmatrix[i+1][j].unlock();
			}
			else if(l>=k && l>=m)
			{//finding the maximum value among all the neighbors and firstly lock cout for getting enought time to print and then our base(cell have neighbors) getting value from its neighbor as its value and of the cond.all of the neighbor mutexes unlocked 
				max=l;
				if(max>=2*t)
				{
					coutmutex.lock();
					cout<<"Row-"<<i<<",Col-"<<j<<" ("<<matrix[i][j]<<") is incremented by "<<ceil(t/3)<<" by stealing from the cell below ("<<matrix[i+1][j]<<")."<<endl;
					coutmutex.unlock();
					matrix[i][j]+=ceil(t/3);
					matrix[i+1][j]-=ceil(t/3);
						isdone=true;
				
				}
					mutexmatrix[i-1][j].unlock();
					mutexmatrix[i][j+1].unlock();
					mutexmatrix[i][j].unlock();
					mutexmatrix[i+1][j].unlock();
			}
			else if(m>=k && m>=l)
			{//finding the maximum value among all the neighbors and firstly lock cout for getting enought time to print and then our base(cell have neighbors) getting value from its neighbor as its value and of the cond.all of the neighbor mutexes unlocked 
				max=m;
				if(max>=2*t)
				{
					coutmutex.lock();
					cout<<"Row-"<<i<<",Col-"<<j<<" ("<<matrix[i][j]<<") is incremented by "<<ceil(t/3)<<" by stealing from the cell to the right ("<<matrix[i-1][j]<<")."<<endl;
					coutmutex.unlock();
					matrix[i][j]+=ceil(t/3);
					matrix[i-1][j]-=ceil(t/3);
						isdone=true;
				}
					mutexmatrix[i-1][j].unlock();
					mutexmatrix[i][j+1].unlock();
					mutexmatrix[i][j].unlock();
					mutexmatrix[i+1][j].unlock();

			}


			break;
		}
		else if(flag==false)
		{// if we locked any of neighbor but not all of them we have to unlocked it because at least one of them was locked before out trying and it is under processessing situation 
			if(a==true)
			{
				mutexmatrix[i][j+1].unlock();
			}
			if(b==true)
			{
				mutexmatrix[i+1][j].unlock();
			}
			if(c==true)
			{
				mutexmatrix[i-1][j].unlock();
			}
			if(d==true)
			{
				mutexmatrix[i][j].unlock();
			}
			this_thread::yield();



		}



	}
	else if(i!=0 && j ==col-1 && i !=row-1)
	{// processing the right edge
		a=mutexmatrix[i-1][j].try_lock();
		b=mutexmatrix[i+1][j].try_lock();//finding the neighbor cells and unlock them if they are available (if they are not locked)
		c=mutexmatrix[i][j-1].try_lock();
		d=mutexmatrix[i][j].try_lock();
		if(a==true && b ==true && c==true&& d==true)// if all the neighbor unlocked flag true(beginning of our process)
		{
			flag=true;
		}
		if(flag)
		{
			t=matrix[i][j];
			k=matrix[i-1][j];
			l=matrix[i+1][j];
			m=matrix[i][j-1];
			if(k>=l && k>=m)
			{//finding the maximum value among all the neighbors and firstly lock cout for getting enought time to print and then our base(cell have neighbors) getting value from its neighbor as its value and of the cond.all of the neighbor mutexes unlocked 
				max=k;
				if(max>=2*t)
				{
					coutmutex.lock();
					cout<<"Row-"<<i<<",Col-"<<j<<" ("<<matrix[i][j]<<") is incremented by "<<ceil(t/3)<<" by stealing from the cell above ("<<matrix[i-1][j]<<")."<<endl;
					coutmutex.unlock();
					matrix[i][j]+=ceil(t/3);
					matrix[i-1][j]-=ceil(t/3);
						isdone=true;
			
				}
					mutexmatrix[i+1][j].unlock();
					mutexmatrix[i][j-1].unlock();
					mutexmatrix[i][j].unlock();
					mutexmatrix[i-1][j].unlock();
			}
			else if(l>=k && l>=m)
			{//finding the maximum value among all the neighbors and firstly lock cout for getting enought time to print and then our base(cell have neighbors) getting value from its neighbor as its value and of the cond.all of the neighbor mutexes unlocked 
				max=l;
				if(max>=2*t)
				{
					coutmutex.lock();
					cout<<"Row-"<<i<<",Col-"<<j<<" ("<<matrix[i][j]<<") is incremented by "<<ceil(t/3)<<" by stealing from the cell below ("<<matrix[i+1][j]<<")."<<endl;
					coutmutex.unlock();
					matrix[i][j]+=ceil(t/3);
					matrix[i+1][j]-=ceil(t/3);
						isdone=true;
				
				}
					mutexmatrix[i+1][j].unlock();
					mutexmatrix[i][j-1].unlock();
					mutexmatrix[i][j].unlock();
					mutexmatrix[i-1][j].unlock();
			}
			else if(m>=k && m>=l)
			{//finding the maximum value among all the neighbors and firstly lock cout for getting enought time to print and then our base(cell have neighbors) getting value from its neighbor as its value and of the cond.all of the neighbor mutexes unlocked 
				max=m;
				if(max>=2*t)
				{
					coutmutex.lock();
					cout<<"Row-"<<i<<",Col-"<<j<<" ("<<matrix[i][j]<<") is incremented by "<<ceil(t/3)<<" by stealing from the cell to the left ("<<matrix[i][j-1]<<")."<<endl;
					coutmutex.unlock();
					matrix[i][j]+=ceil(t/3);
					matrix[i][j-1]-=ceil(t/3);
						isdone=true;
		
				}
					mutexmatrix[i+1][j].unlock();
					mutexmatrix[i][j-1].unlock();
					mutexmatrix[i][j].unlock();
					mutexmatrix[i-1][j].unlock();
			}

			break;

		}
		else if(flag==false)
		{// if we locked any of neighbor but not all of them we have to unlocked it because at least one of them was locked before out trying and it is under processessing situation 
			if(a==true)
			{
				mutexmatrix[i-1][j].unlock();
			}
			if(b==true)
			{
				mutexmatrix[i+1][j].unlock();
			}
			if(c==true)
			{
				mutexmatrix[i][j-1].unlock();
			}
			if(d==true)
			{
				mutexmatrix[i][j].unlock();
			}

			this_thread::yield();


		}




	}
	else if(i>0 && i<row-1 && j>0 && j<col-1)//processing the all of the part of matrix without edge and corner
	{//finding the neighbor cells and unlock them if they are available (if they are not locked)
		a=mutexmatrix[i+1][j].try_lock();
		b=mutexmatrix[i-1][j].try_lock();
		c=mutexmatrix[i][j-1].try_lock();
		d=mutexmatrix[i][j+1].try_lock();
		e=mutexmatrix[i][j].try_lock();
		if(a==true && b==true && c==true && d==true && e==true)
		{
			flag=true;
		}// if all the neighbor unlocked flag true(beginning of our process)
		if(flag)
		{
			t=matrix[i][j];
			k=matrix[i-1][j];
			l=matrix[i][j-1];
			m=matrix[i][j+1];
			n=matrix[i+1][j];
			if(k>=l && k>=m && k>=n )
			{//finding the maximum value among all the neighbors and firstly lock cout for getting enought time to print and then our base(cell have neighbors) getting value from its neighbor as its value and of the cond.all of the neighbor mutexes unlocked 
				max=k;
				if(max>=2*t)
				{
					coutmutex.lock();
					cout<<"Row-"<<i<<",Col-"<<j<<" ("<<matrix[i][j]<<") is incremented by "<<ceil(t/3)<<" by stealing from the cell above ("<<matrix[i-1][j]<<")."<<endl;
					coutmutex.unlock();
					matrix[i][j]+=ceil(t/3);
					matrix[i-1][j]-=ceil(t/3);
						isdone=true;
			
				}
						mutexmatrix[i+1][j].unlock();
					mutexmatrix[i][j+1].unlock();
					mutexmatrix[i][j].unlock();
					mutexmatrix[i][j-1].unlock();
					mutexmatrix[i-1][j].unlock();
			}
			else if(l>=k && l>=m && l>=n)
			{//finding the maximum value among all the neighbors and firstly lock cout for getting enought time to print and then our base(cell have neighbors) getting value from its neighbor as its value and of the cond.all of the neighbor mutexes unlocked 
				max=l;
				if(max>=2*t)
				{
					coutmutex.lock();
					cout<<"Row-"<<i<<",Col-"<<j<<" ("<<matrix[i][j]<<") is incremented by "<<ceil(t/3)<<" by stealing from the cell to the left ("<<matrix[i][j-1]<<")."<<endl;
					coutmutex.unlock();
					matrix[i][j]+=ceil(t/3);
					matrix[i][j-1]-=ceil(t/3);
						isdone=true;
				}	
				mutexmatrix[i+1][j].unlock();
					mutexmatrix[i][j+1].unlock();
					mutexmatrix[i][j].unlock();
					mutexmatrix[i][j-1].unlock();
					mutexmatrix[i-1][j].unlock();
			}
			else if(m>=k && m>=l && m>=n)
			{
				max=m;
				if(max>=2*t)
				{
					coutmutex.lock();
					cout<<"Row-"<<i<<",Col-"<<j<<" ("<<matrix[i][j]<<") is incremented by "<<ceil(t/3)<<" by stealing from the cell to the right ("<<matrix[i][j+1]<<")."<<endl;
					coutmutex.unlock();
					matrix[i][j]+=ceil(t/3);
					matrix[i][j+1]-=ceil(t/3);
						isdone=true;
				//finding the maximum value among all the neighbors and firstly lock cout for getting enought time to print and then our base(cell have neighbors) getting value from its neighbor as its value and of the cond.all of the neighbor mutexes unlocked 
				}
					mutexmatrix[i+1][j].unlock();
					mutexmatrix[i][j+1].unlock();
					mutexmatrix[i][j].unlock();
					mutexmatrix[i][j-1].unlock();
					mutexmatrix[i-1][j].unlock();
			}
			else if(n>=k && n>=l && n>=m)
			{
				max=n;
				if(max>=2*t)
				{//finding the maximum value among all the neighbors and firstly lock cout for getting enought time to print and then our base(cell have neighbors) getting value from its neighbor as its value and of the cond.all of the neighbor mutexes unlocked 
					coutmutex.lock();
					cout<<"Row-"<<i<<",Col-"<<j<<" ("<<matrix[i][j]<<") is incremented by "<<ceil(t/3)<<" by stealing from the cell below ("<<matrix[i+1][j]<<")."<<endl;
					coutmutex.unlock();
					matrix[i][j]+=ceil(t/3);
					matrix[i+1][j]-=ceil(t/3);
						isdone=true;
				
				}
					mutexmatrix[i+1][j].unlock();
					mutexmatrix[i][j+1].unlock();
					mutexmatrix[i][j].unlock();
					mutexmatrix[i][j-1].unlock();
					mutexmatrix[i-1][j].unlock();
			}
			break;
		}
		else if(flag==false)
		{// if we locked any of neighbor but not all of them we have to unlocked it because at least one of them was locked before out trying and it is under processessing situation 
			if(a==true)
			{
				mutexmatrix[i+1][j].unlock();
			}
			if(b==true)
			{
				mutexmatrix[i-1][j].unlock();
			}
			if(c==true)
			{
				mutexmatrix[i][j-1].unlock();
			}
			if(d==true)
			{
				mutexmatrix[i][j+1].unlock();
			}
			if(e==true)
			{
				mutexmatrix[i][j].unlock();
			}

			this_thread::yield();


		}



	}
	




	}

}



int main()
{
	cout<<"Welcome to the last homework :("<<endl;
	string filename;
	cout<<"Please enter a file name for the matrix: ";
	cin>>filename;
	cout<<"-----"<<endl;
	string line;
	ifstream f;
	f.open(filename.c_str());
	if(f.fail())
	{
		cout<<"mlsf"<<endl;
	}
	// creating a dynamic allocated matrix with pointers 
	getline(f,line);
	int number;
	istringstream ss(line);
	int row,col;
	ss>>number;
	row=number;
	ss>>number;
	col=number;
	int **matrix=new int *[row];
	for(int i=0;i<row;i++)
	{
		matrix[i]=new int[col];
	}
	int numbers;
	int i=0,k;
	while(getline(f,line))
	{
		k=0;
		istringstream ss(line);
		while(ss>>number)
		{
			matrix[i][k]=number;
			k++;
		}
		i++;
	}
	cout<<"Printing the original matrix:"<<endl;
	printingmatrix(matrix,row,col);
	cout<<"------"<<endl;
	cout<<"A new round starts"<<endl;
	thread **threadmatrix=new thread *[row];
	for(int i=0;i<row;i++)
	{
		threadmatrix[i]=new thread[col];// creating a dynamic allocated thread matrix
	}
	mutexmatrix=new mutex*[row];	
	for(int i=0;i<row;i++)
	{
		mutexmatrix[i]=new mutex[col];
	}
	while(isdone)
	{//while loop doing the loop for processing continuity
	isdone=false;
	for(int k=0;k<row;k++)
	{
		for(int t=0;t<col;t++)
		{
			threadmatrix[k][t]=thread(&func,k,t,ref(matrix),row,col);//creating the matrix which contains the severeal thread
			
		}
	}
	
	for(int i=0;i<row;i++)
	{
		for(int k=0;k<col;k++)
		{
			threadmatrix[i][k].join();// joining for a processor in the gpu
		}

	}

	if(isdone)// it means there is a change in the matrix it is a updates
	{
		cout<<"The round ends with updates"<<endl;
		cout<<"Printing the matrix after the updates:"<<endl;
		printingmatrix(matrix,row,col);
		cout<<"----"<<endl;
		cout<<"A new round starts"<<endl;
	}
	}
	cout<<"The round ends without updates."<<endl;
	cout<<"------"<<endl;
	cout<<"Program is exiting...";	

	DeleteMatrix(matrix,row);
	DeleteMatrixmutex(mutexmatrix,row);//deleting the all three allocated matrix in end of the program
	DeleteMatrixthread(threadmatrix,row);
	system("pause");
	return 1;
	







}
