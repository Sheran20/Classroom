#include <stdio.h>
#include <stdlib.h>

//creating student structure//
typedef struct
{
    int ID_No;
    char first_name[15];
    char last_name[15];
    int proj_1;
    int proj_2;
    float final_grade;
} student;

//function 1 prototype//
student **create_class_list(char *filename, int *sizePtr);
//function 1 defenition//
student **create_class_list(char *filename, int *sizePtr)
{
    int num_std; //number of students//

    //opening file for read//
    FILE *input_file;
    input_file = fopen(filename, "r");
    //recieving the first character, 3, as integer//
    fscanf(input_file,"%d",&num_std);

    //defining class list and allocating dynamic memory//
    student **class_list = calloc(num_std, sizeof(student));  //note: array of pointers pointing at student variables//
    int i; //use of calloc because it intializes memory where the length is paramter of num_std * sizeof(student)//
           //allocated memory is initialized to zero therfore you dont have to initialize it as zero//

    //create forloop to add memory to each student variable//
    for(i = 0; i < num_std; i++)
    {
        //allocating memory for each student variable//
        class_list[i] = calloc(1,sizeof(student)); //splitting the dynamic memory into sections, like an array. use calloc to initialize to zero//
        //accessing student number and name and initializing values//
        fscanf(input_file,"%d%s%s", &class_list[i]->ID_No, class_list[i]->first_name, class_list[i]->last_name);
    }

    //ordering the list in terms of least to greatest student number//
    int j;
    for (i = 0; i < num_std; i++)
	{
		for (j = 0; j < num_std; j++)  //nested forloop//
		{
			if (class_list[j] ->ID_No > class_list[i] ->ID_No) //sorting alogirthm//
			{
			    student *temp = class_list[i];  //create temp student to store the ith student
				class_list[i] = class_list[j];  //switching student at i, to student at j position
				class_list[j] = temp;           //setting the jth student as the lower one//
			}
		}
	}

    //changing size_class to 3//
    *sizePtr = num_std;
    //file close//
    fclose(input_file);
    //printing out the list//
    for(i=0;i<num_std;i++)
    {
        printf("%d\n%s\n%s\n%d\n%d\n%0.1f\n", class_list[i]->ID_No, class_list[i]->first_name, class_list[i]->last_name,class_list[i]->proj_1, class_list[i]->proj_2, class_list[i]->final_grade);
    }
    //return//
    return class_list;
    free(class_list);
}

//function 2 prototype//
int find(int idNo, student **list, int size);
//function 2 defenition//
int find(int idNo, student **list, int size)
{
    int i;

    for(i=0;i<size;i++)
    {
        //finding the matching student ID//
        if(idNo == list[i]->ID_No)
            {
                return i;
                break;  //breaking loop if ID found//
            }
    }

    return -1;
}

//function 3 prototype//
void input_grades(char *filename, student **list, int size);
//function 3 defenition//
void input_grades(char *filename, student **list, int size)
{
   //opening file for read//
    FILE *input_file = fopen(filename, "r");

    int i;
    for(i=0;i<size;i++)
    {
        //reading from file and storing values in temps, definiting student variables as temps//
        int temp_id, temp_gr1, temp_gr2;
        fscanf(input_file,"%d%d%d", &temp_id, &temp_gr1, &temp_gr2);
        list[find(temp_id,list,size)]->proj_1 = temp_gr1;
        list[find(temp_id,list,size)]->proj_2 = temp_gr2;
    }
    fclose(input_file);
}

//function 4 prototype//
void compute_final_course_grades(student **list, int size);
//function 4 defenition//
void compute_final_course_grades(student **list, int size)
{
    int i;
    for(i=0;i<size;i++)
    {
        //computing final grade by casting int grades to float//
        list[i]->final_grade =((float) list[i] -> proj_1 + (float) list[i] -> proj_2)/2;
    }
}

//function 5 prototype//
void output_final_course_grade(char *filename, student **list, int size);
//function 5 defenition//
void output_final_course_grade(char *filename, student **list, int size)
{
    //opening file for write//
    FILE *output_file = fopen(filename, "w");
    int i;
    //writing in file//
    for(i=0;i<size;i++)
    {
        fprintf(output_file,"%d %0.1f\n", list[i]->ID_No, list[i]->final_grade);
    }
}

//function 6 prototype//
void print_list(student **list, int size);
//function 6 defenition//
void print_list(student **list, int size)
{
    //printing out student variables//
    int i;
    for(i=0;i<size;i++)
    {
        printf("ID: %d, name: %s %s, project 1 grade: %d, project 2 grade: %d, final grade: %0.1f\n", list[i]->ID_No, list[i]->first_name, list[i]->last_name, list[i]->proj_1, list[i]->proj_2, list[i]->final_grade);
    }
}

//function 7 prototype//
void withdraw(int idNo, student **list, int *sizePtr);
//function 7 defenition//
void withdraw(int idNo, student **list, int *sizePtr)
{
    //find the student and store the index//
    int index_withdraw_std = find(idNo,list,*sizePtr);
    if(index_withdraw_std != -1)
    {
        int i;
        for(i=index_withdraw_std;i<(*sizePtr-1);i++)
        {
            //alorithm to move withdraw student to end of list//
            student *temp = list[i+1];
            list[i+1] = list[i];
            list[i] = temp;
        }
        //cut end of list//
        free(list[(*sizePtr-1)]);  //free the dynamic mem//
        *sizePtr = *sizePtr - 1;  //change the # students//
    }
    //if cannot find student, let user know//
    else
    {
        printf("This Student is Not in the List\n");
    }
}

//function 8 prototype//
void destroy_list(student **list, int *sizePtr);
//function 8 defenition//
void destroy_list(student **list, int *sizePtr)
{
    free(list);
    *sizePtr = 0;
}

//PROGRAM TESTING//
int main()
{
    int size_class = 5;
    //function 1 call and stored//
    student **class_list = create_class_list("Class.txt",&size_class);
    printf("^^^^^STUDENT LIST^^^^^\n");
    //testing the change of size//
    printf("The Change of Size is: %d\n", size_class);
    //function 2 call//
    int index_find = find(1200,class_list,size_class);
    printf("The index of that ID is: %d\n", index_find);

    //function 3 call//
    input_grades("grades.txt",class_list,size_class);
    //function 3 test//
    int i;
    for(i=0;i<size_class;i++)
    {
        printf("%d\n%d\n%0.1f\n",class_list[i]->proj_1, class_list[i]->proj_2, class_list[i]->final_grade);
    }
    printf("^^^^^UPDATED LIST^^^^^\n");
    //function 4 call//
    compute_final_course_grades(class_list, size_class);
    for(i=0;i<size_class;i++)
    {
        printf("%0.1f\n", class_list[i]->final_grade);
    }
    printf("^^^^^final marks^^^^^\n");

    //function 5 call//
    output_final_course_grade("final_marks.txt",class_list,size_class);

    //function 6 call//
    print_list(class_list, size_class);
    printf("______________________\n\n");

    //function 7 call//
    withdraw(4581, class_list, &size_class);
    print_list(class_list, size_class);
    printf("__________________________\n\n");
    withdraw(9000, class_list, &size_class);
    print_list(class_list, size_class);
    printf("__________________________\n\n");
    withdraw(4580, class_list, &size_class);
    print_list(class_list, size_class);
    printf("__________________________\n\n");
    //last function call//
    destroy_list(class_list, &size_class);
    print_list(class_list, size_class);

    printf("END OF PROGRAM OUTPUTS\n");
}
