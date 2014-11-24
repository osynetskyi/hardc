#!/bin/bash

for (( i=1; i<=1000; i++ ))
do
  ./ex23 >> ex23_data.dat
done

echo -n 'normal  '
awk '{ total += $1 } END { print total/NR }' ex23_data.dat
echo -n 'duff    '
awk '{ total += $2 } END { print total/NR }' ex23_data.dat
echo -n 'duff_32 '
awk '{ total += $3 } END { print total/NR }' ex23_data.dat
echo -n 'zed     '
awk '{ total += $4 } END { print total/NR }' ex23_data.dat
rm ex23_data.dat
