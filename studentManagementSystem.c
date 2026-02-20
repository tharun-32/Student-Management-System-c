#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int id;
    char name[50];
    double cgpa;
}Student ;

void add();
void delete();
void show();

int main(){
    int user_choice;
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
                break;
            case 2:
                delete();
                break;
            case 3:
                show();
                break;
        }
        printf("\n");
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
        printf("no such file!\n");
        return;
    }
    FILE *pFile = fopen("student_data.txt","a");
    for(int i=0; i < no_of_students; i++){
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
        fprintf(pFile,"%d %s %.2lf",student[i].id,student[i].name,student[i].cgpa);
        fprintf(pFile,"\n"); // while printing there will be a gap 
    };
    fclose(pFile);
    free(student);
    student = NULL;
}
//remove
void delete(){
    int delete_id;
    char buffer[5];
    printf("Enter the student id: ");
    fgets(buffer,sizeof(buffer),stdin);
    delete_id = (int)strtol(buffer,NULL,10);
    FILE *pFile = fopen("student_data.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");
    if(pFile == NULL || tempFile == NULL){
        printf("File error!\n");
        return;
    }
    int id;
    char name[50];
    float cgpa;
    int found = 0;
    while(fscanf(pFile, "%d %s %f", &id, name, &cgpa) == 3){
        if(id == delete_id){
            found = 1;          // skip this record
            continue;
        }
        fprintf(tempFile, "%d %s %.2f\n", id, name, cgpa);
    }
    fclose(pFile);
    fclose(tempFile);
    remove("student_data.txt");
    rename("temp.txt", "student_data.txt");
    if(found)
        printf("Student deleted successfully.\n");
    else
        printf("Student ID not found.\n");
}
//view
void show(){
    int id;
    char name[50];
    float cgpa;
    FILE *pFile = fopen("student_data.txt","r");
    char buffer[1024] = {0};
    printf("%-10s %-15s %-10s\n", "ID", "NAME", "CGPA");
    printf("--------------------------------------\n");
    while(fscanf(pFile, "%d %s %f", &id, name, &cgpa) == 3){
        printf("%-10d %-15s %-10.2f\n", id, name, cgpa);
    } 
    fclose(pFile);
    printf("\n");
}
