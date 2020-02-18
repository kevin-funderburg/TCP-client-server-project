//
// Created by Kevin Funderburg on 2/11/20.
//

#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAXCHAR 1024

struct student
{
    int id, score;
    char Fname[25], Lname[25];
};

struct student students[100];
char* datafile = "data.csv";
int studentCount;
char serverMessage[MAXCHAR];    //message sent to client

int add(int ID, char *Fname, char *Lname, int score);
int delete(int ID);
int display_all();
int display(int score);
int getStudentData();
bool studentExists(int ID);
bool idValid(char*);
void tableHeader();
void showStudent(struct student s);
void error(char *msg);
void showusage();

#endif //SERVER_H
