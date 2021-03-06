#!/bin/sh

CC=`../scripts/compiler`
MAKE=`../scripts/make`
OS=`../scripts/os`
TARGET=`../scripts/target`
BINDIR="../bin/${OS}"
CONFIG="../bin/${OS}/`../scripts/config`"
NULL=/dev/null
BASE=/tmp/dummy


trap 'rm -f ${BASE}$$.s ${BASE}$$.c ${BASE}$$.o ${BASE}$$; exit 1' 1 2 15

# check for HP-UX's ANSI compiler
echo "main(int ac, char *av[]) { int i; }" > ${BASE}$$.c
if ${CC} ${CFLAGS} -o ${BASE}$$ ${BASE}$$.c 1>${NULL} 2>${NULL}
then
	true;
else
	rm -f ${BASE}$$
	if ${CC} ${CFLAGS} -Ae -o ${BASE}$$ ${BASE}$$.c 1>${NULL} 2>${NULL}
	then
		CFLAGS="${CFLAGS} -Ae"
	fi
fi
rm -f ${BASE}$$ ${BASE}$$.o ${BASE}$$.c
	
# check for IA64 HP-UX w/ HP's ANSI compiler; may need pointer swizzling
arch=`echo $OS | awk -F- '{print $1;}'`
if [ X$CC = "Xcc" -a X$arch = "Xia64" ]
then
	echo "#include <stdlib.h>" > ${BASE}$$.c
	echo "main(int ac, char *av[])" >> ${BASE}$$.c
	echo "{ long* p = (long*)malloc(sizeof(long));" >> ${BASE}$$.c
	echo "*p = 0; exit((int)*p); }" >> ${BASE}$$.c
	${CC} ${CFLAGS} +DD64 -o ${BASE}$$ ${BASE}$$.c 1>${NULL} 2>${NULL} \
		&& [ -x ${BASE}$$ ] \
		&& ${BASE}$$ \
		&& CFLAGS="${CFLAGS} +DD64"
	rm -f ${BASE}$$ ${BASE}$$.o ${BASE}$$.c
fi
	
# check for bcopy (optionally set the SYS5 flag)
echo "#include <string.h>" > ${BASE}$$.c
echo "main() { char a[256], b[256]; bcopy(a, b, 256); }" >> ${BASE}$$.c
${CC} ${CFLAGS} -o ${BASE}$$ ${BASE}$$.c 1>${NULL} 2>${NULL} \
	|| CFLAGS="${CFLAGS} -DSYS5"
rm -f ${BASE}$$ ${BASE}$$.o ${BASE}$$.c

# check for valloc
echo "#include <stdlib.h>" > ${BASE}$$.c
echo "main() { char* buf = valloc(123); }" >> ${BASE}$$.c
${CC} ${CFLAGS} -o ${BASE}$$ ${BASE}$$.c 1>${NULL} 2>${NULL} \
	|| CFLAGS="${CFLAGS} -Dvalloc=malloc"
rm -f ${BASE}$$ ${BASE}$$.o ${BASE}$$.c

# check for getrusage
echo "#include <sys/types.h>" > ${BASE}$$.c
echo "#include <sys/time.h>" >> ${BASE}$$.c
echo "#include <sys/resource.h>" >> ${BASE}$$.c
echo "#ifndef RUSAGE_SELF" >> ${BASE}$$.c
echo "#define RUSAGE_SELF 0" >> ${BASE}$$.c
echo "#endif /* RUSAGE_SELF */" >> ${BASE}$$.c
echo "main() { struct rusage ru; getrusage(RUSAGE_SELF, &ru); }" >> ${BASE}$$.c
${CC} ${CFLAGS} -o ${BASE}$$ ${BASE}$$.c 1>${NULL} 2>${NULL} \
	&& CFLAGS="${CFLAGS} -DRUSAGE"
rm -f ${BASE}$$ ${BASE}$$.o ${BASE}$$.c

# check for -lnsl
echo "extern int pmap_getport(); main() { pmap_getport(); }" > ${BASE}$$.c
if ${CC} ${CFLAGS} -o ${BASE}$$ ${BASE}$$.c 1>${NULL} 2>${NULL}; then
	true;
else
	${CC} ${CFLAGS} -o ${BASE}$$ ${BASE}$$.c -lnsl 1>${NULL} 2>${NULL} \
		&& LDLIBS="${LDLIBS} -lnsl"
