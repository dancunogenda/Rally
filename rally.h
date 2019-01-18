//
//  projekti.h
//  C Programming Project
//
//  Created by Dancun Ogenda on 09/04/2018.
//  Copyright © 2018 Dancun Ogenda. All rights reserved.
//

/*
 A Kankkunen Renault
 A Latvala Volkswagen
 U Kankkunen 0 52 16
 U Latvala 1 01 20
 U Kankkunen 0 49 50
 U Latvala 0 47 15
 L
 W tulokset
 Q
 */

#ifndef rally_h
#define rally_h

#include <stdio.h>

struct Time
{
    int hours;
    int minutes;
    int seconds;
};

struct Driver
{
    char *lastname;
    char *team;
    struct Time overallTime;
};

struct Driver* addDriver(char *lastname, char *team, struct Driver *driverTimes, int numberOfElements);
int updateTotalTime(char *lastname, int hours, int minutes, int seconds, struct Driver *driverTimes, int numberOfElements);
int printResults(struct Driver *driverTimes, int numberOfDrivers);
int saveResults(char *tulokset, struct Driver *driverTimes, int numberOfElements);
int loadResults(char *tulokset, struct Driver *driverTimes, int numberOfElements);
int compareFunction(const void *driverTime1, const void *driverTime2);
#endif /* projekti_h */


