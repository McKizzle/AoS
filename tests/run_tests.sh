BASEDIR=$(dirname $0)

for tst in $@
do 
    ./$tst --log_level=test_suite >> $BASEDIR/tests.out
done

cat $BASEDIR/tests.out

