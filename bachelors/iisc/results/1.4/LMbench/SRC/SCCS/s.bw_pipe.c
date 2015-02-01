h65103
s 00004/00000/00086
d D 1.11 01/01/07 16:47:39 staelin 12 11
c - bw_pipe: close uneeded pipe file descriptors so child process will
c   die properly
cC
cHhpli8.hpli.hpl.hp.com
cK62093
cZ+02:00
e
s 00004/00006/00082
d D 1.10 97/06/25 10:25:01 lm 11 10
c ifdef TOUCH
cC
cK55727
cSAlpha2.11
e
s 00005/00000/00083
d D 1.9 97/06/23 23:27:09 lm 10 9
c touch the data for dm.
cK03370
e
s 00001/00001/00082
d D 1.8 97/06/16 19:05:50 lm 9 8
c lint
cK53028
e
s 00007/00007/00076
d D 1.7 97/06/15 22:38:58 lm 8 7
c lint
cK52471
e
s 00020/00017/00063
d D 1.6 97/06/12 21:30:06 lm 7 6
c new bench.h macros.
cK48507
cZ-07:00
e
s 00041/00043/00039
d D 1.5 96/11/11 03:36:51 lm 6 5
c Auto adjusting changes.
cK40425
e
s 00002/00001/00080
d D 1.4 96/11/08 19:57:56 lm 5 4
c gcc -Wall cleanup.
cK39174
cZ-08:00
e
s 00027/00023/00054
d D 1.3 96/05/30 00:31:40 lm 4 3
c Make them auto time themselves.
cK35844
cZ-07:00
e
s 00004/00005/00073
d D 1.2 96/01/24 17:09:19 lm 3 2
c Make everything use XFERSIZE
cK31617
e
s 00078/00000/00000
d D 1.1 94/11/18 00:49:48 lm 2 1
c Initial revision
cK32537
e
s 00000/00000/00000
d D 1.0 94/11/18 00:49:47 lm 1 0
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHlm.bitmover.com
cK54645
cPsrc/bw_pipe.c
cRfa12331757b8149c
cV4
cX0x21
cZ-08:00
e
u
U
f e 0
f x 0x21
t
lmbench src
T
I 2
/*
 * bw_pipe.c - pipe bandwidth benchmark.
 *
 * Usage: bw_pipe
 *
 * Copyright (c) 1994 Larry McVoy.  Distributed under the FSF GPL with
 * additional restriction that results may published only if
 * (1) the benchmark is unmodified, and
 * (2) the version in the sccsid below is included in the report.
 * Support for this development by Sun Microsystems is gratefully acknowledged.
 */
char	*id = "$Id$\n";

D 6
#include	"timing.c"
I 5
#include	<sys/types.h>
#include	<sys/wait.h>
E 6
I 6
D 7
#include "timing.h"
E 7
#include "bench.h"
D 7
#include <sys/types.h>
#include <sys/wait.h>
E 7
E 6
E 5

D 3
#define	BUFSIZE	(64*1024)
E 3
D 4
#define	XFER	(1024*1024*50)

E 4
D 8
extern	void	exit();		/* for lint on SunOS 4.x */
void		writer(), reader();
E 8
I 8
void	reader(int control[2], int pipes[2], int bytes);
void	writer(int control[2], int pipes[2]);
E 8

I 4
D 6
int	XFER	= 10*1024*1024;
E 6
I 6
D 7
int	XFER	= 100*1024*1024;
E 7
I 7
int	XFER	= 10*1024*1024;
E 7
int	pid;
char	*buf;

