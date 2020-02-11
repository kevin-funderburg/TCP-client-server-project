/****************** SERVER CODE ****************/

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdbool.h>
#include<stdlib.h>

int add(int ID, char *Fname, char *Lname, int score);
int delete(int ID);
int getRowNum(int rowID);
int display_all();

#define MAXCHAR 1024
char* datafile = "data.csv";

int add(int ID, char *Fname, char *Lname, int score)
{
    FILE *fp;
    fp = fopen(datafile, "a");
    if (fp == NULL) {
        printf("Could not open file %s", datafile);
        return 1;
    }
    if (getRowNum(ID) != -1)
        delete(ID);

    fprintf(fp, "%d,%s,%s,%d\n", ID, Fname, Lname, score);
    fclose(fp);
    return 0;
}

int delete(int ID)
{
    FILE *fp1, *fp2;
    char str[MAXCHAR];

    fp1 = fopen(datafile, "r");
    if (!fp1) {
        printf(" File not found or unable to open the input file!!\n");
        return 0;
    }
    fp2 = fopen("temp.csv", "w"); // open the temporary file in write mode
    if (!fp2) {
        printf("Unable to open a temporary file to write!!\n");
        fclose(fp1);
        return 0;
    }

    int ctr = 0;
    int rowNum = getRowNum(ID);
    // copy all contents to the temporary file except the specific line
    while (!feof(fp1))
    {
        strcpy(str, "\0");
        fgets(str, MAXCHAR, fp1);
        if (!feof(fp1)) {
            ctr++;
            /* skip the line at given line number */
            if (ctr != rowNum) {
                printf("line to be copied: %s", str);
                fprintf(fp2, "%s", str);
            }
        }
    }

    fclose(fp1);
    fclose(fp2);
    remove(datafile);  		// remove the original file
    rename("temp.csv", datafile); 	// rename the temporary file to original name
    return 0;
}

int getRowNum(int rowID)
{
    FILE *fp1;
    char buf[MAXCHAR];
    int rowNum = 0;

    fp1 = fopen(datafile, "r");
    if (!fp1) {
        printf(" File not found or unable to open the input file!!\n");
        return 0;
    }
    while (fgets(buf, MAXCHAR, fp1)) {
        rowNum++;
        char *field = strtok(buf, ",");
        if (atoi(field) == rowID) return rowNum;
    }
    return -1;
}

int display_all()
{
    FILE *fp = fopen(datafile, "r");

    if (!fp) {
        printf("Can't open file\n");
        return 0;
    }

    char buf[MAXCHAR];
    int row_count = 0;
    int field_count = 0;
    while (fgets(buf, MAXCHAR, fp)) {
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
//    delete(623734);
    add(728716, "Bobby", "Blippy", 85);
//    display_all();
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
