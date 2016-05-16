/*
    Eric Salberg
    2/9/16
    CSE 2421, T/TH 5:20PM
    0x05194445
*/
#include<stdlib.h>
#include<stdio.h>
#include"integer.h"

int main(void)
{
    char c;
    char  op;
    immense_int* num_1 = newImmenseInt();
    immense_int* num_2 = newImmenseInt();
    immense_int* result;

    //gets the first very large integer
    while((c = getchar()) != '\n')
    {
        insert(&num_1,(int)c - '0');        
    }
    
    //gets the second very large integer
    while((c = getchar()) != '\n')
    {
        insert(&num_2,(int)c - '0');        
    }
    
    //gets the opperator 
    op = getchar();
    
    switch(op)
    {
        case '+':
            result = add(num_1, num_2); 
            break;

        case '-':
            result = subtract(num_1, num_2);
            break;
    }

    printImmenseInt(&result);
    destoryImmenseInt(&num_1);
    destoryImmenseInt(&num_2);
    destoryImmenseInt(&result); 
    
    return 0;
}

//creates an new immense_int that points to NULL
immense_int* newImmenseInt(void)
{
    immense_int* head = NULL;
    return head;
}

//frees all the nodes in an immense_int
void destoryImmenseInt(immense_int** head)
{
    immense_int* digit;
    immense_int* next;
    for(digit = *head; digit; digit = next)
    {
        next = digit->next;
        free(digit);
    }
}

//adds 2 immense_ints together and returns the sum as a new immense_int
immense_int* add(immense_int* num_1, immense_int* num_2)
{
    int data, carry = 0, done = 0;
    immense_int* cur_1 = num_1;
    immense_int* cur_2 = num_2;
    immense_int* sum = newImmenseInt();
    
    while(!done)
    {
        data = cur_1->digit + cur_2->digit;

        //takes care of carrys
        if(carry)
        {
            data += 1;
            carry = 0;
        }
        if(data >= 10)
        {
            data -= 10;
            carry = 1;
        }
        
        insert(&sum, data);
        cur_1 = cur_1->next;
        cur_2 = cur_2->next;

        //checks to see if one of the numbers runs out of digits to add
        if(cur_1 == NULL || cur_2 == NULL)
        {
            done = 1;
        }
     }
    
    //check if the numbers are the same length
    if(cur_1 == NULL && cur_2 == NULL)
    {
        //adds a carry if there was one
        if(carry)
        {
            insert(&sum, carry);
        }
    }
    
    //checks if num_2 is longer than num_1
    else if(cur_1 == NULL && cur_2 != NULL)
    {
        //loops until num_2 is empty
        while(cur_2 != NULL)
        {
            data = cur_2->digit;
    
            //takes care of carrys
            if(carry)
            {
                data += 1;
                carry = 0;
            }
            if(data >= 10)
            {
                data -= 10;
                carry = 1;
            }
            insert(&sum, data);
            cur_2 = cur_2->next;
        }
        if(carry)
        {
            insert(&sum, carry);
        }
    }
    
    //checks if num_1 is longer than num_2
    else if(cur_1 != NULL && cur_2 == NULL)
    {
        //loops until num_1 is empty
        while(cur_1 != NULL)
        {
            data = cur_1->digit;

            //takes care of carrys
            if(carry)
            {
                data += 1;
                carry = 0;
            }
            
            if(data >= 10)
            {
                data -= 10;
                carry = 1;
            }
            insert(&sum, data);
            cur_1 = cur_1->next;
        }
        if(carry)
        {
            insert(&sum, carry);
        }
    }
    return sum;
}

//subtracts 2 immense_ints together and returns the difference as a new immense_int
immense_int* subtract(immense_int* num_1, immense_int* num_2)
{
    int data, carry = 0, done = 0;
    immense_int* cur_1 = num_1;
    immense_int* cur_2 = num_2;
    immense_int* dif = newImmenseInt();
    
    while(!done)
    {
        data = cur_1->digit - cur_2->digit;

        //takes care of carrys
        if(carry)
        {
            data -= 1;
            carry = 0;
        }
        if(data < 0)
        {
            data += 10;
            carry = 1;
        }
        
        insert(&dif, data);
        cur_1 = cur_1->next;
        cur_2 = cur_2->next;

        //checks when num_2 is out of digits
        if(cur_2 == NULL)
        {
            done = 1;
        }
     }
    
    //if num_1 is lefted over digits then insert them into dif
    while(cur_1 != NULL)
    {
        data = cur_1->digit;
        if(!carry)
        {
            insert(&dif, data);
        }
        
        else
        {
            data -= 1;
            carry = 0;
            if(data < 0)
            {
                data += 10;
                carry = 1;
            }
            insert(&dif, data);
        }
        cur_1 = cur_1->next;
    }
    return dif;
}
