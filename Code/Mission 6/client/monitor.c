#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/inotify.h>
#include <sys/stat.h>
#include <errno.h>
#include <limits.h>

int main(int argc, char **argv) {
  int fd = inotify_init();
  char buf[sizeof(struct inotify_event) + NAME_MAX + 1];
  struct inotify_event * evp;

  if(fd < 0)
  {
    perror("inotify_init():");
    return -1;
  }

  int watchfd = inotify_add_watch(fd, argv[1], IN_MODIFY | IN_CREATE | IN_DELETE);
  while(1) {
    read(fd, buf, sizeof(buf));
    evp = (struct inotify_event * )buf;

    if (evp->len > 0) {
      if (evp->mask & IN_CREATE) {
          printf("The file %s was created.\n", evp->name);
      } else if (evp->mask & IN_DELETE) {
          printf("The file %s was deleted.\n", evp->name);
      } else if (evp->mask & IN_MODIFY) {
          printf("The file %s was modified.\n", evp->name);
      }
    }
  }
}