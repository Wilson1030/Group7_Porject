//Created By Group7
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Course
{
	char code[100];
	char name[50];
	char evaluation_name[100];
	float grade[100];
	float evaluation_percentage;
	float evaluation_fullmark;
};
struct Course course[100];

struct Grade
{
	int numGrade;
	float ActualGrade;
}
struct Grade GradeRecord[100];

void SaveCourse();
void ReadCourse();
void SaveCourseDetails();
void ReadCourseDetails();
void SaveGrade(int answer4, int answer5, int CountNum);
void ReadGrade(int answer4, int answer5);
int CheckCourseCode();
int CheckCourseName();
void test();
void AddCourse();
void DeleteCourse();
int DelCourse(int answer2);
void DeleteAllCourse();
void DeleteAllCourseDetails();
void ModifyCourseChoice();
void ModifyCourse(int answer3);
void ModifyCourseName(int answer3);
void ModifyItemName(int answer3);
void ModifyItemPercentage(int answer3);
void ModifyItemFullmark(int answewr3);
void AddGrade();
void DeleteGrade();
void DeleteAllGrades();
void ModifyGrade();
void SingleCourseDetail(int choice3,int classchoose);
void EditGrade();


int CourseCount = 0;
int CourseDetailsCount = 0;
int count=0;//Caculate Grade Number
int choice2;//special choice
int choice3;//special choice


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
		    EditGradeChoice();
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
	RCD = fopen("./CourseDetailsInfo.txt", "w+");
	int i = 0;
	for (i = 0; i < CourseDetailsCount; i++)
	{
		fprintf(RCD, "%s\t%f\t%f\n", course[i].evaluation_name, course[i].evaluation_percentage, course[i].evaluation_fullmark);
	}
	fclose(RCD);
	RCD = NULL;
}

void SaveGrade(int answer4, int answer5, int CountNum)
{
	FILE* RG = NULL;
	RG = fopen("./CourseGrade.txt", "w+");
	int i = 0;
	CountGradeNum = 3 * answer4 + answer5 - 4;
	char ch = '\n';
	for (i = 0; i < CountGradeNum + 1; i++)
	{
		for (int m = 0; m < CountNum; m++)
		{
			fprintf(RG, "%.2f\t", course[i].grade[m]);
	    }
		fprintf(RG, "%c", ch);
	}
	fclose(RG);
	RG = NULL;
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
	CourseDetailsCount = i;
	fclose(RCD);
	RCD = NULL;
}

void ReadGrade(int answer4, int answer5)
{
	FILE* RG = NULL;
	RG = fopen("./CourseGrade.txt", "r");
	CountGradeNum = 3 * answer4 + answer5 - 4;
	int i = 0;
	int m = 0;
	while(fscanf(RG, "%f", &course[i].grade) != EOF)
	{
		while(fscanf(RG, "%f", &course[i].grade[m]) != EOF)
		{
			m++;
		}
		i++;
	}
	CountNum = m;
	fclose(RG);
	RG = NULL;
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
		int has_space = 0;
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
	if ((RCD = fopen("./CourseDetailsInfo.txt", "w+")) == NULL)
	{
		puts("Fail to open file!");
		return;
	}
	fclose(RCD);
	printf("All courses are deleted!");
	CourseDetailsCount = 0;
	SaveCourseDetails();
	return;
}

void ModifyCourseChoice()
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

void ModifyCourse(int answer3)
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
			printf("ERROR: Can't add items as they're exist already!\n\n");
			ModifyCourse(answer3);
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
		    ModifyItemFullmark(answer3);
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
	scanf("%*c%[^\n]", course[3 * answer3 + num - 4].evaluation_name);
	int has_space = 0;
	int m = 0;
	for (m = 0; course[3 * answer3 + num - 4].evaluation_name[m]; m++)
	{
		if (isspace(course[3 * answer3 + num - 4].evaluation_name[m]))
	    {
		    has_space = 1;
	    }
	}
	if (has_space)
	{
		printf("Invalid input! (attention: no space in names)\n");
		return;
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

void ModifyItemFullmark(int answer3)
{
	printf("Enter the No. of an Item to be modified: ");
	int num = 0;
	scanf("%d", &num);
	while (num < 1 || num > 3)
	{
		printf("Invalid No. Please input again!\n");
        printf("Enter the No. of an Item to be modified:");
		scanf("%d", &num);
	}
    printf("Enter a new fullmark:");
	scanf("%f", &course[3 * answer3 + num - 4].evaluation_fullmark);
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
			ModifyCourseChoice();
			break;
		default:
			break;
		}
	}	
}

