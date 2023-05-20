#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


#define T_Vertical() printf("\u2502") //print verticle line
#define T_Horizontal() printf("\u2500") //print horizontal line
#define T_L() printf("\u2514") //print L shape
#define T_Box() printf("\u2591") //print box

//terminal right n times 
void T_right(int x){

	for(int i=0 ; i<x ; i++){
	
		printf(" ") ;
	}
}


//Making a struct for details of a person.This is used for the dynamic array.not for the linked list
typedef struct _{

        char name[30] ;
        int participants ;
        int time ;
	int meetings ;
}persondetail ;

//making a struct for a linked list for a details of a person
typedef struct person{

	char name[30] ;
	int participants ;
	int time ;
	int meetings ;

	struct person *next ;
}linkedPerson ;

//making a struct for the total details for the linked list
typedef struct total{

	persondetail *array ;

	int filledAmount   ;
	int maxStrSize ;
	int maxParticipants ;
	int maxTime ;
	int maxMeetings ;

	double totalTime , totalParticipants , totalMeetings ;
	
}linkedTotal ;


// LINKED   Open the file -> read the data -> get it into a linked list
linkedPerson* linkedGetFile(char fileName[] , linkedPerson *first) ;

//string compare to check hether 2 strings are equal or not
int strCompare(char str1[] , char str2[]) ;

//string copy to copy the string to another array
void strCopy(char from[] , char to[]) ;

//print the verticle bar with the information
void infoBar(char name[],int space ,int size , int number ) ;

//print the table ----option is for scaled or not. c is for the meeting or participants or time
void table(linkedTotal alpha,int size,char c,char option) ;

//to sort the array according to the meeting or time or participants and print
void sortChart(linkedTotal alpha ,int size,char c , char option) ;

//to count the number of digits 
int digits(int num) ;

//check whether its a csv file
int checkCSV(char str[]) ;

//to check whether a positive integer
int isInt(char str[]) ;


