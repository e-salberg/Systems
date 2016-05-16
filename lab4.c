/*
	Eric Salberg
	2/19/16
	CSE 2421, T/TH 5:20PM
	0x05194445
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lab4.h"

int main(void)
{
    //get the dimensions of the matrix
    int i, j, k, x, y, z;
    scanf("%d %d %d ",&x, &y, &z);

    //allocate memory on heap for an 3d array that will store inputed data
    spacial_data**** matrix = (spacial_data****)calloc(x, sizeof(spacial_data***));
    for(i = 0; i < x; i++)
    {
        matrix[i] = (spacial_data***)calloc(y, sizeof(spacial_data**));
    }
    for(i = 0; i < x; i++)
    {
        for(j = 0; j < y; j++)
        {
            matrix[i][j] = (spacial_data**)calloc(z, sizeof(spacial_data*));
        }
    }

	//set up function pointers
	typedef int(*funk_pointer)(spacial_data**, double, double);
	funk_pointer *pointer_array;
	pointer_array = calloc(4, sizeof(funk_pointer*));
	pointer_array[0] = add;
	pointer_array[1] = multiply;
	pointer_array[2] = squareRoot;
	pointer_array[3] = square;
   
    //reads in all the data points
    for(i = 0; i < x; i++)
    {
        for(j = 0; j < y; j++)
        {
            for(k = 0; k < z; k++)
            {
                double celsius, density;
                scanf("%lf %lf\n", &celsius, &density);
		spacial_data* data = (spacial_data*) malloc(sizeof(spacial_data));
		data->celsius = celsius;
		data->density = density;
                matrix[i][j][k] = data;
            }
        }
    } 

	//reads in the instructions and checks if an error was returned
	int op;
	double celsius, density;
	while(scanf("%d %lf %lf\n", &op, &celsius, &density) == 3)
	{
		//scanf("%d %lf %lf\n", op, celsius, density);
		for(i = 0; i < x; i++)
		{
			for(j = 0; j < y; j++)
			{
				for(k = 0; k < z; k++)
				{
					if(pointer_array[op](&matrix[i][j][k], celsius, density))
					{
						printf("Error: funtion failed");
					}
				}
			}
		}
		
	}

	//prints out the contents of the 3d matrix
	for(i = 0; i < x; i++)
	{
		for(j = 0; j < y; j++)
		{
			for(k = 0; k < z; k++)
			{
				printf("%lf %lf\n", matrix[i][j][k]->celsius, matrix[i][j][k]->density);
			}
		}
	}

	//frees the 3d matrix
	for(i = 0; i < x; i++)
	{
		for(j = 0; j < y; j++)
		{
			for(k = 0; k < z; k++)
			{
				free(matrix[i][j][k]);
			}
		}
	}
	for(i = 0; i < x; i++)
	{
		for(j = 0; j < y; j++)
		{
			free(matrix[i][j]);
		}
	}
	for(i = 0; i < x; i++)
	{
		free(matrix[i]);
	}
	free(matrix);
	free(pointer_array);
    	return 0;
}
