#include <stdio.h>
#include <stdlib.h>

void InitializeBoard(int m, int n , char board[][n]);

void PrintBoard(int m, int n, char board[][n]);

void CreateBoard(int m, int n, char board[][n]);

int IsValidBoard(int m, int n, char board[][n]);

void ListWinningCells(int m, int n, char board[][n]);

void RowWinningCells(int m, int n , char board[][n], int oWinningCell[][n], int xWinningCell[][n]);

void ColumnWinningCells(int m, int n , char board[][n], int oWinningCell[][n], int xWinningCell[][n]);

void DiaWinningCells(int m, int n , char board[][n], int oWinningCell[][n], int xWinningCell[][n]);

void checkGroupOf3(int oCounter, int xCounter, int blankCell, int oWinningCell[][3], int xWinningCell[][3]);

char WhoIsTheWinner(int m, int n, char board[][n]);

char RowWinner(int m, int n, char board[][n], int x,int y);

char ColumnWinner(int m, int n, char board[][n], int x,int y);

char DiaWinner(int m, int n, char board[][n]);


int main (void){
	
	char input ='0';
	char output = '0';
	char board[3][3];
	InitializeBoard(3,3,board);
	
	do{
		puts("press 'p' to print the tic-tac-toe board");
		puts("press 'c' to create a tic-tac-toe board with X and O cells");
		puts("press 't' to test if a tic-tac-toe board is valid or invalid board");
		puts("press 'w' to predict winning cell for player X or O");
		puts("press 'd' to check if their is a winner of the board");
		puts("press 'e' to exit");
		scanf(" %c", &input);
		
		switch (input){
			case 'p':
				PrintBoard(3,3,board);
				break;				
			case 'c':
				CreateBoard(3,3,board);
				break;
			case 't':
				if(IsValidBoard(3,3,board))puts("the current board is valid");
				else puts("the current board is invalid");
				break;
			case 'w':
				if(IsValidBoard(3,3,board))	ListWinningCells(3,3,board);
				else puts("winning cells cannot be predicted on an invalid board");
				break;				
			case 'd':			
				output = WhoIsTheWinner(3,3,board);				
				if(output != 'D') printf("The winner of the game is player %c\n",output);
				else printf("There is no winner of the game yet\n");				
				break;				
			case 'e':
				puts("Thank you for playing");
				break;
			default:
				puts("please give a proper input");
		}
		
	}while(input!= 'e');	
	
	return 0;	
}

void InitializeBoard(int m, int n, char board[][n]){
    int c = 1; // c = counter
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            board[i][j] = c + '0';
            c++;
        }
    }
}

void PrintBoard(int m, int n, char board[][n]){				//prints the board values with proper format for the grid
for(int i = 0; i < m; i++){
        printf("   |   |\n");
        for(int j = 0; j < n; j++){
            if(j+1 == n){
                printf(" %c \n", board[i][j]);
            }
            else{
                printf(" %c |", board[i][j]);
            }
        }
        if(i+1 == m){
            printf("   |   |\n");
        }
        else{
            printf("___|___|___\n");
        }
    }
}	

void CreateBoard(int m, int n, char board[][n]){			//initializes the board and creates the board using user inputs for board position and marker not allowing for incorrect inputs
	InitializeBoard(n, m, board);
	PrintBoard(n, m, board);
	
	int inputCell = 0;
	char inputChar = 0;
	
	do{
		puts("Enter the number of the cell you want to insert X or O or enter -1 to exit");
		scanf(" %d", &inputCell);
		if(inputCell >0 && inputCell <10){
			while(1){
				printf("type X or O\n");
				scanf(" %c", &inputChar);
				if (inputChar == 'X' || inputChar== 'O') break;
			}
			board[(inputCell-1)/3][(inputCell-1)%3] = inputChar;
			PrintBoard(n, m, board);
		}
	}while(inputCell!= -1);
}

int IsValidBoard(int m, int n, char board[][n]){			//checks to see if the board is a possible valid board by checking the difference between the number of markers
	

	
	int xCounter =0;
	int oCounter =0;
	
	for(int i =0; i<m; i++){
		for(int j=0; j< n; j++){
			if(board[i][j] == 'O') oCounter++;
			if(board[i][j] == 'X') xCounter++;			
		}
	}
	
	if( abs(oCounter - xCounter) == 0 || abs(oCounter - xCounter) == 1) return 1;
	else return 0;
	
	
}

void checkGroupOf3(int oCounter, int xCounter, int blankCell, int oWinningCell[][3], int xWinningCell[][3]){	//checks to see if a group of 3 values cells contain 2 of a marker and none of the other so that a winning movie exists
	
	if (oCounter ==2 && xCounter == 0){
			oWinningCell[(blankCell-1)/3][(blankCell-1)%3] ++;			
		}
		if (xCounter ==2 && oCounter == 0){
			xWinningCell[(blankCell-1)/3][(blankCell-1)%3] ++;			
		}
	
}

void RowWinningCells(int m, int n , char board[][n], int oWinningCell[][n], int xWinningCell[][n]){		//checks for the winning moves possible in the rows of the board
	
	int xCount = 0;
	int oCount = 0;
	int blankCell = 0;
	
	for(int i =0; i<m; i++){
		for(int j=0; j< n; j++){
			if(board[i][j] == 'O') oCount++;
			else if(board[i][j] == 'X') xCount++;
			else  blankCell = 3*(i)+(j+1);
		}
		
		checkGroupOf3(oCount,xCount,blankCell,oWinningCell,xWinningCell);
		
		xCount=0;
		oCount=0;
	}
	
}

