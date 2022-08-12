#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<time.h>





char * randomword(FILE *fp,int n) {
int 	i=0 ;
int     x ;
char   *ch=(char *)malloc((n)*sizeof(char)) ; ;
char   *s=(char *)malloc((n)*sizeof(char)) ; ;	
		 srand(time(NULL)) ;
		while (fgets(s,100,fp) ) {      /* fgets(s,100,fp) will give us every word in every line because we are sure that there is no word longer than 100 */
		if (strlen(s)==n+1) {                 /* searching for a word with length n then we choose a random number between 1 and 0    
	                                        if the number is 1 we choose that word else we search for an other word with the same length 
	                                         but if the number is 0 and there is no other word with length n in the list so we have to choose 
	                                         that word  that`s why we have to save the content of s in ch everytime  
                                                              	*/  
		x=rand()%2 ;                   
		if (x==1) {                         
			return s ;                       
		}
		else {
			strcpy(ch,s) ;
			
		}
		}
	}
	return ch ;
}



char * modif(char* s,char*ch ,char c) {
	char *a=(char *)malloc((strlen(ch))*sizeof(char)) ;
	char *ch1=(char *)malloc((strlen(ch))*sizeof(char)) ;
	strcpy(ch1,s) ;
	int i=0;
	a=strchr(ch,c) ;
	while (  i<strlen(ch)   && a!="\0" ) { /* if the caracter c occurs in the string ch more than once we have to change every dash in the string s
	                                         to that caracter . ater changing the first dash to that caracter we have to see if a=! "\0" ... if not 
	                                         so there is no other caracter c in that string so it`s the end of while. */
	                                   
	 	a=strchr(ch,c) ;
	 	if (ch[i]==c) {
	 		ch1[i]=c ;  }
	 		i++ ;
		 }
		 return ch1 ;
}


int notify(char *s,char c) {
  	int i;
  	for(i=0;i<strlen(s);i++) {
  		if (s[i]==c) {
  			return 1 ;
		  }
	  }
	  return 0 ;
}



void save_last_game(double t, int r,char *ch) {
		FILE *fp= fopen("history.txt","a") ;
 	printf("give your name please: ") ;
	 char s[20] ;
	 scanf("%s",s) ;	
	if (r==0) {
		fprintf(fp,"%s you took %f to finish the game !! the word was %s ! unfortunately you lost",s,t,ch) ;

		}
		else {
			fprintf(fp,"%s you took %f to guess the word %s ! congratulations you won",s,t,ch) ; }
		fprintf(fp,"\n") ;
}


void show_result_and_time(int d , int x , char* ch,clock_t t) {
	d==x ?  printf("you lost the word is %s\n",ch) : printf("you won\n") ;
	t = clock() - t; 
	double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
    printf("the player took %f seconds to finish the game \n", time_taken); 
	
	save_last_game(time_taken,d-x,ch) ;
}


void play(char*ch,char*s,int d)     {
     char c ;
     int x=0 ;
	 char *s1=(char *)malloc((strlen(ch))*sizeof(char)) ;
	 clock_t t; 
     t = clock(); 
	
		 
		 	while ( x<d && strcmp(s,ch)!=0)  {
	 	fflush(stdin);
	 	printf("give a letter :");
	 	scanf("%c",&c) ;
	 	
	 	
	 	if (notify(s,c)==1 ) {
	 		printf("be careful this guessed letter has already been guessed.\n") ;
	 		
		 }
		 else {
		 s1=modif(s,ch,c) ; /* every time i will compare s1 to s if there are differences so that`s mean that the guessed word is true
		                           if it is true so x is increased by 1 .
								     if x reached d after several guesses that`s mean that the player lost the game
									
									  */
	   if (strcmp(s1,s) ==0) {
	 	    printf("%s misses %c  //The number of possible guesses are %d\n",s,c,d-x-1) ;
		 	x++ ;
		 }
		 else {
		 	printf("%s correct  guess\n",s1) ;
		 }
		 strcpy(s,s1) ; }	 
}

 show_result_and_time(d,x,ch,t) ;

} 



int main ()   {
	int i,x,d ;
	int l ;
	char c;
	char *ch=(char *)malloc((l)*sizeof(char)) ;
	char *s=(char *)malloc((l)*sizeof(char)) ;
   

	printf("give the length of the word\n") ;
	scanf("%d",&l) ;

	
	FILE *fp= fopen("words.txt","r") ;
	
    ch=randomword(fp,l) ;
    ch[l]='\0';
	
	for (i=0;i<l;i++) {
		s[i]='-' ;    
	}
	s[i]='\0';
	puts(s) ;
	
	printf("change difficulty\n") ;
	scanf("%d",&d) ;
	
	play(ch,s,d) ;



	
	return 0 ;
}
