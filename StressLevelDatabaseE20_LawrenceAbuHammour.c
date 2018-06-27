#include <stdio.h> /*printf and scanf definitions*/
#include <strings.h> /*String Function Library*/
#include <string.h> /*Strings Function Library*/
#define MAX 100 /*Define a MAX Value*/
#define MAX2 200 /*Define a second MAX value*/

/*Define new type of structure*/
typedef struct Stress{
	char lastname[MAX];
	char firstname[MAX2];
	char gender[10];
	int age;
	float level;
}stress_t;
/*Function Prototypes*/
int ReadFile(stress_t database[], int size); 
void DisplayRecord(int size, stress_t database[], int sort[]);
int SearchRecord(int size, const stress_t database[], char lastname[]); 
void DisplayMenu(void); 
int SearchRecord2(int size, const stress_t database[], float level); 
void Option(void); 
void sortArray(int size, const stress_t database[], int sort[]); 
void sortArray2(int size, const stress_t database[], int sort[]); 
int deleteRecord(int *size, stress_t database[], char lastname2[], int sort[]); 
int addRecord(int *size, stress_t database[], int sort[]);
int SaveRecord(int size, stress_t database[], int sort[]);

int main(void) 
{
	FILE *ifile; /*Define main file you are working with*/
	char input; /*Define char input*/
	int i, input2, option; /*Define integer variables for use*/
	stress_t database[MAX]; /*Define database as typedef struct*/
	int size; /*Define size variable of array*/
	char filename2[MAX]; /*Define character string for user entry of filename*/
	char lastname2[MAX]; /*Define character string for user entry of last name*/
	float level; /*Define float of stress level*/
	int sort[MAX]; /*Define sort array*/
	char junk, junk2; /*Define junk variables*/
	
	size=30;/*Define initial size of array*/
	
	/*Initialize Sort Array using for loop*/
	for(i=0; i<size; i++) {
    	sort[i]=i;
		}
	/*Display Menu*/	
	DisplayMenu();
	printf("\n");  
	/*Prompt user to enter a filename or press enter*/
	printf("Enter f to enter a filename or press enter to default the initial file used>");
	scanf("%c", &input); 
	/*If statement for user input if they press f to account for capital and lowercase f*/
	if(input=='f'||input=='F'){
	/*Prompt the user to enter the name of the file*/
	printf("Enter the name of the file>");
	scanf("%s", filename2);
	/*Open file that user entered*/
	ifile=fopen(filename2, "r");
		/*If Statement for if file exists*/
    	if(ifile==NULL){
   		 printf("No such file exists! Try again!\n");
			return(-1);
	}
	/*Call Read File Function to scan file data into database struct array*/
	ReadFile(database, size); 
	/*Default for user to enter*/
	}else if(input=='\n'){
		ReadFile(database, size);
	}else{ /*Account for if user enters an invalid input*/
		printf("That was an invalid input! Try again!\n");
		return(-1);
		}
	printf("\n");
	/*Display Options for user to enter*/
	Option();
	/*While Loop for Menu Options*/
	while(1) {
		/*Get the User's Choice of Input*/
		printf("\nEnter the option you would like to choose>"); 
		scanf("%d", &option); 
	/*If Statement for user option*/
	if(option==7) {
		/*Gives users two option for searching*/
		printf("\n"); 
		printf("Enter 89 to search by last name or enter 15 to search all records greater than a certain stress level.\n"); 
		scanf("%d", &input2); 
		/*If Statement for when user chooses either to search by last name or stress level*/
		if(input2==89) {
		printf("Enter the last name you would like to search for>");
		scanf("%s", lastname2);
		/*If User chooses 89, call SearchRecord function*/
		SearchRecord(size, database, lastname2);
		/*If User chooses 15, call SearchRecord2 function*/
		}else if(input2==15) {
		printf("\nEnter the level to display all levels greater than that level: "); 
		scanf("%f", &level); 
		/*If User chooses 15, call SearchRecord2 function*/
		SearchRecord2(size, database, level);
		}else{
			printf("That is not a valid input!");
		}/*If User Chooses 0, quit the database*/
	}else if(option==0){
		printf("Thank you for visiting the database! Come again!\n");
		return(0);
	/*If User Types in 8, call sortArray function to sort in alphabetical order*/
	}else if(option==8){
		sortArray(size, database, sort);
		}
	/*If User Types in 9, call sortArray2 function to sort by a level that the user defines*/
	else if(option==9){
		sortArray2(size, database, sort); 
	/*If User Types in 10, call addRecord function to add a record to the database*/	
	}else if(option==10){
		addRecord(&size, database, sort); 
	/*If User Types in 11, call deleteRecord function to delete a record from the database*/
	}else if(option==11){
		deleteRecord(&size, database, lastname2, sort);
	/*If User Types in 12, call SaveRecord function to save the file as is*/
	}else if(option==12){
		SaveRecord(size, database, sort);
	/*If User Types in 13, call DisplayRecord function to display the records as is*/
	}else if(option==13){
		DisplayRecord(size, database, sort);
	/*If User Types in a number that does not call a function or option, inform them and terminate the program*/
	}else{
	printf("Invalid Input!Run the program again!\n");
	return(0);
	}
	printf("\n");
	/*Every time the user enters something, makes sure that the user knows his/her options*/
	Option();	
	}
	return(0);
}
/*Function Definition for Displaying the Information about the data in the database*/
void DisplayMenu(void){
	printf("\n*************|Welcome to the Stress Levels of College Students Database!|**************\n"); 
	printf("\n"); 
	printf("A study was performed by a Dartmouth student where he measured the stress level of his friends between the ages of 17 and 25\n");
	printf("and it was compared with their gender, age, and a value on a 1-10 scale determined through experiment with blood pressure, stress level, and heart rate.\n");
	printf("This data serves as a reference to show correlation between how stressed someone is and other factors. This database does not take into account other options\n");
	printf("except for age, gender, stress level, last name, and first name.");
	printf("\n");
	printf("\nWith this data, you may search for a particular record, sort the record by last name or by age, add a record to the database,\n");
	printf("delete a record from the data base,save the file after performing various operations, display the data, or quit the database.");
	printf("\n"); 
}
/*Function Definition for Displaying the Options that the user has to choose from*/
void Option(void){
	printf("Here are your menu options!\n");
	printf("\n");
	printf("Option 1: Enter 7 to Search for a Record\n"); 
	printf("Option 2: Enter 8 to Sort the Records in Alphabetical Order\n"); 
	printf("Option 3: Enter 9 to Sort the Records by Stress Level in Ascending Order\n"); 
	printf("Option 4: Enter 10 to Add a Record to the Database\n"); 
	printf("Option 5: Enter 11 to Delete a Record from the Database\n"); 
	printf("Option 6: Enter 12 to Save the File as is\n");
	printf("Option 7: Enter 13 to Display Records\n");
	printf("Option 8: Enter 0 to Quit\n"); 
}
/*Function Definition to Read the File and Scan data into database array*/
int ReadFile(stress_t database[],int size){
	FILE *ifile; /*Defin file to be worked with*/
	int i=0; /*Initialize i (Element) to 0*/ 
	char junk2; /*Define junk character to account for character input*/
	/*Open file for reading*/
	ifile=fopen("StressLevelsOfMyFriends.txt", "r"); 
	/*If Statement for if file exists or not*/
		if (ifile==NULL) {
    		printf("File not found!\n");
    		return(-1);
		/*If size of array ever passes max, inform the user*/
    	}else if(size>=MAX){
			printf("There is no space left in the memory! Try again!");
		}
		i=0;
		/*While Loop for scanning file. To account for commas, the %[^] format was used which was gotten at TA sessions by Brett.*/
		while(fscanf(ifile, "%[^,],%[^,], %[^,], %d, %f%c%c", database[i].lastname,database[i].firstname, database[i].gender, &database[i].age,&database[i].level, &junk2, &junk2) !=EOF){
				i++; 
		} 
		/*Close the file*/
		fclose(ifile); 
}
 /*Function Define to display the records*/
