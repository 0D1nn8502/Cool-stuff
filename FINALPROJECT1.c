#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void print_board2 (const char boards[9]){ 

    int count = 0; 

    for (int i = 0; i < 9; i++){
               
        (count % 3 == 0) ? printf("\n%c ",boards[i]) : printf("%c ", boards[i]); 
        count ++; 

    }

    printf("\n"); 

}


//Computer's turn// 
void play (int choice, char arr1[9]){  

    char* ptr = (char*) malloc(sizeof(char)); 

    ptr = arr1; 

    *(ptr + choice) = 'X';  
  
}

void play2 (int choice, char arr[9]){

    char* ptr = (char*) malloc(sizeof(char)); 

    ptr = arr; 

    *(ptr + choice) = 'O';      

}

bool end_state (char board[9]){

    for (int q = 0; q < 9; q++){
        if (!(board[q] == 'X' || board[q] == 'O')){
            return false; 
        }
    } 

    return true; 

}

//We must check if someone has won//

char checkwin(char a[9]) 
{
    char tie = 'T'; 
    char going = 'P'; 

    if(a[0]==a[1] && a[1]==a[2])    
        return a[0];    
    else if(a[3]==a[4] && a[4]==a[5])
        return a[3]; 
    else if(a[6]==a[7] && a[7]==a[8])
        return a[6];
    else if(a[0]==a[3] && a[3]==a[6])
        return a[0]; 
    else if(a[1]==a[4] && a[4]==a[7])
        return a[1];
    else if(a[2]==a[5] && a[5]==a[8])
        return a[2];
    else if(a[0]==a[4] && a[4]==a[8])
        return a[0];
    else if(a[2]==a[4] && a[4]==a[6])
        return a[2];
    
    else if(a[0]!='0' && a[1]!='1' && a[2]!='2' && a[3]!='3' && a[4]!='4' && a[5]!='5' && a[6]!='6' && a[7]!='7' && a[8]!='8')
        return tie; 
    else
        return going; 
}

int scoreboard (char board[9]){

    if (checkwin (board) == 'X'){
        return 10; 
    }

    else if (checkwin (board) == 'O'){
        return -10; 
    }

    else if (checkwin (board) == 'T'){
        return 0; 
    }

    else{
        return 1;  
    }

}

//Given a valid move for X, get the possible state// 
char* get_state (int move, char board[9]){

    char* statez = (char*) malloc (9*sizeof(char)); //Dummy board// 

    for (int p = 0; p < 9; p++){
        statez[p] = board[p]; 
    }

    play (move, statez); 
    return statez; 

}

// Check if its computer's turn based on number of empty spaces//  
bool turn (char board[9]){

    int filled_spaces = 0; 

    for (int i = 0; i < 9; i++){

        if (board[i] == 'X' || board[i] == 'O'){

            filled_spaces ++; 

        }

    }

    if (filled_spaces == 0){
        return false; 
    }

    else if (filled_spaces % 2 != 0){

        return true; 

    }

    return false; 

}

char* get_state2 (int move, char board[9]){

    char* statez = (char*) malloc (9*sizeof(char)); 

    for (int p = 0; p < 9; p++){
        statez[p] = board[p]; 
    }

    play2 (move, statez); 
    return statez; 

}

int minimax (char board[9]){

    char* falcon = (char*) malloc (9*sizeof(char)); 

    for (int r = 0; r < 9; r++){
        falcon[r] = board[r]; 
    }
    
    if (checkwin (falcon) != 'P'){ 
        return scoreboard (falcon);  
    }

    //if it is Computer's turn// 
    else if (turn (falcon)){
         
        int bestscore = -1000; 

        for (int j = 0; j < 9; j++){

            if (falcon[j] != 'X' && falcon[j] != 'O'){
                char* state2 = (char*) malloc (sizeof(char));
                char* state3 = (char*) malloc (9*sizeof(char)); 
                state2 = get_state (j, falcon);  
                for (int r = 0; r < 9; r++){
                    state3[r] = state2[r]; 
                }
                int score = minimax (state3); 

                if (score > bestscore){
                    bestscore = score; 
                }
                free (state3); 
                free (state2);  

            }

        }
        return bestscore; 

    }

    else{ 
        int bestscore = 1000; 

        for (int k = 0; k < 9; k++){

            if (falcon[k] != 'X' && falcon[k] != 'O'){
                char* another = (char*) malloc (sizeof(char));
                char* one = (char*) malloc (9*sizeof(char)); 

                another = get_state2 (k, falcon); 

                for (int l = 0; l < 9; l++){
                    one[l] = another[l]; 
                }

                int score = minimax (one); 

                if (score < bestscore){
                    bestscore = score; 
                }
                free (one); 
                free (another); 
            }

        }
        return bestscore; 
    }

    free (falcon); 

}

//Suggest bestmove to computer based on the board state// 
int bestmove (char board[9]){ 

    int bestscore = -1000; 
    int choice; 


    for (int k = 0; k < 9; k++){ 

        if (board[k] != 'O' && board[k] != 'X'){

            char* statez = (char*) malloc (sizeof(char));
            char* united = (char*) malloc (9*sizeof(char));  

            statez = get_state (k, board);

            for (int m = 0; m < 9; m++){
                united[m] = statez[m]; 
            }

            int score = minimax (united);   

            if (score > bestscore){
                bestscore = score;  
                choice = k; 
            }
            free (united); 
            free (statez); 

        }

    }
    return choice; 

}

int main (){

    char board[9] = {'0','1','2','3','4','5','6','7','8'}; 

    printf ("\n WELCOME TO UNBEATABLE TIC TAC TOE \n");   


    while (checkwin (board) != 'T' && checkwin (board) != 'X' && checkwin (board) != 'O'){
        //Not the computer's turn// 
        if (!(turn(board))){
            
            int choice; 

            print_board2 (board);  

            printf ("\nCHOOSE YOUR SPOT: "); 
            scanf ("%d", &choice);

            if (board[choice] != 'X' && board[choice] != 'O'){
                play2 (choice, board); 
            } 

            else{
                printf ("\n Invalid choice, ENDING GAME \n");
                break;  
            }

        }

        else{
            int reply; 

            reply = bestmove (board);
            play (reply, board); 

            //print_board2 (board);  
        }

    }

    if (checkwin (board) == 'X'){
        printf ("\n *sigh* You are but a human. YOU LOSE. \n");
    } 

    else if (checkwin (board) == 'T'){
        printf ("\n TIE! Not bad at all. \n"); 
    }
     
    //No other condition because I am confident I dont need it. // 

}