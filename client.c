#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr

void func(int sockfd)
{
    char buff[MAX];
    int n;
    for (;;) {
        bzero(buff, sizeof(buff));
        printf("Enter the string : ");
        n = 0;
        while ((buff[n++] = getchar()) != '\n')
            ;
        write(sockfd, buff, sizeof(buff));
        bzero(buff, sizeof(buff));
        read(sockfd, buff, sizeof(buff));
        printf("From Server : %s", buff);
        if ((strncmp(buff, "exit", 4)) == 0) {
            printf("Client Exit...\n");
            break;
        }
    }
}


//int main (int argc, char **argv)
//{
//    char str[100];
//    int aflag = 0;
//    int bflag = 0;
//    char *cvalue = NULL;
//    int index;
//    int c;
//
//    opterr = 0;
//
//    while ((c = getopt (argc, argv, "abc:")) != -1)
//        switch (c)
//        {
//            case 'a':
//                aflag = 1;
//                break;
//            case 'b':
//                bflag = 1;
//                break;
//            case 'c':
//                cvalue = optarg;
//                break;
//            case '?':
//                if (optopt == 'c')
//                    fprintf (stderr, "Option -%c requires an argument.\n", optopt);
//                else if (isprint (optopt))
//                    fprintf (stderr, "Unknown option `-%c'.\n", optopt);
//                else
//                    fprintf (stderr,
//                             "Unknown option character `\\x%x'.\n",
//                             optopt);
//                return 1;
//            default:
//                abort ();
//        }
//
//    printf ("aflag = %d, bflag = %d, cvalue = %s\n",
//            aflag, bflag, cvalue);
//
//    for (index = optind; index < argc; index++)
//        printf ("Non-option argument %s\n", argv[index]);
//
//    if (aflag == 1) {
//        int id, score;
//        char Fname[25];
//        char Lname[25];
//        printf("adding a student\n");
//        printf("Enter the student ID: ");
//        id = atoi(gets(str));
//        printf("Enter the student's first name: ");
//        gets(Fname);
//        printf("Enter the student's last name: ");
//        gets(Lname);
//        printf("Enter the score: ");
//        score = atoi(gets(str));
//        printf("id is: %d\n", id);
//        printf("fname is: %s\n", Fname);
//        printf("lname is: %s\n", Lname);
//        printf("score is: %d\n", score);
//    }
//    return 0;
//}

//int main(int argc, char *argv[])
//{
//
//    int opt;
//    char str[100];
////    printf("argv[0] is: %s\n", argv[0]);
////    printf("argv[1] is: %s\n", argv[1]);
////    printf("argv[2] is: %s\n", argv[2]);
////    if (argv[1] == 'a')
////    {
////        printf("adding a student\nEnter the students name:");
////        gets(str);
////        printf("name is: %s", str);
////    }
//    // put ':' in the starting of the
//    // string so that program can
//    //distinguish between '?' and ':'
//    while((opt = getopt(argc, argv, ":adso:")) != -1)
//    {
//        switch(opt)
//        {
//            case 'a':
//                printf("adding a student\nEnter the students name:");
////                char *name = gets(str);
////                printf("name is: %s", name);
//            case 'd':
//                printf("deleting a student\n");
//            case 's':
//                printf("show the students who scored better than: %d");
//                break;
//            case 'o':
//                printf("show all the students:\n");
//                break;
//            case ':':
//                printf("option needs a value\n");
//                break;
//            case '?':
//                printf("unknown option: %c\n", optopt);
//                break;
//        }
//    }
//
//    //    optind is for the extra arguments
//    //    which are not parsed
//    for(; optind < argc; optind++){
//
//        printf("extra arguments: %s\n", argv[optind]);
//    }
//
//    return 0;
//}