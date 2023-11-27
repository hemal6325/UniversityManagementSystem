#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_STRING_SIZE 50

int max = 100;
int maximaumNotice = 100000;
char StudentInfos[] = "AddNewStudent.txt";
char Question[] = "CreatePollForStudent_Teacher.txt";
char CandidatesForCR[] = "CandidatesForCR.txt";
char MarkSheet[] = "MarkSheet.txt";
char Temp[] = "Temp.txt";
char Question2[] = "Question2.txt";
char PollResult[] = "PollResult.txt";
char Winnertxt[] = "Winner.txt";
char result[] = "result.txt";
char ccomplain[] = "SeeTheComplains.txt";

char voter[30];

int fileCheck(FILE *file, char *fileName)
{
    if (file == NULL)
    {
        printf("Ooops... %s Could Not Open...\n", fileName);
        return 0;
    }
    return 1;
}

struct entry
{
    int serial;
    char name[30];
    char phone[13];
    char email[40];
    char department[30];
    char semester[4];
    char batch[4];
    char section[4];
    char id[10];
    char pass[8];
};
struct check
{
    int serial;
    char name[30];
    char phone[13];
    char email[40];
    char department[30];
    char semester[4];
    char batch[4];
    char section[4];
    char id[10];
    char pass[8];
};
int AddNewStudent()
{
    struct entry e[max];
    struct check c[max];
    int j = 0;
    int i = 0;
    FILE *file2 = fopen(StudentInfos, "r");
    fileCheck(file2, StudentInfos);
    system("cls");
    printf("Write \"00\" In \"Enter Name\" To Come Out From The Task \n");
    while (1)
    {
        printf("Enter Name : ");
        scanf("%s", e[i].name);

        if (strcmp(e[i].name, "00") == 0)
            break;

        printf("Enter Phone : ");
        scanf("%s", e[i].phone);

        printf("Enter Email : ");
        scanf("%s", e[i].email);

        printf("Enter Department : ");
        scanf("%s", e[i].department);

        printf("Enter Semester : ");
        scanf("%s", e[i].semester);

        printf("Enter Batch : ");
        scanf("%s", e[i].batch);

        printf("Enter Section : ");
        scanf("%s", e[i].section);

        char id[5];
        strncpy(id, e[i].name, 4);
        id[4] = '\0';

        char str[10];
        while (fscanf(file2, "%d %s %s %s %s %s %s %s %s %s",
                      &c[j].serial, c[j].name, c[j].phone,
                      c[j].email, c[j].department, c[j].semester,
                      c[j].batch, c[j].section, c[j].id, c[j].pass) != EOF)
        {
            if (strcmp(c[j].name, e[i].name) == 0 && strcmp(c[j].phone, e[i].phone) == 0)
            {
                printf("Student Is Already Admitted...\n");
                return 1;
            }
            j++;
        }

        e[i].serial = c[j - 1].serial + 1;
        if(j==0)
        {
            c[j].serial = 0;
            e[i].serial = c[j].serial + 1;
        }
        sprintf(str, "%d", e[i].serial);
        strcat(id, str);

        strcpy(e[i].id, id);
        strcpy(e[i].pass, e[i].id);
        FILE *file1 = fopen(StudentInfos, "a");
        fileCheck(file1, StudentInfos);
        fprintf(file1, "%d %s %s %s %s %s %s %s %s %s\n",
                e[i].serial, e[i].name, e[i].phone, e[i].email, e[i].department,
                e[i].semester, e[i].batch, e[i].section, e[i].id, e[i].pass);
        fclose(file1);
        i++;
    }
    fclose(file2);
    int n = 0;
    n = i;
    system("cls");

    return 0;
}
struct question
{
    char subject[30];
    int num;
    char question[500];
    char options[5][50];
    int right;
    char ans[4][10];
};
struct cheksubject
{
    char subject[30];
    int serial;
    int TotalOptions;
};
int MakePoll()
{
    struct question q[max];
    struct cheksubject l[max];
    int i = 0;
    int j = 0;
    int k = 0;
    q[i].num = 1;
    system("cls");
    FILE *file3 = fopen(Question, "a");
    fileCheck(file3, Question);
    printf("\n\tUse Underscore \"_\" Alternative To Space \" \"\n");
    printf("\tUse \"00\" To Skip Making Another Questions\n");

    while (1)
    {

        printf("\n\n\tEnter Subject Name : ");
        char subject[30];
        scanf("%s", subject);
        if (strcmp(subject, "00") == 0)
        {
            break;
        }
        while (1)
        {
            strcpy(q[i].subject, subject);

            j = 1;

            printf("\n\tQuestion %d : ", q[i].num);
            scanf("%s", q[i].question);
            if (strcmp(q[i].question, "00") == 0)
                break;
            fprintf(file3, "%s %d %s ", q[i].subject, q[i].num, q[i].question);
            printf("\n");
            for (int m = 0 ; m<4 ; m++)
            {
                printf("\t %d : ", j);
                scanf("%s", q[i].options[j]);

                if (strcmp(q[i].options[j], "00") == 0)
                    break;
                fprintf(file3, "%d %s ", j, q[i].options[j]);
                j++;
            }
            printf("\n\tRight Answer : ");
            scanf("%d", &q[i].right);
            fprintf(file3, "%d\n", q[i].right);
            q[i].num++;
        }
    }
    fclose(file3);
    return 1;
}
void MakeNotice()
{
    printf("\n\n\tEnter \"All\" If The Notice Is For All Sections\n");
    printf("\n\tEnter Batch : ");
    char sec[10];
    scanf("%s", sec);

    printf("\n\tEnter The Notice: ");
    char notice[maximaumNotice];
    scanf(" %[^\n]", notice); // Use " %[^\n]" to read the entire line, including spaces.

    if (strcmp(sec, "All") == 0)
    {
        FILE *file1 = fopen("AllSectionNotice.txt", "w");
        if (file1 == NULL)
        {
            printf("\n\tError Opening File For Writing.\n");
            return;
        }
        fprintf(file1, "%s", notice);
        fclose(file1);
    }
    else
    {
        strcat(sec, ".txt");
        FILE *file2 = fopen(sec, "w");
        if (file2 == NULL)
        {
            printf("\n\tError Opening File For Writing.\n");
            return;
        }
        fprintf(file2, "%s", notice);
        fclose(file2);
    }
}
int SeeComplain()
{
    FILE *file = fopen(ccomplain, "r");
    if (file == NULL)
    {
        printf("Error: Could Not Open The File.\n");
        return 1;
    }

    char complain[100000];

    while (fgets(complain, sizeof(complain), file) != NULL)
    {
        printf("%s", complain);
    }

    fclose(file);
    getch();
}

