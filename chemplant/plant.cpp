#include<bits/stdc++.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/select.h>
#define file_mode (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)
using namespace std;
int main()
{
	char *nfifo=new char(100);
	strcpy(nfifo,"nfifo");
	//mkfifo(nfifo,file_mode);
	char *hfifo=new char(100);
	strcpy(hfifo,"hfifo");
	//mkfifo(hfifo,file_mode);
	char *ofifo=new char(100);
	strcpy(ofifo,"ofifo");
	//mkfifo(ofifo,file_mode);
	
	int fd1=open(nfifo,O_RDONLY);
	int fd2=open(hfifo,O_RDONLY);
	int fd3=open(ofifo,O_RDONLY);

	vector<int> v;
	v.push_back(fd1);
	v.push_back(fd2);
	v.push_back(fd3);
	char buf[500];
	fd_set set;
	FD_ZERO(&set);
	while(1)
	{
			//sleep(1);
			for(int i=0;i<v.size();i++)
			{
				FD_SET(v[i],&set);
			}

			int po=select(FD_SETSIZE,&set,NULL,NULL,NULL);
			if(po==-1)
			{
				perror("gg");
			}
			for(int i=0;i<v.size();i++)
			{
				sleep(1);
				if(FD_ISSET(v[i],&set));
				{

					
					if(i==0)
					{
						read(fd1,&buf,500);
						cout<<"N: ";
						cout<<"recieved: "<<buf<<endl;
					}
					else if(i==1)
					{
						read(fd2,&buf,500);
						cout<<"H: ";
						cout<<"recieved: "<<buf<<endl;
					}
					else if(2)
						{
							read(fd3,&buf,500);
						cout<<"0: ";
						cout<<"recieved: "<<buf<<endl;
						}
					
				}
			}





	}
		return 0;
	}