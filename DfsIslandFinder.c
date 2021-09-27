//BURAK UGAR 200104004100
// IMPORTANT:this programme includes a lot of recursion so that program stack will cause problem by using 512x512 matrix but it is still ok to use 100x100
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
// Please change the macros according to file that you test before testing!!
#define ROW 512 // number of rows in input file
#define COL 512 // number of coloumn in input file
int controlAdjacent(int M[][COL],int row,int col){ // This function is controlling neighbours cells for entered cell as input. If there exists any cell in under,
// above, left or right direction then it returns 1, if there is not, returns 0.
	if (M[row][col+1]==1 || M[row][col-1]==1 || M[row+1][col]==1 || M[row-1][col]==1 ){
		return 1;
	}
	else {
		return 0;
	}
}
// This function checks whether entered cell fits with grid size and not visited. 
int control(int M[][COL], int row, int col, int visited[][COL]) 
{ 
	if ((row >= 0) && (row < ROW) && (col >= 0) && (col < COL)){
		if(M[row][col] && !visited[row][col]){
				return 1; // if the entered cell fits with grid size and yet not visited by the function searchisland then function returns 1
		}
		else return 0; // if one of the conditions is given below is not satisfied function returns 0
	}
	else 
		return 0;	
    // row number is in range, column number is in range and value is 1 
    // and not yet visited 
} 
// A recursive function to do search for a given two dimentional binary matrix which considers 
// the 4 neighbours as adjacent vertices .
void searchIsland(int M[][COL], int row, int col, int visited[][COL]) 
{ 	int i;
    // These arrays are used to get row and column numbers of 4 neighbours 
    // of a given cell 
     static int numberofrow[] = { -1, 1, 0, 0 }; // first: left, second: right, third:up, fourth: down
     static int numberofcol[] = { 0, 0, -1, 1 }; 
  
    // Mark this cell as visited 
    visited[row][col] = 1; 
  
    // for 4 direction make recursion for neighbours
    for (i = 0; i < 4; ++i) 
        if (control(M, row + numberofrow[i], col + numberofcol[i], visited)) 
            searchIsland(M, row + numberofrow[i], col + numberofcol[i], visited); 
} 
  
// The main function that returns number of islands in a given boolean(0-1) 2D matrix 
int enumareteIslands(int M[][COL], int B[][2]){
	int i,j;
	int count = 0; // number of islands is initially 0
	const int number= 100; // there are at most 100 island can exist as given
	//We are creating an two dimentional array to mark the cells that we already visited
    int visited[ROW][COL]; 
    // Since at first all cells are unvisited, we assign matrix 0
	memset(visited, 0, sizeof(visited)); 
    // Initialize count as 0 and traverse through the all cells of 
    // given matrix 
    for ( i = 0; i < ROW; i++) 
        for ( j = 0; j < COL; j++) 
            if (M[i][j] && !visited[i][j] && controlAdjacent(M,i,j)) // If a cell with value 1 is not 
            { // visited yet, then we find the new island
				searchIsland(M, i, j, visited); // Searching all cells in that island 
                count++; // incrementing number of island
				B[count-1][0]=i; // because we incremented the count by 1 we have to decrement it by 1 to create matrix's elements 
				B[count-1][1]=j;
            } 
    return count; // return the number of islands
} 


void writeOutput(int M[][COL],int B[][2]) { // function that prints the number of island in the grid and their coordinates
	FILE* fp=fopen("output.txt","w");
	int count,i;
	count= enumareteIslands(M,B);
		if (count == 0)
			fprintf(fp, "%d", count); // if the number of island is 0 then print and close the file
		else
			fprintf(fp, "%d\n", count); // if the number of island is different then 0 then print that value with new line and print the coordinates
		for(i=0;i<count;i++){
			fprintf(fp, "%d %d\n", B[i][0],B[i][1]); //print the x and y coordinates of the founded islands
		}
		fclose(fp);
}

void fillMatrix(int M[][COL],FILE* fp){ // We are filling our matrix with 0 and 1's. 0 is for underwater cells and 1 for the cells above the water.
	int i,j;
	int water_level;
	fp= fopen("input.txt","r");
	fscanf(fp, "%d", &water_level); // take the value of water level
	for (i = 0; i < ROW; i++) { // for all cells compare the water level and create the matrix  
		for (j = 0; j < COL; j++){
			fscanf(fp, "%d", &M[i][j]);
			if(M[i][j] <= water_level){
				M[i][j] = 0; // if the cell is in the underwater then it will be 0 if not it will be 1
			}
			else
				{
				M[i][j] = 1;
				}
		}
	}
	fclose(fp);
}
int main(){
	FILE *input,*output;
	int i,j;
	int M[ROW][COL]; // array holds the information of water levels
	int water_level;
	int B[100][2]; // matrix that hold the coordinates of islands there at most 100 island as given
	memset(B,0,sizeof(B)); // at first, all of the coordinates are created with 0.
	int count;
	input=fopen("input.txt","r"); // opening file
	output=fopen("output.txt","w"); // opening file
	fillMatrix(M,input); // fill matrix M with 0 and 1 in terms of water levels
	writeOutput(M,B); // write results to output file
	fclose(input); // closing files
	fclose(output); // closing files
	return 0;
}

