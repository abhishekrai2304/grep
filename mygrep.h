typedef struct options{
	int i_flag;
	int o_flag;
	int r_flag;
	int c_flag;
	int f_flag;
	int m_flag;
	int b_flag;
	int w_flag;
	int h_flag;
	int H_flag;
	int v_flag;
	int q_flag;
	
}options;
typedef struct node{
	char *name;
	struct node *next;
}node;
typedef struct node* list;
void init(list *l);
void insert(list *l, char *name);
void red ();
void matchedLines(int fd, char *pattern, char *file_nm);
int readLine(int fd, char *line);
void grep_Help(int fd);
void grep_version(int fd);
//void otherLines(int fd, char *option, char *pattern, char *file_nm);
void grep_c(int fd,  char *pattern, char *name);
void grep_w(int fd, char *pattern, char *file_name);
void grep_rw(int fd, char *pattern, char *dir_name, char *file_name);
void grep_wc(int fd, char *pattern, char *file_name);
void grep_i(int fd, char *pattern, char *file_name);
void grep_ic(int fd, char *pattern, char *file_name);
int grep_m(int fd, char *pattern, int c, char *file_name);
void grep_o(int fd, char *pattern, char *file_nm);
void grep_oc(int fd, char *pattern, char *file_nm);
void grep_v(int fd, char *pattern, char *file_nm);
void grep_vc(int fd, char *pattern, char *file_nm);
int readPattern(int fd, char *pattern);
void grep_f(int fd1, int fd2);
void grep_H(int fd, char *pattern, char *file_nm);
void grep_H(int fd, char *pattern, char *file_nm);
void grep_h(int fd, char *pattern, char *file_nm);
void grep_b(int fd, char *pattern, char *file_nm);
int read_byte(int fd, char *line, long *byte_count);
void setflags(options var);


