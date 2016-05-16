/*
    Eric Salberg
    2/9/16
    CSE 2421, T/TH 5:20PM
    0x05194445
*/
typedef struct immense_int {
    int digit;
    struct immense_int* next;
} immense_int;

//creates an new immense_int that points to NULL
immense_int* newImmenseInt(void);

//frees all the nodes in an immense_int
void destoryImmenseInt(immense_int**);

//adds 2 immense_ints together and returns the sum as a new immense_int
immense_int* add(immense_int*, immense_int*);

//subtracts 2 immense_ints together and returns the difference as a new immense_int
immense_int* subtract(immense_int*, immense_int*);

//insert a digit into the immense_int
void insert(immense_int** head, int data)
{
    immense_int* temp = (immense_int*)malloc(sizeof(immense_int));
    temp->digit = data;
    temp->next = *head;
    *head = temp;
}

//remove any and all zeros at the front of numbers
void removePadding(immense_int** head)
{
    immense_int* digit = *head;
    immense_int* temp = *head;
    if(digit->next != NULL)
    {
        while(digit->digit == 0)
        {
            temp = digit; 
            *head = digit->next;
            free(temp);
            digit = *head;
        }
    }
}

//prints an immense_int
void printImmenseInt(immense_int** head)
{
    removePadding(head);
    immense_int* digit = *head;
    while(digit != NULL)
    {
        printf("%d", digit->digit);
        digit = digit->next;
    }
    printf("\n");
}