void DisplayRecord(int size, stress_t database[], int sort[])
{		/*Define i as the element in the array/counter*/
		int i; 
		/*For Loop to continously display the names to the screen*/
		for(i=0; i<size; i++) {
		printf("\n");
		printf("%s ", database[sort[i]].lastname); 
		printf("%s ", database[sort[i]].firstname);
		printf("%s ", database[sort[i]].gender); 
		printf("%d ", database[sort[i]].age); 
		printf("%.2f ", database[sort[i]].level);  
		printf("\n"); 
		} 
	
} 
/*Function Definition to search for a particular record in the database*/
int SearchRecord(int size, const stress_t database[], char lastname2[]){	
	int i, found, dummy; /*Define integer variables to be used in function*/
    i = -1; /*Initialize i to some value*/
    found = 0; /*Initialize found to 0 to accurately search*/
    
	/*Set return value of strcmp of user last name entry and actual database string equal to a dummy variable*/
	dummy = strcmp(database[i].lastname, lastname2);
	/*While Loop for searching through the database for the name*/
    while((found==0) && (i < size-1)){
        i++; /*Counter*/
    /*If Statement for checking if strcmp finds the record the user is searching for*/ 
		if(strcmp(database[i].lastname, lastname2)==0){
            found++; /*Increase found by one every time*/
		/*Display the record the user is searching for*/
        printf("\n");
		printf("|||||||");
        printf("%s ", database[i].lastname); 
		printf("%s ", database[i].firstname);
		printf("%s ", database[i].gender); 
		printf("%d ", database[i].age); 
		printf("%.2f ", database[i].level);  
		printf("|||||||");
		printf("\n"); 
		}
        }
	/*If Statement for if the record was not found and to inform the user*/
    if(found == 0) {
     i = -1; 
     printf("That record does not exist! Try again!\n"); 
     }
    return(i);
}
/*Function Definitions for search the database by records greater than a user defined number*/
int SearchRecord2(int size, const stress_t database[], float level){
	int i, found; /*Define integer variables for use in function*/
    i = -1; /*Initialize i*/
    found = 0; /*Initialize found before searching*/
    /*While Loop for searching*/
    while((!found) && (i < size-1)){
        i++;
		/*Comparing the user entry and the levels in the database and checking if the level is greater than 0*/
        if(database[i].level>=level && level>=0.00){
            found++;
            found=0; 
			printf("\n");
			printf("%s ", database[i].lastname); 
			printf("%s ", database[i].firstname);
			printf("%s ", database[i].gender); 
			printf("%d ", database[i].age); 
			printf("%.2f", database[i].level);  
			printf("\n"); 		
		}
		}
		/*If Level is greater than 10, inform user that no record will exist*/
		if(level>10) {
			printf("\nThe scale for this data is on a 1-10 scale. Thus, there is no person with a stress level greater than 10. Try again!\n");  
		}/*If Level is negative, inform user that it is invalid*/
		else if(level<0.00) {
		printf("That stress level is invalid. Try again!\n"); 
		}
    
		return(i);	
}
/*Function Definition for sorting the array in alphabetical order*/
void sortArray(int size, const stress_t database[], int sort[]){
    int i, j; /*Define integer variables for counter*/
    int dummy3; /*Define dummy variable*/
	dummy3=0; /*Initialize dummy variable to 0*/
    /*Implementing Bubble Sort Algorithm with sort array*/
    for(j = 0; j < size; j++){
        for(i = 0; i <= size-2; i++){  
            if(strcmp(database[sort[i]].lastname,database[sort[i+1]].lastname) > 0){
                dummy3 = sort[i];
                sort[i] = sort[i+1];
                sort[i+1] = dummy3;
				}
			}
		}
	printf("\n");
	printf("The records have been sorted in alphabetical order. Enter 13 if you would like to view your sorted data.");
}
/*Function Definition for sorting the array by stress level in ascending order*/
void sortArray2(int size, const stress_t database[], int sort[]){
	int i; /*Define integer variables to be used in function*/
	int j;
	int dummy4;
	/*Initialize defined variables to 0*/
	i=0;
	j=0;
	dummy4=0;
         
    /*Implementing Bubble Sort Algorithm with sort array*/
	for(j=0;j<size-1; j++)   	
         {
		for(i=0;i<size-1;i++)
		{
			if (database[sort[i]].level>database[sort[i+1]].level)
			{
			    dummy4=sort[i+1];
			    sort[i+1]=sort[i];
			    sort[i]=dummy4;
			}	
		}
	}
	printf("\n");
	printf("The records have been sorted by stress level in ascending order. Enter 13 if you would like to view your sorted data");
}
/*Function Definition for deleting a record from the database*/
int deleteRecord(int *size, stress_t database[], char lastname2[], int sort[]){
	
	int ret; /*Define variable for return variable*/
	int i, j; /*Define integer variables for use in function*/
	/*Prompt the user to enter a last name to delete from the database*/
	printf("Enter the last name associated with the record you want to delete>");
	scanf("%s", lastname2);
	/*Implementing the Deleting Algorithm*/
		for(i=0; i < *size; i++){
				ret=strcmp(lastname2,database[i].lastname);
				if(ret==0){
					if (i<(*size)-1){
						database[i]=database[*size-1];
					}
					/*Decrease the size of the array by 1 every time you delete a record*/
					*size=(*size)-1;
					for(j=0; j<*size; j++) {
						sort[j]=j;
					}
					return(3); 
				} 
		}/*If no such entry existed, inform the user*/
		printf("\nThere was no match! Try again!\n");
		return(0);

}
/*Function Definition for adding a record to the database*/
int addRecord(int *size, stress_t database[], int sort[]){
	/*Assigning the size of the array to the sort array*/
	sort[*size]=*size;
	/*If the size of the array is greater than the MAX value, inform the user*/
	if(*size>=MAX){
		printf("There is no space left in the memory!");
		return(-3);
	}else{
	/*Prompt the user to enter all the information to be entered into the database*/
	printf("To add a record to the data, follow the prompts.\n"); 
	
	printf("Enter the last name of the person with the stress level:"); 
	scanf("%s", database[sort[*size]].lastname); 
	
	printf("Enter the first name of the person with the stress level:");
	scanf("%s", database[sort[*size]].firstname);
	
	printf("Enter the gender of the person with the stress level:");
	scanf("%s", database[sort[*size]].gender); 
	 
	printf("Enter the age of the person with the associated stress level>");
	scanf("%d", &database[sort[*size]].age); 
	
	printf("Enter the stress level value (1-10) of the person>");
	scanf("%f", &database[sort[*size]].level); 
	
	/*Display the record that the user added to the database*/
	printf("\n");
	printf("The new record has been added\n"); 
	printf("\n");
  	printf("%s,%s,%s,%d,%.2f\n",database[sort[*size]].lastname,database[sort[*size]].firstname,database[sort[*size]].gender,database[sort[*size]].age,database[sort[*size]].level); 
	printf("----------------------------------------------------------------");
  	printf("\n");
	/*Increase the size of the array by one every time the user adds a record*/
	*size=*size+1;
  	}
}
/*Function Definition for saving the database as it is*/
int SaveRecord(int size, stress_t database[], int sort[])
{
	char input; /*Define input for user*/
	char filename [MAX]; /*Define character string filename for user to enter*/
	int i; /*Define integer variable for use in function*/
	/*Prompt the user if they would like to save or not*/
	printf("You chose to save the current data to a file. Would you like to do that? Enter an S for save and a T if not and D to cancel.>"); 
	scanf(" %c", &input); 
	/*If the user chooses to save*/
	if (input == 's'|| input == 'S')
	{	/*While Loop for user to enter a filename and save to it*/
	while(1){
		
		FILE*(ofile); 
		/*Prompt the user to enter a file name*/
		printf("Please enter a file name ending with .txt to save the file into>"); 
		scanf(" %s", filename); 
		/*Open that file for reading*/
		ofile=fopen(filename, "r");
		/*If Statement for if the file does exist*/
		if(ofile != NULL) 
		{	/*If a file already exists, ask the user if they would like to overwrite that file*/
			printf("That file exists. Would you like to overwrite? Type S for yes and T for no and D for cancel>\n"); 
			scanf(" %c", &input); 
		/*If Statement for if the user chooses to overwrite*/
		if (input == 's'|| input == 'S'){
		/*Close file*/
		fclose(ofile); 
		/*Open file for writing*/
		ofile=fopen(filename, "w");
			if(ofile == NULL)
			{/*If File does not exist, inform the user*/
				printf("Your file does not exist. Try again!.\n"); 
			} 
			/*For Loop for printing to the file*/
			for(i=0; i< size; i++)
			{	
				fprintf(ofile, "%s,%s,%s,%d,%.2f\n",  database[sort[i]].lastname, database[sort[i]].firstname, database[sort[i]].gender, database[sort[i]].age, database[sort[i]].level);  
			}
			/*Close File*/
			fclose(ofile);
			/*Exit Loop*/
			break;
		/*If Statement for if the user chooses to cancel*/
		}else if (input == 'd'|| input == 'D')
		{
			printf("Saving has been cancelled.\n"); 
			return(-3); 
		/*If the user inputs an invalid input*/
		}else{ 
			printf("Invalid input.\n"); 
		}
		
			
		}else{ 
		/*Open the file for writing*/
		ofile=fopen(filename, "w");
			if(ofile == NULL)
			{/*If Statement for if the File Does not exist, inform the user*/
				printf("Could not open the file because it doesn't exist!\n"); 
			} 
			/*For Loop for printing to the file*/
			for(i=0; i< size; i++)
			{
				fprintf(ofile, "%s,%s,%s,%d,%.2f\n",  database[sort[i]].lastname, database[sort[i]].firstname, database[sort[i]].gender, database[sort[i]].age, database[sort[i]].level);  
			}
			/*Close File*/
			fclose(ofile);
			/*Exit Loop*/
			break;
		}
	}
		/*If Statement for if the user does not want to save*/
		}else if (input == 't'|| input == 'T'){ 
			printf("\nYour file was not saved.\n");
			printf("\n");
			return(-5);
		/*If Statement for if the user cancels the save*/
		}else if(input=='d'|| input=='D'){
			printf("\nYou cancelled saving!");
			printf("\n");
		/*If Statement for if the user enters an input that does not do anything*/
		}else{
			printf("That was an invalid input"); 
		return(-6); 
}
}