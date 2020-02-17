/***
 * TCP Client/Server Project
 * @file server.c
 * @authors: Kevin Funderburg
 */

#include "server.h"

/**
 * adds a student to the database
 */
int add(int ID, char *Fname, char *Lname, int score) {
    FILE *fp;
    fp = fopen(datafile, "a");
    if (!fp) {
        printf("Could not open file %s", datafile);
        return 1;
    }
    getStudentData();
    if (!studentExists(ID)) {
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

/**
 * delete student from database
 */
int delete(int ID)
{
    FILE *fp1, *fp2;
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

/**
 * output every student in database
 */
int display_all()
{
    getStudentData();
    for (int i = 0; i < studentCount; ++i)
        showStudent(students[i]);
    return 0;
}

/**
 * show every student who has a score >= score
 */
int display(int score)
{
    getStudentData();
    for (int i = 0; i < studentCount; ++i)
        if (students[i].score >= score)
            showStudent(students[i]);
    return 0;
}

bool studentExists(int ID)
{
    for (int i = 0; i < studentCount; ++i)
        if (students[i].id == ID) return true;
    return false;
}

/**
 * parses the data from data.csv to create an array of students
 */
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
                case 0:
                    students[row_count-2].id = atoi(field);
                    break;
                case 1:
                    strcpy(students[row_count-2].Fname, field);
                    break;
                case 2:
                    strcpy(students[row_count-2].Lname, field);
                    break;
                case 3:
                    students[row_count-2].score = atoi(field);
                    break;
                default:
                    printf("invalid field_count");
                    return -1;
            }
            field = strtok(NULL, ",");
            field_count++;
        }
    }
    return 0;
}

/**
 * creates a compatable string to be passed back to
 * the client
 * @param s student structure
 */
void showStudent(struct student s)
{
    char id[50];
    char fname[50];
    char lname[50];
    char score[50];

    snprintf(id, sizeof(id), "Student ID:\t%d\n", s.id);
    snprintf(fname, sizeof(fname), "First Name:\t%s\n", s.Fname);
    snprintf(lname, sizeof(lname), "First Name:\t%s\n", s.Lname);
    snprintf(score, sizeof(score), "Grade:\t\t%d\n\n", s.score);

    strcat(serverMessage, id);
    strcat(serverMessage, fname);
    strcat(serverMessage, lname);
    strcat(serverMessage, score);
}


void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main()
{
    int n, clilen;
    int welcomeSocket, newSocket;
    char buffer[MAXCHAR];
    struct sockaddr_in serverAddr, clientAddr;
    struct sockaddr_storage serverStorage;
//    socklen_t addr_size;
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
//    addr_size = sizeof serverStorage;
    clilen = sizeof(clientAddr);

    newSocket = accept(welcomeSocket, (struct sockaddr *) &clientAddr, &clilen);
    if (newSocket < 0)
        error("ERROR on accept");

    while (1)
    {
        memset(serverMessage, 0, sizeof serverMessage);
        bzero(buffer, MAXCHAR);
        // read the message from client and copy it in buffer
        n = read(newSocket, buffer, MAXCHAR);
        if (n < 0) error("ERROR reading from socket");
        printf("Here is the message: %s\n", buffer);

        char args[10][25];
        char *pch;
        printf("Splitting string \"%s\" into tokens:\n", buffer);

        pch = strtok(buffer, " ");
        strcpy(args[0], pch);
        int argc = 0;
        while (pch != NULL) {
            argc++;
            printf("%s\n", pch);
            pch = strtok(NULL, " ,.-");
            if (pch != NULL)
                strcpy(args[argc], pch);
            printf("argc: %d", argc);
        }

        if (strncmp("add", args[0], 3) == 0) {
            if (argc < 5) {
                printf("expected 4 arguments and got %d", argc);
                snprintf(serverMessage, sizeof(serverMessage), "expected 4 arguments and got %d", argc);
            }
            add(atoi(args[1]), args[2], args[3], atoi(args[4]));
            strcpy(serverMessage, "Student added successfully.\n");
        } else if (strncmp("display_all", args[0], 11) == 0) {
            display_all();
            printf("serverMessage\n%s", serverMessage);
        } else if (strncmp("showscores", args[0], 10) == 0) {
            if (argc < 2) {
                printf("expected 2 arguments and got %d", argc);
                snprintf(serverMessage, sizeof(serverMessage), "expected 2 arguments and got %d", argc);
            }
            display(atoi(args[1]));
            printf("serverMessage\n%s", serverMessage);
        } else if (strncmp("delete", args[0], 6) == 0) {
            if (argc < 2) {
                printf("expected 2 arguments and got %d", argc);
                snprintf(serverMessage, sizeof(serverMessage), "expected 2 arguments and got %d", argc);
            }
            delete(atoi(args[1]));
            strcpy(serverMessage, "Student deleted successfully.\n");
        } else if (strncmp("exit", args[0], 4) == 0) {
            // if msg contains "Exit" then server exit and chat ended.
            printf("Server Exit...\n");
            break;
        } else {
            printf("%s is not a valid argument", args[0]);
            snprintf(serverMessage, sizeof(serverMessage), "%s is not a valid argument", args[0]);
        }

        bzero(buffer, MAXCHAR);
        // copy serverMessage to server buffer
        strcpy(buffer, serverMessage);
        // and send buffer to client
        n = write(newSocket, buffer, sizeof(buffer));
        if (n < 0) error("ERROR writing to socket");
    }
    close(newSocket);
    return 0;
}