#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/socket.h>
#include<sys/un.h>

#define PATH "./HI"

void send_fd(int usfd, int fd)
{
	struct msghdr msg;
	struct cmsghdr *cmsg;
	char buf[CMSG_SPACE(sizeof fd)];
	memset(&msg, 0, sizeof(struct msghdr));
	
	char m_buffer[1];
    struct iovec io = { .iov_base = m_buffer, .iov_len = sizeof(m_buffer) };

    msg.msg_iov = &io;
    msg.msg_iovlen = 1;
	msg.msg_control = buf;
	msg.msg_controllen = sizeof buf;
	cmsg = CMSG_FIRSTHDR(&msg);
	cmsg->cmsg_level = SOL_SOCKET;
	cmsg->cmsg_type = SCM_RIGHTS;
	cmsg->cmsg_len = CMSG_LEN(sizeof(int));
	
	memcpy(CMSG_DATA(cmsg), &fd, sizeof(int));
	
	if(sendmsg(usfd, &msg, 0) == -1)
	{
		perror("sendmsg ");
		exit(0);
	}
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
	
	unlink(PATH);
	addr.sun_family = AF_UNIX;
	strcpy(addr.sun_path, PATH);
	if(bind(usfd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
	{
		perror("bind ");
		exit(0);
	}
	
	listen(usfd, 5);
	
	struct sockaddr_un cli;
	//int len;
	socklen_t *len = (socklen_t *)&cli;
	int nsfd = accept(usfd, (struct sockaddr*)&cli, len);
	printf("client connected...\n");
	
	fd = STDOUT_FILENO;
	send_fd(nsfd, fd);
	printf("fd sent..\n");
	
	while(1)
		fflush(stdout);
	
}
