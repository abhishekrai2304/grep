#define _GNU_SOURCE
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<strings.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<errno.h>
#include <dirent.h> 
#include "mygrep_imp.c"
void setflags(options var){
	var.i_flag = 0;
	var.o_flag = 0;
	var.r_flag = 0;
	var.c_flag = 0;
	var.f_flag = 0;
	var.m_flag = 0;
	var.w_flag = 0;
	var.h_flag = 0;
	var.H_flag = 0;
	var.q_flag = 0;
	var.b_flag = 0;
	var.o_flag = 0;
	var.v_flag = 0;
}
void clearflags(options *var){
	var->i_flag = 0;
	var->o_flag = 0;
	var->r_flag = 0;
	var->c_flag = 0;
	var->f_flag = 0;
	var->m_flag = 0;
	var->w_flag = 0;
	var->h_flag = 0;
	var->H_flag = 0;
	var->q_flag = 0;
	var->b_flag = 0;
	var->o_flag = 0;
	var->v_flag = 0;

}
int main(int argc, char *argv[]){

options var;
	int fd, fd1, fd2, c, options_c, num;
	char *pattern, *dir_name;
	char *file_name, *option, *option2, *pattern2;
	options_c = argc;
	
	
	clearflags(&var);
	if(!strcmp("--help", argv[1])){
		fd = open("help.txt", O_RDONLY);
		grep_Help(fd);	
		close(fd);
		return 0;
			}
	if(!strcmp("--version", argv[1])){
		fd = open("version.txt", O_RDONLY);
		grep_Version(fd);	
		close(fd);
		return 0;
			}
	while((c = getopt(argc, argv, "rcfmiowhHbovq")) != -1){
		switch(c){
			case 'r':
				var.r_flag = 1;
				break;
			case 'c':
				var.c_flag = 1;
				break;
			case 'f':
				var.f_flag = 1;
				break;
			case 'm':
				var.m_flag = 1;
				
				break;
			case 'i':
				var.i_flag = 1;
				break;
			
			case 'w':
				var.w_flag = 1;
				break;
			case 'h':
				var.h_flag = 1;
				break;
			case 'H':
				var.H_flag = 1;
				break;
			
			case 'b':
				var.b_flag = 1;
				//printf("hello");
				break;
			case 'o':
				var.o_flag = 1;
				break;
			case 'v':
				var.v_flag = 1;
				break;
			case 'q':
				var.q_flag = 1;
				break;
			case '?':
				
				fprintf(stderr, "unknown option %c\n", optopt);
				break;
			
			default:
				
				if (var.q_flag != 1) {
					printf("Usage: grep [OPTION]... PATTERN [FILE]...\n");
				}
				break;
		}	
	}
		
	
	
		
		
			//fd = open(argv[3], O_RDONLY);
				
			option = argv[1];
			pattern = argv[2];
			//file_name = argv[3];
			
			struct dirent *de;
			list l, l2;
			init(&l);
			init(&l2);
			
			optind = optind + 1;
			
			for(; optind  < argc; optind++)
				insert(&l,argv[optind]);


			if(var.r_flag == 1 ){
				node *ptr = l;
				while(ptr!=NULL){
					//fd = open(ptr->name, O_RDONLY);
					DIR *dr = opendir(ptr->name);
					//strcpy(dir_name, ptr->name);
					if (dr == NULL){ // opendir returns NULL if couldn't open directory 
    	
        					printf("Could not open current directory" ); 
        					return 0; 
   	 
					} while ((de = readdir(dr)) != NULL){ 
           
						if(strcmp(de->d_name, ".") && strcmp(de->d_name, "..")){
						 	//printf("%s/:",ptr->name);			
							fd = open(de->d_name, O_RDONLY);
							grep_rw(fd, pattern, ptr->name, de->d_name);
						} 
						if(fd == -1){
							perror("could not open file\n");
						}
			
						close(fd);		
					}
  
    					closedir(dr); 
					
					ptr = ptr->next;
				}
				clearflags(&var);

		}
			if(var.i_flag == 1 && var.w_flag == 1 && var.c_flag == 0 && var.h_flag == 0 && var.v_flag == 0 ){
				node *ptr = l;
				while(ptr!=NULL){
					fd = open(ptr->name, O_RDONLY);
					grep_i(fd, pattern, ptr->name);
					ptr = ptr->next;
				}
				
				clearflags(&var);
			}
	
			if(var.h_flag == 1 && var.i_flag == 1 && var.w_flag == 1 && var.c_flag == 0 ){
				node *ptr = l;
				while(ptr!=NULL){
					fd = open(ptr->name, O_RDONLY);
					//printf("%s:", ptr->name);
					grep_i(fd, pattern, ptr->name);
					ptr = ptr->next;
				}
				
				clearflags(&var);
			}

			if(var.o_flag == 1 && var.c_flag == 1 ){
				node *ptr = l;
				while(ptr!=NULL){
				
					fd = open(ptr->name, O_RDONLY);
					
					file_name = ptr->name;
					//printf("%s:", );
					grep_oc(fd, pattern, ptr->name);
					ptr = ptr->next;
				}
				
				clearflags(&var);
			}
			if(var.v_flag == 1 && var.i_flag == 1 && var.c_flag == 0){
				
				node *ptr = l;
				while(ptr!=NULL){
				
					fd = open(ptr->name, O_RDONLY);
					file_name = ptr->name;
					grep_v(fd, pattern, file_name);
					ptr = ptr->next;
				}
				
				clearflags(&var);
			}
				
				if(var.v_flag == 1 && var.c_flag == 1 ){
				
				node *ptr = l;
				while(ptr!=NULL){
				
					fd = open(ptr->name, O_RDONLY);
					file_name = ptr->name;
					grep_vc(fd, pattern, file_name);
					ptr = ptr->next;
				}
				
				clearflags(&var);
			}
			 if(var.w_flag == 1 && var.c_flag == 1 && var.i_flag == 1){
				
				node *ptr = l;
				while(ptr!=NULL){
					fd = open(ptr->name, O_RDONLY);
					grep_ic(fd, pattern, ptr->name);
					ptr = ptr->next;
				}
				clearflags(&var);
			}
			
			 if(var.w_flag == 1 && var.c_flag == 0){
				
				node *ptr = l;
				while(ptr!=NULL){
					fd = open(ptr->name, O_RDONLY);
					grep_w(fd, pattern, ptr->name);
					ptr = ptr->next;
				}
				clearflags(&var);
			}
		
			if(var.w_flag == 1 && var.c_flag == 1){
				//printf("heloo");
				
				node *ptr = l;
				while(ptr!=NULL){
					fd = open(ptr->name, O_RDONLY);
					//printf("\033[0;35m%s\033[0m:", ptr->name);
					grep_wc(fd, pattern, ptr->name);
					ptr = ptr->next;
				}
				
				clearflags(&var);
			}

			if(var.c_flag == 1 && var.w_flag != 1 && var.i_flag != 1 &&  var.h_flag != 1 && var.H_flag != 1 && var.q_flag != 1 && var.m_flag != 1 && var.b_flag!=1){
				node *ptr = l;
				while(ptr!=NULL){
					fd = open(ptr->name, O_RDONLY);
					grep_c(fd, pattern, ptr->name);
					ptr = ptr->next;
				}
				
				clearflags(&var);
			}

			if(var.i_flag == 1 && var.c_flag != 1 ){
				node *ptr = l;
				while(ptr!=NULL){
					fd = open(ptr->name, O_RDONLY);
					grep_i(fd, pattern, ptr->name);
					ptr = ptr->next;
				}
				
				clearflags(&var);
			}
			if(var.i_flag == 1 && var.c_flag == 1 && var.w_flag == 0 && var.v_flag == 0 ){
				node *ptr = l;
				while(ptr!=NULL){
					fd = open(ptr->name, O_RDONLY);
					grep_ic(fd, pattern, ptr->name);
					ptr = ptr->next;
				}
				
				clearflags(&var);
			}
			

			
			if(var.h_flag == 1 && var.c_flag != 1){
				node *ptr = l;
				while(ptr!=NULL){
					fd = open(ptr->name, O_RDONLY);
					//printf("%s:", ptr->name);
					grep_h(fd, pattern, ptr->name);
					ptr = ptr->next;
				}
				
				clearflags(&var);
			}

			if(var.h_flag == 1 && var.c_flag == 1 && var.w_flag != 1 &&  var.i_flag != 1 && var.H_flag != 1 && var.q_flag != 1 && var.m_flag != 1 && var.b_flag!=1){
				//grep_hc(fd, pattern);
				
				node *ptr = l;
				while(ptr!=NULL){
					fd = open(ptr->name, O_RDONLY);
					
					grep_wc(fd, pattern, ptr->name);//since it has same functionalaties as grep_hc	
					ptr = ptr->next;
				}
							
				clearflags(&var);
			}

			
			if(var.H_flag == 1 && var.c_flag == 0 ){
				node *ptr = l;
				while(ptr!=NULL){
					fd = open(ptr->name, O_RDONLY);
					file_name = ptr->name;
					grep_H(fd, pattern, file_name);	
					ptr = ptr->next;
				}
				
				clearflags(&var);
			}
			if(var.H_flag == 1 && var.c_flag == 1){
				node *ptr = l;
				while(ptr!=NULL){
					fd = open(ptr->name, O_RDONLY);
					file_name = ptr->name;
					grep_Hc(fd, pattern, file_name);
					ptr = ptr->next;
				}
				
				clearflags(&var);
			}

			if(var.b_flag == 1 ){
				node *ptr = l;
				while(ptr!=NULL){
				
					fd = open(ptr->name, O_RDONLY);
					file_name = ptr->name;
					grep_b(fd, pattern, file_name);
					ptr = ptr->next;
				}
				
				clearflags(&var);
			}

			if(var.o_flag == 1 && var.b_flag != 1 && var.c_flag != 1 && var.w_flag != 1 &&  var.i_flag != 1 && var.h_flag != 1 && var.q_flag != 1 && var.m_flag != 1 && var.H_flag!=1){
				node *ptr = l;
				while(ptr!=NULL){
				
					fd = open(ptr->name, O_RDONLY);
					file_name = ptr->name;
					//printf("%s:", ptr->name);
					grep_o(fd, pattern, file_name);
					ptr = ptr->next;
				}
				
				clearflags(&var);
			}
			
			
			if(var.v_flag == 1 && var.c_flag != 1 ){
				node *ptr = l;
				while(ptr!=NULL){
				
					fd = open(ptr->name, O_RDONLY);
					file_name = ptr->name;
					grep_v(fd, pattern, file_name);
					ptr = ptr->next;
				}
				
				clearflags(&var);
			}
		
			
			
			
			if(var.q_flag == 1 ){
	
				clearflags(&var);
				return 0;
			}
			
			if(var.m_flag == 1 && var.c_flag == !1){
				
				option2 = argv[1];
				pattern2 = argv[3];
				num = atoi(argv[2]);
				int k = 4;
				for(; k  < argc; k++)
					insert(&l2,argv[k]);
				node *ptr = l2;
				while(ptr!=NULL){
					fd2 = open(ptr->name, O_RDONLY);
					file_name = ptr->name;
					grep_m(fd2, pattern2, num, file_name);
					ptr = ptr->next;
				}
				
				clearflags(&var);
			}
			
		if(var.f_flag == 1 && var.m_flag != 1 && var.c_flag == !1 && var.w_flag != 1 &&  var.i_flag != 1 && var.h_flag != 1 && var.q_flag != 1 && var.H_flag != 1 && var.b_flag!=1){
			int k;
			char *p_file;
			option2 = argv[1];
			p_file = argv[2];
			fd1 = open(p_file, O_RDONLY);
			k = 3;
			for(; k  < argc; k++)
					insert(&l2,argv[k]);
			node *ptr = l2;
			while(ptr!=NULL){
					fd2 = open(ptr->name, O_RDONLY);
					file_name = ptr->name;
					grep_f(fd1, fd2);
					ptr = ptr->next;
			}
				
				clearflags(&var);
			




		}
		
		
		return 0;
		

}
