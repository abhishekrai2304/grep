#define _GNU_SOURCE
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<strings.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include "mygrep.h"
static long c_byte = 0;
//static int count=0;
void init(list *l){
	*l = NULL;
}
void red () {
  printf("\033[1;31m");
}
void insert(list *l, char *name){
	node *ptr;
	node *new_node = (node*)malloc(sizeof(node));
	new_node->name = name;
	new_node->next = NULL;
	if(*l == NULL){
		*l = new_node;
		new_node->next = NULL;
	}
	if(*l != NULL){
		ptr = *l;
		while(ptr->next != NULL)
			ptr = ptr->next;	
		ptr->next = new_node;
		new_node->next = NULL;
		
	}

}

void grep_rw(int fd, char *pattern, char *dir_name, char *file_name){
	char line[1024], line1[1024], *token;
	char delim[] = " \t\n.";
	static int i = 0;
	static int count=0;
	while(readLine(fd, line)){
		strcpy(line1, line);
		
		token = strtok(line, delim);
		do{
			if(!(strcmp(token, pattern)))
			{
				printf("\033[0;35m%s/\033[0m\033[0;35m%s:\033[0m%s\n", dir_name, file_name,line1);
				//count++;	
				break;


			}



		}while(token = strtok(NULL, delim));

	}
	

	
}

void grep_w(int fd, char *pattern, char *file_name){
	char line[1024], line1[1024], *token;
	char delim[] = " \t\n.";
	static int i = 0;
	static int count=0;
	while(readLine(fd, line)){
		strcpy(line1, line);
		
		token = strtok(line, delim);
		do{
			if(!(strcmp(token, pattern)))
			{
				printf("\033[0;35m%s\033[0m:%s\n", file_name,line1);
				//count++;	
				break;


			}



		}while(token = strtok(NULL, delim));

	}
	


}


void grep_wc(int fd, char *pattern, char *file_name){
	char line[1024], line1[1024], *token;
	char delim[] = " \t\n.";
	static int i = 0;
	 int count = 0;
	while(readLine(fd, line)){
		strcpy(line1, line);
		
		token = strtok(line, delim);
		do{
			if(!(strcmp(token, pattern)))
			{
				//printf("%s\n", line1);
				count++;	
				break;


			}
			



		}while(token = strtok(NULL, delim));

	}
	
		printf("\033[0;35m%s\033[0m:%d\n", file_name, count);
		//count = 0;
		close(fd);

}
int readPattern(int fd, char *pattern){
	char ch;
	int i = 0; 
	while(read(fd, &ch, 1)){
		if(ch == '\n'){
			pattern[i] = '\0';
			i = 0;
			return 1;
			
		}
		else{
			pattern[i++] = ch;
		}
	}

}
/*void matchedLines_f(int fd1, int fd2){
	char pattern[1024], line[1024], line1[1024], *token, delim[] = " \t\n.";
	start:while(readPattern(fd1, pattern)){
		while(readLine(fd2, line)){
			strcpy(line1, line);
			token  = strtok(line, delim);
			do{
				if(!strcmp(token, pattern)){
					printf("%s\n", line1);
					//break;
				}
			}while(token = strtok(NULL, delim));
			goto start;

		}
		
	    }
	close(fd1);
	close(fd2);	

}*/

void grep_f(int fd1, int fd2){
	char pattern[1024], line[1024], line1[1024], *token, *token1,delim[] = " \t\n.", delim1[] = "\n.";
	char *str;
	
	while(readLine(fd2, line)){
		//printf("line:%s\n", line);
		start: while(readPattern(fd1, pattern)){
			
			str =strstr(line, pattern);
			if(str){
				printf("%s\n", line);
				break;
			}
			else
				goto start;

		}

	}

}
int readLine(int fd, char *line){
	int i = 0;
	char ch;
	while(read(fd, &ch, 1)){
		if(ch == '\n'){
			line[i] = '\0';
			i = 0;
			return 1;

		}
		else{
			line[i++] = ch;
		}
				
	}
}

void grep_Help(int fd){

	char ch;
	while(read(fd, &ch, 1)){
		printf("%c", ch);


	}
	close(fd);
}

