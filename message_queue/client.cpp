#include<bits/stdc++.h>
#include<sys/ipc.h> 
#include<sys/msg.h> 
#include<sys/types.h>
#include<unistd.h>
using namespace std;
struct mymsg {
      long      mtype;    /* message type */
      char mtext[100]; /* message text of length 100 */
		long pid;
		long gid;
};
int main()
{
	struct mymsg buffer;
	int msgid;
	msgid = msgget((key_t)125, 0666 | IPC_CREAT);
	if(msgid==-1)
	{
		cout<<"Message queue failed\n";

	}

	buffer.mtype=69;
	buffer.pid=1;
	buffer.gid=1;

	int m=fork();
	if(m==0)
	{	
		while(1)
		{
			cout<<"type to text:  \n";
			cin>>buffer.mtext;
			//strcpy(buffer.mtext,"hello beta");
			int m=rand()%10 +1;
			char k=m+48;
			char *kl=&k;
			//strcat(buffer.mtext,kl);
			//strcat(buffer.mtext,"\n");
			int l= strlen(buffer.mtext)+1;
			//cout<<buffer.mtext;
			if(msgsnd(msgid,&buffer,sizeof(buffer),IPC_NOWAIT)<0)
			{
				cout<<"message sending failed\n";

			}
			else
			cout<<"Sent: "<<buffer.mtext<<endl;
			//sleep(1);
		}
	}
	else
	{	
		//out<<"parent exec\n";
		while(1)
		{
			//cout<<"parent exec\n";
			mymsg reply;
			if(msgrcv(msgid,&reply,sizeof(reply),1,IPC_NOWAIT)<0)
			{
				//cout<<"no reply:(";
			}
			else
			cout<<reply.mtext<<endl;
		//sleep(1);
		}
	}
	return 0;
}