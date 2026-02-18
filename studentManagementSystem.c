#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int id;
    char name[50];
    double cgpa;
}Student ;

int main(){
    char buffer[50];
    printf("Studen Management System\n");
    int no_of_students;
    printf("Total number of students: ");
    fgets(buffer,sizeof(buffer),stdin);
    no_of_students = (int)strtol(buffer,NULL,10);
    Student *student = malloc(no_of_students * sizeof(Student));
    FILE *pFile = fopen("student_data.txt","w");
    for(int i=0; i < no_of_students; i++){
        fprintf(pFile,"student: %d\n",i+1);
        printf("student: %d\n",i+1);
        //student id
        printf("enter the student id: ");
        fgets(buffer,sizeof(buffer),stdin);
        student[i].id = (int)strtol(buffer,NULL,10);
        //student name
        printf("enter the student name: ");
        fgets(student[i].name,sizeof(student[i].name),stdin);
        student[i].name[strlen(student[i].name) - 1 ] = '\0';
        //student cgpa
        printf("enter the cgpa: ");
        fgets(buffer,sizeof(buffer),stdin);
        student[i].cgpa= (float)strtod(buffer,NULL);
        //printing the values
        fprintf(pFile,"id: %d\n",student[i].id);
        fprintf(pFile,"name: %s\n",student[i].name);
        fprintf(pFile,"cgpa: %.2lf\n",student[i].cgpa);
    };
    fclose(pFile);
    free(student);
    student = NULL;
    return 0;
}
