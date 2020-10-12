#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<netdb.h>
int main()
{
	int c_sock;
	int n1,n2,ch;
	double ans;
	c_sock = socket(AF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in client;
	socklen_t client_len;
	client_len = sizeof(client);
	client.sin_family = AF_INET;
	client.sin_port = htons(9009);
	client.sin_addr.s_addr = INADDR_ANY;
	printf("Enter first number \n");
	scanf("%d",&n1);
	sendto(c_sock,&n1,sizeof(n1), 0, (struct sockaddr*)&client,sizeof(client));
	printf("Enter second number\n");
	scanf("%d",&n2);
	sendto(c_sock,&n2, sizeof(n2), 0, (struct sockaddr*)&client,sizeof(client));
	printf("Enter ur choice \n");
	scanf("%d",&ch);
	sendto(c_sock,&ch, sizeof(&ch), 0, (struct sockaddr*)&client,sizeof(client));
	recvfrom(c_sock,&ans, sizeof(ans), 0, (struct sockaddr*)&client,&client_len);
	printf("Result: %f\n",ans);
	close(c_sock);
	return 0;
}