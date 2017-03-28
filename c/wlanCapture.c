#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define isxdigit(x) (((x) >= '0' && (x) <= '9') || ((x) >= 'A' && (x) <= 'Z') || ((x) >= 'a' && (x) <= 'z'))
typedef unsigned char uint8;

int transMacStrToCfg(char * cfgPtr, int macMaxCnt, char * strPtr, int strLenLimit)
{
	int  	en[6];
	char 	*val;
	char 	*tempStr;
	uint8 	count=0;
	int 	i, len;
	uint8	numAssigned = 0;
	char	*str;
	int		error = 0;
	int		tmp = 0;
	int		ret = -1;
	if( (len = strlen(strPtr)) > strLenLimit )
	{
		printf("transMaxStrToCfg: mac str length exceed the limit\n");
		return -1;
	}
	printf("len = %d\n", len);
	str = (char*)malloc(len+1);
	strcpy(str, strPtr);
	val = strtok_r(str, ", ", &tempStr);
	if(!val)
	{
		printf("transMacFilterStringToCfg : strtok_r failed \n");
		free(str);
		return -1;
	}
	while(val)
	{
		if(count == macMaxCnt)
		{
			ret = -1;
			break;
		}
		if(strlen(val) == 12)
		{
			for(i=0; i<12; i++)
			{
				if(!isxdigit((int)val[i]))
				{
					error = 1;
					break;
				}
			}

			if(error)
			{
				ret = -1;
				break;
			}
			numAssigned = sscanf(str, "%02x%02x%02x%02x%02x%02x",
							&en[0], &en[1], &en[2], &en[3], &en[4], &en[5]);
		}
  		else if(strlen(val) == 17)
		{
			for(i=0; i<17; i++)
			{
				if((i-2)%3 == 0)
				{
					i++;
				}
				if(!isxdigit((int)val[i]))
				{
					error = 1;
					break;
				}
			}
			if(error)
			{
				ret = -1;
				break;
			}
			numAssigned = sscanf(val, "%02x:%02x:%02x:%02x:%02x:%02x",
							&en[0], &en[1], &en[2], &en[3], &en[4], &en[5]);
			if(numAssigned != 6)
			{
				numAssigned = sscanf(val, "%02x-%02x-%02x-%02x-%02x-%02x",
							&en[0], &en[1], &en[2], &en[3], &en[4], &en[5]);
			}
		}
		else
		{
			ret = -1;
			break;
		}

		if(numAssigned != 6)
		{
			ret = -1;
			break;
		}

		for (i = 0; i < 6; i++)
		{
			*cfgPtr = (char)en[i];
			printf("char en = %c, dec en = %d, hex en = %02x\n", *cfgPtr,en[i], en[i]); 
			tmp += en[i];
			cfgPtr++;
		}

		/* skip the all zero mac*/
		if(tmp == 0)
		{
			cfgPtr -= 6;
		}
		tmp = 0;
		
		count++;
		if(count < macMaxCnt)
		{
			sprintf(strPtr, "%02X:%02X:%02X:%02X:%02X:%02X,",
							en[0], en[1], en[2], en[3], en[4], en[5]);
			strPtr += 18;
		}
		else
		{
			sprintf(strPtr, "%02X:%02X:%02X:%02X:%02X:%02X",
							en[0], en[1], en[2], en[3], en[4], en[5]);
		}
		
		val = strtok_r(NULL, ", ", &tempStr);
	}
	/* success in parsing */
	free(str);
	return ret;
}

int main()
{
	int strlenlimit = 1024;
	int macMaxCnt = 5;
	char *strPtr;
	char* cfgPtr;
	strPtr = malloc(strlenlimit);
	cfgPtr = malloc(strlenlimit);
	printf("input mac:\n");
	scanf("%s", strPtr);
	transMacStrToCfg(cfgPtr, macMaxCnt, strPtr, strlenlimit);
	printf("cfgPtr:%s\nstrPtr:%s\n", cfgPtr, strPtr);
	free(strPtr);
	free(cfgPtr);
	return 0;
}
