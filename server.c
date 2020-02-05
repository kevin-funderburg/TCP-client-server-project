/****************** SERVER CODE ****************/

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#define MAXCHAR 1000

int add()
{
//    printf("adding");
    FILE *fp;
    char str[MAXCHAR];
    char* filename = "data.txt";

    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Could not open file %s",filename);
        return 1;
    }
    while (fgets(str, MAXCHAR, fp) != NULL)
        printf("%s", str);
    fclose(fp);
    return 0;
}

int display_all()
{
    FILE *fp = fopen("data.txt", "r");

    if (!fp) {
        printf("Can't open file\n");
        return 0;
    }

    char buf[1024];
    int row_count = 0;
    int field_count = 0;
    while (fgets(buf, 1024, fp)) {
        field_count = 0;
        row_count++;

        if (row_count == 1) {
            continue;
        }

        char *field = strtok(buf, ",");
        while (field) {
            if (field_count == 0) {
                printf("Student ID:\t");
            }
            if (field_count == 1) {
                printf("First Name:\t");
            }
            if (field_count == 2) {
                printf("Last Name:\t");
            }
            if (field_count == 3) {
                printf("Grade:\t\t");
            }

            printf("%s\n", field);
            field = strtok(NULL, ",");

            field_count++;
        }
        printf("\n");
    }

    fclose(fp);

    return 0;
}

int main()
{
//    add();
    display_all();
//  int welcomeSocket, newSocket;
//  char buffer[1024];
//  struct sockaddr_in serverAddr;
//  struct sockaddr_storage serverStorage;
//  socklen_t addr_size;
//
//  /*---- Create the socket. The three arguments are: ----*/
//  /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
//  welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);
//
//  /*---- Configure settings of the server address struct ----*/
//  /* Address family = Internet */
//  serverAddr.sin_family = AF_INET;
//  /* Set port number, using htons function to use proper byte order */
//  serverAddr.sin_port = htons(7891);
//  /* Set IP address to localhost */
//  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
//  /* Set all bits of the padding field to 0 */
//  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
//
//  /*---- Bind the address struct to the socket ----*/
//  bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
//
//  /*---- Listen on the socket, with 5 max connection requests queued ----*/
//  if(listen(welcomeSocket,5)==0)
//    printf("Listening\n");
//  else
//    printf("Error\n");
//
//  /*---- Accept call creates a new socket for the incoming connection ----*/
//  addr_size = sizeof serverStorage;
//  newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);
//
//  /*---- Send message to the socket of the incoming connection ----*/
//  strcpy(buffer,"Hello World\n");
//  send(newSocket,buffer,13,0);

  return 0;
}
