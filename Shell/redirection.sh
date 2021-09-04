#!/bin/bash
FILE="date.txt"
printf "Today Date: " > ${FILE}
date >> ${FILE}
cat < ${FILE}
echo "Removing file"
rm -rf ${FILE}
