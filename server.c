/****************** SERVER CODE ****************/

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdbool.h>
#include<stdlib.h>

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
    printf("Grade:\t%d\n", s.score);
    printf("\n");
}

int main()
{
//    delete(623734);
//    add(738210, "Francois", "Butter", 55);
//    display_all();
//    display(82);
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
