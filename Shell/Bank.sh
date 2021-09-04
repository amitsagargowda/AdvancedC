#! /bin/bash
###############################################################################
# Student ID   : 
#
# Student Name : 
#
# File Name    : debit.sh
#
# This script should take two arguments. A filename that points to the account
# balance, and a number that indicates the debit amount. The script should 
# reduce the account balance by the debit amount, and save the result.
###############################################################################
BALANCEFILE=$1
DEBITAMT=0

main()
{
	
	#shift filename it is not required
	shift
	
	#while loop till all number are read and debited
	while [ -n "$1" ]; do
		DEBITAMT=$1
		#check if balance if valid number
		#if valid perform debit operation
		if echo "$DEBITAMT" | grep -qE '^[0-9]+$'; then
			read balance < $BALANCEFILE
			
			echo "Debiting Amount : \$$DEBITAMT"
			
			newbalance=$((balance - DEBITAMT))
			
			#check if sufficient balance present to debit
			#if not throw error and exit
			if [ $newbalance -lt 0 ]
			then
				printf "Insufficient Balance \n"
				exit 1
			fi			

			echo $newbalance > $BALANCEFILE
		else
			echo "Desposit amount is not a valid number"
		fi
		#shift to next number
		shift
	done
	

}

validatefile()
{
	# Balance file is required for all operation 
	# check for it and throw error
	if [ ! -f $BALANCEFILE ]
	then
		printf "$BALANCEFILE file missing\n"
		printf "Balance file is required for debit\n"
		exit 1
	fi
	
	read balance < $BALANCEFILE
	
	#check if balance in balance file is valide
	if echo "$balance" | grep -qE '^[0-9]+$'; then
		printf ""
	else
		echo "Account Balance in file is a not a valid number"
		exit 1
	fi
}

#check if valid number of arguments are passed
if [ $# -lt 2 ]
then
	printf "Usage: \n"
	printf "\t ./debit.sh <balance file> <desposit amout>\n"
	printf "\t Example: ./debit.sh balance.txt 100\n"
	exit 1
fi

#validate balance file content
validatefile

#first entry main
main $@


