BASEDIR=$(dirname $0)

for tst in $@
do 
    ./$tst
done


