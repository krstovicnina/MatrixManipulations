#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int PrintMenu()
{//The menu function. Return value is for the switch(option) in the main function to activate.
	int option;
	printf("\n");
	printf("Enter 1 to read two matrices and calculate their sum.\n");
	printf("Enter 2 to read two matrices and calculate their difference.\n");
	printf("Enter 3 to read a matrix and a variable to calculate their scalar product.\n");
	printf("Enter 4 to read two matrices and calculate their product.\n");
	printf("Enter 5 to read a matrix and calculate its transposed matrix.\n");
	printf("Enter 6 to read a matrix and print its values in a zigzag form.\n");
	printf("Enter 7 to read a matrix and print out all entries, which have a an even sum of its neighbours.\n");
	printf("Enter 8 to exit the program.\n");
	scanf("%d", &option);
	return option;
}
void CheckOnes(int Number, int *numOfOnes)
/*{//This method does not work for negative numbers
	int mask = 1;
	int counter =  *numOfOnes;
	while(Number != 0)
	{
		if(Number & mask)
			counter++;
		Number >>=1;
	}
	*numOfOnes = counter;
}*/
{//Function to check number of ones in bit format of a number.
	int mask = 1 << sizeof(int) * 8 - 1;
	int counter =  *numOfOnes;
	while(Number != 0)
	{
		if(Number & mask)
			counter++;
		Number <<= 1; //Since integer can be a negative number, we move everything to the left.
	}
	*numOfOnes = counter;
}
void FreeMatrix(int **Matrix, int Rows) 
{//Function to free the memory of dynamicly allocated memory for the matrices.
	int i;
	for(i = 0; i < Rows; i++)
	{
		free(Matrix[i]);
	}
	free(Matrix);
}
void EnterMatrixDimensions(int *Rows, int *Columns)
{//Function for entering matrix dimensions. Have to be pointers; otherwise only copies of rows and columns will be taken and any changes removed.
	int Wronginput = 0;
	do
	{
		if (Wronginput)
		{
			printf("Please enter correct dimensions for the matrix.\n");
		}
	printf("Enter the number of rows.\n");
	scanf("%d", Rows);
	printf("Enter the number of columns.\n");
	scanf("%d", Columns);
	Wronginput = 1;
	} while(*Rows < 1 || *Columns < 1);
}
int ** EnterMatrixElements(int **Matrix, int Rows, int Columns)
{//Function for entering matrix elements.
	int i, j;
	Matrix = malloc(Rows * sizeof(int*)); //Allocating memory for all rows.
	for(i = 0; i < Rows; i++)
	{
		Matrix[i] = malloc(Columns * sizeof(int)); //Allocating memory for each row with number of columns.
		printf("Row %d\n", i + 1);
		for(j = 0; j < Columns; j++)
		{
			scanf("%d", &Matrix[i][j]);
		}
	}
	return Matrix; // Has a return value so that the value is stored for the matrix.
}
void PrintMatrix(int **Matrix, int Rows, int Columns)
{ //Function for printing a matrix.
	int i, j;
	for(i = 0; i < Rows; i++)
	{
		for(j = 0; j < Columns; j++)
		{
		printf(" %d ", Matrix[i][j]);
		}
		printf("\n");
	}
}
void SumOf2Matrices(int **MatrixA, int **MatrixB, int **MatrixC)
{ //Function which performs matrix operation C=A+B
	int Rows, Columns;
	printf("Enter dimensions of the matrices.\n");
	EnterMatrixDimensions(&Rows, &Columns);
	printf("Enter the elements of the first matrix.\n");
	MatrixA = EnterMatrixElements(MatrixA, Rows, Columns);
	printf("Enter the elements of the second matrix.\n");
	MatrixB = EnterMatrixElements(MatrixB, Rows, Columns);
	int i, j;
	MatrixC = malloc(Rows * sizeof(int*));//Same as in entering elements, allocating memory first for number of rows.
	for(i = 0; i < Rows; i++)
	{
		MatrixC[i] = malloc(Columns * sizeof(int));//Same as in entering elements, allocating memory for each row.
		for(j = 0; j < Columns; j++)
		{
			MatrixC[i][j] = MatrixA[i][j] + MatrixB[i][j];
		}
	}
	FreeMatrix(MatrixA, Rows);
	FreeMatrix(MatrixB, Rows);
	printf("The sum of the two matrices has the following form:\n");
	PrintMatrix(MatrixC, Rows, Columns);
	FreeMatrix(MatrixC, Rows);
}
void Minus2Matrices(int **MatrixA, int **MatrixB, int **MatrixC)
{//Function which performs matrix operation C=A-B. Function is almost identical to the sum of 2 matrices.
	int Rows, Columns;
	printf("Enter dimensions of the matrices.\n");
	EnterMatrixDimensions(&Rows, &Columns);
	printf("Enter the elements of the first matrix.\n");
	MatrixA = EnterMatrixElements(MatrixA, Rows, Columns);
	printf("Enter the elements of the second matrix.\n");
	MatrixB = EnterMatrixElements(MatrixB, Rows, Columns);
	int i, j;
	MatrixC = malloc(Rows * sizeof(int*));
	for(i = 0; i < Rows; i++)
	{
		MatrixC[i] = malloc(Columns * sizeof(int));
		for(j = 0; j < Columns; j++)
		{
			MatrixC[i][j] = MatrixA[i][j] - MatrixB[i][j];
		}
	}
	FreeMatrix(MatrixA, Rows);
	FreeMatrix(MatrixB, Rows);
	printf("The resulting matrix has the following form:\n");
	PrintMatrix(MatrixC, Rows, Columns);
	FreeMatrix(MatrixC, Rows);
}
void ScalarMultiplication(int **MatrixA, int **MatrixC)
{//Function that performs the matrix operation C=k*A, where k is an integer variable. Function almost identical to sum and minus;
	int Rows, Columns, k;
	printf("Enter dimensions of the matrix.\n");
	EnterMatrixDimensions(&Rows, &Columns);
	printf("Enter elements of the matrix.\n");
	MatrixA = EnterMatrixElements(MatrixA, Rows, Columns);
	printf("Enter a constant value for multiplication.\n");
	scanf("%d", &k);
	int i, j;
	MatrixC = malloc(Rows * sizeof(int*));
	for(i = 0; i < Rows; i++)
	{
		MatrixC[i] = malloc(Columns * sizeof(int));
		for(j = 0; j < Columns; j++)
		{
			MatrixC[i][j] = k * MatrixA[i][j];
		}
	}
	FreeMatrix(MatrixA, Rows);
	printf("The result of the matrix has the following form.\n");
	PrintMatrix(MatrixC, Rows, Columns);
	FreeMatrix(MatrixC, Rows);
}
void Product2Matrixes(int **MatrixA, int **MatrixB, int **MatrixC)
{//Function that multiplies 2 matrices.
	int RowsA, ColumnsA, RowsB, ColumnsB, sum = 0;
	printf("Enter dimensions of the first matrix.\n");
	EnterMatrixDimensions(&RowsA, &ColumnsA);
	printf("Enter dimensions of the second matrix.\n");
	do
	{	
		printf("**NOTE**\nThe number of rows of the second matrix needs to equal the number of columns of the first matrix!\n");
		EnterMatrixDimensions(&RowsB, &ColumnsB);
	} while (RowsB != ColumnsA);//Making sure multiplication can be performed.
	printf("Enter elements of the first matrix.\n");
	MatrixA = EnterMatrixElements(MatrixA, RowsA, ColumnsA);
	printf("Enter elements of the second matrix.\n");
	MatrixB = EnterMatrixElements(MatrixB, RowsB, ColumnsB);
	int i, j, k;
	MatrixC = malloc(RowsA * sizeof(int*));//Since matrix C will have the dimensions of [RowsA, ColumnsB] we allocate memory first for number of Rows.
	for (i = 0; i < RowsA; i++)
	{
		MatrixC[i] = malloc(ColumnsB * sizeof(int*));//Allocating memory for matrix C; for each RowA allocating ColumnsB.
		for (j = 0; j < ColumnsB; j++)
		{
			for (k = 0; k < RowsB; k++)
			{//MatrixC[i][j] will have the value of the sum of multiplication of all elements of row i times columns j.
				sum += MatrixA[i][k] * MatrixB[k][j];
			}
			MatrixC[i][j] = sum;
			sum = 0;
		}
	}
	FreeMatrix(MatrixA, RowsA);
	FreeMatrix(MatrixB, RowsB);
	printf("The product of the matrices has the following form.\n");
	PrintMatrix(MatrixC, RowsA, ColumnsB);
	FreeMatrix(MatrixC, RowsA);
}
void TransposedMatrix(int **MatrixA, int **MatrixC)
{//Function for createing a transposed matrix.
	int Rows, Columns;
	printf("Enter dimensions of the matrix.\n");
	EnterMatrixDimensions(&Rows, &Columns);
	printf("Enter elements of the matrix\n");
	MatrixA = EnterMatrixElements(MatrixA, Rows, Columns);
	int i, j;
	MatrixC = malloc(Columns * sizeof(int*));//If A has dimensions [Rows, Columns], C will have [Columns, Rows]. 
	for(i = 0; i < Columns; i++)
	{
		MatrixC[i] = malloc(Rows * sizeof(int));//First allocate memory for C, then transpose values from A to C.
	}
	for(i = 0; i < Rows; i++)
	{
		for(j = 0; j < Columns; j++)
		{
			MatrixC[j][i] = MatrixA[i][j];
		}
	}
	FreeMatrix(MatrixA, Rows);
	printf("The transposed matrix has the following form:\n");
	PrintMatrix(MatrixC, Columns, Rows);
	FreeMatrix(MatrixC, Columns);
}
void ZigZagMatrix(int **Matrix)
{//Function to print out matrix in zigzag form. 1 row left to right, next right to left, and so on.
	int Rows, Columns;
	printf("Enter dimensions of the matrix.\n");
	EnterMatrixDimensions(&Rows, &Columns);
	printf("Enter the elements of the matrix.\n");
	Matrix = EnterMatrixElements(Matrix, Rows, Columns);
	printf("Here is the zigzag representation of the matrix.\n");
	int i, j;
	for(i = 0; i < Rows; i++)
	{
		if(!(i%2))
		{//Every even row prints from left to right (first row is 0). Every odd row prints from right to left.
		for(j = 0; j < Columns; j++)
		{
		printf(" %d ", Matrix[i][j]);
		}
		//printf("\n");
		}
		else
		{
		for(j = Columns - 1; j >= 0; j--)
		{
		printf(" %d ", Matrix[i][j]);
		}
		//printf("\n");
		}
	}
	FreeMatrix(Matrix, Rows);
}
void CheckNeighbours(int **Matrix)
{//Function which looks for the even sum of neighbouring elements and prints all valid results. 
	int Rows, Columns;
	printf("Enter dimensions of the matrix.\n");
	EnterMatrixDimensions(&Rows, &Columns);
	printf("Enter elements of the matrix.\n");
	Matrix = EnterMatrixElements(Matrix, Rows, Columns);	
	int i, j, m, n, numOfOnes = 0;
	printf("The following numbers have an even sum of neighbouring elements:\n");
	for(m = 0; m < Rows; m++)
	{
		for(n = 0; n < Columns; n++)
		{
			for(i = m - 1; i <= m + 1; i++)
			{
			if(i < 0 || i >= Rows)//If out of bounds, skip CheckOnes.
			{
				continue;
			}
			for(j = n - 1; j <= n + 1; j++)
			{
				if(j < 0 || j >= Columns)//If out of bounds, skip CheckOnes.
				{
					continue;
				}
				if(i == m && j == n)//If the number is the one we are checking, skip CheckOnes.
				{
					continue;
				}
				CheckOnes(Matrix[i][j], &numOfOnes);//If the neighbour exists
			}
			}
			if(!(numOfOnes % 2))//If sum is even, print number and its location. Computer counts from 0, not 1. Thereforre, m + 1 and n + 1.
			{
				printf("%d in row %d and column %d\n", Matrix[m][n], m + 1, n + 1);
			}
			numOfOnes = 0;
		}
	}
	FreeMatrix(Matrix, Rows);
}
int main()
{
	printf("\n\n  ***!Welcome User!***\n\n");
	int **MatrixA, **MatrixB, **MatrixC, k;
	while(1)
	{
		switch(PrintMenu())
		{
			case 1:
				SumOf2Matrices(MatrixA, MatrixB, MatrixC);
				break;
			case 2:
				Minus2Matrices(MatrixA, MatrixB, MatrixC);
				break;
			case 3:
				ScalarMultiplication(MatrixA, MatrixC);
				break;
			case 4:
				Product2Matrixes(MatrixA, MatrixB, MatrixC);
				break;
			case 5:
				TransposedMatrix(MatrixA, MatrixC);
				break;
			case 6:
				ZigZagMatrix(MatrixA);
				break;
			case 7:
				CheckNeighbours(MatrixA);
				break;
			case 8:
				return 0;
				break;
			default:
				printf("\nYou have entered an invalid option. Please try again.\n");
				break;
		}
	}
}