int TeacherPortal()
{
    while (1)
    {
        system("cls");
        printf("\n\n\n\t1. Add New Student \n\t2. Create Poll For Student \n\t3. Notice For Student \n\t4. See The Complains\n\n\tSelect 0 To Go To Home \n\n\tPlease Enter Which Service You Need : ");
        int option;
        scanf("%d", &option);
        switch (option)
        {
        case 0:
        {
            system("cls");
            return 0;
        }
        case 1:
        {
            system("cls");
            AddNewStudent();
            break;
        }
        case 2:
        {
            system("cls");
            MakePoll();
            break;
        }
        case 3:
        {
            system("cls");
            MakeNotice();
            break;
        }
        case 4:
        {
            system("cls");
            SeeComplain();
            break;
        }
        default:
        {
            system("cls");
            printf("Ooops... %d Is The  Wrong Option...\n", option);
        }
        }
    }
}
struct candidate
{
    int serial;
    char id[10];
    int vote;
    char voter[30];
    char department[10];
    char semester[10];
    char batch[10];
    char sec[10];
};
struct checkcandidate
{
    int serial;
    char id[10];
    int vote;
    char voter[30];
    char department[10];
    char semester[10];
    char batch[10];
    char sec[10];
};
int Candidate()
{
    struct checkcandidate cc[max];
    struct candidate ee[max];
    struct entry e[max];
    struct check c[max];
    int i = 0;
    int j = 0;
    int found = 0;
back:
    printf("Enter User ID : ");
    scanf("%s", e[i].id);
    FILE *file4 = fopen(StudentInfos, "r");
    fileCheck(file4, StudentInfos);
    while (fscanf(file4, "%d %s %s %s %s %s %s %s %s %s",
                  &c[j].serial, c[j].name, c[j].phone,
                  c[j].email, c[j].department, c[j].semester,
                  c[j].batch, c[j].section, c[j].id, c[j].pass) != EOF)
    {
        if (strcmp(e[i].id, c[j].id) == 0)
        {
            found = 1;
            break;
        }
        j++;
    }
    fclose(file4);
    if (found != 1)
    {
        printf("Ooops... Your ID Not Found...\n");
        goto back;
    }
    printf("Enter Password : ");
    scanf("%s", e[i].pass);
    j = 0;
    FILE *file5 = fopen(StudentInfos, "r");
    fileCheck(file5, StudentInfos);
    while (fscanf(file4, "%d %s %s %s %s %s %s %s %s %s",
                  &c[j].serial, c[j].name, c[j].phone,
                  c[j].email, c[j].department, c[j].semester,
                  c[j].batch, c[j].section, c[j].id, c[j].pass) != EOF)
    {
        if (strcmp(e[i].pass, c[j].pass) == 0)
        {
            found = 1;
            break;
        }
        j++;
    }
    fclose(file5);
    if (found != 1)
    {
        printf("Ooops... Your Pass Not Found...\n");
        goto back;
    }
    j = 0;
    FILE *file9 = fopen(CandidatesForCR, "r");
    fileCheck(file9, CandidatesForCR);
    while (fscanf(file9, "%d %s %d %s %s %s %s %s", &cc[j].serial, cc[j].id, &cc[j].vote, cc[j].voter,cc[j].department, cc[j].semester,cc[j].batch, cc[j].sec) != EOF)
    {
        if (strcmp(cc[j].id, e[i].id) == 0)
        {
            printf("You Are Already On The Candidate List \n");
            return 0;
        }
        j++;
    }
    fclose(file9);
    FILE *file7 = fopen(CandidatesForCR, "a");
    fileCheck(file7, CandidatesForCR);
    fprintf(file7, "%d %s %d %s %s %s %s %s\n", c[i].serial, c[i].id, cc[j].vote, c[i].id, c[i].department, c[i].semester,c[i].batch, c[i].section);
    printf("You Are Now A Candidate\n");
    fclose(file7);

    return 1;
}

