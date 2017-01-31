#include<bits/stdc++.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#define file_mode (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)
using namespace std;
int main()
{
	
	char *nfifo=new char(100);
	cout<<"starting\n";
	strcpy(nfifo,"ofifo");
	mkfifo(nfifo,file_mode);;
	int fd=open(nfifo,O_WRONLY);
	if(fd==-1)
	{
		cout<<"error\n";
	}
	char buf[100];
	cout<<"Sending data\n";
	while(1)
	{
		char buf[100];
		strcpy(buf,"O:");
		int m=rand()%9+1;
		cout<<m<<endl;
		char c=char(m)+48;
		buf[2]=c;
		cout<<buf<<endl;
		write(fd,&buf,sizeof(buf));
		sleep(5);
	}
	return 0;

}