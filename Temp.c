#include <stdio.h>
#include <wiringPi.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "ifttt.h"

#define degreeDivision 1000

int main(int argc, char **argv) 
{
	char strTemp[5];
	int flagT;
	int result;
	int i;
	i = 0;
	int lowestTemp;
	lowestTemp = 100;
	int highestTemp;
	highestTemp = 0;
	int currTemp;
	currTemp = 0;
	
	char ct[200];
	char ht[200];
	char lt[200];
	
	FILE *fptr;
	fptr = fopen("/sys/bus/w1/devices/28-01131bcbcd23/w1_slave", "r");

	while (1)
	{
		fseek(fptr, 69, SEEK_SET);
		fread(strTemp, 5, 69, fptr);
	
		if (fptr == NULL || argc >= 2) 
		{
		printf("ERROR!\n");
		exit(1);
		}
	
		result = strtol(strTemp, NULL ,10);
		result = result / degreeDivision;
		printf("%d\n", result);
		currTemp = result;
		
		if (currTemp > highestTemp) 
		{
		highestTemp = currTemp;
		}
		if (currTemp < lowestTemp) 
		{
		lowestTemp = currTemp;
		}
		
		sprintf(ct, "Current Temperature: %d", currTemp);
		sprintf(ht, "Highest Temperature: %d", highestTemp);
		sprintf(lt, "Lowest Temperature: %d", lowestTemp);
		
		
		if (abs(highestTemp - currTemp) || abs(lowestTemp - currTemp) >= 1) 
		{
			ifttt("https://maker.ifttt.com/trigger/alarm_triggered/with/key/hO4F6aLWEqeIPlPaEIKfcpkUW-1ysrpMdrDwRzf4heZ", ct, ht, lt);
		}
	
		rewind(fptr);
	
	}
    
	return 0;
}
