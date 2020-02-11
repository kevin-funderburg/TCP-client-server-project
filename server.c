/****************** SERVER CODE ****************/

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>
#define MAX 150
#define PORT 8080
#define SA struct sockaddr

struct student
{
    int id, score;
    char Fname[25], Lname[25];
};

int add(int ID, char *Fname, char *Lname, int score);
int delete(int ID);
int getRowNum(int rowID);
int display_all();
int display(int score);
int getStudentData();
bool studentExists(int ID);
void showStudent(struct student s);
void func(int sockfd);

#define MAXCHAR 1024
char* datafile = "data.csv";
int studentCount;
struct student students[100];

void init()
{
    studentCount = 0;
}

int add(int ID, char *Fname, char *Lname, int score) {
    FILE *fp;
    fp = fopen(datafile, "a");
    if (!fp) {
        printf("Could not open file %s", datafile);
        return 1;
    }
    getStudentData();
    if (!studentExists(ID)) {
//        delete(ID);
        fprintf(fp, "%d,%s,%s,%d\n", ID, Fname, Lname, score);
        studentCount++;
        students[studentCount].id = ID;
        strcpy(students[studentCount].Fname, Fname);
        strcpy(students[studentCount].Lname, Lname);
        students[studentCount].score = score;
        fclose(fp);
    }
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

    getStudentData();
    fprintf(fp2, "%s", "studentID,firstName,lastName,score\n");
    for (int i = 0; i < studentCount; ++i) {
        if (students[i].id != ID) {
//            printf("%d,%s,%s,%d\n", students[i].id, students[i].Fname, students[i].Lname, students[i].score);
            fprintf(fp2, "%d,%s,%s,%d\n", students[i].id, students[i].Fname, students[i].Lname, students[i].score);
        }
    }

    fclose(fp1);
    fclose(fp2);
    remove(datafile);  		// remove the original file
    rename("temp.csv", datafile); 	// rename the temporary file to original name
    studentCount--;
    return 0;
}

int getRowNum(int rowID)
{
    getStudentData();
    for (int i = 0; i < studentCount; ++i)
        if (students[i].id == rowID)
            return ++i;
    return -1;
}

int display_all()
{
    getStudentData();
    for (int i = 0; i < studentCount; ++i)
        showStudent(students[i]);
    return 0;
}

int display(int score)
{
    getStudentData();
    for (int i = 0; i < studentCount; ++i)
        if (students[i].score >= score)
            showStudent(students[i]);
    return -1;
}

bool studentExists(int ID)
{
    for (int i = 0; i < studentCount; ++i)
        if (students[i].id == ID) return true;
    return false;
}

int getStudentData()
{
    FILE *fp = fopen(datafile, "r");
    if (!fp) {
        printf("Can't open file\n");
        return 0;
    }
    char buf[MAXCHAR];

    studentCount = 0;
    int field_count = 0;
    int row_count = 0;
    while (fgets(buf, MAXCHAR, fp)) {
        field_count = 0;
        row_count++;

        if (row_count == 1) continue;
        studentCount++;

        char *field = strtok(buf, ",");
        while (field)
        {
            switch (field_count)
            {
                case 0: students[row_count-2].id = atoi(field);
                    break;
                case 1: strcpy(students[row_count-2].Fname, field);
                    break;
                case 2: strcpy(students[row_count-2].Lname, field);
                    break;
                case 3: students[row_count-2].score = atoi(field);
                    break;
                default: printf("invalid field_count");
                    return -1;
            }
            field = strtok(NULL, ",");
            field_count++;
        }
    }
    return 0;
}

void showStudent(struct student s)
{
    printf("Student ID:\t%d\n", s.id);
    printf("First Name:\t%s\n", s.Fname);
    printf("Last Name:\t%s\n", s.Lname);
    printf("Grade:\t\t%d\n", s.score);
    printf("\n");
}

