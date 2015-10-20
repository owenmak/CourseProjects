#!/bin/bash
#echo "Please enter a password:"
pw=$1
POINT=0
LENGTH=0
while read line; do
	let LENGTH=LENGTH+${#line};
done < $pw

if [ $LENGTH -gt 32 ] || [ $LENGTH -lt 6 ]; then
	echo "Error: Password invalid length."
	exit 0
fi

let POINT=POINT+$LENGTH;

if egrep -q "[#$+%@]" $pw;then
	let POINT=POINT+5
fi

if egrep -q "[0-9]" $pw;then
	let POINT=POINT+5
fi

if egrep -q "[a-zA-Z]" $pw;then
	let POINT=POINT+5
fi

if egrep -q "([0-9a-zA-Z])\1+" $pw;then
	let POINT=POINT-10
fi

if egrep -q "[0-9][0-9][0-9]" $pw;then
	let POINT=POINT-3
fi

if egrep -q "[a-z][a-z][a-z]" $pw;then
	let POINT=POINT-3
fi

if egrep -q "[A-Z][A-Z][A-Z]" $pw;then
	let POINT=POINT-3
fi

echo "Password Score: $POINT"
