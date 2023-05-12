/*
	PROJECT: 
	A SIMPLE CONSOLE BASED SLOT MACHINE GAME TO PLAY .
									-Rajan Marasini.
*/
#include <stdio.h>
#include<stdbool.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<conio.h>

static int owner_money = 0;

//Function to check if the input value is correct or not to start the game.
bool is_valid_number(char *str){
	int i=0;
	int len = strlen(str);
	if(str[0]=='-'){
		i=1;
	}
	
	for(i; i<len; i++){
		if(!isdigit(str[i])){
			return false;
			break;
		}
	}
	return true;
}

//Function for depositing the amount to start playing the bet.
int getDeposit(){
    char input[20];
    int deposit;
    bool is_valid = false;
    
    while(!is_valid){
    	printf("\nEnter the amount you want to deposit. Rs.");
    	scanf("%s",input);
    	
    	if(is_valid_number(input)){
    		deposit = atoi(input);
    		
    		if(deposit > 0){
    			is_valid = true;
			}else{
				printf("\nAmount must be greater than Rs.0");
			}
		}else{
			printf("\nInvalid Amount. Amount must be in number. ");
		}
    	
	}
    return deposit;
}

//Function for getting the number of lines player want to bet on.
int getLines(){

	char input[10];
	int line;
	bool is_valid = false;
	
	while(!is_valid){
		printf("\nEnter the number of lines: range is 1-3 ");
		scanf(" %s", input);
		
		if(is_valid_number(input)){
			line = atoi(input);
			
			if(line > 0 && line <4){
				is_valid = true;
			}else{
				printf("\nLines must be in range of 1-3: ");
			}
		}else{
			printf("\nInvalid input. Lines must in number.");
		}
	}
	return line;
}

//Function for getting the betting amount.
int getBet(){
	char input[10];
	int bet;
	bool is_valid = false;
	
	while(!is_valid){
		printf("\nEnter the amount you want to bet on each lines. Rs.");
		scanf("%s",input);
		
		if(is_valid_number(input)){
			bet = atoi(input);
			
			if(bet > 0){
				is_valid = true;
			}else{
				printf("\nBetting Amount must be greater than Rs.0.");
			}
		}else{
			printf("\nInvalid Input. Please Enter the amount in number. ");
		}
	}
	return bet;
}

//Function to get the random value of slot machine in the row.
int getRandom(){
    int upper = 68, lower= 65;
    
    int num = (rand() % (upper - lower + 1)) + lower;
    
    return num;
}

