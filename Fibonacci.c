//Mykell Spencer
//ID: 8054
//COP 4415 Data Structures Section 01
//Huge Fibonacci
//Started: February 21, 2021
//Finished: March 6, 2021

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "Fibonacci.h"

//This helper function helps determine if the length of p is larger than q or not
int isPlenLarger(HugeInteger *p, HugeInteger *q)
{
    return (p->length > q->length) ? 1 : 0;
}


// Count digits
int findLength(unsigned int n) {
    int digits = 0;
    do {
        digits++;
        n /= 10;
    } while (n > 9); {
        return digits;
    }
}

//==========================END OF HELPER FUNCTIONS============================
//=============================================================================
//=============================================================================


HugeInteger *hugeAdd(HugeInteger *p, HugeInteger *q)
{   //Testing to see if the values are NULL. If not, then continue.
    if (p == NULL || q == NULL)
        return NULL;
    else
    {
        int x, size = 0;
        HugeInteger *hugeAdder = NULL;
        hugeAdder = malloc(sizeof(HugeInteger));
        if(hugeAdder == NULL)
            return NULL;
        if(isPlenLarger(p, q) == 1)
            hugeAdder->digits = calloc(p->length + 7, sizeof(int));
        else
            hugeAdder->digits = calloc(q->length + 7, sizeof(int));

        //If the memory allocation does not work, remove the struct as well as the reference
        if(hugeAdder->digits == NULL) {
            free(hugeAdder->digits);
            free(hugeAdder);
            hugeAdder = NULL;
            return NULL;
        }

        //Always start with the largest struct first
        if(isPlenLarger(p, q) == 1) {
            //from 0 to the length of the small struct
            for (x = 0; x < q->length; x++){
                //Huge Addition
                hugeAdder->digits[x] = hugeAdder->digits[x] + q->digits[x] + p->digits[x];
                //If the Huge Add > 9, divide it by 10 and store the remainder at x
                if(hugeAdder->digits[x] > 9){
                    hugeAdder->digits[x + 1] = hugeAdder->digits[x] / 10;
                    //remainder
                    hugeAdder->digits[x] = hugeAdder->digits[x] % 10;
                }

                //If any extra number places are created, update the length of the number
                if(hugeAdder->digits[p->length])
                    size++;
                size++;
            }
            // Now repeat the same process for other structs to the larger digit's length
            for(x = q->length; x < p->length; x++){
                hugeAdder->digits[x] += p->digits[x];
                if(hugeAdder->digits[x] > 9){
                    hugeAdder->digits[x + 1] = hugeAdder->digits[x] / 10;
                    hugeAdder->digits[x] = hugeAdder->digits[x] % 10;
                }
                if(hugeAdder->digits[p->length])
                    size++;
                size++;
            }
            hugeAdder->length = size;
        }
        else{
            for(x = 0; x < p->length; x++) {
                hugeAdder->digits[x] = hugeAdder->digits[x] + p->digits[x] + q->digits[x];
                if(hugeAdder->digits[x] > 9){
                    hugeAdder->digits[x + 1] = hugeAdder->digits[x] / 10;
                    hugeAdder->digits[x] = hugeAdder->digits[x] % 10;
                }
                if(hugeAdder->digits[q->length])
                    size++;
                size++;
            }
            for(x = p->length; x < q->length; x++){
                hugeAdder->digits[x] = q->digits[x];
                if(hugeAdder->digits[x] > 9){
                    hugeAdder->digits[x + 1] = hugeAdder->digits[x] / 10;
                    hugeAdder->digits[x] = hugeAdder->digits[x] % 10;
                }
                if(hugeAdder->digits[q->length])
                    size++;
                size++;
            }
            hugeAdder->length = size;
        }
        return hugeAdder;
        }
}

//===================================ENDS HUGE ADDITION======================================
//===========================================================================================
//===========================================================================================

//This function is to free the memory and to clear anything else
HugeInteger *hugeDestroyer(HugeInteger *p)
{
    //ONly need to free p because if either p or q is NULL, then the entire process will be NULL
    if (p != NULL){
        if(p->digits != NULL)
            free(p->digits);
        free(p);
        p = NULL;
        return NULL;
    }
    else
        return NULL;
}


//===================================ENDS HUGE DESTROYER=====================================
//===========================================================================================
//===========================================================================================


