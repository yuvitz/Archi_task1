//#include<unistd.h>
#include <stdio.h>
int main()
{
	int c;
	c=fgetc(stdin);
	while(c!=EOF){
		if ((c>64) & (c<91))
			putc(c+32, stdout);
		else
			putc(c, stdout);
		c=fgetc(stdin);
	}
    return 0;
}