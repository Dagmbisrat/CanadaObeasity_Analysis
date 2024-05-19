#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum agegroup {AGE_35to49years , AGE_50to64years , AGE_65yearsandover};
enum gender{MALE,FEMALE};

typedef struct Diabetes{
	
	char GEO[500];
	int age_group;
	int sex;
	int REF_DATE;
	double VALUE;
	
}Diabetes;

//function that helps print the data
void printd(Diabetes a){
	
	if(strlen(a.GEO) > 0){
		printf("\nGEO: ");
		puts(a.GEO);
		printf(" ");
	}
	else{
		printf("GEO: ");
		printf("NoName  ");
	}
	
	printf("  AGE Group: %d", a.age_group);
	printf("  sex: %d", a.sex);
	printf("  ref date: %d", a.REF_DATE);
	printf("  percent: %.2lf  \n", a.VALUE);
	
	
}
char* remove_first_last_chars(char* str) {
	
   
    if (str == NULL) {
        return "null"; // Empty string if input is too short
    }
    str[strlen(str)-1] = '\0'; // Set last character to null terminator
    return &str[1]; // Return pointer to second character
}

void Organize_data(char File_name[],Diabetes Can_Data[]){
	
	
	
	//open file
	FILE* Data = fopen(File_name, "r");
    //if file isnt found
    if (!Data)
        printf("Can't open file\n"); 
         
    else {
		
		//set the buffer and the start of the row/string element
		char buffer[1024];
        int i = -1;
        
 
        while (fgets(buffer,1024, Data)) {
			
			if(i >=0 ){
				//get the first col of the row and save it as the ref date also removin the " from the string
				char* str = remove_first_last_chars(strtok(buffer, ","));
				Can_Data[i].REF_DATE = atoi(str);
			
				//get the second col of the row and save it as the ref date
				str = remove_first_last_chars(strtok(NULL, ","));
				if(str != NULL)
					 strcpy(Can_Data[i].GEO ,str);
				
				//disregard the third col
				strtok(NULL, ",");
				
				//get the forth col of the row and save it as the age group (0 if 35-49 1 if 50-64 2 if 65+)
				str = remove_first_last_chars(strtok(NULL, ","));
				if(atoi(str) == 35)
					Can_Data[i].age_group = AGE_35to49years;
				if(atoi(str) == 50)
					Can_Data[i].age_group = AGE_50to64years;
				if(atoi(str) == 65)
					Can_Data[i].age_group = AGE_65yearsandover;
				else if(atoi(str) == 0)
					Can_Data[i].age_group = -1;
					
				//get the fivth col of the row and save it as the sex(0 if its a male and 1 if female)
				str = remove_first_last_chars(strtok(NULL, ","));
				if(!strcmp(str, "Males") )
					Can_Data[i].sex = MALE;
				if(!strcmp(str, "Females") )
					Can_Data[i].sex = FEMALE;
				else if(strcmp(str, "Males") && strcmp(str, "Females") )
					Can_Data[i].sex = -1;
				
				
				//disregard the 6 - 13 col
				for(int i = 0; i < 8;i++)
					strtok(NULL, ",");
					
				//get the 14th col of the row and save it as the percent
				str = remove_first_last_chars(strtok(NULL, ","));
				Can_Data[i].VALUE = atof(str);
				
				//print***
				printf("%d :",i+1);
				printd(Can_Data[i]);
			}
			
			i++;	
			
			
		}
		
		// Close the file
		fclose(Data);
		//printf("%d :",i);
		}
	
}


double Provincial_averages();


