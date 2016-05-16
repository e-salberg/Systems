/*
	Eric Salberg
	2/19/16
	CSE 2421, T/Th 5:20PM
	0x0519445
	
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lab4.h"

//adds cels to the temperature part of matrix and den to the density part
int add(spacial_data** matrix, double cels, double den)
{
	int err = 0;
	spacial_data*  data = *matrix;	
	
	//checks for overflow	
	if((cels > 1.0 && data->celsius + cels < data->celsius) || (den > 1.0 && data->density + den < data->density))
	{
		err = 1;
	}

	else
	{
		data->celsius += cels;
		data->density += den;	
	}
	*matrix = data;
	return err;
}

//multipes cels and the temerature part of matrix; multipes den and the density part of matrix
int multiply(spacial_data** matrix, double cels, double den)
{
	int err = 0;
	spacial_data* data = *matrix;
	
	//checks for overflow
	if((cels > 1.0 && data->celsius * cels < data->celsius) || (den > 1.0 && data->density * den < data->density))
	{
		err = 1;
	}

	else
	{
		data->celsius *= cels;
		data->density *= den;	
	}
	*matrix = data;
	return err;
}

//if cels is 1.0 then takes the square root of the temperature part of matrix; if den is 1.0 then takes the square root of the density part of matrix
int squareRoot(spacial_data** matrix, double cels, double den)
{
	int err= 0;
	spacial_data* data = *matrix;	
	
	//checks if trying to take the sqrt of a negative number
	if(cels == 1.0)
	{
		if(data->celsius < 0.0)
		{
			err = 1;
		}
		
		else
		{
			data->celsius = sqrt(data->celsius);
		}
	}
	if(den == 1.0)
	{
		if(data->density < 0.0)
		{
			err = 1;
		}
		
		else
		{
			data->density = sqrt(data->density);
		}
	}
	*matrix = data;
	return err;
}

//if cels is 1.0 then squares the temperature part of matrix; if den is 1.0 then squares the density part of matrix
int square(spacial_data** matrix, double cels, double den)
{
	int err = 0;
	spacial_data*  data = *matrix;
	if(cels == 1.0)
	{
		//checks for overflow for the temperature
		if(data->celsius > 1.0 && data->celsius * data->celsius < data->celsius)
		{
			err = 1;
		}
		else
		{
			data->celsius *= data->celsius;
		}
	}
	if(den == 1.0)
	{
		//checks for overflow for the density
		if(data->density > 1.0 && data->density * data->density < data->density)
		{
			err = 1;
		}
		else
		{
			data->density *= data->density;
		}
	}
	*matrix = data;
	return err;
}
