#include<unistd.h>
#include <stdio.h>
#include<stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
	//mode params
	int enc_mode=0, addition=0, read_mode=0, write_mode=0;
	//index params
	int  i, enc_arg_index, enc_char_index=2, read_arg_index, write_arg_index;
	//read char
	int c;

	FILE *in_file=stdin;
	FILE *out_file=stdout;

	//check mode
	for (i = 1; i < argc; i++){
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
		//set read
		if(strncmp(argv[i], "-i", 2)==0){
			read_mode=1;
			read_arg_index=i;
		}
		//set write
		if(strncmp(argv[i], "-o", 2)==0){
			write_mode=1;
			write_arg_index=i;
		}		
	}

	if(read_mode==1){
		int read_arg_size = strlen(argv[read_arg_index])-2;
		char *input_file_adress = calloc(read_arg_size, 1);
		strncpy(input_file_adress, argv[read_arg_index] + 2, read_arg_size);
		in_file=fopen(input_file_adress, "r");
	}

	if(write_mode==1){
		int write_arg_size = strlen(argv[write_arg_index])-2;
		char *output_file_adress = calloc(write_arg_size, 1);
		strncpy(output_file_adress, argv[write_arg_index] + 2, write_arg_size);
		out_file=fopen(output_file_adress, "w");
	}
	
	//read
	c=fgetc(in_file);
	while(c!=EOF){
		//encryption mode
		if(enc_mode==1){
			//addition
			if(addition==1){
				fputc(c+argv[enc_arg_index][enc_char_index], out_file);
			}
			//substruction
			else{
				fputc(c-argv[enc_arg_index][enc_char_index], out_file);
			}
			enc_char_index++;	
			if (enc_char_index > strlen(argv[enc_arg_index])-1)
	            enc_char_index=2;
	        if(c =='\n'){
               	enc_char_index=2;
               	fputc('\n', out_file);
           	}
		}
		//not encryption mode
		else{
			if ((c>='A') & (c<='Z'))
				putc(c+('a'-'A'), out_file);
			else
				putc(c, out_file);
		}
		c=fgetc(in_file);
	}
}
