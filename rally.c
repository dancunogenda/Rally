//
//  projekti.c
//  C Programming Project
//
//  Created by Dancun Ogenda on 09/04/2018.
//  Copyright © 2018 Dancun Ogenda. All rights reserved.
//

#include "rally.h"
#include <stdlib.h>
#include <string.h>

struct Driver* addDriver(char *lastname, char *team, struct Driver *driverTimes, int numberOfElements)
{
    driverTimes = realloc(driverTimes,  numberOfElements*sizeof(struct Driver));
    driverTimes[numberOfElements - 1].lastname = malloc((strlen(lastname) + 1 )*sizeof(char));
    driverTimes[numberOfElements - 1].team = malloc((strlen(team) + 1 )*sizeof(char));
    strcpy(driverTimes[numberOfElements - 1].lastname, lastname);
    strcpy(driverTimes[numberOfElements - 1].team, team);
    
    driverTimes[numberOfElements - 1].overallTime.hours = 0;
    driverTimes[numberOfElements - 1].overallTime.minutes = 0;
    driverTimes[numberOfElements - 1].overallTime.seconds = 0;
    
    return driverTimes;
    
}

int updateTotalTime(char *lastname, int hours, int minutes, int seconds, struct Driver *driverTimes, int numberOfElements)
{
    int FLAG = 0;
    
    for(int i = 0; i < numberOfElements; i++)
    {
        if (strcmp(driverTimes[i].lastname, lastname) == 0)
        {
            driverTimes[i].overallTime.hours += hours;
            driverTimes[i].overallTime.minutes += minutes;
            
            FLAG = 1;
            
            driverTimes[i].overallTime.seconds += seconds;
            if(driverTimes[i].overallTime.seconds >= 60)
            {
                driverTimes[i].overallTime.minutes += driverTimes[i].overallTime.seconds / 60;
                driverTimes[i].overallTime.seconds = driverTimes[i].overallTime.seconds % 60;
            }
            if(driverTimes[i].overallTime.minutes >= 60)
            {
                driverTimes[i].overallTime.hours += driverTimes[i].overallTime.minutes / 60;
                driverTimes[i].overallTime.minutes = driverTimes[i].overallTime.minutes % 60;
            }
        }
    }
    if(FLAG == 0)
    {
        printf("Driver Not Yet Added!\n ");
    }
    return 0;
}

int compareFunction(const void *driverTime1, const void *driverTime2)
{
    const struct Driver *testSort1 = driverTime1;
    const struct Driver *testSort2 = driverTime2;
    int totalTime1 = (testSort1->overallTime.hours*60*60) + (testSort1->overallTime.minutes*60) + (testSort1->overallTime.seconds);
    int totalTime2 = (testSort2->overallTime.hours*60*60) + (testSort2->overallTime.minutes*60) + (testSort2->overallTime.seconds);
    return (totalTime1 - totalTime2);
}

int printResults(struct Driver *driverTimes, int numberOfDrivers)
{
    qsort(driverTimes, numberOfDrivers, sizeof(struct Driver), compareFunction);
    for(int i = 0; i < numberOfDrivers; i++)
    {
        printf("%s %s %d:%d:%d\n", driverTimes[i].lastname, driverTimes[i].team,
               driverTimes[i].overallTime.hours, driverTimes[i].overallTime.minutes,
               driverTimes[i].overallTime.seconds);
    }
    return 0;
}


int saveResults(char *tulokset, struct Driver *driverTimes, int numberOfElements)
{
    FILE *file_ptr = fopen(tulokset, "a");
    if(!file_ptr)
    {
        printf("File cannot be openned for Saving! ");
        return -1;
    }
    
    int i = 0;
    for(i = 0; i < numberOfElements; i++)
    {
        fprintf(file_ptr, "%s %s %d %d %d\n", driverTimes[i].lastname,driverTimes[i].team,driverTimes[i].overallTime.hours, driverTimes[i].overallTime.minutes,
                driverTimes[i].overallTime.seconds);
    }
    fclose(file_ptr);
    return 0;
}
int loadResults(char *tulokset, struct Driver *driverTimes, int numberOfElements)
{
    FILE *file_ptr = fopen(tulokset, "r");
    if(!file_ptr)
    {
        printf("File cannot be openned for Loading! ");
        return -1;
    }
    
    for(int index = 0; index < numberOfElements; index++)
    {
        fscanf(file_ptr, "%s %s %d %d %d", driverTimes[index].lastname,driverTimes[index].team,&driverTimes[index].overallTime.hours, &driverTimes[index].overallTime.minutes,
               &driverTimes[index].overallTime.seconds);
        
    }
    fclose(file_ptr);
    return 0;
}

int main(int argc, const char * argv[])
{
    char buffer1[500];
    char buffer2[500];
    int numberOfElements = 0;
    
    struct Driver *driverTimes = NULL;
    int hours, minutes, seconds;
    int FLAG = 1;
    
    char firstLetter;
    printf("Please enter an input: \n");
    while(FLAG)
    {
        scanf("%c", &firstLetter);
        switch (firstLetter) {
            case 'A':
                scanf("%s %s", buffer1, buffer2);
                numberOfElements++;
                driverTimes = addDriver(buffer1  , buffer2, driverTimes, numberOfElements);
                break;
                
            case 'U':
                scanf("%s %d %d %d", buffer1, &hours, &minutes, &seconds);
                updateTotalTime(buffer1, hours, minutes, seconds, driverTimes, numberOfElements);
                break;
                
            case 'L':
                printResults(driverTimes, numberOfElements);
                break;
                
            case  'W':
                scanf("%s", buffer1);
                saveResults(buffer1, driverTimes, numberOfElements);
                break;
                
            case 'O':
                scanf("%s", buffer2);
                loadResults(buffer2, driverTimes, numberOfElements);
                break;
                
            case 'Q':
                FLAG = 0;
                break;
                
            default:
                break;
        }
    }
    int i = 0;
    while(i < numberOfElements)
    {
        free(driverTimes[i].lastname);
        free(driverTimes[i].team);
    }
    free(driverTimes);
}


















