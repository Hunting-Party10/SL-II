#!/bin/sh
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
less $filename.txt
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