int main()
{
	Diabetes Can_Data[210];
	char Data[] = {"statscan_diabetes.csv"};
	
	Organize_data(Data,Can_Data);
	
																							
	
	
	double ONT_AVE = 0;
	double QUE_AVE = 0;
	double BC_AVE = 0;
	double AL_AVE = 0;
	double CAN_AVE = 0;
	
	double ONT_AVE_2015to2021[7];
	double QUE_AVE_2015to2021[7];
	double BC_AVE_2015to2021[7];
	double AL_AVE_2015to2021[7];
	double CAN_AVE_2015to2021[7];
	
	int j = 0;
																												//Answer to Qestion 1a)
																												
	printf("\nANSWER TO QUESTION 1A)\n");
	//finding the ave for Ontario
	for(int i = 0; i < 210; i++){
		
		if(!strcmp(Can_Data[i].GEO,"Ontario") && Can_Data[i].VALUE ){
			
			ONT_AVE +=  Can_Data[i].VALUE;
			j++;
			
		}
	}
	ONT_AVE = ONT_AVE/j;
	printf("The Average Diabetes percentge for Ontario(for all years and age groups) is: %.2lf%%  \n\n", ONT_AVE);
	
	
	//finding the ave for Quebec
	j = 0;
	for(int i = 0; i < 210; i++){
		
		if(!strcmp(Can_Data[i].GEO,"Quebec") && Can_Data[i].VALUE ){
			
			QUE_AVE +=  Can_Data[i].VALUE;
			j++;
			
		}
	}
	
	QUE_AVE = QUE_AVE/j;
	printf("The Average Diabetes percentge for Quebec(for all years and age groups) is: %.2lf%%  \n\n",QUE_AVE);
	
	
	
	//finding the ave for British Columbia
	j = 0;
	for(int i = 0; i < 210; i++){
		
		if(!strcmp(Can_Data[i].GEO,"British Columbia") && Can_Data[i].VALUE ){
			
			BC_AVE +=  Can_Data[i].VALUE;
			j++;
			
		}
	}
	
	BC_AVE = BC_AVE/j;
	printf("The Average Diabetes percentge for British Columbia(for all years and age groups) is: %.2f%% \n\n", BC_AVE);
	
	
	//finding the ave for Alberta
	j = 0;
	for(int i = 0; i < 210; i++){
		
		if(!strcmp(Can_Data[i].GEO,"Alberta") && Can_Data[i].VALUE ){
			
			AL_AVE +=  Can_Data[i].VALUE;
			j++;
			
		}
	}
	
	AL_AVE = AL_AVE/j;
	printf("The Average Diabetes percentge for Alberta(for all years and age groups) is: %.2f%% \n\n", AL_AVE);
	
																															//Answer to Qestion 1b)
	printf("\nANSWER TO QUESTION 1B)\n");
	
	//finding the ave for Canada
	j = 0;
	for(int i = 0; i < 210; i++){
		
		if(!strcmp(Can_Data[i].GEO,"Canada (excluding territories)") && Can_Data[i].VALUE ){
			
			CAN_AVE +=  Can_Data[i].VALUE;
			j++;
			
		}
	}
	
	CAN_AVE = CAN_AVE/j;
	printf("The Average Diabetes percentge for Canada(for all years and age groups) is: %.2f%% \n\n", CAN_AVE);
	
																														//Answer tp Question 1c)
																														
	printf("\nANSWER TO QUESTION 1C)\n");
	
	//finding the ave for Ontario from 2015 - 2021
	for(int k = 0; k < 7; k++){
		
			j = 0;
			for(int i = 0; i < 210; i++){
		
				if(!strcmp(Can_Data[i].GEO,"Ontario") && Can_Data[i].REF_DATE == 2015+k && Can_Data[i].VALUE ){
			
					ONT_AVE_2015to2021[k] +=  Can_Data[i].VALUE;
					j++;
			
				}
			}
			ONT_AVE_2015to2021[k] = ONT_AVE_2015to2021[k]/j;
			printf("The Average Diabetes percentge for Ontario(for %d) is: %.2lf%%  \n\n", 2015+k, ONT_AVE_2015to2021[k]);	
		
	}
	printf("\n");
	
	//finding the ave for Quebec from 2015 - 2021
	for(int k = 0; k < 7; k++){
		
			j = 0;
			for(int i = 0; i < 210; i++){
		
				if(!strcmp(Can_Data[i].GEO,"Quebec") && Can_Data[i].REF_DATE == 2015+k && Can_Data[i].VALUE ){
			
					QUE_AVE_2015to2021[k] +=  Can_Data[i].VALUE;
					j++;
			
				}
			}
			QUE_AVE_2015to2021[k] = QUE_AVE_2015to2021[k]/j;
			printf("The Average Diabetes percentge for Quebec(for %d) is: %.2lf%%  \n\n", 2015+k, QUE_AVE_2015to2021[k]);	
		
	}
	printf("\n");
	
	//finding the ave for British Columbia from 2015 - 2021
	for(int k = 0; k < 7; k++){
		
			j = 0;
			for(int i = 0; i < 210; i++){
		
				if(!strcmp(Can_Data[i].GEO,"British Columbia") && Can_Data[i].REF_DATE == 2015+k && Can_Data[i].VALUE ){
			
					BC_AVE_2015to2021[k] +=  Can_Data[i].VALUE;
					j++;
			
				}
			}
			BC_AVE_2015to2021[k] = BC_AVE_2015to2021[k]/j;
			printf("The Average Diabetes percentge for British Columbia(for %d) is: %.2lf%%  \n\n", 2015+k, BC_AVE_2015to2021[k]);	
		
	}
	printf("\n");	
	
	//finding the ave for Alberta from 2015 - 2021
	for(int k = 0; k < 7; k++){
		
			j = 0;
			for(int i = 0; i < 210; i++){
		
				if(!strcmp(Can_Data[i].GEO,"Alberta") && Can_Data[i].REF_DATE == 2015+k && Can_Data[i].VALUE ){
			
					AL_AVE_2015to2021[k] +=  Can_Data[i].VALUE;
					j++;
			
				}
			}
			AL_AVE_2015to2021[k] = AL_AVE_2015to2021[k]/j;
			printf("The Average Diabetes percentge for Alberta(for %d) is: %.2lf%%  \n\n", 2015+k, AL_AVE_2015to2021[k]);	
		
	}
	printf("\n");	
	
	//finding the ave for Canada from 2015 - 2021
	for(int k = 0; k < 7; k++){
		
			j = 0;
			for(int i = 0; i < 210; i++){
		
				if(!strcmp(Can_Data[i].GEO,"Canada (excluding territories)") && Can_Data[i].REF_DATE == 2015+k && Can_Data[i].VALUE ){
			
					CAN_AVE_2015to2021[k] +=  Can_Data[i].VALUE;
					j++;
			
				}
			}
			CAN_AVE_2015to2021[k] = CAN_AVE_2015to2021[k]/j;
			printf("The Average Diabetes percentge for Canada(for %d) is: %.2lf%%  \n\n", 2015+k, CAN_AVE_2015to2021[k]);	
		
	}
	printf("\n");																											
	
																																		//Answer to Question 2)
	
	
	
	
	return 0;
}

