#!/bin/bash
echo "Hello $USER!!" > tmp-message
echo >> tmp-message
echo "Today is" 'date' >> tmp-message
../lab2 -s "mail-hello" $USER < tmp-message
echo "Message sent."