int Vote()
{
    struct checkcandidate c[max];
    struct check cx[max];
back:
    printf("Enter Your ID : ");
    char voter[30];
    scanf("%s", voter);
    printf("Enter Your Password : ");
    char passpin[30];
    scanf("%s",passpin);
    printf("Enter Your Batch : ");
    char batch[30];
    scanf("%s", batch);
    printf("Enter Section : ");
    char sec[30];
    scanf("%s", sec);

    int found = 0;
    int i=0;
    FILE *file4 = fopen(StudentInfos, "r");
    fileCheck(file4, StudentInfos);
    while (fscanf(file4, "%d %s %s %s %s %s %s %s %s %s",
                  &cx[i].serial, cx[i].name, cx[i].phone,
                  cx[i].email, cx[i].department, cx[i].semester,
                  cx[i].batch, cx[i].section, cx[i].id, cx[i].pass) != EOF)
    {
        if (strcmp(voter, cx[i].id) == 0 && strcmp(cx[i].section,sec)==0 && strcmp(passpin,cx[i].pass)==0)
        {
            found = 1;
            break;
        }
        i++;
    }
    fclose(file4);

    if(found==0)
    {
        printf("Check The Informations Again\n");
        goto back;
    }




    FILE *file11 = fopen(CandidatesForCR, "r");
    fileCheck(file11, CandidatesForCR);

    int j = 0;
    while (fscanf(file11, "%d %s %d %s %s %s %s %s", &c[j].serial, c[j].id, &c[j].vote, c[j].voter, c[j].department, c[j].semester, c[j].batch, c[j].sec) != EOF)
    {
        if (strcmp(c[j].voter, voter) == 0)
        {
            printf("You Cannot Vote. Because You Are a Candidate...\n");
            fclose(file11);
            return 1;
        }
        j++;
    }
    fclose(file11);

    FILE *file8 = fopen(CandidatesForCR, "r");
    fileCheck(file8, CandidatesForCR);

    j = 0;
    while (fscanf(file8, "%d %s %d %s %s %s %s %s", &c[j].serial, c[j].id, &c[j].vote, c[j].voter, c[j].department, c[j].semester, c[j].batch, c[j].sec) != EOF)
    {
        if (strcmp(batch, c[j].batch) == 0 && strcmp(sec, c[j].sec) == 0)
        {
            printf("\n%d. %s\n", c[j].serial, c[j].id);
        }
        j++;
    }
    fclose(file8);

    printf("\nEnter Your Favorite Candidate's Number: ");
    int option = 0;
    scanf("%d", &option);


    FILE *fileWinner = fopen(Winnertxt, "a");
    fileCheck(fileWinner, Winnertxt);

    FILE *fileWinner1 = fopen(CandidatesForCR, "a");
    fileCheck(fileWinner1, CandidatesForCR);

    j = 0;
    while (fscanf(fileWinner1, "%d %s %d %s %s %s %s %s", &c[j].serial, c[j].id, &c[j].vote, c[j].voter, c[j].department, c[j].semester, c[j].batch, c[j].sec) != EOF)
    {
        if (c[j].serial == option)
        {
            found = 1;
            break;
        }
        j++;
    }

    if (found == 1)
    {
        printf("You Voted for:\n");
        printf("\n\n%d. %s\n", c[j].serial, c[j].id);
        fprintf(fileWinner, "%d %s %d %s %s %s %s %s", c[j].serial, c[j].id, c[j].vote, c[j].voter, c[j].department, c[j].semester, c[j].batch, c[j].sec);
    }
    else
    {
        printf("You Couldn't Vote for the selected candidate.\n");
        return 1;
    }

    fclose(fileWinner1);
    fclose(fileWinner);
    return 0;
}
struct win
{
    char winning[30];
    int vote;
};
void CalculateAndRecordResults()
{
    struct checkcandidate c[max];
    struct win won[max];
    FILE *fileWinner = fopen(Winnertxt, "r");
    fileCheck(fileWinner, Winnertxt);
    FILE *re = fopen(result, "w");
    int j = 0;
    while (fscanf(fileWinner, "%d %s %d %s %s %s %s %s", &c[j].serial, c[j].id, &c[j].vote, c[j].voter, c[j].department, c[j].semester, c[j].batch, c[j].sec) != EOF)
    {
        strcpy(won[j].winning, c[j].id);
        j++;
    }

    for (int i = 0; i < j; i++)
    {
        won[i].vote = 0;
        int k = 0;
        rewind(fileWinner);

        while (fscanf(fileWinner, "%d %s %d %s %s %s %s %s", &c[k].serial, c[k].id, &c[k].vote, c[k].voter, c[k].department, c[k].semester, c[k].batch, c[k].sec) != EOF)
        {
            if (strcmp(won[i].winning, c[k].id) == 0)
            {
                won[i].vote = won[i].vote + 1;
            }
            k++;
        }

        fprintf(re, "%s %s %s %s %s %d\n", won[i].winning, c[0].department, c[0].semester, c[0].batch, c[0].sec, won[i].vote);
        printf("The CR Of Section %s And Batch %s is %s. He Won The Vote By %d Votes\n", c[0].sec, c[0].batch, won[i].winning, won[i].vote);
    }


    fclose(fileWinner);
    fclose(re);
}