fi
rm -f ${BASE}$$ ${BASE}$$.o ${BASE}$$.c


# check for -lsocket
echo "extern void* getservent(); main() { getservent(); }" > ${BASE}$$.c
if ${CC} ${CFLAGS} -o ${BASE}$$ ${BASE}$$.c 1>${NULL} 2>${NULL}; then
	true;
else
	${CC} ${CFLAGS} -o ${BASE}$$ ${BASE}$$.c -lsocket 1>${NULL} 2>${NULL} \
		&& LDLIBS="${LDLIBS} -lsocket"
fi
rm -f ${BASE}$$ ${BASE}$$.o ${BASE}$$.c

# check for OSs that have S_IFFIFO instead of S_IFIFO
echo "#include <sys/stat.h>" > ${BASE}$$.c
echo "main() { return (S_IFIFO); }" >> ${BASE}$$.c
if ${CC} ${CFLAGS} -o ${BASE}$$ ${BASE}$$.c 1>${NULL} 2>${NULL}; then
	true;
else
	rm -f ${BASE}$$ ${BASE}$$.o ${BASE}$$.c
	echo "#include <sys/stat.h>" > ${BASE}$$.c
	echo "main() { return (S_IFFIFO); }" >> ${BASE}$$.c
	${CC} ${CFLAGS} -o ${BASE}$$ ${BASE}$$.c 1>${NULL} 2>${NULL} \
		|| CFLAGS="${CFLAGS} -DS_IFIFO=S_IFFIFO"
fi
rm -f ${BASE}$$ ${BASE}$$.o ${BASE}$$.c

# check that we have uint
echo "#include <stdlib.h>" > ${BASE}$$.c
echo "#include <sys/types.h>" >> ${BASE}$$.c
echo "main() { uint i = 0; return (i); }" >> ${BASE}$$.c
${CC} ${CFLAGS} -o ${BASE}$$ ${BASE}$$.c 1>${NULL} 2>${NULL} \
	&& CFLAGS="${CFLAGS} -DHAVE_uint=1";
rm -f ${BASE}$$ ${BASE}$$.o ${BASE}$$.c

# check that we have uint64
echo "#include <stdlib.h>" > ${BASE}$$.c
echo "#include <sys/types.h>" >> ${BASE}$$.c
echo "main() { uint64_t i = 0; return (int)(i); }" >> ${BASE}$$.c
${CC} ${CFLAGS} -o ${BASE}$$ ${BASE}$$.c 1>${NULL} 2>${NULL} \
	&& CFLAGS="${CFLAGS} -DHAVE_uint64_t=1";
rm -f ${BASE}$$ ${BASE}$$.o ${BASE}$$.c

# check that we have drand48 and srand48
echo "#include <stdlib.h>" > ${BASE}$$.c
echo "main() { srand48(973); return (int)(1.0E9 * drand48()); }" >> ${BASE}$$.c
if ${CC} ${CFLAGS} -o ${BASE}$$ ${BASE}$$.c 1>${NULL} 2>${NULL}; then
	true;
else
	rm -f ${BASE}$$ ${BASE}$$.o ${BASE}$$.c
	echo "#include <stdlib.h>" > ${BASE}$$.c
	echo "main() { srand(973); return (10 * rand()) / RAND_MAX; }" >> ${BASE}$$.c
	if ${CC} ${CFLAGS} -o ${BASE}$$ ${BASE}$$.c 1>${NULL} 2>${NULL}; then
		CFLAGS="${CFLAGS} -DUSE_RAND"
        else
		rm -f ${BASE}$$ ${BASE}$$.o ${BASE}$$.c
		echo "#include <stdlib.h>" > ${BASE}$$.c
		echo "main() { srandom(973); return (10 * random()) / RAND_MAX; }" >> ${BASE}$$.c
		${CC} ${CFLAGS} -o ${BASE}$$ ${BASE}$$.c 1>${NULL} 2>${NULL} \
			|| CFLAGS="${CFLAGS} -DUSE_RANDOM"
	fi
fi
rm -f ${BASE}$$ ${BASE}$$.o ${BASE}$$.c

# echo Building for $(TARGET)
if [ ! -d ${BINDIR} ]; then mkdir -p ${BINDIR}; fi

# now go ahead and build everything!
${MAKE} CC="${CC}" CFLAGS="${CFLAGS}" LDLIBS="${LDLIBS}" O="${BINDIR}" $*
