#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <pthread.h>
#include <unistd.h>

#define SERVER_PORT 5500
#define BUF_SIZE 1024
#define LISNUM 10

int main(){
	int sock_fd, new_fd;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;

	int sin_size,myport,lisnum;
	int n;
	char s_net2usb_buff[BUF_SIZE+1];
	//char s_usb2net_buff[BUF_SIZE+1];
	char s_usb2net_buff[BUF_SIZE+1] = "The information is from server.The server will send message frequtlly and you will always know it.If you is connected,you could see the information!Have a good time!";
	bool usb_connect,net_connect ;
	int on = 1;
	pthread_t s_usb2net_id,s_net2usb_id;

	/* open the point*/
/*	int fp = open("/dev/impinj",O_RDWR);
	if(!fp){
		perror("open device ERROR");
		exit(0);
	}else{
		printf("open device success!\n");
	}
*/
/*	if(argc!=2){
		printf(stderr,"Usage:%s n\a\n",argv[0]);
		exit(1);
	}

	if((n = atoi(argv[1])) < 0){
		printf(stderr,"Usage:%s n\a\n",argv[0]);
		exit(1);
	}

	if(argv[1])
		myport = atoi(argv[1]);
	else
		myport = 7838;

	if(argv[2])
		lisnum = atoi(argv[2]);
	else
		lisnum = 10;
		
*/

	if ((sock_fd = socket(AF_INET,SOCK_STREAM,0)) == -1){
		perror("socket");
		exit(1);
	}

	/* Enable address reuse */
	setsockopt(sock_fd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));

	bzero(&server_addr,sizeof(struct sockaddr_in));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(SERVER_PORT);

	if(bind(sock_fd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr)) == -1){
		perror("bind");
		exit(1);
	}
	
	printf("Hello,welcome to server!\n");
	
	if(listen(sock_fd,LISNUM) == -1){
		perror("listen");
		exit(1);
	}

	while(1){
		sin_size = sizeof(struct sockaddr_in);

		if ((new_fd = accept(sock_fd,(struct sockaddr *)&(client_addr),&sin_size))==-1) {
			perror("accept");
//			continue;
			exit(1);
		}else{
				if(send(new_fd,"connect to server success!",30,0) == -1){
					perror("send");
					close(new_fd);
				    exit(0);
				}
		}

		printf("server:got connection from %s,port %d,socket %d\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port),new_fd);
		

		/*the read and send thread */
		void *S_UsbtoNet_Thread(void *arg){
			
		/*		char writebuff[] = {0x01,0x00,0x00,0x07,0xFF,0xFF,0x00,0x00};
					printf("You want to write:%s\n",writebuff);
				if(8 == write(fp,writebuff,8)){
					printf("write success!\n");
				}else{
					printf("write failed!please write the command:");
					char  str[80];
					scanf("%s",&str);
					write(fp,str,strlen(str));
				}

				char writebuff_1[] = {0x01,0x00,0x00,0xF0,0x0F,0x00,0x00,0x00};
					printf("You want to write_1:%s\n",writebuff_1);
				if(8 == write(fp,writebuff_1,8)){
					printf("write success!\n");
				}else{
					printf("write failed!please write the command:");
					char  str[80];
					scanf("%s",&str);
					write(fp,str,strlen(str));
				}
			*/
			while(1){
			/*	if((num = read(fp,s_usb2net_buff,BUF_SIZE)) < 0){
					perror("Read ERROR");
				}else{
					printf("Read buff %d bytes:%s\n",num,s_usb2net_buff);
					memset(s_usb2net_buff,0,1024);
				//	close(fp);
				}*/
			//	if(num > 0){
					if(send(new_fd,s_usb2net_buff,strlen(s_usb2net_buff),0) == -1){
						perror("send");
						//close(new_fd);
						//exit(0);
					}else{
						printf("server send success!\n");
					}
			//	}
			}
		}

		/*the receive and write thread */
   		void *S_NettoUsb_Thread(void *arg){
			while(1){
				bzero(s_net2usb_buff,BUF_SIZE+1);
				if ( (n = recv(new_fd,s_net2usb_buff,BUF_SIZE,0 ))== -1) {
					perror("server recv ERROR");
					//exit(1);
				}
				s_net2usb_buff[n] = 0;
				if(n > 0){
					printf("Server recv %d bytes:%s\n",n,s_net2usb_buff);

				/*	if(strlen(s_net2usb_buff) == write(fp,s_net2usb_buff,strlen(s_net2usb_buff))){
						printf("write success!\n");
					}else{
						printf("write failed!\n");
					}*/
				}
			}
		}


		/* create the receive and write thread */
		if(pthread_create(&s_net2usb_id,NULL,S_NettoUsb_Thread,NULL)){
			printf("S_NettoUsb_thread is created failed!\n");
			//return -1;
		}


		/* create the read  and send thread */
		if(pthread_create(&s_usb2net_id,NULL,S_UsbtoNet_Thread,NULL)){
			printf("S_UsbtoNet_thread is created failed!\n");
			//return -1;
		}
	
		if((pthread_join(s_net2usb_id,NULL)) != 0){
			perror("pthread_join ERROR");
		}
		if((pthread_join(s_usb2net_id,NULL)) != 0){
			perror("pthread_join ERROR");
		}

	}

	close(sock_fd);
	exit(0);
}

