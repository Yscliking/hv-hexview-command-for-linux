#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
int main(int argv,char*argvs[])
{
	if(argv !=2)
	{
		printf("Usage %s <filename> \n",argvs[0]);
		return 0;
	}
	int fd = open(argvs[1],O_RDONLY); //open a file
	if(fd < 0)
	{
		perror("FILE OPEN FAILED");
		return 0;
	}
	int i =0;	//this is a var for calc the chunk nums such as 16/8 =2 chunk is 2
	int les;	//this is a var for storing the file small picess FILE_SIZE%16 will equal the les value
			//
	unsigned int line =0x00;	// as its name ,it records the lines
	while(1)
	{
		unsigned char buf[16];	// store the 16 Byte binnary
		les = read(fd,buf,16);
		if (les !=16 )	// it means that you will be in the end of file
		{
			printf("%08x  ",line++);
			for(i =0 ; i<les;i++)
			{
				printf("%02x  ",buf[i]);
				if(i == 7)
				{
					printf("\n");	// if les is more than 8 ,it will change line for neat output
				}
			}
			printf("\n");
			close(fd);
			break;
		}	
		printf("%08x  ",line++);
		for(i =0 ; i<2;i++)	
		{
			printf("%02x  %02x  %02x  %02x  %02x  %02x  %02x  %02x  ",buf[0+i],buf[1+i],buf[2+i],buf[3+i],buf[4+i],buf[5+i],buf[6+i],buf[7+i]);
		}
		printf("\n");
	}
	
	return 0;
}
