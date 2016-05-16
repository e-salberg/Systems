#include <stdio.h>

typedef struct spacial_data
{
    //temperature is in celsius
    double celsius;
    //density is in kg/m^2
    double density;
} spacial_data;

int add(spacial_data**, double, double);

int multiply(spacial_data**, double, double);

int squareRoot(spacial_data**, double, double);

int square(spacial_data**, double, double);
