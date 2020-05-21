#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

#define ipaddr "192.168.1.100"
struct sockaddr_in *psockaddr;
unsigned short int netprot = 5678;

int main(int argc, char **argv)
{
	int fd = -1;
	int new_fd = -1;
	int error = -1;
	char buf[21] ={0};
	unsigned int clilen = sizeof(struct sockaddr_in);
	fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(fd < 0)
	{
		printf("socket fail.\n");
		return -1;
	}
	psockaddr = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
	memset(psockaddr, 0, sizeof(struct sockaddr_in));
	psockaddr->sin_family	    = AF_INET;
	psockaddr->sin_port 	= htons(netprot);
	//psockaddr->sin_addr.s_addr  = inet_aton(ipaddr);
	psockaddr->sin_addr.s_addr  =htonl(INADDR_ANY); //表示自动识别和绑定本机所有ip
	
	error = bind(fd, (struct sockaddr *)psockaddr, sizeof(struct sockaddr_in));
	if(error != 0)
	{
		printf("bind fail.\n");
		return -1;
	}
	
	listen(fd, 5);
	
	for(;;)
	{
		new_fd = accept(fd, (struct sockaddr *)psockaddr,&clilen);
		if(error == -1)
		{
			printf("accept fail.\n");
			return -1;
		}

		error = recv(new_fd, buf, 20, 0);
		
		buf[error] = '\0';
		printf("recv: %s,receve count: %d \n",buf,error);
	}
	
	close(fd);
	free(psockaddr);
	return 0;
}
