#!/bin/sh

RELEASE_DIR=./release

# Get SHA-1 first 6 chatacters
dt=`date "+%Y%m%d"`
sha1=`git rev-parse HEAD | cut -c 1-7`
workdir=$RELEASE_DIR/${dt}_${sha1}/rba
docdir=$RELEASE_DIR/$sha1/doc
rbadir=`pwd`
includedir=$workdir/include/rba
libdir=$workdir/lib
unittestdir=$workdir/unittest

# Make work directory
if [ ! -d $workdir ]; then
    mkdir -p $workdir
fi

# if [ ! -d $docdir ]; then
#     mkdir -p $docdir
# fi

# Make librba
builddir=./build_release
if [ ! -d $builddir ]; then
    mkdir -p $builddir
fi

pushd $builddir
if [ -f CMakeCache.txt ]; then
    /bin/rm -f CMakeCache.txt
fi
cmake -DNOLOG=1 -DRELEASE=1 .. 
make -j9
popd

# Copy lib files
if [ ! -d $libdir ]; then
    mkdir -p $libdir
fi

cp lib/librba.* $libdir/.

# Copy header files
if [ ! -d $includedir ]; then
    mkdir -p $includedir
fi

for hppfile in `/bin/ls include/rba/*.hpp`; do
    # remove internal region
    anim=`echo $hppfile | grep "Animation"`
    if [ -n "$anim" ]; then
	continue
    fi
    cat $hppfile | python3 script/remove_internal.py > __tmp
    /bin/mv -f __tmp $workdir/$hppfile
done
echo "Copy header files...done"

# Copy unittest
if [ -d $unittestdir ]; then
    /bin/rm -fr $unittestdir
fi
/bin/mkdir -p $unittestdir
/bin/cp -f unittest/BUILD.md $unittestdir/.
/bin/cp -f unittest/main.cpp $unittestdir/.
/bin/cp -f unittest/exec_unittest.bat $unittestdir/.
#/bin/cp -f unittest/CMakeLists.txt $unittestdir/.
echo "set(NOLOG TRUE)" > $unittestdir/CMakeLists.txt
cat unittest/CMakeLists.txt >> $unittestdir/CMakeLists.txt

/bin/mkdir -p $unittestdir/script
/bin/cp -f unittest/script/install_gt.sh $unittestdir/script/.
/bin/cp -f unittest/script/gtbuild.bat $unittestdir/script/.
/bin/cp -f unittest/script/make_ut.bat $unittestdir/script/.

/bin/cp -r unittest/logic_test $unittestdir/.
/bin/cp -r unittest/api_test $unittestdir/.

echo Copy unittest...done

echo $workdir

exit
#
# make document
#
pushd doc
sh mkdoc.sh
popd
cp -r ./doc/work/rtf_en $docdir/.
cp -r ./doc/work/rtf_jp $docdir/.

echo Release directory is $workdir
echo done

# end of file