int CRVote()
{
    while (1)
    {
        printf("\n\n\t1. Candidate \n\t2. Vote \n\t3. See Winner \n\n\tPlease Enter Which Service You Need : ");
        int option;
        scanf("%d", &option);
        switch (option)
        {
        case 0:
        {
            return 1;
        }
        case 1:
        {
            system("cls");
            Candidate();
            break;
        }
        case 2:
        {
            system("cls");
            Vote();
            break;
        }
        case 3 :
        {
            CalculateAndRecordResults();
            break;
        }
        default:
        {
            system("cls");
            printf("Ooops... %d Is The  Wrong Option...\n", option);
        }
        }
    }
}
int Quiz()
{

    struct question q[max];
    int i = 0;
    int o = 1;
    int serial = 1;
    FILE *file12 = fopen(Question, "r");
    fileCheck(file12, Question);
    while (fscanf(file12, "%s %d %s %s %s %s %s %s %s %s %s %d", q[i].subject, &q[i].num, q[i].question, q[i].ans[1],
                  q[i].options[1], q[i].ans[2], q[i].options[2], q[i].ans[3], q[i].options[3], q[i].ans[4],
                  q[i].options[4], &q[i].right) != EOF)
    {
        if (strcmp(q[i - 1].subject, q[i].subject) != 0)
        {
            printf("%d. %s\n", serial, q[i].subject);
            serial++;
        }
        i++;
    }
    fclose(file12);
    printf("Enter Subject You Want To Perticipent : ");
    char subject[30];
    scanf("%s", subject);
    FILE *file13 = fopen(Question, "r");
    fileCheck(file13, Question);
    FILE *file14 = fopen(MarkSheet, "a");
    fileCheck(file14, MarkSheet);
    int point = 0;
    int j = 0;
    while (fscanf(file13, "%s %d %s %s %s %s %s %s %s %s %s %d", q[i].subject, &q[i].num, q[i].question, q[i].ans[1],
                  q[i].options[1], q[i].ans[2], q[i].options[2], q[i].ans[3], q[i].options[3], q[i].ans[4],
                  q[i].options[4], &q[i].right) != EOF)
    {
        if (strcmp(q[i].subject, subject) != 0)
        {
            printf("%d. %s \n %s. %s\n %s. %s\n %s. %s\n %s. %s\n\n",
                   q[i].num, q[i].question,
                   q[i].ans[1], q[i].options[1],
                   q[i].ans[2], q[i].options[2],
                   q[i].ans[3], q[i].options[3],
                   q[i].ans[4], q[i].options[4]);
            printf("Enter The Correct Answer :");
            int Choose;
            scanf("%d", &Choose);
            if (q[i].right == Choose)
            {
                point = point + 1;
                printf("Correct\n\n\n");
            }
            else
            {
                printf("Incorrect\n\n\n");
            }
            j++;
        }
        i++;
    }
    int wrong;
    wrong = j - point;
    fprintf(file14, "%s %d %d %s\n", voter, point, wrong, q[i].subject);
    fclose(file13);
    fclose(file14);
    printf("Correct Answered : %d\n", point);
    printf("Wrong Answered   : %d\n", wrong);
}
struct result
{
    char cr[30];
    char dep[10];
    char semester[10];
    char batch[10];
    char sec[10];
    int voter;
};
int CRPoll()
{
    struct result cc[max];
    struct candidate ee[max];
    struct question q[max];
    struct cheksubject l[max];
    struct check c[max];
    int i = 0;
    int j = 0;
    int k = 0;
    int found = 0;
    q[i].num = 1;
    system("cls");
    FILE *file15 = fopen(result, "r");
    fileCheck(file15, result);
    while (fscanf(file15, "%s %s %s %s %s %d", cc[j].cr, cc[j].dep, cc[j].semester, cc[j].batch, cc[j].sec, &cc[j].voter) != EOF)
    {
        if (strcmp(cc[j].cr, voter) == 0)
        {
            found = 1;
        }
        j++;
    }
    fclose(file15);
    if (found != 1)
    {
        printf("You Can Not Make Poll Ask CR To Give Permission.\n");
back:
        printf("Enter CR User ID : ");
        char checkId[30];
        scanf("%s", checkId);
        printf("Enter CR Password : ");
        char pass[30];
        scanf("%s", pass);
        j = 0;
        found = 0;
        FILE *file5 = fopen(StudentInfos, "r");
        fileCheck(file5, StudentInfos);
        while (fscanf(file5, "%d %s %s %s %s %s %s %s %s %s",
                      &c[j].serial, c[j].name, c[j].phone,
                      c[j].email, c[j].department, c[j].semester,
                      c[j].batch, c[j].section, c[j].id, c[j].pass) != EOF)
        {
            if (strcmp(pass, c[j].pass) == 0)
            {
                found = 1;
                break;
            }
            j++;
        }
        fclose(file5);
        if (found != 1)
        {
            printf("Ooops... Your Pass Not Found...\n");
            goto back;
        }
    }
    i = 0;
    j = 0;
    k = 0;
    found = 0;
    FILE *file3 = fopen(Question2, "a");
    fileCheck(file3, Question2);
    while (1)
    {
        printf("Enter Subject Name : ");
        char subject[30];
        scanf("%s", subject);
        if (strcmp(subject, "00") == 0)
        {
            break;
        }
        while (1)
        {
            strcpy(q[i].subject, subject);

            j = 1;
            printf("Use Underscore \"_\" Alternative To Space \" \"\n");
            printf("Question %d : ", q[i].num);
            scanf("%s", q[i].question);
            if (strcmp(q[i].question, "00") == 0)
                break;
            fprintf(file3, "%s %d %s ", q[i].subject, q[i].num, q[i].question);
            while (j != 5)
            {
                printf("Option %d : ", j);
                scanf("%s", q[i].options[j]);

                if (strcmp(q[i].options[j], "00") == 0)
                    break;
                fprintf(file3, "%d %s ", j, q[i].options[j]);
                j++;
            }
            q[i].num++;
        }
    }
    fclose(file3);
    return 1;
}
int PerPoll()
{
    struct question q[max];
    int i = 0;
    int o = 1;
    int serial = 1;
    FILE *file12 = fopen(Question2, "r");
    fileCheck(file12, Question2);
    while (fscanf(file12, "%s %d %s %s %s %s %s %s %s %s %s", q[i].subject, &q[i].num, q[i].question, q[i].ans[1],
                  q[i].options[1], q[i].ans[2], q[i].options[2], q[i].ans[3], q[i].options[3], q[i].ans[4],
                  q[i].options[4]) != EOF)
    {
        if (strcmp(q[i - 1].subject, q[i].subject) != 0)
        {
            printf("%d. %s\n", serial, q[i].subject);
            serial++;
        }
        i++;
    }
    fclose(file12);
    printf("Enter Subject You Want To Perticipent : ");
    char subject[30];
    scanf("%s", subject);
    FILE *file13 = fopen(Question2, "r");
    fileCheck(file13, Question2);
    FILE *file14 = fopen(PollResult, "a");
    fileCheck(file14, PollResult);
    int point = 0;
    int j = 1;
    int Choose = 0;
    while (fscanf(file13, "%s %d %s %s %s %s %s %s %s %s %s %d", q[i].subject, &q[i].num, q[i].question, q[i].ans[1],
                  q[i].options[1], q[i].ans[2], q[i].options[2], q[i].ans[3], q[i].options[3], q[i].ans[4],
                  q[i].options[4]) != EOF)
    {
        if (strcmp(q[i].subject, subject) != 0)
        {
            printf("%d. %s \n1. %s\n2. %s\n3. %s\n4. %s\n\n",
                   q[i].num, q[i].question,
                   q[i].options[1],
                   q[i].options[2],
                   q[i].options[3],
                   q[i].options[4]);

            printf("Enter The Correct Answer :");



            scanf("%d", &Choose);
            if (Choose >= 1 && Choose <= 4)
            {
                fprintf(file14, "%s %s %s %d %s\n", q[i].subject, voter, q[i].question, Choose, q[i].options[Choose]);
            }
            else
            {
                printf("Ooops... Wrong Option...\n");
            }
        }
        i++;
    }
    fclose(file14);
    fclose(file13);
    return 1;
}
int PollResultShow()
{
    struct question q[max];
    int i = 0;
    int j = 1;
    int Choose = 0;

    FILE *file = fopen(PollResult, "r");
    fileCheck(file, PollResult);

    while (fscanf(file, "%s %s %s %d %s", q[i].subject, voter, q[i].question, &Choose, q[i].options[Choose]) != EOF)
    {
        printf("%d. %s\n", j, q[i].subject);
        j++;
        i++;
    }

    fclose(file);

    printf("Enter Your Option: ");
    int option;
    scanf("%d", &option);

    if (option >= 1 && option <= i)
    {
        i = 0;
        j = 0;

        FILE *file17 = fopen(PollResult, "r");
        fileCheck(file17, PollResult);

        while (fscanf(file17, "%s %d %s %d %s", q[i].subject, voter, q[i].question, &Choose, q[i].options[Choose]) != EOF)
        {
            j++;
            if (j == option)
            {
                printf("%d. %s %d Answered By %s\n", j, q[i].question, Choose, voter);
                break;
            }
            i++;
        }

        fclose(file17);
    }
    else
    {
        printf("Ooops... Wrong Option...\n", i);
    }
    return 1;
}
int Poll()
{
back:
    printf("1. Make Poll \n2. Perticipent In Poll \n3. See Result \nSelect One : ");
    int option;
    scanf("%d", &option);
    switch (option)
    {
    case 1:
    {
        CRPoll();
        break;
    }
    case 2:
    {
        PerPoll();
        break;
    }
    case 3:
    {
        PollResultShow();
        break;
    }
    default:
    {
        printf("Ooops... Wrong Option\n");
        goto back;
    }
    }
}
void Notice()
{
    FILE *file1 = fopen("AllSectionNotice.txt", "r");


    char notesAll[maximaumNotice];
    if (fscanf(file1, " %[^\n]", notesAll) == 1)
    {
        printf("Notice for All Sections: %s\n", notesAll);
    }
    else
    {
        printf("No notice found for all sections.\n");
    }

    fclose(file1);

    printf("Your Batch: ");
    char sec[10];
    scanf("%s", sec);

    strcat(sec, ".txt");
    FILE *file2 = fopen(sec, "r");
    if (file2 == NULL)
    {
        printf("Error opening the file for reading.\n");
        return;
    }

    char notesSection[maximaumNotice];
    if (fscanf(file2, " %[^\n]", notesSection) == 1)
    {
        printf("Notice for Your Section: %s\n", notesSection);
    }
    else
    {
        printf("No notice found for your section.\n");
    }
    fclose(file2);
    getch();
}