//in the main fuction we are mainly handling the errors.getting the linked list into a dinamic memory.Other things are as functions.
int main(int argc , char **argv) {

	int length =10 ;

	char option = 'm' ;
	int optionCount = 0 ;
	
	char YorN='n' ;

	int inputFiles = 0 ;


	linkedPerson *first , firstStudent  ; //firstStudent is for the easyness in the linked list.

	firstStudent.next=NULL ;
	first =&firstStudent ;

	linkedPerson *current ;
	

	linkedTotal beta ;

	beta.filledAmount = 0 ;
	beta.maxStrSize = 0 ;
	beta.maxParticipants = 0 ;
	beta.maxTime = 0 ;
	beta.maxMeetings = 0 ;
	beta.totalTime = 0 ;
	beta.totalParticipants = 0;
	beta.totalMeetings = 0 ;

	


	if(argc==0){
	
		printf("No input files were given\n") ;
		printf("usage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n",argv[0]) ;

		return 1 ;
	}

	for(int i=1 ; i<argc ; i++){
	
		if(argv[i][0]=='-'){

			if(strCompare( argv[i],"-l") ) {

				if(i==(argc-1)){

					printf("Not enough options for [-l]\n") ;
					printf("usage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n",argv[0]) ;

					return 1 ;
				
				}
				
				i++;
				length=atoi(argv[i]) ;
				
				if(length<0){
									
					printf("Invalid option(negative) for [-l]\n") ;
					printf("usage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n",argv[0]) ;
					return 1;

				}else if(isInt(argv[i])==0){
				
					printf("Invalid options for [-l]\n") ;
					printf("usage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n",argv[0]);
					
					return 1 ;

				}else if(length ==0){
				
					return 0 ;
				}else{

					for(int j=0 ; j<strlen(argv[i]);j++){
				
						if(isdigit(argv[i][j])){
					
							continue ;
						}else{
					
							printf("Invalid options for [-l]\n") ;
							printf("usage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n",argv[0]) ;
							return 1 ;
						}
					}
				}

			}else if(strCompare( argv[i],"-t") ){
				
				if(optionCount==0){
					option ='t' ;
					optionCount++ ;
				}else if(option!='t'){
				
					optionCount++ ;
				}	

			}else if(strCompare( argv[i],"-m")){
			
				if(optionCount==0){
					option = 'm' ;
					optionCount++ ;
				}else if(option!='m'){

					optionCount++ ;
				}
				

			}else if(strCompare( argv[i],"-p")){
			
				if(optionCount==0){
					option = 'p';
					optionCount++ ;
				}else if(option!='p'){
				
					optionCount++ ;
				}
				
			}else if(strCompare( argv[i],"--scaled") ){
			
				

				YorN='y' ;
				continue ;
			}else{

				printf("Invalid option [%s]\n",argv[i]) ;
				printf("usage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n",argv[0]);

				return 1 ;

			}	

		}else{
			continue ;
		}

	
	}

	if(optionCount>1){
		printf("Cannot plot multiple parameters in same graph.\n") ;
		printf("usage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n",argv[0]);

		return 1 ;
	}


	
	for(int i=1 ; i<argc ;i++ ){
	
		if(argv[i][0] != '-'){
		
			if(checkCSV(argv[i])==1){
				
				first = linkedGetFile(argv[i] , first) ;

				if(first == NULL){
					return 1;

				}

				inputFiles++ ;
	
			}else if(strCompare(argv[i-1],"-l")==1){
				
				continue ;

			}else{
			
				printf("Only .csv files should be given as inputs.\n") ;

				return 1 ;
			}
		}
	}

	if(inputFiles==0){
	
		printf("No input files were given\n") ;
		printf("usage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n",argv[0]) ;

		return 1;
	}

	for(current=first ; current->next!=NULL ;current=current->next){
	
		beta.filledAmount++ ;

		if(strlen(current->name)>beta.maxStrSize)
			beta.maxStrSize = strlen(current->name) ;

		if(beta.maxParticipants<(current->participants))
			beta.maxParticipants = (current->participants) ;

		if(beta.maxTime<(current->time))
			beta.maxTime=(current->time) ;

		if(beta.maxMeetings<(current->meetings))
			beta.maxMeetings=(current->meetings) ;


		beta.totalTime = beta.totalTime + current->time;
		beta.totalParticipants = beta.totalParticipants + current->participants;
		beta.totalMeetings = beta.totalMeetings + current->meetings;
	}

	beta.array = (persondetail*)malloc(sizeof(persondetail)*beta.filledAmount) ;


	int i =0 ;
	linkedPerson *temp ;
	for(current = first ; current->next!=NULL ;current=current->next ){

		temp=current ;
		beta.array[beta.filledAmount-i-1].participants = current->participants ;
		beta.array[beta.filledAmount-i-1].time = current->time ;
		beta.array[beta.filledAmount-i-1].meetings = current->meetings ;

		strCopy(current->name , beta.array[beta.filledAmount-i-1].name) ;


		free(temp) ;

		i++ ;

	}

	sortChart(beta,length,option,YorN) ;

	return 0 ;
}


//*************************************** DATA MANIPULATION WITH THE FILE ********************************************

