#include<unistd.h>
#include <stdio.h>
#include<stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
	//mode params
	int deb_mode=0, enc_mode=0, addition=0, read_mode=0;

	//index params
	int j, i, enc_arg_index, enc_char_index=2, read_arg_index;
	//read char
	int c;

	FILE *in_file=stdin;
	

	//check mode
	for (i = 1; i < argc; i++){
		if(strcmp(argv[i], "-D")==0)
			if(deb_mode==0){
				deb_mode=1;
				for (j = 1; j < argc; j++)
					puts(argv[j]);	
			}
		//set addition
		if((strncmp(argv[i], "+e", 2))==0){
			enc_mode=1;
			addition=1;
			enc_arg_index=i;	
		}
		//set substruction
		if((strncmp(argv[i], "-e", 2))==0){
			enc_mode=1;
			enc_arg_index=i;
		}
		if(strncmp(argv[i], "-i", 2)==0){
			read_mode=1;
			read_arg_index=i;
		}		
	}

	int arg_size = strlen(argv[read_arg_index])-2;
	char *file_adress = calloc(arg_size, 1);
	strncpy(file_adress, argv[read_arg_index] + 2, arg_size);
	if(read_mode==1)
	 	in_file=fopen(file_adress, "r");

	//read
	c=fgetc(in_file);

	 while(c!=EOF){
	 		 	if(deb_mode==1)
	 		fprintf(stderr, "%#02x\t", c);
			//encryption mode
			if(enc_mode==1){
				//addition
				if(addition==1){
					fputc(c+argv[enc_arg_index][enc_char_index], stdout);
					if(deb_mode==1)
			 			fprintf(stderr, "%#02x\n", c+argv[enc_arg_index][enc_char_index]);				
			}
			//substruction
			else{
				fputc(c-argv[enc_arg_index][enc_char_index], stdout);
				if(deb_mode==1)
			 		fprintf(stderr, "%#02x\n", c-argv[enc_arg_index][enc_char_index]);	
			}
			enc_char_index++;	
			if (enc_char_index>strlen(argv[enc_arg_index])-1)
		                enc_char_index=2;
		        if(c =='\n'){
                		enc_char_index=2;
                		fputc('\n', stdout);
            		}
		}
		//not encryption mode
		else{
	 		if ((c>='A') & (c<='Z')){
 				if(deb_mode==1)
	 				fprintf(stderr, "%#02x\n", c+('a'-'A'));
	 			putc(c+('a'-'A'), stdout);
	 		}
	 		else{
	 			if(deb_mode==1)
	 				fprintf(stderr, "%#02x\n", c);
	 			putc(c, stdout);
	 		}
		}
	 	c=fgetc(in_file);
	}
	free(in_file);
}
