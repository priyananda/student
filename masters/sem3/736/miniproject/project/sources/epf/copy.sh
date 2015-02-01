SRCDIR=/project/linux-2.6.27.5
BACK=/project/backup/mine-dec4
EPF=/project/typed-prefetch/trunk

ln -f -s $EPF/mm/epf_cache.c $SRCDIR/mm/epf_cache.c
ln -f -s $EPF/mm/Makefile $SRCDIR/mm/Makefile
ln -f -s $EPF/mm/filemap.c $SRCDIR/mm/filemap.c
ln -f -s $EPF/mm/open.c $SRCDIR/fs/open.c
ln -f -s $EPF/mm/readahead.c $SRCDIR/mm/readahead.c
ln -f -s $EPF/mm/swap.c $SRCDIR/mm/swap.c
ln -f -s $EPF/mm/vmscan.c $SRCDIR/mm/vmscan.c

ln -f -s $EPF/include/mm_types.h $SRCDIR/include/linux/mm_types.h
ln -f -s $EPF/include/fs.h $SRCDIR/include/linux/fs.h
ln -f -s $EPF/include/epf_cache.h $SRCDIR/include/linux/epf_cache.h

#mv $SRCDIR/mm/swap.c $BACK
#ln  -s $EPF/swap.c $SRCDIR/mm/swap.c

#mv $SRCDIR/include/linux/mm_types.h $BACK
#ln -s $EPF/mm_types.h $SRCDIR/include/linux/mm_types.h

#mv $SRCDIR/include/linux/mm_types.h $BACK
#ln -s $EPF/mm_types.h $SRCDIR/include/linux/mm_types.h

#mv $SRCDIR/mm/filemap.c $BACK
#ln -s $EPF/filemap.c $SRCDIR/mm/filemap.c

#mv $SRCDIR/mm/readahead.c $BACK
#ln -s $EPF/readahead.c $SRCDIR/mm/readahead.c

#mv $SRCDIR/mm/vmscan.c $BACK
#ln -s $EPF/vmscan.c $SRCDIR/mm/vmscan.c
