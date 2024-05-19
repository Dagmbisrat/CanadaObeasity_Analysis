#include <stdio.h>
#include <string.h>
#include <stdlib.h>


enum Provinces {ONTARIO, QUEBEC, BC, ALBERTA, CANADA_ET};
enum agegroup {AGE_35to49years , AGE_50to64years , AGE_65yearsandover};
enum gender{MALE,FEMALE};

//creating an object to make ansering qestions and storeing data easier
typedef struct Diabetes{

	int GEO;
	int age_group;
	int sex;
	int REF_DATE;
	double VALUE;

}Diabetes;

//function that helps print the province data
char* printPROV(int GEO){

	if(GEO == ONTARIO)
		return "Ontario";
	if(GEO == QUEBEC)
		return "Quebec";
	if(GEO == BC)
		return "British Columbia";
	if(GEO == ALBERTA)
		return "Alberta";
	if(GEO == CANADA_ET)
		return "Canada excluding territories";
	else
		return "no name";
}
//function that helps print the age group data
char* printAgegroup(int ages){

	if(ages == AGE_35to49years)
		return "35-49";
	if(ages == AGE_50to64years)
		return "60-64";
	if(ages == AGE_65yearsandover)
		return "65+";
	else
		return "N/A";

}
//function that helps print the object for trobleshooting
void printd(Diabetes a){


	printf("Name: %s", printPROV(a.GEO));
	printf("  AGE Group: %s", printAgegroup(a.age_group));
	printf("  sex: %d", a.sex);
	printf("  ref date: %d", a.REF_DATE);
	printf("  percent: %.2lf  \n", a.VALUE);


}
//function that helps remove the last and first commas when reading from csv file
char* remove_first_last_chars(char* str) {


    if (str == NULL) {
        return "null"; // Empty string if input is too short
    }
    str[strlen(str)-1] = '\0'; // Set last character to null terminator
    return &str[1]; // Return pointer to second character
}
//function that organizes and saves all important data from the csv file
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
				if(str != NULL){
					if(!strcmp("Ontario",str))
						Can_Data[i].GEO = ONTARIO;
					if(!strcmp("Quebec",str))
						Can_Data[i].GEO = QUEBEC;
					if(!strcmp("British Columbia",str))
						Can_Data[i].GEO = BC;
					if(!strcmp("Alberta",str))
						Can_Data[i].GEO = ALBERTA;
					if(!strcmp("Canada (excluding territories)",str))
						Can_Data[i].GEO = CANADA_ET;
				}
				if(!strcmp("null",str))
					Can_Data[i].GEO = -1;



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
				//printf("%d :",i+1);
				//printd(Can_Data[i]);
			}

			i++;


		}

		// Close the file
		fclose(Data);
		//printf("%d :",i);
		}

}
//function that answers question 1a)
void Provincial_averages(Diabetes Can_Data[],double PROV_AVE[]){


	//finding the ave for Eatch province

	for(int k = 0; k < 5; k++ ){

		int j = 0;

		for(int i = 0; i < 212; i++){

			if(Can_Data[i].GEO == ONTARIO+k && Can_Data[i].VALUE ){

				PROV_AVE[k] +=  Can_Data[i].VALUE;
				j++;

			}
		}
		PROV_AVE[k] = PROV_AVE[k]/j;
		printf("The Average Diabetes percentge for %s(for all years and age groups) is: %.2lf%%  \n\n",printPROV(k), PROV_AVE[k]);


	}



}
//function that answers question 1b) and c)
void Provincial_averages_peryear(Diabetes Can_Data[], double PROV_AVE_peryear[5][7] ){


	//finding the ave for each province for every year

	for(int k = 0; k < 5; k++ ){

		for(int n = 0; n < 7; n++){

			int j = 0;

			for(int i = 0; i < 212; i++){

				if(Can_Data[i].GEO == ONTARIO+k && Can_Data[i].REF_DATE == 2015+n && Can_Data[i].VALUE ){

					PROV_AVE_peryear[k][n] +=  Can_Data[i].VALUE;
					j++;

				}
			}
			PROV_AVE_peryear[k][n] = PROV_AVE_peryear[k][n]/j;
			printf("The Average Diabetes percentge for %s(for the year %d) is: %.2lf%%  \n\n",printPROV(k),2015+n, PROV_AVE_peryear[k][n]);



		}
		printf("\n");

	}



}
//function that answers question 1d)
void Provincial_averages_perAGE(Diabetes Can_Data[], double PROV_AVE_perAGE[5][3] ){



	//finding the ave for Eatch province for every age group

	for(int k = 0; k < 3; k++ ){

		for(int n = 0; n < 5; n++){

			int j = 0;

			for(int i = 0; i < 212; i++){

				if(Can_Data[i].GEO == ONTARIO+n && Can_Data[i].age_group == AGE_35to49years+k && Can_Data[i].VALUE ){

					PROV_AVE_perAGE[n][k] +=  Can_Data[i].VALUE;
					j++;

				}
			}
			PROV_AVE_perAGE[n][k] = PROV_AVE_perAGE[n][k]/j;
			printf("The Average Diabetes percentge for %s(for age groups: %s) is: %.2lf%%  \n\n",printPROV(n),printAgegroup(k), PROV_AVE_perAGE[n][k]);



		}
		printf("\n");

	}



}
//answers question 2)
void LargestandSmallest(double arr[]) {

    // Finds the largest and smallest numbers in an array of doubles.
    double smallest[] = {arr[0],0};
    double largest[] = {arr[0],0};
    int i;

    for (i = 1; i < 4; i++) {
        if (arr[i] < smallest[0] ) {
            smallest[0] = arr[i];
            smallest[1] = i;

        } else if (arr[i] > largest[0]) {
            largest[0] = arr[i];
            largest[1] = i;
        }
    }
    printf("The province with the largest Diabetes population is %s with a percentage of %.2lf%%\n",printPROV(largest[1]),largest[0]);
    printf("The province with the Smallest Diabetes population is %s with a percentage of %.2lf%%\n\n",printPROV(smallest[1]),smallest[0]);

}
//answers question 3)
void Higerorlower(double arr[]){

	for(int i = 0; i<4; i++){

		if(arr[i] < arr[4])
			printf("The privince %s has a smaller dibeates population(%.2lf%%) than the provintial average at %.2lf%%\n",printPROV(i),arr[i],arr[4]);
		if(arr[i] > arr[4])
			printf("The privince %s has a Larger dibeates population(%.2lf%%) than the provintial average at %.2lf%%\n",printPROV(i),arr[i],arr[4]);

	}
	printf("\n");
}
//answers qestion 4)
void LargestandSmallestforallyears(double arr[5][7]){

	double min_val = 100.0;
    double max_val = 0.0;
	int min_row ;
    int min_col ;
    int max_row ;
    int max_col ;

    //ittirate through the whole data and find the higest percentage at the year and province

	   for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 7; j++) {
            if (arr[i][j] < min_val) {
                min_val = arr[i][j];
                min_row = i;
                min_col = j;
            } else if (arr[i][j] > max_val) {
                max_val = arr[i][j];
                max_row = i;
                max_col = j;
            }
        }
    }

    printf("In the province of %s in %d had the largest Diabetes polulation at %.2lf%%\n",printPROV(max_row),2015+max_col,max_val);
    printf("In the province of %s in %d  had the smallest Diabetes population at %.2lf%%\n",printPROV(min_row),2015+min_col,min_val);

    // check for ties and print all numbers at which they are tied with
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 7; j++) {
            if (arr[i][j] == min_val && (i != min_row || j != min_col)) {
                printf("Also tied with the largest we have the province of %s in %d with a Diabetes population at %.2lf%%\n",printPROV(max_row),2015+max_col,max_val);
            } else if (arr[i][j] == max_val && (i != max_row || j != max_col)) {
                printf("Also tied with the Smallest we have the province of %s in %d with a Diabetes population at %.2lf%%\n",printPROV(min_row),2015+min_col,min_val);
            }
        }
    }

	printf("\n");
}
//function that answers question 5 and 6(graph scripts)
void grpahs(char* PROV_FILES[], char* AGEGroup_FILES, double PROV_AVE_2015to2021[5][7], double PROV_AVE_perAGE[5][3], FILE* fp, FILE* gnupipe){



	// answering #5

	// go through each province and open a new file, then write in that file the data year and the avrage for that year for all 7 years
	for(int i = 0; i < 5;i++){

		fp = fopen(PROV_FILES[i],"w");
		gnupipe = popen("gnuplot -persitent","w");

		for(int j = 0;j < 7;j++){

			fprintf(fp,"%d  %lf\n",2015+j,PROV_AVE_2015to2021[i][j]);


		}


	}

	//plot all the files in one graph
	fprintf(gnupipe,"plot %s w lp title \"ONT\" ,%s w lp title \"QUE\",%s w lp title \"BC\",%s w lp title \"AL\",%s w lp title \"CAD ET\" lw 6 dt 3 lc 7 \n",PROV_FILES[0],PROV_FILES[1],PROV_FILES[2],PROV_FILES[3],PROV_FILES[4]);
	fprintf(gnupipe,"set title \"ALL Provinces Diabetes percentages\" font ',15'\n");
	fprintf(gnupipe,"set xlabel \"Time(years)\" font ',13'\n");
	fprintf(gnupipe,"set ylabel \" Diabetes percentages(%%)\" font ',13'\n");
	fprintf(gnupipe,"set grid\n");
	fprintf(gnupipe,"replot\n");



	//answering #6
	//write the avrage percentages for each age groups in canada(excluding terittores)
	fp = fopen(AGEGroup_FILES,"w");
	gnupipe = popen("gnuplot -persitent","w");


	for(int i = 0;i < 3;i++){

			fprintf(fp,"%lf  ",PROV_AVE_perAGE[4][i]);

		}
	fprintf(gnupipe,"set style data histogram\n");
	fprintf(gnupipe,"set style histogram cluster gap 1\n");
	fprintf(gnupipe,"plot %s using 1:xtic(1) title \"Ages 35-49\" lc \"red\", %s using 2 title \"Ages 50-64\" lc \"blue\",%s using 3 title \"Ages 65+\" lc \"green\" \n",AGEGroup_FILES,AGEGroup_FILES,AGEGroup_FILES );
	fprintf(gnupipe,"set xlabel \"Canadas Age groups\" font ',13' \n");
	fprintf(gnupipe,"set ylabel \" Diabetes percentages(%%)\"  font ',13' \n");
	fprintf(gnupipe,"set title \"Canadas (excluding territories) Diabetes perentages for all age groups\" font ',15'\n");
	fprintf(gnupipe,"unset xtics\n");
	fprintf(gnupipe,"set grid\n");
	fprintf(gnupipe,"replot\n");

}



