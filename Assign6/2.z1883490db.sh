#!/bin/bash
#script shows user's active processes

#We passed through dbname and param1
new(){
	if [ -n "$param1" ]; then
		echo "$param1" > $dbname
	else
		echo "Untitled database "  > $dbname
	fi
	printf "File successfully created \n"
}
help(){
	echo "# dbname - filename of database file use"
	echo "# command - which of the funtions to call: new, add, show, delete"
	echo "# param1  - first non-dbname parameter to whichever command function chosen"
	echo "# ...     - placeholder for parameters between 1 and N"
	echo "# paramN  - to whichever cammand funtion chosen"
	printf "dbname command param1 param2 ... paramN\nor enter \"quit\" to exit the program or enter \"help\" for syntax: "
	printf "\n\n"
}

printf "Thank you for using z1883490 DataBase program 😍😝💩 \n\n"
read -p "Please enter the file you will be using: " dbname

printf "\n\n"
printf "Please enter (help) for more info\n"
printf "or enter \"quit\" to exit the program or enter \"help\" for syntax:\n"

printf "============================\n"
printf "============================\n"
printf "=                          =\n"
printf "= new)                     =\n"
printf "= add)                     =\n"
printf "= show)                    =\n"
printf "= delete)                  =\n"
printf "= help)                    =\n"
printf "= quit)                    =\n"
printf "=                          =\n"
printf "============================\n"
printf "============================\n"

until [[ $dbname == "quit" ]]; do


	read -p "Please Enter a command: " command

	if   [ "$command" = "new"    ]; then
		read -p "Please enter a label for the database file, else, leave it blank:" param1
		printf "\n"
		new . dbname param1
	elif [ "$dbname" = "help"    ]; then
		help .
	elif [ "$command" = "add"    ]; then
		echo "added"
	elif [ "$command" = "show"   ]; then
		echo "show"
	elif [ "$command" = "delete" ]; then
		echo "delete"
	elif [ "$command" = "quit"   ]; then
		echo "quitting"
		break;
	else
		printf "command: $command is not part of the command library,\n please enter valid command \n\n"
	fi

	read -p "Please enter the file you will be using: " dbname
	printf "\n"

done

echo "leaving database program"
