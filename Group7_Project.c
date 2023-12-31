//Created By Group7
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Course
{
	char code[100];
	char name[50];
	char evaluation_name[100];
	float evaluation_percentage;
	float evaluation_fullmark;
};
struct Course course[100];

void SaveCourse();
void ReadCourse();
void SaveCourseDetails();
void ReadCourseDetails();
int CheckCourseCode();
int CheckCourseName();
void test();
void AddCourse();
void DeleteCourse();
int DelCourse(int answer2);
void DeleteAllCourse();
void DeleteAllCourseDetails();
void ModifyCourse();
void ModifyCourseChoice(int answer3);
void ModifyCourseName(int answer3);
void ModifyItemName(int answer3);
void ModifyItemPercentage(int answer3);
void ModifyItemFullmark();
void EditCourse();

int CourseCount = 0;
int CourseDetailsCount = 0;


int main()
{
	while (1)
	{
		ReadCourse();
		ReadCourseDetails();
		printf("\n============== Main Menu ==============\n");
		printf("\t1. Edit Course\n");
		printf("\t2. Edit Grade\n");
		printf("\t3. Expected Final Grade\n");
		printf("\t4. View Course\n");
		printf("\t5. Exit\n");
		printf("=======================================\n\n");

		printf("Enter a number and choose an choiceation:");
		int choice;
		scanf("%d", &choice);
		switch (choice)
		{
		case 1: // Edit Course
			EditCourse();
			break;
		case 2: // Edit Grade
			break;
		case 3: // Expected Final Grade
			break;
		case 4: // View Course
			break;
		case 5: // Exit
			return 1;
			break;
		default:
			break;
		}
	}
	return 0;
}

void SaveCourse()
{
	FILE* RC = NULL;
	RC = fopen("./CourseInfo.txt", "w+");
	int i = 0;
	for (i = 0; i < CourseCount; i++)
	{
		fprintf(RC, "%s\t%s\n",course[i].code, course[i].name);
	}
	fclose(RC);
	RC = NULL;
}

void SaveCourseDetails()
{
	FILE* RCD = NULL;
	RCD = fopen("./CourseDetailsInfo.txt", "a+");
	int i = 0;
	for (i = 0; i < CourseDetailsCount; i++)
	{
		fprintf(RCD, "%s\t%f\t%f\n", course[i].evaluation_name, course[i].evaluation_percentage, course[i].evaluation_fullmark);
	}
	fclose(RCD);
	RCD = NULL;
}

void ReadCourse()
{
	FILE* RC = NULL;
	RC = fopen("./CourseInfo.txt", "r");
	int i = 0;
	while (fscanf(RC, "%s%*c%[^\n]", course[i].code, course[i].name) != EOF)
	{
		i++;
	}
	CourseCount = i;
	fclose(RC);
	RC = NULL;
}

void ReadCourseDetails()
{
	FILE* RCD = NULL;
	RCD = fopen("./CourseDetailsInfo.txt", "r");
	int i = 0;
	while (fscanf(RCD, "%s%f%f", course[i].evaluation_name, &course[i].evaluation_percentage, &course[i].evaluation_fullmark) != EOF)
	{
		i++;
	}
	fclose(RCD);
	RCD = NULL;
}

int CheckCourseCode(char* code)
{
	int i = 0;
	int res = -1;
	for (i = 0; i < CourseCount; i++)
	{
        if (strcmp(code, course[i].code) == 0)
		{
			res = i;
			break;
		}
	}
	return res;
}

int CheckCourseName(char* name)
{
	int i = 0;
	int res = -1;
	for (i = 0; i < CourseCount; i++)
	{
		if (strcmp(name, course[i].name) == 0)
		{
			res = i;
			break;
		}
	}
	return res;
}

void test()
{
	int i = 0;
	for (i = 0; i < CourseCount; i++)
	{
		printf("%d.\t%-5s\t%-5s\n\n\n", i + 1, course[i].code, course[i].name);
	}
}

