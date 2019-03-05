#include<unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	int j, i;
	int deb_mode=0;
	int c;

	//check debug mode
	for (i = 0; i < argc; i++){
		if(strcmp(argv[i], "-D")==0)
			if(deb_mode==0){
				deb_mode=1;
				for (j = 1; j < argc; j++)
					puts(argv[j]);	
			}
	}

//read
	c=fgetc(stdin);

	 while(c!=EOF){
	 	if(deb_mode==1)
	 			fprintf(stderr, "0x%x\t", c);
	 	if ((c>64) & (c<91)){
 			if(deb_mode==1)
	 			fprintf(stderr, "0x%x\n", c+32);
	 		putc(c+32, stdout);
	 	}
	 	else{
	 		if(deb_mode==1)
	 			fprintf(stderr, "0x%x\n", c);
	 		putc(c, stdout);
	 	}
	 c=fgetc(stdin);
	}
}