void grep_Version(int fd){
	char ch;
	while(read(fd, &ch, 1)){
		printf("%c", ch);


	}
	close(fd);
	



}
void grep_c(int fd, char *pattern, char *file_nm){
char line[1024], line1[1024], *token, delim[] = " \t\n.";
	static int count = 0;
	while(readLine(fd, line)){
		strcpy(line1, line);
		
		token = strtok(line, delim);
		do{
			if(!(strcmp(token, pattern)))
			{
				count++;
				
				break;


			}



		}while(token = strtok(NULL, delim));

	}

	printf("\033[0;35m%s\033[0m:%d\n",file_nm,count);
	count = 0;
	close(fd);



}
void grep_H(int fd, char *pattern, char *file_nm){
	char line[1024], line1[1024], *token,  *str;
		char delim[] = " \t\n.";
		while(readLine(fd, line)){
			strcpy(line1, line);
			
			token = strtok(line, delim);
			do{



				str = strstr(token, pattern);
				
				if(str || !(strcmp(token, pattern)))
				{
					printf("\033[0;35m%s\033[0m:%s\n", file_nm,line1);
					
					break;
	
	
				}



			}while(token = strtok(NULL, delim));

		}
		close(fd);

}

void grep_Hc(int fd, char *pattern, char *file_nm){
	char line[1024], line1[1024], *token,  *str;
	char delim[] = " \t\n.";
	int count = 0;
	
	while(readLine(fd, line)){
		strcpy(line1, line);
			
		token = strtok(line, delim);
		do{
			str = strstr(token, pattern);
			if(str || !(strcmp(token, pattern)))
				{
					++count;
					//printf("%s:%d\n", file_nm,count);
					break;
	
	
				}



			}while(token = strtok(NULL, delim));

		}
	printf("\033[0;35m%s\033[0m:%d\n", file_nm, count);
		close(fd);

}



void grep_h(int fd, char *pattern, char *file_nm){
	char line[1024], line1[1024], *token,  *str;
		char delim[] = " \t\n.";
		while(readLine(fd, line)){
			strcpy(line1, line);
			
			token = strtok(line, delim);
			do{



				str = strstr(token, pattern);
				
				if(str || !(strcmp(token, pattern)))
				{
					printf("\033[0;35m%s\033[0m:%s\n", file_nm, line1);
					
					break;
	
	
				}



			}while(token = strtok(NULL, delim));

		}
		close(fd);

}

void matchedLines(int fd, char *pattern, char *file_nm){
	char line[1024], line1[1024], *token,  *str;
	char delim[] = " \t\n.";
	while(readLine(fd, line)){
		strcpy(line1, line);
		
		token = strtok(line, delim);
		do{



			str = strstr(token, pattern);
			
			if(str || !(strcmp(token, pattern)))
			{
				printf("%s\n", line1);
				
				break;


			}



		}while(token = strtok(NULL, delim));

	}
	close(fd);

}



void grep_b(int fd, char *pattern, char *file_nm){
	char line[1024], line1[1024], *token,  *str;
	char delim[] = " \t\n.";
	
	long  byte_count = 0;;
	 
	while(read_byte(fd, line, &byte_count)){
		strcpy(line1, line);
		//printf("byte offset: %ld\n", byte_count);
		token = strtok(line, delim);
		do{



			str = strstr(token, pattern);
			
			if(!(strcmp(token, pattern)))
			{	
				printf("\033[0;35m%s\033[0m:%ld:%s\n", file_nm,byte_count,line1);
				byte_count = c_byte;	
				break;


			}
			


		}while(token = strtok(NULL, delim));

	}
	close(fd);

}

int read_byte(int fd, char *line, long *byte_count){
	static int i = 0;
	char ch;
	*byte_count = c_byte;
	//printf("byte offset: %ld\n", *byte_count);	
	while(read(fd, &ch, 1)){
		if(ch == '\n'){
			line[i] = '\0';
			i = 0;
			return 1;

		}
		else{
			line[i++] = ch;
		
			c_byte++;
			
		}
				
	}
}

void grep_o(int fd, char *pattern, char *file_nm){
	char line[1024], line1[1024], *token,  *str;
	char delim[] = " \t\n.";
	static int count = 0;
	
	while(readLine(fd, line)){
		strcpy(line1, line);
		
		token = strtok(line, delim);
		do{



			str = strstr(token, pattern);
			
			if(str)
			{	//printf("\033[1;31m");
				printf("\033[0;35m%s\033[0m:\033[1;31m%s\033[0m\n", file_nm,pattern);
				//printf("\033[0m");
				count++;
				break;


			}



		}while(token = strtok(NULL, delim));

	}
	
	
	close(fd);	
	
}