int main()
{
	//array off all the rows in the data
	Diabetes Can_Data[212];

	double PROV_AVE[5];
	double PROV_AVE_2015to2021[5][7];
	double PROV_AVE_perAGE[5][3];

	//file name and save all the rows of data into can data array
	char Data[] = {"statscan_diabetes.csv"};
	Organize_data(Data,Can_Data);

	//find all the Provincial averages for all years
	Provincial_averages(Can_Data,PROV_AVE);

	//find all the Provincial averages for eac year
	Provincial_averages_peryear(Can_Data, PROV_AVE_2015to2021);

	//find all the Provincial averages for each age
	Provincial_averages_perAGE(Can_Data,PROV_AVE_perAGE);

	//find  the Largest and Smallest Provincial averages 
	LargestandSmallest(PROV_AVE);

	//find if each Provincial avrages are higher than the total  Provincial average
	Higerorlower(PROV_AVE);

	//find largest and smallest yearly Provincial average 
	LargestandSmallestforallyears(PROV_AVE_2015to2021);


	//graph 

	FILE* fp = NULL;
	FILE* gnupipe = NULL;

	char* PROV_FILES[] = {"'ON_Data.tmp'","'QE_Data.tmp'","'BC_Data.tmp'","'AL_Data.tmp'","'Can_Data.tmp'"};
	char* AGEGroup_FILES = {"'Age_group_data.tmp'"};

	grpahs(PROV_FILES, AGEGroup_FILES, PROV_AVE_2015to2021, PROV_AVE_perAGE, fp, gnupipe);



	return 0;
}
