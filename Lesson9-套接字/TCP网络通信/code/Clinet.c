#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <pthread.h>

#define MAXDATASIZE 1024

int main(int argc, char *argv[]){
	int sockfd, portnumber,nbytes;
	char c_usb2net_buf[MAXDATASIZE] = "Hello,show you are success to send word from clinet if you can see this sentence! The programe took my three day to make it work!And their is a will,there is a way!Enjoy your time!Best Regards!";
	char c_net2usb_buf[MAXDATASIZE];
	bool conn = true,send_thread = true;
	struct hostent *he;
	struct sockaddr_in server_addr;
	int i;
	pthread_t c_usb2net_id,c_net2usb_id;
	
	if(argc != 3){
		fprintf(stderr,"Usage:%s  hostname portnumber\a\n",argv[0]);
		exit(1);
	}

	if ( (portnumber = atoi(argv[2])) < 0 ) {
		fprintf(stderr,"Usage:%s  hostname portnumber\a\n",argv[0]);
		exit(1);

	}

	if ( (he = gethostbyname(argv[1])) == NULL ) {
		perror("gethostbyname");
		exit(1);
	}

	if ( (sockfd = socket(AF_INET,SOCK_STREAM,0))== -1) {
		perror("socket");
		exit(1);
	}

	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(portnumber);
	server_addr.sin_addr = *((struct in_addr *)he->h_addr);
	
	while(1){

		while(conn){
			if(connect(sockfd, (struct sockaddr *)&server_addr,sizeof(struct sockaddr)) == -1){
				perror("connect");
				exit(1);
			}
			conn = false;
		}

		/*****************   the send thread function ********************/
		void *C_UsbtoNet_Thread(void *arg){
			i=0;i++;
			printf("send thread ------>%d",i);
			while(1){
				if(send(sockfd,c_usb2net_buf,strlen(c_usb2net_buf),0) == -1){
					perror("send");
					//				  close(sockfd);
				}else if(send(sockfd,c_usb2net_buf,strlen(c_usb2net_buf),0) == 0){
					printf("----> clinet is ranking and waiting!\n");
				}else{
					printf("----> clinet send success!\n");
				}
			}
		}
		
		/* create the thread */
		while(send_thread){
			if(pthread_create(&c_usb2net_id,NULL,C_UsbtoNet_Thread,NULL)){
				printf("C_UsbtoNet_thread is created failed!\n");
				send_thread = true;
			}
			send_thread = false;
		}
		/* stock the thread */
		/*if((pthread_join(c_usb2net_id,NULL)) != 0){
			perror("usb2net_thread_join ERROR");
		}*/


		/**************** the receive action in the main thread ***********/
		bzero(c_net2usb_buf,MAXDATASIZE+1);
		if ( (nbytes = recv(sockfd,c_net2usb_buf,MAXDATASIZE,0 ))== -1) {
			perror("server recv ERROR");
			//exit(1);
		}
		c_net2usb_buf[nbytes] = 0;
		if(nbytes > 0){
			printf("clinet recv %d bytes:%s\n",nbytes,c_net2usb_buf);
		}

	}
	close(sockfd);
	exit(0);
}
