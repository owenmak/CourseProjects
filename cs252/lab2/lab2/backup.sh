#!/bin/bash
file=$1
backupDir=$2
sleepSec=$3
maxBackups=$4
currBackups=0
myname="zmai"

#copy it first
let currBackups=currBackups+1
cp $file $backupDir/$(date +%Y"-"%m"-"%d"-"%H"-"%M"-"%S"-"$myname)$file

while true; do
	sleep $sleepSec
	otherfile=$backupDir/`ls -1tr * | tail -1`
	if diff -q "$file" "$otherfile"; then
		:
	else
#		echo "different!"
		let currBackups=currBackups+1
		if [ $currBackups -gt $maxBackups ];then
			rm $backupDir/`ls $backupDir | head -1`
			let currBackups=currBackups-1
		fi
		cp $file $backupDir/$(date +%Y"-"%m"-"%d"-"%H"-"%M"-"%S"-"$myname)$file
		echo "Hello $USER!" > tmp-message
	#	echo >> tmp-message
		diff "$file" "$otherfile" >> tmp-message
	#	cat < tmp-message
		/usr/bin/mailx -s "Diff" $USER < tmp-message
		echo "Message sent."
		
	fi	
done
	
