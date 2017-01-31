#include<bits/stdc++.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/types.h>
#include<unistd.h>
using namespace std;
struct mymsg
	{	
		long mtype;
		char mtext[100];
		long pid;
		long gid;
	};

int main()
{


	int msgid;
	mymsg buffer;
	msgid=msgget((key_t)125,0666);
	if(msgid==-1)
	{
		cout<<"failed to open message queue\n";
	}
	else
	{
		cout<<"reading\n";
		while(1)
		{	cout<<"reading\n";
			if(msgrcv(msgid,&buffer,sizeof(buffer),69,IPC_NOWAIT)<0)
			{

			//	cout<<"failed to recieve\n";
				
			}
			else
			{
				
				mymsg reply;
				int i=0,j=0;
				if(buffer.gid==1)
				{
					i=1;j=2;
				}
				else if(buffer.gid==2)
				{
					i=3;j=4;
				}
				for(i;i<=j;i++)
				{


					strcpy(reply.mtext,buffer.mtext);
					reply.mtype=i;
					if(msgsnd(msgid,&reply,sizeof(reply),IPC_NOWAIT)<0)
					{
						cout<<"sending failed";
					}
					else
					{

						cout<<"put in queue "<<reply.mtext<<" "<<reply.mtype;
					}
				}
			}
			sleep(1);
		}
	}
	return 0;

}