void AddGrade(){
    while(1){
	    printf("Enter a grade to added to the item or a negative number back: ");
		if (scanf("%f",&GradeRecord[count].ActualGrade)==1)
		{
			if (GradeRecord[count].ActualGrade<0)
			{
				break;
			}
			GradeRecord[count].numGrade=count+1;
			count++;
	}
}
	//put the information of the grade into a file
	FILE *fpgrade;
	fpgrade=fopen("Gradeinformation.txt","r+");
	if (fpgrade==NULL)
	{
		printf("Error opening file for writing!");
		return;
	}
	
	for (int i = 0; i < count; i++)
	{
		fprintf(fpgrade,"%d : %.2f ",GradeRecord[i].numGrade,GradeRecord[i].ActualGrade);
	}
	fclose(fpgrade);

	//print the information after being editted
		SingleCourseDetail(choice3,choice2);
		for (int i = 0; i < count; i++)
		{
			printf(" %d: %.2f",GradeRecord[i].numGrade,GradeRecord[i].ActualGrade);
		}
		printf("\n        -----------------------------------\n");

}

void DeleteGrade(){//这里留一个指针用于把对应课程的不同部分文件分开存 待接入singlecourse函数里
	int choice5;
	printf("Enter the number of a grade to delete or any other key back: ");
	if (scanf("%d",&choice5)!=1)
	{
		return;//用户输入非整数，返回
	}
	if (choice5>0&&choice5<=count)
	{
		for (int i = choice5-1; i < count-1; i++)
		{
			GradeRecord[i]=GradeRecord[i+1];
		}
		count--;//更新总成绩数

		FILE *fpgrade;
		fpgrade=fopen("Gradeinformation.txt","r+");
		if (fpgrade==NULL)
		{
			printf("Error opening file for writing!\n");
			return;
		}
		for (int i = 0; i < count; i++)
		{
			fprintf(fpgrade,"%d: %.2f",GradeRecord[i].numGrade,GradeRecord[i].ActualGrade);
		}
		fclose(fpgrade);//更新文件中的成绩
		
	}
		SingleCourseDetail(choice3,choice2);
		for (int i = 0; i < count; i++) {
            printf(" %d: %.2f", GradeRecord[i].numGrade, GradeRecord[i].ActualGrade);
        }
		printf("\n        -----------------------------------\n");
 
} 

void DeleteAllGrades() {
    FILE* ff = fopen("Gradeinformation.txt", "w");
    fclose(ff);

    count = 0; // 重置成绩数量为0

    SingleCourseDetail(choice3, choice2);

    // 输出被删除后的信息
    for (int i = 0; i < count; i++) {
        printf(" %d: %.2f", GradeRecord[i].numGrade, GradeRecord[i].ActualGrade);
    }
    printf("\n        -----------------------------------\n");
}



void ModifyGrade() {
    SingleCourseDetail(choice3, choice2);
    
    printf("\n============== Edit Grade ==============\n");
    for (int i = 0; i < count; i++) {
        printf(" %d: %.2f", GradeRecord[i].numGrade, GradeRecord[i].ActualGrade);
    }
    printf("\n        -----------------------------------\n");
    
    printf("Enter the number of a grade to modify or any other key back: ");
    int choice6;
    scanf("%d", &choice6);
    
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (choice6 == GradeRecord[i].numGrade) {
            printf("You want to change Assignment Grade %d from %.2f to: ", GradeRecord[i].numGrade, GradeRecord[i].ActualGrade);
            scanf("%f", &GradeRecord[i].ActualGrade);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Grade not found.\n");
    }

    // 写入文件
    FILE* newGradefp;
    newGradefp = fopen("Gradeinformation.txt", "w");
    if (newGradefp == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(newGradefp, "%d: %.2f", GradeRecord[i].numGrade, GradeRecord[i].ActualGrade);
    }
    fclose(newGradefp); // 更新文件中的成绩

    SingleCourseDetail(choice3, choice2);
    for (int i = 0; i < count; i++) {
        printf(" %d: %.2f", GradeRecord[i].numGrade, GradeRecord[i].ActualGrade);
    }
    printf("\n        -----------------------------------\n");
}