E 6
E 4
int
main()
{
D 6
	int	pipes[2];
I 4
	int	usecs;
E 6
I 6
D 7
	int	i, N, pipes[2];
E 7
I 7
	int	pipes[2];
	int	control[2];
E 7
E 6
D 5
	char	c;
E 5
E 4

I 6
	buf = valloc(XFERSIZE);
D 9
	bzero(buf, XFERSIZE);
E 9
I 9
D 11
	bzero((void*)buf, XFERSIZE);
E 11
I 11
	touch(buf, XFERSIZE);
E 11
E 9
E 6
D 4
	write(2, id, strlen(id));
E 4
	if (pipe(pipes) == -1) {
		perror("pipe");
D 8
		exit(1);
E 8
I 8
		return(1);
E 8
	}
I 7
	if (pipe(control) == -1) {
		perror("pipe");
D 8
		exit(1);
E 8
I 8
		return(1);
E 8
	}
E 7
D 4
	switch (fork()) {
	    case 0:
		reader(pipes[0]);
		exit(0);
		/*NOTREACHED*/
E 4
I 4
D 6
	do {
		switch (fork()) {
	    	case 0:
		    writer(pipes[1]);
		    exit(0);
		    /*NOTREACHED*/
E 4
	    	
D 4
	    case -1:
		perror("fork");
		exit(1);
		/*NOTREACHED*/
E 4
I 4
		    case -1:
			perror("fork");
			exit(1);
			/*NOTREACHED*/
E 6
I 6
	switch (pid = fork()) {
	    case 0:
I 12
		close(control[1]);
		close(pipes[0]);
E 12
D 7
		writer(pipes);
E 7
I 7
		writer(control, pipes);
E 7
D 8
		exit(0);
E 8
I 8
		return(0);
E 8
		/*NOTREACHED*/
	    
	    case -1:
		perror("fork");
D 8
		exit(1);
E 8
I 8
		return(1);
E 8
		/*NOTREACHED*/
E 6
E 4

D 4
	    default:
	    	writer(pipes[1]);
		wait(0);
		exit(0);
		/*NOTREACHED*/
	}
E 4
I 4
D 6
		    default:
			sleep(1);
			start();
			reader(pipes[0]);
			usecs = stop();
			XFER <<= 2;
			wait(0);
		}
	} while (usecs < 1000000);
E 6
I 6
	    default:
I 12
		close(control[0]);
		close(pipes[1]);
E 12
		break;
	}
D 7
	LOOP_FIRST(N, i, ENOUGH);
	reader(pipes);
	LOOP_LAST(N, i, ENOUGH);
E 7
I 7
	BENCH(reader(control, pipes, XFER), MEDIUM);
E 7
E 6
	fprintf(stderr, "Pipe bandwidth: ");
D 6
	mb(XFER >> 2);
E 6
I 6
D 7
	mb(N * XFER);
E 7
I 7
	mb(get_n() * XFER);
E 7
	kill(pid, 15);
E 6
D 8
	exit(0);
E 8
I 8
	return(0);
E 8
E 4
}

void
D 6
writer(fd)
	int	fd;
E 6
I 6
D 7
writer(int pipes[2])
E 7
I 7
writer(int control[2], int pipes[2])
E 7
E 6
{
D 6
	int	todo = XFER;
	int	n, done = 0;
D 3
	char	buf[BUFSIZE];
E 3
I 3
	char	*buf = valloc(XFERSIZE);
E 6
I 6
D 7
	int	todo, done, n;
E 7
I 7
	int	todo, n;
E 7
E 6
E 3

D 3
	while ((done < todo) && ((n = write(fd, buf, sizeof(buf))) > 0))
E 3
I 3
D 6
	while ((done < todo) && ((n = write(fd, buf, XFERSIZE)) > 0))
E 3
		done += n;
I 4
	free(buf);
E 6
I 6
	for ( ;; ) {
D 7
		done = 0;
		todo = XFER;
		while ((done < todo) && ((n = write(pipes[1], buf, XFERSIZE)) > 0))
			done += n;
E 7
I 7
		read(control[0], &todo, sizeof(todo));
		while (todo > 0) {
I 11
#ifdef	TOUCH
			touch(buf, XFERSIZE);
#endif
E 11
			n = write(pipes[1], buf, XFERSIZE);
			todo -= n;
I 10
D 11
			buf[0] = buf[4<<10] = buf[8<<10] = buf[12<<10] =
			buf[16<<10] = buf[20<<10] = buf[24<<10] = buf[28<<10] =
			buf[32<<10] = buf[36<<10] = buf[40<<10] = buf[44<<10] =
			buf[48<<10] = buf[52<<10] = buf[56<<10] = buf[60<<10] =
			buf[63<<10] = 1;
E 11
E 10
		}
E 7
	}
E 6
E 4
}

void
D 6
reader(fd)
	int	fd;
E 6
I 6
D 7
reader(int pipes[2])
E 7
I 7
reader(int control[2], int pipes[2], int bytes)
E 7
E 6
{
D 6
	int	todo = XFER;
	int	n, done = 0;
D 3
	char	buf[BUFSIZE];
E 3
I 3
	char	*buf = valloc(XFERSIZE);
E 3

D 4
	sleep(1);
	start();
E 4
D 3
	while ((done < todo) && ((n = read(fd, buf, sizeof(buf))) > 0))
E 3
I 3
	while ((done < todo) && ((n = read(fd, buf, XFERSIZE)) > 0))
E 6
I 6
	int	todo = XFER, done = 0, n;
I 7

	write(control[1], &bytes, sizeof(bytes));
E 7
	while ((done < todo) && ((n = read(pipes[0], buf, XFERSIZE)) > 0)) {
E 6
E 3
		done += n;
D 4
	stop();
	fprintf(stderr, "Pipe bandwidth: ");
	mb(todo);
E 4
I 4
D 6
	free(buf);
E 6
I 6
	}
E 6
E 4
}
E 2
I 1
E 1
