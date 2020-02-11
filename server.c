/****************** SERVER CODE ****************/

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdbool.h>
#include<stdlib.h>


#define MAXCHAR 1000

int add(int ID, char *Fname, char *Lname, int score)
{
    FILE *fp;
    char* filename = "data.csv";

    fp = fopen(filename, "a");
    if (fp == NULL){
        printf("Could not open file %s",filename);
        return 1;
    }

    fprintf(fp, "%d,%s,%s,%d\n", ID, Fname, Lname, score);
    fclose(fp);
    return 0;
}

int delete(int ID)
{
    FILE *fp1, *fp2;
    char* filename = "data.csv";

    fp1 = fopen(filename, "r");
    if (!fp1)
    {
        printf(" File not found or unable to open the input file!!\n");
        return 0;
    }
    fp2 = fopen("temp.csv", "w"); // open the temporary file in write mode
    if (!fp2)
    {
        printf("Unable to open a temporary file to write!!\n");
        fclose(fp1);
        return 0;
    }

//    // copy all contents to the temporary file except the specific line
//    while (!feof(fp1))
//    {
//        strcpy(str, "\0");
//        fgets(str, MAX, fp1);
//        if (!feof(fp1))
//        {
//            char *field = strtok(buf, ",");
//
//            ctr++;
//            /* skip the line at given line number */
//            if (ctr != lno)
//            {
//                fprintf(fptr2, "%s", str);
//            }
//        }
//    }

    char buf[1024];
    int row_count = 0;
    int field_count = 0;
    bool IDfound = false;
    while (fgets(buf, 1024, fp1))
    {
        field_count = 0;
        row_count++;

        if (row_count == 1) {
            continue;
        }

        char *field = strtok(buf, ",");
        while (field) {
            // only check the first field for the ID
            if (field_count == 0) {
                int fieldID = atoi(field); //cast string to int
                if (fieldID == ID) {
                    printf("FOUND: %s\n", field);
                }
            }
            field = strtok(NULL, ",");

            field_count++;
        }
    }

    fclose(fp1);
    return 0;
}

int display_all()
{
    FILE *fp = fopen("data.csv", "r");

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