struct abbcr
{
    char id[30];
    char dep[10];
    char sem[10];
    char bat[10];
    char sec[10];
    int vote;
};
void AboutCR()
{
    struct check cc[max];
    struct abbcr c[max];
    int i = 1;
    printf("CR Infos: \n");

    FILE *file = fopen(CandidatesForCR, "r");
    fileCheck(file, CandidatesForCR);

    while (fscanf(file, "%s %s %s %s %s %d", c[i].id, c[i].dep, c[i].sem, c[i].bat, c[i].sec, &c[i].vote) != EOF)
    {
        printf("%d->\n", i);

        printf("User ID : %s\n", c[i].dep);
        printf("Department : %s\n", c[i].sec);
        i++;
    }

    printf("Enter Serial Number: ");
    int option;
    scanf("%d", &option);

    i = 1;
    int found = 0;

    rewind(file);

    while (fscanf(file, "%s %s %s %s %s %d", c[i].id, c[i].dep, c[i].sem, c[i].bat, c[i].sec, &c[i].vote) != EOF)
    {
        if (option == i)
        {
            found = 1;
            break;
        }
        i++;
    }

    fclose(file);

    if (found != 1)
    {
        printf("Wrong Option!!!");
        return;
    }

    FILE *file4 = fopen(StudentInfos, "r");
    fileCheck(file4, StudentInfos);

    int j = 0;
    found = 0;

    while (fscanf(file4, "%d %s %s %s %s %s %s %s %s %s",
                  &cc[j].serial, cc[j].name, cc[j].phone,
                  cc[j].email, cc[j].department, cc[j].semester,
                  cc[j].batch, cc[j].section, cc[j].id, cc[j].pass) != EOF)
    {
        if (strcmp(c[i].id, cc[j].id) == 0)
        {
            found = 1;
            break;
        }
        j++;
    }

    fclose(file4);
    if (found == 1)
    {
        printf("Name     : %s\n", cc[j].name);
        printf("Email    : %s\n", cc[j].email);
        printf("Phone    : %s\n", cc[j].phone);
        printf("Batch    : %s\n", cc[j].batch);
        printf("Section  : %s\n", cc[j].section);
        printf("Semester : %s\n", cc[j].semester);
        getch();
    }
    fclose(file4);
    fclose(file);
}


