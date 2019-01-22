#include <ctype.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
//This function is for Step 4
char * time2str(const time_t * when, long ns) {
  char * ans = malloc(128 * sizeof(*ans));
  char temp1[64];
  char temp2[32];
  const struct tm * t = localtime(when);
  strftime(temp1, 512, "%Y-%m-%d %H:%M:%S", t);
  strftime(temp2, 32, "%z", t);
  snprintf(ans, 128, "%s.%09ld %s", temp1, ns, temp2);
  return ans;
}

void step2_2_1(struct stat * statbuf) {  //Switch-case statement for step2.2
  switch (statbuf->st_mode & S_IFMT) {
    case S_IFBLK:
      printf("b");
      break;
    case S_IFCHR:
      printf("c");
      break;
    case S_IFDIR:
      printf("d");
      break;
    case S_IFIFO:
      printf("p");
      break;
    case S_IFLNK:
      printf("l");
      break;
    case S_IFREG:
      printf("-");
      break;
    case S_IFSOCK:
      printf("s");
      break;
    default:
      break;
  }
}
const char * step1_lastarg(
    struct stat *
        statbuf) {  //Called from step1 to print out line2's last format conversion, dependent on st_mode and S_IFMT
  switch (statbuf->st_mode & S_IFMT) {
    case S_IFBLK:
      return "block special file";
    case S_IFCHR:
      return "character special file";
    case S_IFDIR:
      return "directory";
    case S_IFIFO:
      return "fifo";
    case S_IFLNK:
      return "symbolic link";
    case S_IFREG:
      return "regular file";
    case S_IFSOCK:
      return "socket";
    default:
      return "unknown";
  }
}
void step1(struct stat * statbuf) {
  printf(
      "  Size: %-10lu\tBlocks: %-10lu IO Block: %-6lu %s\n",  //Printing the second line of mystat
      statbuf->st_size,
      statbuf->st_blocks,
      statbuf->st_blksize,
      step1_lastarg(
          statbuf));  //Last format conversion is based on the case statement of S_IFxxx variations
  if (S_ISCHR(statbuf->st_mode) > 0 ||
      S_ISBLK(statbuf->st_mode) >
          0) {  //Third line of step1(with addition of Step6). If file stated is device
    printf("Device: %lxh/%lud\tInode: %-10lu  Links: %-5lu Device type: %x,%x\n",
           statbuf->st_dev,
           statbuf->st_dev,
           statbuf->st_ino,
           statbuf->st_nlink,
           major(statbuf->st_dev),   //Cannot figure out, incorrect values
           minor(statbuf->st_dev));  //Likewise, incorrect value coming here
  }
  else {
    printf("Device: %lxh/%lud\tInode: %-10lu  Links: %lu\n",  //If file stated is not a device
           statbuf->st_dev,
           statbuf->st_dev,
           statbuf->st_ino,
           statbuf->st_nlink);
  }
}  //end of step1
void step2printr(mode_t mode) {  //Checking whether to print r/-
  if (mode != 0) {               //Caller has read permissison
    printf("r");
  }
  else {  //Caller does not have read permission
    printf("-");
  }
}
void step2printw(mode_t mode) {  //Checking whether to print w/-
  if (mode != 0) {               //Caller has write permissison
    printf("w");
  }
  else {  //Caller does not have write permission
    printf("-");
  }
}
void step2printx(mode_t mode) {  //Checking whether to print x/-
  if (mode != 0) {               //Caller has execute permissison
    printf("x");
  }
  else {  //Caller does not have execute permission
    printf("-");
  }
}
void step2(struct stat * statbuf) {  //add three separate abstraction, r/- mode_t as parameter
  printf("Access: (%04o/", statbuf->st_mode & ~S_IFMT);  //step2.1
  step2_2_1(statbuf);                       //step2.2.1, calling the case statement function
  step2printr(statbuf->st_mode & S_IRUSR);  //step2.2.2, Checking if owner has read permission
  step2printw(statbuf->st_mode & S_IWUSR);  //step2.2.3, Checking if owner has write permission
  step2printx(statbuf->st_mode & S_IXUSR);  //step2.2.4, checking if owner has execute permission
  step2printr(statbuf->st_mode & S_IRGRP);  //step2.2.5, checking if group has read permission
  step2printw(statbuf->st_mode & S_IWGRP);  //step2.2.6, checking if group has write permission
  step2printx(statbuf->st_mode & S_IXGRP);  //step2.2.7, checking if group has execute permission
  step2printr(statbuf->st_mode & S_IROTH);  //step2.2.8, checking if other has read permission
  step2printw(statbuf->st_mode & S_IWOTH);  //step2.2.9, checking if other has write permission
  step2printx(statbuf->st_mode & S_IXOTH);  //step2.2.10, checking if other has execute permission
  printf(")");                              //Close the parenthesis on the permission group
}

void step3(struct stat * statbuf) {  //Printing line 4, all in one printf function
  struct passwd * passwd_ptr = getpwuid(statbuf->st_uid);  //user name
  struct group * group_ptr = getgrgid(statbuf->st_gid);    //group's name
  printf("  Uid: (%5d/%8s)   Gid: (%5d/%8s)\n",
         statbuf->st_uid,
         passwd_ptr->pw_name,
         statbuf->st_gid,
         group_ptr->gr_name);
}

void step4(struct stat * statbuf) {  //Printing last 4 lines
  char * access_time = time2str(&statbuf->st_atime, statbuf->st_atim.tv_nsec);
  char * modify_time = time2str(&statbuf->st_mtime, statbuf->st_mtim.tv_nsec);
  char * change_time = time2str(&statbuf->st_ctime, statbuf->st_ctim.tv_nsec);
  printf("Access: %s\nModify: %s\nChange: %s\n Birth: -\n", access_time, modify_time, change_time);
  free(
      access_time);  //freeing the mallocs done implicitly by time2str,applies to two functions below as well
  free(modify_time);
  free(change_time);
}
int main(int argc, char ** argv) {
  if (argv == NULL) {  //checking for valid input
    fprintf(stderr, "Invalid call, terminating now");
    exit(EXIT_FAILURE);
  }
  if (argc < 2) {
    fprintf(stderr, "stat: missing operand\nTry 'stat --help' for more information.\n");
    exit(EXIT_FAILURE);
  }

  for (int i = 1; i < argc; i++) {  //Run the whole process for each input file
    struct stat statbuf;
    if (lstat(argv[i], &statbuf) == -1) {
      fprintf(stderr, "stat: cannot stat '%s': No such file or directory\n", argv[i]);
      if (i != (argc - 1)) {  //Stat does not terminate when argv[1] is invalid and argc>2
        continue;
      }
      exit(EXIT_FAILURE);
    }
    if (S_ISLNK(
            statbuf
                .st_mode)) {  //Checking if file is symbolic link, if so modifying the first line of input
      char linktarget[256];
      ssize_t len = readlink(argv[i], linktarget, 256);
      if (len == -1) {
        fprintf(stderr, "Symbolic link's target not read properly, terminating");
        exit(EXIT_FAILURE);
      }
      else {
        linktarget[len] = '\0';  //Due to readlink not appending null terminator
        printf("  File: %s -> %s\n", argv[i], linktarget);
      }
    }
    else {  //If file is not a symbolic link
      printf("  File: %s\n", argv[i]);
    }
    step1(&statbuf);  //Function call for step1
    step2(&statbuf);  //Function call for step2
    step3(&statbuf);  //Function call for step3
    step4(&statbuf);  //Function call for step4
  }
  return EXIT_SUCCESS;
}