// Open the file -> read the data -> get it into a linked list
// We are getting this into a linked list as one node for each person(it is created if he is exists only) and feeding it continuoesly.
 linkedPerson* linkedGetFile(char fileName[] , linkedPerson *first) {
 
	FILE *Pfile ;

	char name[30] , data[100];
	int participants , hours , minutes , seconds ;
	char *tokenD;
	int test ;
	

	linkedPerson *current ;



	 Pfile = fopen(fileName,"r") ;

	 if(Pfile==NULL){

		printf("Cannot open one or more given files\n") ;
		return NULL ;
	}else{
	
		while(fgets(data,100,Pfile)){


			tokenD=strtok(data,",") ;
			if(tokenD==NULL){
			
				printf("File/s contain wrong entries.\n") ;
				return NULL ;

			}
			strCopy(tokenD,name) ;



			tokenD=strtok(NULL,",") ;
			if(tokenD==NULL){

				printf("File/s contain wrong entries.\n") ;
				return NULL ;

			}
			participants=atoi(tokenD) ;



			tokenD=strtok(NULL,":") ;
			if(tokenD==NULL){

				hours = 0 ;

			}else{
			
				hours=atoi(tokenD) ;
				
			}

			tokenD=strtok(NULL,":") ;
			if(tokenD==NULL){
			
				minutes = 0 ;
			}else
				minutes=atoi(tokenD) ;

			tokenD=strtok(NULL,",:") ;
			if(tokenD==NULL)
				seconds=0;
			else
				seconds=atoi(tokenD) ;


			test=0 ;
			
			for(current=first ; current->next!=NULL ; current=current->next){
			
				if(strCompare(name,current->name)==1){
				
					(*current).participants = (*current).participants + participants ;
					(*current).time = (*current).time + minutes + (hours*60) +seconds/60 ;
					(*current).meetings = (*current).meetings + 1 ;
					test=1 ;

					break ;

				}
			}

			if(test==0){
			
				current = (linkedPerson*)malloc(sizeof(linkedPerson)) ;
				current->next = first ;
				first = current ;


				strCopy(name,(*current).name) ;
				(*current).participants = participants ;
				(*current).time =  minutes + (hours*60) ;
				(*current).meetings =  1 ;

			}

		}

	}

	 fclose(Pfile) ;

	 return first ;

 }

//to compair two strings
int strCompare(char str1[] , char str2[] ) {

		if(strcmp(str1,str2)==0){
		
			return 1;
		}else{
		
			return 0;
		}

	
}

//to copy a string
void strCopy(char from[] , char to[]) {

	
	strcpy(to,from) ;
}

//*************************************************GRAPHICS MANIPULATION************************************************


//to print a bar with the respective information of a person
void infoBar(char name[],int space ,int size ,int number ){ //space->space after the name..number-> number at the end..size->length to print.


	T_right(space+strlen(name)+1) ;
	T_Vertical();

	for(int i=0 ; i<size ; i++)
		T_Box();

	printf("\n") ;


	printf(" %s",name) ;
	T_right(space) ;
	T_Vertical();

	for(int i=0 ; i<size ; i++)
		T_Box();

	printf("%d\n",number) ;


	T_right(space+strlen(name)+1) ;
	T_Vertical();

	for(int i=0 ; i<size ; i++)
		T_Box();

	printf("\n") ;


	T_right(space+strlen(name)+1) ;
	T_Vertical();
	printf("\n") ;



} 

