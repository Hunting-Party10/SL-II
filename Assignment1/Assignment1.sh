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
	echo "|Roll  |   Name   | Age  |Marks |" 
	tabletail	
}

echo -n "Enter Name of Employee Database:"
read filename
touch "$filename.txt"
choice=1
while [ $choice != 6 ]
do
	echo -n -e "\nPress 1 to insert record\nPress 2 to View Database\nPress 3 to Search record\nPress 4 to modify record\nPress 5 to delete record\nPress 6 to Exit\nEnter Choice:"
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
		echo -e "$roll $name $age $marks" >> $filename.txt
		;;

	2)
		echo "Displaying db"
		tablehead
		while read -a line
		do
			printf "|%6s|%10s|%6d|%6d|\n" "${line[0]}" "${line[1]}" "${line[2]}" "${line[3]}"
			tabletail
		done < "$filename.txt"
		;;
	3)
		echo -n "Enter Roll Number to be searched:"
		read r
		grep "^$((r))" -q $filename.txt && echo "Record found" || echo "Record not found"
		count=$(ls -l | grep "^$((r))" -q $filename.txt)
		result=$(ls -l | grep "^$((r))" $filename.txt)
		if [ $count -eq 0 ]
		then
			echo "Record Not Found"
		else
			tablehead
			IFS=' '
			read -a line <<< "$result"
			printf "|%6s|%10s|%6d|%6d|\n" "${line[0]}" "${line[1]}" "${line[2]}" "${line[3]}"
			tabletail
		fi
		

		
		
		;;
	4)
		echo -n "Enter Roll Number to be modified:"
		read r
		grep "^$((r))" -q $filename.txt && echo "Record Found,Modifying" || echo "Record not found"
		sed -i "/^$((r))/d" $filename.txt
		echo -n "Enter New Name:"
		read name
		echo -n "Enter new Age:"
		read age
		echo -n "Enter new Marks:"
		read marks
		echo -e "$r $name $age $marks" >> $filename.txt
		
		;;

	5)	
		echo -n "Enter Roll Number to be deleted:"
		read r
		grep "^$((r))" -q $filename.txt && echo "Found Record, Deleting" || echo "Could not find Record"
		sed -i "/^$((r))/d" $filename.txt
		
		;;
	
	6)
		echo "Exit";;
		
	*)echo "Invalid Input"
	esac
done