void SingleCourseDetail(int choice3,int classchoose){
	
	for (int n = 1; n <= CourseCount; n++)
	{
		if (classchoose == n)
		{
			if (choice3==1)
	{
		printf("        %s%s\n", course[n - 1].code, course[n - 1].name);
		printf("        -----------------------------------\n");
		printf("        | No.    | Item                | Percentage     | Full Mark    | Grades\n");
		printf("        | 1      | %-20s| %-15f| %-15f |", course[n-1].evaluation_name, course[n-1].evaluation_percentage, course[n-1].evaluation_fullmark);
		
	}else if (choice3==2)
	{
		printf("        %s%s\n", course[n - 1].code, course[n - 1].name);
		printf("        -----------------------------------\n");
		printf("        | No.    | Item                | Percentage     | Full Mark    | Grades\n");
		printf("        | 2      | %-20s| %-15f| %-15f |", course[n].evaluation_name, course[n].evaluation_percentage, course[n].evaluation_fullmark);
		
	}else if (choice3==3)
	{
		printf("        %s%s\n", course[n - 1].code,course[n - 1].name);
		printf("        -----------------------------------\n");
		printf("        | No.    | Item                | Percentage     | Full Mark    | Grades\n");
		printf("        | 3      | %-20s| %-15f| %-15f |", course[n+1].evaluation_name, course[n+1].evaluation_percentage, course[n+1].evaluation_fullmark);
		
	}else
	{
		return;
	}
	


			//printf("        %s%s\n", course[n - 1].code, course[n - 1].name);
		}
	}
	
	printf("\n");
}

void EditGrade(){
	printf("\nThere're totally %d courses recorded:\n\n", CourseCount);
	test();
	printf("Enter a number to edit the related course grades or any other key back:");
	
	//print the course information
	scanf("%d", &choice2);
	for (int n = 1; n <= CourseCount; n++)
	{
		if (choice2 == n)
		{
			printf("        %s%s\n", course[n - 1].code, course[n - 1].name);
			printf("        -----------------------------------\n");
			printf("        | No.    | Item                | Percentage     | Full Mark    | Grades\n");
			int i = 0;
			for (i = 3 * (n - 1); i < 3 * n; i++)
			{
				printf("        | %d      | %-20s| %-15f| %-15f        \n", i - 3 * (n - 1) + 1, course[i].evaluation_name, course[i].evaluation_percentage, course[i].evaluation_fullmark);
			}
			FILE *fpgrade;
			fpgrade=fopen("Gradeinformation.txt","r");
			if (fpgrade!=NULL)//有点疑问 不知道打印空的结构体会不会造成bug
			{
				for (int i = 0; i < count; i++)
			{
			printf(" %d: %.2f",GradeRecord[i].numGrade,GradeRecord[i].ActualGrade);
			}
			printf("\n        -----------------------------------\n");
	
			}else{
			printf("\n        -----------------------------------\n");
			}
		}		
	}
	
	printf("Enter the No. of an Item whose grades to be edited or any other key back: ");
	scanf("%d",&choice3);
	SingleCourseDetail(choice3,choice2);
	printf("\n        -----------------------------------\n");

	while (1)
	{
		printf("\n============== Edit Grade ==============\n");
		printf("\t1. Add Grade\n");
		printf("\t2. Delete Grade\n");
		printf("\t3. Delete All Grade\n");
		printf("\t4. Modify Grade\n");
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
		case 1: // Add Grade
			AddGrade();
			break;
		case 2: // Delete Grade
			DeleteGrade();
			break;
		case 3: // Delete All Grade
			DeleteAllGrades();
			break;
		case 4: // Modify Grade
			ModifyGrade();
			break;
		default:
			break;
		}
	}

}