int Complain()
{
    struct check cc[max];
    struct abbcr c[max];
    int i = 1;
    printf("CR Infos: \n");

    FILE *file = fopen(result, "r");
    fileCheck(file, result);

    while (fscanf(file, "%s %s %s %s %s %d", c[i].id, c[i].dep, c[i].sem, c[i].bat, c[i].sec, &c[i].vote) != EOF)
    {
        printf("%d->\n", i);
        printf("Batch   : %s\n", c[i].bat);
        printf("Section : %s\n", c[i].sec);
        i++;
    }

    printf("Enter Serial Number: ");
    int option;
    scanf("%d", &option);

    i = 1;
    int found = 0;

    rewind(file);

    while (fscanf(file, "%s %s %s %s %s %d", c[i].id, c[i].dep, c[i].sem, c[i].bat, c[i].sec, &c[i].vote) != EOF)
    {
        if (option == i)
        {
            found = 1;
            break;
        }
        i++;
    }

    fclose(file);

    if (found != 1)
    {
        printf("Wrong Option!!!");
        return;
    }

    FILE *file4 = fopen(StudentInfos, "r");
    fileCheck(file4, StudentInfos);

    int j = 0;
    found = 0;

    while (fscanf(file4, "%d %s %s %s %s %s %s %s %s %s",
                  &cc[j].serial, cc[j].name, cc[j].phone,
                  cc[j].email, cc[j].department, cc[j].semester,
                  cc[j].batch, cc[j].section, cc[j].id, cc[j].pass) != EOF)
    {
        if (strcmp(c[i].id, cc[j].id) == 0)
        {
            found = 1;
            break;
        }
        j++;
    }

    fclose(file4);
    if (found == 1)
    {
        printf("Name     : %s\n", cc[j].name);
        printf("Email    : %s\n", cc[j].email);
        printf("Phone    : %s\n", cc[j].phone);
        printf("Batch    : %s\n", cc[j].batch);
        printf("Section  : %s\n", cc[j].section);
        printf("Semester : %s\n", cc[j].semester);
        printf("\n\tUse Underscore \"_\" Alternative To Space \" \"\n");
        printf("Write The Complain: ");
        char complain[100000];
        scanf("%s",complain);

        FILE *file101=fopen(ccomplain,"a");
        fprintf(file101,"%s \n%s",cc[j].name,complain);
        fclose(file101);
        getch();
    }
    fclose(file4);
    fclose(file);
}
int AfterTask()
{
    while (1)
    {
        printf("\n\n\t1. CR Vote \n\t2. Quiz \n\t3. Poll \n\t4. About CR \n\t5. Notice \n\t6. Complain On CR \n\n\tPlease Enter Which Service You Need : ");
        int option;
        scanf("%d", &option);
        switch (option)
        {
        case 0:
        {
            system("cls");
            return 1;
        }
        case 1:
        {
            system("cls");
            CRVote();
            break;
        }
        case 2:
        {
            system("cls");
            Quiz();
            break;
        }
        case 3:
        {
            system("cls");
            Poll();
            break;
        }
        case 4:
        {
            system("cls");
            AboutCR();
            break;
        }
        case 5:
        {
            system("cls");
            Notice();
            break;
        }
        case 6:
        {
            system("cls");
            Complain();
            break;
        }
        default:
        {
            system("cls");
            printf("Ooops... %d Is The  Wrong Option...\n", option);
        }
        }
    }
}


