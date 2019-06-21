#!/bin/sh

tabletail () {
	i=0
	while [ $i -lt 33 ]
	do
		echo -n "-"
		i=$((i+1))
	done
	echo		
}

tablehead () { 
	tabletail
	echo "|    Name  |Roll  | Age  |Marks |" 
	tabletail	
}

echo -n "Enter Name of Employee Database:"
read filename
touch "$filename.txt"
choice=1
while [ $choice != 5 ]
do
	echo -n -e "\nPress 1 to insert record\nPress 2 to View Database\nPress 3 to modify record\nPress 4 to delete record\nPress 5 to Exit\nEnter Choice:"
	read choice
	case "$choice" in

	1)
		echo -e "Inserting Record\n"
		echo -n "Enter Name:"
		read name
		echo -n "Enter Roll Number:"
		read roll
		echo -n "Enter Age:"
		read age
		echo -n "Enter Marks:"
		read marks
		echo -e "$name $roll $age $marks" >> $filename.txt
		;;

	2)
		echo "Displaying db"
		tablehead
		while read -a line
		do
			printf "|%10s|%6s|%6d|%6d|\n" "${line[0]}" "${line[1]}" "${line[2]}" "${line[3]}"
			tabletail
		done < "$filename.txt"
		;;
	3)
		echo "Modify";;

	4)
		echo "Delete";;

	5)
		echo "Exit";;
		
	*)echo "Invalid Input"
	esac
done
