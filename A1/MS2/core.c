/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 2
Full Name  : Renato Cordova
Student ID#: 153325238
Email      : rcordova3@myseneca.ca
Section    : NDD

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
//
// Copy your work done from Milestone #1 (core.c) into this file
// - Organize your functions in the same order as they are listed in the core.h file
// - Also copy the commented "sections" to help with finding functions quickly!
//

#include "core.h"

// As demonstrated in the course notes:
// https://intro2c.sdds.ca/D-Modularity/input-functions#clearing-the-buffer
// Clear the standard input buffer
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

// Wait for user to input the "enter" key to continue
void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}

int inputInt(void) {

    char newLine = 'x';
    int value;

    while (newLine != '\n') {
        scanf("%d%c", &value, &newLine);
        if (newLine != '\n') {
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        }
    }
    return value;
}

int inputIntPositive(void) {
    int value;

    do {
        value = inputInt();
        if (value <= 0) {
            printf("ERROR! Value must be > 0: ");
        }
    } while (value <= 0);

    return value;

}

int inputIntRange(int min, int max) {
    int value, flag = 1;

    do {
        flag = 1;
        value = inputInt();
        if (value < min || value > max) {
            flag = 0;
            printf("ERROR! Value must be between %d and %d inclusive: ", min, max);
        }

    } while (!flag);

    return value;
}

char inputCharOption(const char validChars[]) {
    char value, newLine = 'x';
    int i, flag = 1;

    do {
        flag = 1;
        scanf(" %c%c", &value, &newLine);
        if (newLine != '\n') {
            clearInputBuffer();
            printf("ERROR: Character must be one of [%s]: ", validChars);
            flag = 0;
        }
        else {
            for (i = 0; validChars[i] != '\0'; i++) {
                if (value == validChars[i]) {
                    flag = 1;
                    break;
                }
                else {
                    flag = 0;
                }
            }
            if (!flag) {
                printf("ERROR: Character must be one of [%s]: ", validChars);
            }
        }
    } while (!flag);

    return value;
}

void inputCString(char* str, int minLen, int maxLen) {
    int flag = 0, length;
    do {
        flag = 1;
        scanf("%[^\n]", str);

        length = 0;
        while (str[length] != '\0') {
            length++;
        }

        clearInputBuffer();

        if (length < minLen) {
            flag = 0;
            if (minLen == maxLen) {
                printf("ERROR: String length must be exactly %d chars: ", minLen);
            }
            else {
                printf("ERROR: String length must be between %d and %d chars: ", minLen, maxLen);
            }

        }
        else if (length > maxLen) {
            flag = 0;
            if (minLen == maxLen) {
                printf("ERROR: String length must be exactly %d chars: ", minLen);
            }
            else {
                printf("ERROR: String length must be no more than %d chars: ", maxLen);
            }
        }
    } while (!flag);
}

void displayFormattedPhone(const char* phoneNumber) {
    int i;

    if (!phoneNumber) {
        printf("(___)___-____");
        return;
    }

    for (i = 0; i < 10 && phoneNumber[i] != '\0'; i++) {
        if (!(phoneNumber[i] >= '0' && phoneNumber[i] <= '9')) {
            break;
        }
    }

    if (i == 10 && phoneNumber[i] == '\0') {
        printf("(%c%c%c)%c%c%c-%c%c%c%c", phoneNumber[0], phoneNumber[1], phoneNumber[2],
            phoneNumber[3], phoneNumber[4], phoneNumber[5], phoneNumber[6],
            phoneNumber[7], phoneNumber[8], phoneNumber[9]);
    }
    else {
        printf("(___)___-____");
    }
}