//to print the graph as we want.
void table(linkedTotal alpha,int size,char c,char option) { //option is for scaled or not y-yes n-no. for c  m-meetings t-time p-participants

	double fact , tempfact ,y_fact , n_fact;
	int digits_num ;
	
	if(c=='m'){

		tempfact = (79-(alpha.maxStrSize+2+digits(alpha.maxMeetings))) ;//gives remaining length
		y_fact = tempfact/alpha.maxMeetings ;
		n_fact = tempfact/alpha.totalMeetings ;
		digits_num = digits(alpha.maxMeetings) ;

		

		if(option=='y'){
		
			fact = y_fact ;

		}else if(option=='n'){ 		
			fact= n_fact ;
			
		}
	

		for(int i=0 ; i<size ; i++){
		
			infoBar(alpha.array[i].name,(alpha.maxStrSize+1)-strlen(alpha.array[i].name) ,(int)alpha.array[i].meetings*fact ,alpha.array[i].meetings ) ;

		

			if(i==alpha.filledAmount-1)
				break ;
		}
	
	}else if(c=='t') {
		
		tempfact = (79-(alpha.maxStrSize+2+digits(alpha.maxTime))) ;//gives remaining length
		y_fact = tempfact/alpha.maxTime ;
		n_fact = tempfact/alpha.totalTime ;
		digits_num = digits(alpha.maxTime) ;
		

		if(option=='y'){

			fact = y_fact ;
		}else if(option=='n'){

			fact= n_fact ;
		}

		for(int i=0 ; i<size ; i++){
			
			infoBar(alpha.array[i].name,(alpha.maxStrSize+1)-strlen(alpha.array[i].name) ,(int)alpha.array[i].time*fact ,alpha.array[i].time ) ;
		
			if(i==alpha.filledAmount-1)
				break ;
			}

	}else if(c=='p') {
		
		tempfact = (79-(alpha.maxStrSize+2+digits(alpha.maxParticipants))) ;//gives remaining length
		y_fact = tempfact/alpha.maxParticipants ;
		n_fact = tempfact/alpha.totalParticipants ;
		digits_num = digits(alpha.maxParticipants) ;

		if(option=='y'){

			fact = y_fact ;
		}else if(option=='n'){

			fact= n_fact ;
		}

		for(int i=0 ; i<size ; i++){
			infoBar(alpha.array[i].name,(alpha.maxStrSize+1)-strlen(alpha.array[i].name) ,(int)(alpha.array[i].participants*fact) ,alpha.array[i].participants ) ;

			if(i==alpha.filledAmount-1)
				break ;

		}
	}

	

	T_right((alpha.maxStrSize+2)) ;
	T_L() ;

	for(int i=0 ; i<((int)tempfact + digits_num ) ;i++){
	
		T_Horizontal() ;
	}

	printf("\n") ;

	

}

//sort and print the chart as we want.
void sortChart(linkedTotal alpha , int size,char c,char option) {

	persondetail temp ;
	alpha.maxStrSize=0 ;

	printf("\n") ;

	
	for(int i=0 ; i< alpha.filledAmount ; i++){
		
		for(int j=0 ; j<(alpha.filledAmount-1) ; j++){

			temp = alpha.array[j] ;
			

			if(c=='m'){
			
				if(alpha.array[j].meetings < alpha.array[j+1].meetings){
				
					alpha.array[j] = alpha.array[j+1] ;
					alpha.array[j+1] = temp ;
					
				}

			}else if(c == 't'){
			
				if(alpha.array[j].time < alpha.array[j+1].time){
				
					alpha.array[j] = alpha.array[j+1] ;
					alpha.array[j+1] = temp ;
				}
			}else if(c=='p'){
			
				if(alpha.array[j].participants < alpha.array[j+1].participants){
				
					alpha.array[j] = alpha.array[j+1] ;
					alpha.array[j+1] = temp ;
				}
			}
			
		}

	}
	
	for(int i=0 ; i<size ; i++){
	
		if(alpha.maxStrSize < (int)strlen(alpha.array[i].name)){

			alpha.maxStrSize = (int)strlen(alpha.array[i].name) ;
		}

		if(i==alpha.filledAmount-1)
			break;
	}
	
	table(alpha,size,c,option) ;
	

}

//*****************************************************OTHER MANIPULATIONS********************************************************

//to find the digits of an integer
int digits(int num) {

	int count=0 ;

	for(int i=0 ;;i++){
	
		if(num/10!=0){
		
			num = num/10 ;
			count++ ;
		}else{
		
			break ;
		}
	}
	return ++count ;
}

//To check whether a csv file
int checkCSV(char str[]) {

	int s= strlen(str)  ;

	if(str[s-1]=='v' && str[s-2]=='s' && str[s-3]=='c' && str[s-4]=='.'){
	
		return 1 ;
	}else{
	
		return 0 ; 
	}
}

//to check whether an integer +
int isInt(char str[]) {

	for(int i=0 ; i< strlen(str) ; i++){
	
		if(isdigit(str[i])==0){
		
			return 0 ;
		}
	}
	return 1;
}