//Function to spin the slot machine
void slot_machine_spin(int deposit, int bettingAmount, int totalbettingAmount, int lines){
   
    int i, j, count = 0;
    char choice,ch;
    int slot_machine_value[3][3];
    
    srand(time(0));
    
    for(i = 0; i < 3; i++){
        for(j = 0; j<3; j++){
            slot_machine_value[i][j] = getRandom();
        }
    }
    
    printf("You have got \n\n");
    for( i = 0; i<3; i++){
    	printf("\t");
        for(j = 0; j < 3; j++){
            printf("%c\t", slot_machine_value[i][j]);
        }
        printf("\n");
    }
    
    for(i = 0; i<3; i++){
    	if(slot_machine_value[i][0] == slot_machine_value[i][1] && slot_machine_value[i][0] == slot_machine_value[i][2]){
    		count++;
		}
	}
	if(count!=0){
		if(count == lines){
			owner_money-= ((count+lines) * totalbettingAmount * 2);
			deposit = ((count+lines) * totalbettingAmount * 2 ) + deposit;
			printf("Congratulation!\nYou have won Rs.%d\n",(count+lines) * totalbettingAmount * 2);
			printf("Your current balance is Rs.%d\n",deposit);		
		}else if(count>lines){
			if((count - lines) >= 2){
				owner_money-= ((count-lines) * totalbettingAmount * 2 * lines);
				deposit = ((count-lines) * totalbettingAmount * 2 * lines) + deposit;
				printf("Congratulation!\nYou have won Rs.%d\n",(count-lines)*totalbettingAmount*2*lines);
				printf("Your current balance is Rs.%d\n",deposit);
			}else{
				owner_money-= ((count - lines) * totalbettingAmount * 4 * lines);
				deposit = ((count-lines) * totalbettingAmount * 4 * lines) + deposit;
				printf("Congratulation!\nYou have won Rs.%d\n",(count-lines)*totalbettingAmount*4*lines);
				printf("Your current balance is Rs.%d\n",deposit);
			}
		}else{
			if(owner_money != 0){
				owner_money -= (count * bettingAmount * 4);
			}
			deposit = (count * bettingAmount * 4) + deposit;
			printf("Congratulation!\nYou have won Rs.%d\n",count*bettingAmount* 4);
			printf("Your current balance is Rs.%d\n",deposit);
		}
	}else{
		owner_money+=totalbettingAmount;
		deposit = deposit - totalbettingAmount;
		printf("\nSorry! Better luck next time: \n");
		printf("Your current balance is Rs.%d\n",deposit);
	}
	
	
		 if(deposit<=0){
   			printf("Do you want to deposit more? Press ENTER bar to deposit. \n");
   			ch = getch();
   			switch(toupper(ch)){
   			case '\r':
   				deposit = getDeposit();
   				break;
   			
   			default:
				// printf("Owner has earn: Rs.%d",owner_money);
   				printf("\nThanks for playing with us.\n");
				exit(0);
	   }
  	 }
	
	
	printf("\nPress ENTER to play again \n");
	choice = getch();
	switch(toupper(choice)){
	case '\r':
		 lines = getLines();
   	     bettingAmount = getBet();
 	     totalbettingAmount = lines * bettingAmount;
    
   	    if(totalbettingAmount <= deposit){
        	 printf("\nYour balance is Rs.%d\n", deposit);
   			 printf("You are betting Rs.%d on %d lines.\nYour total betting amount is Rs.%d\n",bettingAmount, lines, totalbettingAmount);
        }
        break;
        
    default:
		// printf("Owner has earn: Rs.%d",owner_money);
    	printf("\nThanks for playing");
    	printf("\nYour remaining balance is Rs.%d",deposit);
    	exit(0);
}
    while(totalbettingAmount>deposit){
        printf("You dont have sufficient balance!\n");
        bettingAmount = getBet();
        totalbettingAmount = lines * bettingAmount;
        if(totalbettingAmount <= deposit){
        	 printf("\nYour balance is Rs.%d\n", deposit);
   			 printf("You are betting Rs.%d on %d lines.\nYour total betting amount is Rs.%d\n",bettingAmount, lines, totalbettingAmount);
            break;
        }
        
    }
   printf("\nAre you ready to continue. Press ENTER to continue: \n");
    printf("Enter any other key to quit this game. ");
    
	choice = getch();
	
	switch(toupper(choice)){
       case '\r':
         slot_machine_spin(deposit, bettingAmount, totalbettingAmount,lines);
         break;
        
       default:
	    // printf("Owner has earn: Rs.%d",owner_money);
       	 printf("\nYour remaining balance is Rs.%d",deposit);
         exit(0);
   } 
   
}

//Main Function begin from here
int main() {
    char choice;
    int deposit = getDeposit();
    int lines = getLines();
    int bettingamount = getBet();
    int totalbettingAmount = lines * bettingamount;
    
     if(totalbettingAmount <= deposit){
        	 printf("\nYour balance is Rs.%d\n", deposit);
   			 printf("You are betting Rs.%d on %d lines.\nYour total betting amount is Rs.%d\n",bettingamount, lines, totalbettingAmount);
        }
    
    while(totalbettingAmount>deposit){
        printf("You dont have sufficient balance!\n");
        bettingamount = getBet();
        totalbettingAmount = lines * bettingamount;
        if(totalbettingAmount <= deposit){
        	 printf("\nYour balance is Rs.%d\n", deposit);
   			 printf("You are betting Rs.%d on %d lines.\nYour total betting amount is Rs.%d\n",bettingamount, lines, totalbettingAmount);
            break;
        }
        
    }
    printf("\nAre you ready to continue. Press ENTER to continue: \n");
    printf("Enter any other key to quit this game. ");
    choice = getch();
    printf("\n");
   switch(toupper(choice)){
       case '\r':
         slot_machine_spin(deposit, bettingamount, totalbettingAmount, lines);
         break;
        
       default:
       	printf("\nYour balance is Rs.%d",deposit);
		exit(0);
   } 
    return 0;
}