void AddCourse()
{
	ReadCourse();
	ReadCourseDetails();
	printf("\nThere're totally %d courses recorded:\n\n", CourseCount);
    test();
	printf("Enter NEW course ID (Character+Number, lenghth < 10) or any single key back:");
	scanf("%s", course[CourseCount].code);
	int index = CheckCourseCode(course[CourseCount].code);
	if (index > -1)
	{
		printf("The course code is exist.\n");
		return;
	}
	if (strlen(course[CourseCount].code) > 1 && strlen(course[CourseCount].code) < 10)
	{
		printf("Enter course name (less than 50 characters with spaces):");
		scanf("%*c%[^\n]", course[CourseCount].name);
		int index = CheckCourseName(course[CourseCount].name);
		if (index > -1)
		{
			printf("The course name is exist.\n");
			return;
		}
	}
	else
	{
		return;
	}
	printf("Add course successfully but evaluation items.\n\n");
	printf("The newly added course is %s, %s.\n\n", course[CourseCount].code, course[CourseCount].name);
	printf("Continue to set the evaluation items for this course? (Y or y: yes; any other character: no): ");
	CourseCount += 1;
	char answer1;
	scanf(" %c", &answer1);
	if (answer1 == 'Y' || answer1 == 'y')
	{
		printf("Enter number of evaluation items for the new course:");
		int num = 0;
		scanf("%d", &num);
		printf("Input name, percentage, full marks for each item\n(attention: no space in names and the total percentage should be 100):");
		int i = 0;
		for (i = CourseDetailsCount; i < CourseDetailsCount + num; i++)
		{
			scanf("%s %f %f", course[i].evaluation_name, &course[i].evaluation_percentage, &course[i].evaluation_fullmark);
		}
		CourseDetailsCount += 3;
		int Item = CourseDetailsCount;
		SaveCourse();
		SaveCourseDetails();
		AddCourse();
	}
	else
	{
		return;
	}
}

void DeleteCourse()
{
	ReadCourse();
	printf("\nThere're totally %d courses recorded:\n\n", CourseCount);
	for (int n = 0; n < CourseCount; n++)
	{
		printf("%d.\t%s\t%s\n\n\n", n + 1, course[n].code, course[n].name);
	}
	printf("Enter a number to delete the related course or any other key back: ");
	int answer2;
	scanf("%d", &answer2);
	if (answer2 < 1 || answer2 > CourseCount)
	{
		return;
	}
	else
	{
		int res = DelCourse(answer2);
	} 
	SaveCourse();
	SaveCourseDetails();
}

int DelCourse(int answer2)
{
	if (answer2 >= 0 && answer2 <= CourseCount)
	{
		int i;
		for (i = answer2; i <= CourseCount - 1; i++)
		{
			course[i - 1] = course[i];
		}
		CourseCount--;
		return 1;
	}
	else
	{
		return 0;
	}
}

void DeleteAllCourse()
{
	FILE* RC;
	if ((RC = fopen("./CourseInfo.txt", "w")) == NULL) 
	{
		puts("Fail to open file!");
		return;
	}
	fclose(RC);
	CourseCount = 0;
	SaveCourse();
	return;
}

void DeleteAllCourseDetails()
{
	FILE* RCD;
	if ((RCD = fopen("./CourseDetailsInfo.txt", "w")) == NULL)
	{
		puts("Fail to open file!");
		return;
	}
	fclose(RCD);
	printf("All courses are deleted!");
	CourseDetailsCount;
	SaveCourseDetails();
	return;
}

void ModifyCourse()
{
	ReadCourse();
	ReadCourseDetails();
	printf("\nThere're totally %d courses recorded:\n\n", CourseCount);
	for (int n = 0; n < CourseCount; n++)
	{
		printf("%d.\t%s\t%s\n\n\n", n + 1, course[n].code, course[n].name);
	}
	printf("Enter a number to modify the related course details or any other key back: ");
	int answer3;
	scanf("%d", &answer3);
	if (answer3 < 1 || answer3 > CourseCount)
	{
		return;
	}
	else
	{
		for (int n = 1; n <= CourseCount; n++)
	    {
		if (answer3 == n)
		   {
			   printf("        %s %s\n", course[n - 1].code, course[n - 1].name);
			   printf("        -----------------------------------\n");
			   printf("        | No.    | Item                | Percentage     | Full Mark    | Grades\n");
			   int i = 0;
			   for (i = 3 * (n - 1); i < 3 * n; i++)
			   {
			      printf("        | %d      | %-20s| %-15f| %-15f        \n", i - 3 * (n - 1) + 1, course[i].evaluation_name, course[i].evaluation_percentage, course[i].evaluation_fullmark);
			   }  
			   printf("        -----------------------------------\n");
			   ModifyCourseChoice(answer3);
		   }		
	    }
	}
}

