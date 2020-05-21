#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <strings.h>

#define serverip "192.168.1.100"
unsigned short int netprot = 5678;

int main(int argc, char **argv)
{
	//const char buf[] = "i love linux";
	char buf[200] = {0};
	int fd = -1;
	int error;
	struct sockaddr_in dest_addr ;
	fd = socket(AF_INET, SOCK_STREAM, 0);
	if(fd < 0)
	{
		printf("socket fail.\n");
		return -1;
	}
	dest_addr.sin_family = AF_INET ;
	dest_addr.sin_port = htons(netprot);
	dest_addr.sin_addr.s_addr = inet_addr(serverip);
	bzero(&(dest_addr.sin_zero), 8);
	error = connect(fd, (struct sockaddr *)&dest_addr, sizeof(struct sockaddr_in));
	if(error != 0)
	{
		printf("connect fail \n");
		return -1;
	}
	
	fgets(buf, sizeof(buf), stdin);
	send(fd, buf, strlen(buf), 0);
	
	close(fd);
	
	exit(0);
}
