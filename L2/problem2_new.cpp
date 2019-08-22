#include <bits/stdc++.h>
#include <sys/types.h>
#include <unistd.h> 

using namespace std;
int main()
{
	if(fork()==0)
	{
		sleep(2);
		cout<<"\nChild is an orphan process : "<<getpid()<<"\n";
		if(fork()==0)
		{
			cout<<"Grandchild finished "<<getpid()<<"\n";
			return 0;
		}
		sleep(1);
		cout<<"Grandchild process is a zombie process : \n";
		sleep(2);
		return 0;
	}
	cout<<"Parent finished "<<getpid()<<"\n";
}