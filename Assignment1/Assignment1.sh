#!/bin/sh

tabletail () {
	i=0
	while [ $i -lt 48 ]
	do
		echo -n "-"
		i=$((i+1))
	done
	echo
}

tablehead () {
	tabletail
	echo "|Roll  |           Name          | Age  |Marks |"
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
		flag=0
		while [ $flag -eq 0 ]
		do
			echo -n "Enter Roll Number:"
			read roll
			grep "^$((roll))" -q $filename.txt && echo "Record Already Exists" || flag=1
		done
		echo -n "Enter Name:"
		read name
		echo -n "Enter Age:"
		read age
		echo -n "Enter Marks:"
		read marks
		echo -e "$roll|$name|$age|$marks" >> $filename.txt
		;;

	2)


		if 	[[ -s "$filename.txt" ]]; then
			echo "Displaying db"
			tablehead
			IFS='|'
			while read -a line
			do
				printf "|%6s|%25s|%6d|%6d|\n" "${line[0]}" "${line[1]}" "${line[2]}" "${line[3]}"
				tabletail
			done < "$filename.txt"
		else
			echo "Database is Empty"
		fi

		;;
	3)
		echo -n "Enter Roll Number to be searched:"
		read r
		flag=0
		grep "^$((r))" -q $filename.txt && flag=1 || flag=0
		if [ $flag -eq 0 ]
		then
			echo "Record Not Found"
		else
			result=$(ls -l | grep "^$((r))" $filename.txt)
			tablehead
			IFS='|'
			read -a line <<< "$result"
			printf "|%6s|%25s|%6d|%6d|\n" "${line[0]}" "${line[1]}" "${line[2]}" "${line[3]}"
			tabletail
		fi

		;;
	4)
		echo -n "Enter Roll Number to be modified:"
		read r
		grep "^$((r))" -q $filename.txt && echo "Record Found,Modifying" || echo "Record not found"
		
		echo -n "Enter New Name:"
		read name
		echo -n "Enter new Age:"
		read age
		echo -n "Enter new Marks:"
		read marks
		sed -i.bak "s/^$((r))/$r|$name|$age|$marks/g" $filename.txt
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
