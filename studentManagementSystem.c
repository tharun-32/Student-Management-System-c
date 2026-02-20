#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct{
    int id;
    char name[50];
    double cgpa;
}Student ;

void add();
void delete();
void show();

int main(){
    char user_choice;
    char buffer[4];
    do{
        printf("Studen Management System\n");
        printf("\n");
        printf("1.Add student\n");
        printf("2.Remove student\n");
        printf("3.View record\n");
        printf("4.exit\n");
        printf("Enter your choice: ");
        fgets(buffer,sizeof(buffer),stdin);
        user_choice= (int)strtol(buffer,NULL,10);
        printf("\n");
        printf("\033[H\033[J");//clear screen for next loop
        switch (user_choice) {
            case 1:
                add();
            case 2:
                delete();
            case 3:
                show();
        }
    }while(user_choice != 4);
    return 0;
}

//functions 
//add
void add(){
    char buffer[50];
    int no_of_students;
    printf("Total number of students: ");
    fgets(buffer,sizeof(buffer),stdin);
    no_of_students = (int)strtol(buffer,NULL,10);
    Student *student = malloc(no_of_students * sizeof(Student));
    if(student == NULL){
        printf("Memory allocation failed!\n");
        return;
    }
    FILE *pFile = fopen("student_data.txt","a");
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
        fprintf(pFile,"\n"); // while printing there will be a gap 
    };
    fclose(pFile);
    free(student);
    student = NULL;
}
//remove
void delete(){

}
//view
void show(){
    FILE *pFile = fopen("student_data.txt","r");
    char buffer[1024] = {0};
    while(fgets(buffer,sizeof(buffer),pFile) != NULL){
        printf("%s",buffer);
    }
    fclose(pFile);
}