//Function for login for students


int Login()
{
    struct entry e[max];
    struct check c[max];
    int j = 0;
    int i = 0;
    int found = 0;
    system("cls");
back:
    printf("\n\tEnter User ID : ");
    scanf("%s", e[i].id);
    strcpy(voter,e[i].id);
    FILE *file4 = fopen(StudentInfos, "r");
    fileCheck(file4, StudentInfos);
    while (fscanf(file4, "%d %s %s %s %s %s %s %s %s %s",
                  &c[j].serial, c[j].name, c[j].phone,
                  c[j].email, c[j].department, c[j].semester,
                  c[j].batch, c[j].section, c[j].id, c[j].pass) != EOF)
    {
        if (strcmp(e[i].id, c[j].id) == 0)
        {
            found = 1;
            break;
        }
        j++;
    }
    fclose(file4);
    if (found != 1)
    {
        printf("\tOoops... Your ID Not Found...\n");
        goto back;
    }
    printf("\tEnter Password : ");
    scanf("%s", e[i].pass);
    system("cls");
    j = 0;
    found = 0;
    FILE *file5 = fopen(StudentInfos, "r");
    fileCheck(file5, StudentInfos);
    while (fscanf(file5, "%d %s %s %s %s %s %s %s %s %s",
                  &c[j].serial, c[j].name, c[j].phone,
                  c[j].email, c[j].department, c[j].semester,
                  c[j].batch, c[j].section, c[j].id, c[j].pass) != EOF)
    {
        if (strcmp(e[i].pass, c[j].pass) == 0)
        {
            found = 1;
            break;
        }
        j++;
    }
    fclose(file5);
    if (found != 1)
    {
        printf("\n\tOoops... Your ID Not Found...\n");
        goto back;
    }
    strcpy(voter, e[i].id);
    AfterTask();
}


//Function for forget password


int Forget()
{
    struct entry e;
    struct check c[MAX_STUDENTS];
    int j = 0;
    int found = 0;

    FILE *file2 = fopen(StudentInfos, "r");
    if (file2 == NULL)
    {
        perror("Error opening file");
        return 0;
    }

    system("cls");
    printf("\n\n\tTo Exit This Page Enter \"00\" In \"Enter Name\" To Create New Account.\n");
    printf("\n\tEnter Name : ");
    scanf("%s", e.name);

    if (strcmp(e.name, "00") == 0)
    {
        fclose(file2);
        return 0;
    }

    printf("\tEnter Phone : ");
    scanf("%s", e.phone);

    printf("\tEnter Email : ");
    scanf("%s", e.email);

    printf("\tEnter Department : ");
    scanf("%s", e.department);

    printf("\tEnter Semester : ");
    scanf("%s", e.semester);

    printf("\tEnter Batch : ");
    scanf("%s", e.batch);

    printf("\tEnter Section : ");
    scanf("%s", e.section);

    char id[5];
    strncpy(id, e.name, 4);
    id[4] = '\0';

    while (fscanf(file2, "%d %s %s %s %s %s %s %s %s %s",
                  &c[j].serial, c[j].name, c[j].phone,
                  c[j].email, c[j].department, c[j].semester,
                  c[j].batch, c[j].section, c[j].id, c[j].pass) != EOF)
    {
        if (strcmp(c[j].name, e.name) == 0 &&
                strcmp(c[j].phone, e.phone) == 0 &&
                strcmp(c[j].email, e.email) == 0 &&
                strcmp(c[j].department, e.department) == 0 &&
                strcmp(c[j].semester, e.semester) == 0 &&
                strcmp(c[j].batch, e.batch) == 0 &&
                strcmp(c[j].section, e.section) == 0)
        {
            found = 1;
            break;
        }
        j++;
    }

    fclose(file2);

    if (found == 1)
    {
        printf("Your User ID  : %s\n", c[j].id);
        printf("Your Password : %s\n", c[j].pass);

        printf("Do You Want To Change ID Or Pass?\n1. Yes\n2. No \nSelect One: ");
        int option = 0;
        scanf("%d", &option);
        char NewUserId[MAX_STRING_SIZE];
        char Password[MAX_STRING_SIZE];

        if (option == 1)
        {
            printf("Enter Your New User ID: ");
            scanf("%s", NewUserId);
            printf("Enter Your New Password: ");
            scanf("%s", Password);

            strncpy(c[j].id, NewUserId, sizeof(c[j].id));
            strncpy(c[j].pass, Password, sizeof(c[j].pass));
        }
    }
    else
    {
        printf("No Details Found\n");
        return 1;
    }

    FILE *File1 = fopen(StudentInfos, "r");
    if (File1 == NULL)
    {
        perror("Error opening file");
        return 0;
    }

    FILE *temp = fopen(Temp, "w");
    if (temp == NULL)
    {
        perror("Error opening file");
        return 0;
    }

    j = 0;
    while (j < MAX_STUDENTS && c[j].serial > 0)
    {
        fprintf(temp, "%d %s %s %s %s %s %s %s %s %s\n",
                c[j].serial, c[j].name, c[j].phone,
                c[j].email, c[j].department, c[j].semester,
                c[j].batch, c[j].section, c[j].id, c[j].pass);
        j++;
    }

    fclose(temp);
    fclose(File1);
    remove(StudentInfos);
    rename(Temp, StudentInfos);

    return 1;
}