void ModifyCourseChoice(int answer3)
{
	while(1)
	{   
		printf("\n============== Edit Course ==============\n");
		printf("\t1. Modify Course Name\n");
		printf("\t2. Modify Item Name\n");
		printf("\t3. Modify Item Percentage\n");
		printf("\t4. Modify Item Fullmark\n");
		printf("\t5. Add Items If No Item Yet\n");
		printf("=========================================\n\n");
		printf("Enter a number to modify the related course details or any other key back:");
		int choice;
		scanf("%d", &choice);
		if (choice == 5)
		{
			printf("ERROR: Can't add items as they're exist already!\n\n\n");
			ModifyCourse();
		}
		switch (choice)
		{
		case 1: // Modify Course Name
		    ModifyCourseName(answer3);
			break;
		case 2: // Modify Item Name
			ModifyItemName(answer3);
			break;
        case 3: // Modify Item Percentage
		    ModifyItemPercentage(answer3);
			break;
		case 4: // Modify Item Fullmark
		    break;
		default:
		    return;
		}
	}
}

void ModifyCourseName(int answer3)
{
	printf("You want to change name of course \"%s\" as :", course[answer3 - 1].name);
	scanf("%*c%[^\n]", course[answer3 - 1].name);
	SaveCourse();
	printf("\n");
	printf("        %s %s\n", course[answer3 - 1].code, course[answer3 - 1].name);
	printf("        -----------------------------------\n");
    printf("        | No.    | Item                | Percentage     | Full Mark    | Grades\n");
	int i = 0;
	for (i = 3 * (answer3 - 1); i < 3 * answer3; i++)
	{
		printf("        | %d      | %-20s| %-15f| %-15f        \n", i - 3 * (answer3 - 1) + 1, course[i].evaluation_name, course[i].evaluation_percentage, course[i].evaluation_fullmark);
	}
	printf("        -----------------------------------\n");   
}

void ModifyItemName(int answer3)
{
	ReadCourseDetails();
	printf("Enter the No. of an Item to be modified: ");
	int num = 0;
	scanf("%d", &num);
	while (num < 1 || num > 3)
	{
		printf("Invalid No. Please input again!\n");
		printf("Enter the No. of an Item to be modified: ");
		scanf("%d", &num);
	}
	printf("Enter a new name:");
	char name[100];
	scanf("%*c%[^\n]", course[3 * answer3 + num - 4].evaluation_name, name);
	SaveCourseDetails();
	printf("\n");
	printf("        %s %s\n", course[answer3 - 1].code, course[answer3 - 1].name);
	printf("        -----------------------------------\n");
	printf("        | No.    | Item                | Percentage     | Full Mark    | Grades\n");
	int i = 0;
	for (i = 3 * (answer3 - 1); i < 3 * answer3; i++)
	{
		printf("        | %d      | %-20s| %-15f| %-15f        \n", i - 3 * (answer3 - 1) + 1, course[i].evaluation_name, course[i].evaluation_percentage, course[i].evaluation_fullmark);
	}
	printf("        -----------------------------------\n");  
}



void ModifyItemPercentage(int answer3)
{
	printf("Enter the new percentages in order:");
	int n = 0;
	for (n = 3 * (answer3 - 1); n < 3 * answer3; n++)
	{
		scanf("%f", &course[n].evaluation_percentage);
	}
    SaveCourseDetails();
	printf("\n");
	printf("        %s %s\n", course[answer3 - 1].code, course[answer3 - 1].name);
	printf("        -----------------------------------\n");
	printf("        | No.    | Item                | Percentage     | Full Mark    | Grades\n");
	int i = 0;
	for (i = 3 * (answer3 - 1); i < 3 * answer3; i++)
	{
		printf("        | %d      | %-20s| %-15f| %-15f        \n", i - 3 * (answer3 - 1) + 1, course[i].evaluation_name, course[i].evaluation_percentage, course[i].evaluation_fullmark);
	}
	printf("        -----------------------------------\n");  
}

void EditCourse()
{
	while (1)
	{
		printf("\n============== Edit Course ==============\n");
		printf("\t1. Add Course\n");
		printf("\t2. Delete Course\n");
		printf("\t3. Delete All Course\n");
		printf("\t4. Modify Course\n");
		printf("\t5. Back\n");
		printf("=========================================\n\n");
		printf("Enter a number and choose an choiceation:");
		int choice;
		scanf("%d", &choice);
		if (choice == 5)
		{
			break;
		}
		switch (choice)
		{
		case 1: // Add Course
			AddCourse();
			break;
		case 2: // Delete Course
			DeleteCourse();
			break;
		case 3: // Delete All Courses
			DeleteAllCourse();
			DeleteAllCourseDetails();
			break;
		case 4: // Modify Course
			ModifyCourse();
			break;
		default:
			break;
		}
	}
}