void grep_oc(int fd, char *pattern, char *file_nm){
	char line[1024], line1[1024], *token,  *str;
	char delim[] = " \t\n.";
	 int c = 0;
	
	while(readLine(fd, line)){
		strcpy(line1, line);
		
		token = strtok(line, delim);
		do{



			str = strstr(token, pattern);
			
			if(str)
			{
				//printf("%s\n", pattern);
				c++;
				break;


			}



		}while(token = strtok(NULL, delim));

	}
	
	
	
		printf("\033[0;35m%s\033[0m:%d\n",file_nm, c);
		close(fd);
	
}

void grep_i(int fd, char *pattern, char *file_nm){
	char line[1024], line1[1024], *token,  *str;
	char delim[] = " \t\n.";
	int i = 0, j = 0;
	static int count = 0;
	while(readLine(fd, line)){
		strcpy(line1, line);
		
		token = strtok(line, delim);
		do{



			str = strcasestr(token, pattern);
			 
			/*i = strcasecmp(token, pattern);
			j = strcasecmp(str, pattern);*/	
			if(str)
			{
				printf("\033[0;35m%s\033[0m:%s\n", file_nm, line1);
				
				break;


			}



		}while(token = strtok(NULL, delim));

	}
	close(fd);
}



void grep_ic(int fd, char *pattern, char *file_name){
	char line[1024], line1[1024], *token,  *str;
	char delim[] = " \t\n.";
	int i = 0, j = 0;
	static int count = 0;
	while(readLine(fd, line)){
		strcpy(line1, line);
		
		token = strtok(line, delim);
		do{



			str = strcasestr(token, pattern);
			 
			/*i = strcasecmp(token, pattern);
			j = strcasecmp(str, pattern);*/	
			if(str)
			{
				//printf("%s\n", line1);
				count++;
				break;


			}



		}while(token = strtok(NULL, delim));

	}
	
		printf("\033[0;35m%s\033[0m:%d\n", file_name,count);
		count = 0;
		close(fd);
}

void grep_v(int fd, char *pattern, char *file_nm){
	char line[1024], line1[1024], *token, *str;
	char delim[] = " \t\n.";
	while(readLine(fd, line)){
		strcpy(line1, line);
		str = strstr(line, pattern);
		if(!str)
			printf("\033[0;35m%s\033[0m:%s\n", file_nm,line);
		/*token = strtok(line, delim);
		do{
			if((strcmp(token, pattern)))
			{
				printf("%s\n", line1);
				
				break;


			}



		}while(token = strtok(NULL, delim));*/

	}
	close(fd);

}
void grep_vc(int fd, char *pattern, char *file_nm){
	char line[1024], line1[1024], *token, *str;
	char delim[] = " \t\n.";
	int count = 0;
	
	while(readLine(fd, line)){
		strcpy(line1, line);
		str = strstr(line, pattern);
		if(!str){
			count++;
			//printf("%s:%s\n", file_nm,line);
		}
		/*token = strtok(line, delim);
		do{
			if((strcmp(token, pattern)))
			{
				printf("%s\n", line1);
				
				break;


			}



		}while(token = strtok(NULL, delim));*/

	}
	printf("\033[0;35m%s\033[0m:%d\n", file_nm,count);
	close(fd);

}



int grep_m(int fd, char *pattern, int c, char *file_nm){
	char line[1024], line1[1024], *str;
	char *token, delim[] = " \t\n.";
	 int count = 0;
	
	while(count < c && readLine(fd, line)){
		strcpy(line1, line);	
		str = strstr(line, pattern);
		if(str != NULL){
			printf("\033[0;35m%s\033[0m:%s\n", file_nm,line1);
					count++;
		}
		/*token = strtok(line, delim);
		do{
			if(!strcmp(token, pattern)){
				
				
					printf("%s\n", line1);
					count++;
					break;	
			}
			

		}while(strtok(NULL, delim));*/

	}
	close(fd);
	return 0;
		
}

/*int readOtherLine(int fd, char *line){
	int i = 0;
	char ch;
	while(read(fd, &ch, 1)){
		if(ch == '\n'){
			line[i] = '\0';
			i = 0;
			return 1;

		}
		else{
			line[i++] = ch;
		}
				
	}


}
*/