void ColumnWinningCells(int m, int n , char board[][n], int oWinningCell[][n], int xWinningCell[][n]){		//checks for the winning moves possible in the column of the board
	
	int xCount = 0;
	int oCount = 0;
	int blankCell = 0;
	
	for(int i =0; i<m; i++){
		for(int j=0; j< n; j++){
			if(board[j][i] == 'O') oCount++;
			else if(board[j][i] == 'X') xCount++;
			else  blankCell = 3*(j)+(i+1);
		}
		
		checkGroupOf3(oCount,xCount,blankCell,oWinningCell,xWinningCell);
		xCount=0;
		oCount=0;		
	}
	
	
}

void DiaWinningCells(int m, int n , char board[][n], int oWinningCell[][n], int xWinningCell[][n]){		//checks for the winning moves possible in the diagonals of the board
	
	int xCount = 0;
	int oCount = 0;
	int blankCell = 0;
	
	for(int i = 0; i < 3; i ++){
		if(board[i][i] == 'O') oCount++;
		else if(board[i][i] == 'X') xCount++;
		else  blankCell = 3*(i)+(i+1);		
	}
	
	checkGroupOf3(oCount,xCount,blankCell,oWinningCell,xWinningCell);	
	xCount=0;
	oCount=0;
	
	
	
	for(int i = 0, j = 2; i < 3; i ++, j--){
		if(board[i][j] == 'O') oCount++;
		else if(board[i][j] == 'X') xCount++;
		else  blankCell = 3*(i)+(j+1);		
	}
	
	checkGroupOf3(oCount,xCount,blankCell,oWinningCell,xWinningCell);
	xCount=0;
	oCount=0;
	
	
}

void ListWinningCells(int m, int n, char board[][n]){		//lists the cells that would be a winning move for each player 
	 
	int oWinningCell[3][3] = {};			//an array that will hold the amount of times a given cell is the winning cell for a player for every cell
	int xWinningCell[3][3] = {};		 
	
	RowWinningCells(m, n , board, oWinningCell, xWinningCell);	

	ColumnWinningCells(m, n , board, oWinningCell, xWinningCell);
	
	DiaWinningCells(m, n , board, oWinningCell, xWinningCell);	
	
	int oHasWin = 0;
	for(int i =0; i<m; i++){
		for(int j=0; j< n; j++){			
			if(oWinningCell[i][j]){	
				if(oHasWin == 0)	printf("Cell #%d ",3*(i)+(j+1));				
				else	printf("and #%d ",3*(i)+(j+1));
				oHasWin++;
			}
		}
	}
	if(oHasWin ==1 ) puts("is a winning cell for player O");
	else if(oHasWin > 1 ) puts("are winning cells for player O");	
	
	int xHasWin = 0;
	for(int i =0; i<m; i++){
		for(int j=0; j< n; j++){			
			if(xWinningCell[i][j]){	
				if(xHasWin == 0)	printf("Cell #%d ",3*(i)+(j+1));				
				else	printf("and #%d ",3*(i)+(j+1));
				xHasWin++;
			}
		}
	}
	if(xHasWin ==1 ) puts("is a winning cell for player X");
	else if(xHasWin > 1 ) puts("are winning cells for player X");	
	
	if (xHasWin ==0 && oHasWin == 0) puts("No winning cells for player X or O");	 
 }
 
char WhoIsTheWinner(int m, int n, char board[][n]){		//states which if any player won the board
	
	
	char curValue;
	
	if((curValue = ColumnWinner(m,n,board,3,1)) != 'D') return curValue;
	else if((curValue = ColumnWinner(m,n,board,3,2)) != 'D') return curValue;
	else if((curValue = ColumnWinner(m,n,board,3,3)) != 'D') return curValue;
	else if((curValue = RowWinner(m,n,board,3,1)) != 'D') return curValue;
	else if((curValue = RowWinner(m,n,board,3,2)) != 'D') return curValue;
	else if((curValue = RowWinner(m,n,board,3,3)) != 'D') return curValue;
	else if((curValue = DiaWinner(m,n,board)) != 'D') return curValue;
	else return 'D'; 
	
}

char ColumnWinner(int m, int n, char board[][n], int x, int y){		//recursively solved if a win happened in a column
	
	if (x==1)return board[x-1][y-1];
	if(board[x-1][y-1] + ColumnWinner(m,n,board,x-1,y)== 2 * 'X')return 'X';
	else if (board[x-1][y-1]+ ColumnWinner(m,n,board,x-1,y)== 2 * 'O')return 'O';
	else return 'D';
	
}

char RowWinner(int m, int n, char board[][n], int x, int y){		//recursively solved if a win happened in a row
	
	if (x==1)return board[y-1][x-1];
	if(board[y-1][x-1] + RowWinner(m,n,board,x-1,y)== 2 * 'X')return 'X';
	else if (board[y-1][x-1]+ RowWinner(m,n,board,x-1,y)== 2 * 'O')return 'O';
	else return 'D';
	
}

char DiaWinner(int m, int n, char board[][n]){		//solves if a win happened in the diagonals
    
    int downDia = board[0][0]+ board[1][1]+ board[2][2];
    int upDia = board[2][0]+ board[1][1]+ board[0][2];
    
    if(upDia == 3 * 'X'|| downDia == 3 * 'X') return 'X';
    else if(upDia == 3 * 'O'|| downDia == 3 * 'O') return 'O';
    else return 'D';
}