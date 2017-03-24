#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/socket.h>
#include<sys/un.h>

#define PATH "./HI"

void recv_fd(int usfd, int *fd)
{
	struct msghdr msg;
	struct cmsghdr *cmsg;
	memset(&msg, 0, sizeof(struct msghdr));
	char buf[256] = {0};
	
	char m_buffer[1];
    struct iovec io = { .iov_base = m_buffer, .iov_len = sizeof(m_buffer) };
    msg.msg_iov = &io;
    msg.msg_iovlen = 1;
	
	msg.msg_control = buf;
	msg.msg_controllen = sizeof buf;
	printf("1\n");
	if (recvmsg(usfd, &msg, 0) < 0)
    {
        perror("recvmsg");
        exit(-1);
    }
	printf("1\n");
	cmsg = CMSG_FIRSTHDR(&msg);
	
	memcpy(fd, CMSG_DATA(cmsg), sizeof(int));
    printf("Extracted fd %d\n", *fd);
}

int main()
{
	int usfd, fd;
	struct sockaddr_un addr;
	
	if((usfd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
	{
		perror("socket ");
		exit(0);
	}
	
	addr.sun_family = AF_UNIX;
	strcpy(addr.sun_path, PATH);
	if(connect(usfd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
	{
		perror("connect ");
		exit(0);
	}
	
	recv_fd(usfd, &fd);
	char buff[] = "Hey, this is client writing to your stdout..\n";
	write(fd, buff, sizeof buff);
	
	close(fd);
	exit(0);
}
