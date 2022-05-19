#include <mqueue.h>
       #include <sys/stat.h>
       #include <fcntl.h>
       #include <stdio.h>
       #include <stdlib.h>
       #include <unistd.h>

       #define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); \
                               } while (0)

       int
       main(int argc, char *argv[])
       {
           mqd_t mqd;
           struct mq_attr attr;

           if (argc != 2) {
               fprintf(stderr, "Usage: %s mq-name\n", argv[0]);
               exit(EXIT_FAILURE);
           }

           mqd = mq_open(argv[1], O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, NULL);
           if (mqd == (mqd_t) -1)
               errExit("mq_open");

           if (mq_getattr(mqd, &attr) == -1)
               errExit("mq_getattr");

           printf("Maximum # of messages on queue:   %ld\n", attr.mq_maxmsg);
           printf("Maximum message size:             %ld\n", attr.mq_msgsize);

           if (mq_unlink(argv[1]) == -1)
               errExit("mq_unlink");
	return 0;
}