//This function converts the number on the string to HugeInteger
HugeInteger *parseString(char *str)
{
    if (str == NULL)
        return NULL;

    //Acquire how long the string is
    int strLength = strlen(str);
    HugeInteger *parsedString = NULL;
    parsedString = malloc(sizeof(HugeInteger));

    //If the string is not NULL, then we will allocate the memory
    if(parsedString == NULL)
        return NULL;

    parsedString->length = strLength;
    parsedString->digits = calloc(parsedString->length, sizeof(int));

    if(parsedString->digits == NULL)
        return NULL;

    int counter = 0;
    for(int i = parsedString->length - 1; i >= 0; i--)
    {
        parsedString->digits[counter] = str[i];

        //Converts to integers
        switch(parsedString->digits[counter])
        {
        case 48:
            parsedString->digits[counter] = 0;
            break;
        case 49:
            parsedString->digits[counter] = 1;
            break;
        case 50:
            parsedString->digits[counter] = 2;
            break;
        case 51:
            parsedString->digits[counter] = 3;
            break;
        case 52:
            parsedString->digits[counter] = 4;
            break;
        case 53:
            parsedString->digits[counter] = 5;
            break;
        case 54:
            parsedString->digits[counter] = 6;
            break;
        case 55:
            parsedString->digits[counter] = 7;
            break;
        case 56:
            parsedString->digits[counter] = 8;
            break;
        case 57:
            parsedString->digits[counter] = 9;
            break;
        default:
            parsedString->digits[counter] = 0;
            break;
        }
        counter++;
    }
    //To check if the parsed sting is valid or NULL
    return (parsedString == NULL) ? NULL : parsedString;
}


//===================================ENDS PARSE STRING=======================================
//===========================================================================================
//===========================================================================================


HugeInteger *parseInt(unsigned int n)
{
    int i = 0;
    HugeInteger *parsedInt;
    parsedInt = malloc(sizeof(HugeInteger));

    if(parsedInt == NULL)
        return NULL;
    else if (n < 10)
        parsedInt->length = findLength(n);
    else
        parsedInt->length = (findLength(n) + 1);

    parsedInt->digits = calloc(parsedInt->length + 1, sizeof(int));

    //If the allocation fails, destroy struct
    if(parsedInt->digits == NULL)
    {
        free(parsedInt);
        parsedInt == NULL;
        return NULL;
    }

    for(i = 0; i < parsedInt->length; i++)
    {
        parsedInt->digits[i] = n % 10;
        n /= 10;
    }

    return parsedInt;
}

//===================================ENDS PARSE INT =========================================
//===========================================================================================
//===========================================================================================


unsigned int *toUnsignedInt(HugeInteger * p)
{
    //Creating our structs for both integer types
    HugeInteger *integerHuge = parseInt(INT_MAX);
    HugeInteger *uIntHuge = parseInt(UINT_MAX);

    int x = 0, y, z =0, power = 1, unsignedArray[uIntHuge->length];
    unsigned int temp = UINT_MAX;
    unsigned int *unsignedInt = malloc(sizeof(unsigned int));

    if(unsignedInt == NULL)
        return NULL;

    *unsignedInt = 0;

    if(p == NULL || p->length > integerHuge->length || p->length > uIntHuge->length)
        return NULL;
    if(p->length == uIntHuge->length)
    {
        while(x < uIntHuge->length)
        {
            unsignedArray[x] = temp % 10;
            temp /= 10;
            x++;
        }

        for (y = p->length - 1; y >= 0; y--)
        {
            if(p->digits[y] < unsignedArray[y])
                break;
            if(p->digits[y] > unsignedArray[y])
                return NULL;
        }
    }

    while(z < p->length)
    {
        *unsignedInt += (p->digits[z] * power);
        power *= 10;
        z++;
    }

    return unsignedInt;
}


//===================================ENDS UNSIGNED INT=======================================
//===========================================================================================
//===========================================================================================

//This function calculates the Fibonacci sequence
HugeInteger *fib(int n)
{
    HugeInteger *x = NULL, *y = NULL, *z = NULL, *result = NULL;
    int j, m = 0, count = -1;

    //Initializing our structs x, y, and z
    x = parseInt(1); y = parseInt(2); z = parseInt(3);

    if (n == 0)
        return parseInt(0);
    else if (n == 1 || n == 2)
        return parseInt(1);

    for (j = 0; j < n; j++)
    {
        //Our base cases for the Fibonacci sequence are displayed here
        if (j == 0 || j == 1 || j == 2)
        {
            count ++;
            continue;
        }
        //The addition arithmetic of the Fibonacci Sequence

        if(j % 3 == 0)
        {
            if (m == 0)
                hugeDestroyer(z);
            z = hugeAdd(y, x);
            hugeDestroyer(x);
            count++;
        }
        if(j % 3 == 1)
        {
            if(m == 0)
                hugeDestroyer(x);
            x = hugeAdd(z, y);
            hugeDestroyer(y);
            count++;
        }
        if(j % 3 == 2)
        {
            if(m == 0)
                hugeDestroyer(y);
            y = hugeAdd(x, z);
            hugeDestroyer(z);
            count++;
        }
        m = 1;
    }

    if(count % 3 == 0)
        result = z;
    else if(count % 3 == 1)
        result = x;
    else if(count % 3 == 2)
        result = y;

    return result;
}

//===================================ENDS FIB ===============================================
//===========================================================================================
//===========================================================================================

double difficultyRating(void)
{
    return 4.6; //A lot of review and research needed to be made. This project was increasingly difficult because of its length
}

double hoursSpent(void)
{
    return 22; //A lot of this code was made by trial and error. With that, research on topics was done to figure out the code
}