//First function for students portal


int StudentPortal()
{
    system("cls");
    printf("\n\n\t1. Log In \n\t2. New Or Forget ID or Password \n\n\tPlease Enter Which Service You Need : ");
    int option;
    scanf("%d", &option);
    switch (option)
    {
    case 1:
    {
        Login();
        break;
    }
    case 2:
    {
        Forget();
        break;
    }
    default:
    {
        system("cls");
        printf("Ooops... %d Is The  Wrong Option...\n", option);
    }
    }
    return 1;
}


//File append for new setup


int setup()
{
    char data[] = "Appended data\n";

    FILE *file1 = fopen(StudentInfos, "a");
    if (file1 != NULL)
    {
        fclose(file1);
    }
    else
    {
        printf("Error opening StudentInfos.txt for append.\n");
    }

    FILE *file2 = fopen(Question, "a");
    if (file2 != NULL)
    {
        fclose(file2);
    }
    else
    {
        printf("Error opening Question.txt for append.\n");
    }

    FILE *file3 = fopen(CandidatesForCR, "a");
    if (file3 != NULL)
    {
        fclose(file3);
    }
    else
    {
        printf("Error opening CandidatesForCR.txt for append.\n");
    }

    FILE *file4 = fopen(MarkSheet, "a");
    if (file4 != NULL)
    {

        fclose(file4);
    }
    else
    {
        printf("Error opening MarkSheet.txt for append.\n");
    }

    FILE *file5 = fopen(Temp, "a");
    if (file5 != NULL)
    {
        fclose(file5);
    }
    else
    {
        printf("Error opening Temp.txt for append.\n");
    }

    FILE *file6 = fopen(Question2, "a");
    if (file6 != NULL)
    {
        fclose(file6);
    }
    else
    {
        printf("Error opening Question2.txt for append.\n");
    }

    FILE *file7 = fopen(PollResult, "a");
    if (file7 != NULL)
    {
        fclose(file7);
    }
    else
    {
        printf("Error opening PollResult.txt for append.\n");
    }
    system("cls");
}


//Front Part Code


int main()
{
    system("color 0F");
    int pin=1234, option, enteredpin, count=0, amount=1;
    float balance = 112000;
    int continueTransaction = 1;

    time_t now;
    time(&now);
    printf("\n");
    printf("\t\t\t%s", ctime(&now));
    while (1)
    {
        printf("\n\t\t      University Mangaement System \n\n");
        printf("\n\tDAFFODIL INTERNATIONAL UNIVERTISY       \n");
        printf("\tDaffodil Smart City, Ashulia, Dhaka-1341, Bangladesh.\n \n");

        printf("\tDepartment of Software Engineering.\n \n");

        printf("\tCopyright : \n");
        printf("\tMD Rohejul Islam Hemal & Shahporan Alif - 2023 - All Rights Reserved. \n \n \n");
        printf("\n\n\tWelcome To, University Management System!!!\n\n\n");
        printf("\t1. Student Portal \n\t2. Teacher Portal \n\n\tPlease Enter Which Service You Need : ");
        int option;
        scanf("%d", &option);
        switch (option)
        {
        case 0:
        {
            setup();
            break;
        }
        case 1:
        {
            system("cls");
            StudentPortal();
            break;
        }
        case 2:
        {
            system("cls");
            TeacherPortal();
            break;
        }
        case 3:
        {
            CalculateAndRecordResults();
            break;
        }
        default:
        {
            printf("Ooops... Wrong Option...\n");
            break;
        }
        }
    }
}
