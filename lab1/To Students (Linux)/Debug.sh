#!/bin/bash
EXE=run_me

g++ -g -o$EXE Student_Code/*.cpp ignoreme.a
if (( $? )) ;
then 
	echo Compilation Failed;
	read -p "Press enter to exit";
else 
	gdb $EXE; 
fi;