// Function designed for chat between client and server.
void func(int sockfd)
{
    struct student s;
    char buff[MAXCHAR];
    int n;
    // infinite loop for chat
    for (;;) {
        bzero(buff, MAXCHAR);

        // read the message from client and copy it in buffer
        read(sockfd, buff, sizeof(buff));
        // print buffer which contains the client contents
        printf("From client: %s\t To client : ", buff);
        bzero(buff, MAXCHAR);
        n = 0;
        // copy server message in the buffer
        while ((buff[n++] = getchar()) != '\n')
            ;

        // and send that buffer to client
        write(sockfd, buff, sizeof(buff));

        // if msg contains "Exit" then server exit and chat ended.
        if (strncmp("exit", buff, 4) == 0) {
            printf("Server Exit...\n");
            break;
        }
    }
}

void parse(char *str[])
{
    char *temp;
    char *field = strtok(str, " ");

//    for (int i = 0; i < strlen(str); ++i) {
//        temp[i] = str[i];
//    }
}
void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main()
{
    char buf[] = "add 192893 kecin davis 84";
    char args[10][25];
    char * pch;
    printf ("Splitting string \"%s\" into tokens:\n",buf);

    pch = strtok (buf," ");
    strcpy(args[0], pch);
    int argc = 0;
    while (pch != NULL)
    {
        argc++;
        printf ("%s\n",pch);
        pch = strtok (NULL, " ,.-");
        if (pch != NULL)
            strcpy(args[argc], pch);
    }
    if (strncmp("add", args[0], 3) == 0) {
        if (argc < 5) {
            printf("expected 4 arguments and got %d", argc);
            return 0;
        }
        add(atoi(args[1]), args[2], args[3], atoi(args[4]));
    } else if (strncmp("display_all", args[0], 11) == 0) {
        display_all();
    } else if (strncmp("showscores", args[0], 10 ) == 0) {
        if (argc < 2) {
            printf("expected 2 arguments and got %d", argc);
            return 0;
        }
        display(atoi(args[1]));
    } else if (strncmp("delete", args[0], 6 ) == 0) {
        if (argc < 2) {
            printf("expected 2 arguments and got %d", argc);
            return 0;
        }
        display(atoi(args[1]));
    }
    return 0;
    int n, clilen;
    int welcomeSocket, newSocket;
    char buffer[1024];
    struct sockaddr_in serverAddr, clientAddr;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size;

    /*---- Create the socket. The three arguments are: ----*/
    /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
    welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);
    if (welcomeSocket < 0)
        error("ERROR opening socket");

    /*---- Configure settings of the server address struct ----*/
    /* Address family = Internet */
    serverAddr.sin_family = AF_INET;
    /* Set port number, using htons function to use proper byte order */
    serverAddr.sin_port = htons(7891);
    /* Set IP address to localhost */
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    /* Set all bits of the padding field to 0 */
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

    /*---- Bind the address struct to the socket ----*/
    bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

    /*---- Listen on the socket, with 5 max connection requests queued ----*/
    if(listen(welcomeSocket,5)==0)
        printf("Listening\n");
    else
        printf("Error\n");

    /*---- Accept call creates a new socket for the incoming connection ----*/
    addr_size = sizeof serverStorage;
    clilen = sizeof(clientAddr);

//    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
//    newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);
    newSocket = accept(welcomeSocket, (struct sockaddr *) &clientAddr, &clilen);
    if (newSocket < 0)
        error("ERROR on accept");

    bzero(buffer,256);
    n = read(newSocket,buffer,255);
    if (n < 0) error("ERROR reading from socket");
    printf("Here is the message: %s\n",buffer);

    if (strncmp("add", buffer, 3) == 0)
    {
        int x = 0;
        char prompt[50];
        struct student s;
        printf("Adding a student to the database\n");
        while (x < 4)
        {
            bzero(buffer, MAX);

            // read the message from client and copy it in buffer
            n = read(newSocket, buffer, sizeof(buffer));
            switch (x)
            {
                case 0:
                    strcpy(prompt, "Enter the student ID: ");
                    s.id = atoi(buffer);
                    printf("s.score is: %d\n", s.id);
                    break;
                case 1:
                    strcpy(prompt, "Enter the first name: ");
                    strcpy(s.Fname, buffer);
                    printf("s.Fname is: %s\n", s.Fname);
                    break;
                case 2:
                    strcpy(prompt, "Enter the last name: ");
                    strcpy(s.Lname, buffer);
                    printf("s.Lname is: %s\n", s.Lname);
                    break;
                case 3:
                    strcpy(prompt, "Enter the score: ");
                    s.score = atoi(buffer);
                    printf("s.score is: %d\n", s.score);
                    break;
            }
            // print buffer which contains the client contents
//            printf("From client: %s\t To client : ", buffer);
            bzero(buffer, MAX);
            n = 0;

            // copy server message in the buffer
//            while ((buffer[n++] = getchar()) != '\n')
//                ;
            strcpy(buffer, prompt);

            // and send that buffer to client
            n = write(newSocket, buffer, sizeof(buffer));
            if (n < 0) error("ERROR writing to socket");


            x++;
        }
        showStudent(s);

    } else if (strncmp("display_all", buffer, 11) == 0) {
        display_all();
    }
    else if (strncmp("showscores", buffer, 10 ) == 0)
    {
        int thelen = strlen(buffer);
        printf("thelen: %d\n", thelen);
        printf("score is: ");
        int strt = 10;
        int end = thelen-2;
        char thescore[2];
        printf("buffer[11][12]: %c%c", buffer[11], buffer[12]);
        if (thelen == 14) {

            thescore[0] = buffer[11];
            thescore[1] = buffer[12];
        } else if (thelen == 15) {
            char thescore[3];
            thescore[0] = buffer[11];
            thescore[1] = buffer[12];
            thescore[1] = buffer[13];
        }
        int score = atoi(thescore);
        printf("showing scores greater than: %c%c\n", thescore[0],thescore[1]);
//        for (int q = strt; q < end; ++q) {
//            printf(buffer[q]);
//        }
//        printf("\n");

//        char thescore[strlen(buffer-11)];
//        for (int q = strlen(buffer-11); q < strlen(buffer); q++) {
//            thescore[q] = buffer[q];
//        }

//        int score = -1;
//        printf("Showing scores greater than:%d\n", atoi(thescore));

        bzero(buffer, MAX);
        n = 0;
        strcpy(buffer, "enter the score: ");
        // and send that buffer to client
        n = write(newSocket, buffer, sizeof(buffer));
        if (n < 0) error("ERROR writing to socket");
        bzero(buffer, MAX);
        // read the message from client and copy it in buffer
        n = read(newSocket, buffer, sizeof(buffer));
        score = atoi(buffer);
        if (score < 0 || score > 100)
            error("invalid score");
        printf("showing scores greater than: %d\n", score);
        display(score);

    }
    else if (strncmp("delete", buffer, 6 ) == 0)
    {
        int id = -1;
        printf("Showing scores\n");
        bzero(buffer, MAX);
        n = 0;
        strcpy(buffer, "enter the id of the student to delete: ");
        // and send that buffer to client
        n = write(newSocket, buffer, sizeof(buffer));
        if (n < 0) error("ERROR writing to socket");

        bzero(buffer, MAX);
        // read the message from client and copy it in buffer
        n = read(newSocket, buffer, sizeof(buffer));
        id = atoi(buffer);
        if (id < 0)
            error("invalid score");
        printf("deleting student with id: %d\n", id);
        delete(id);
    }
        // if msg contains "Exit" then server exit and end.
    else if (strncmp("exit", buffer, 4) == 0) {
        printf("Server Exit...\n");
//        break;
    }
    if (n < 0) error("ERROR writing to socket");
//    /*---- Send message to the socket of the incoming connection ----*/
//    strcpy(buffer,"Hello World\n");
//    send(newSocket,buffer,13,0);

    return 0;
}