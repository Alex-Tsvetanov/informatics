declare -x tests="../tests/E"
for folder in `ls -d */` ;
do
	declare -x result=0;
	declare -x text="";
	g++ ${folder%%/}/e1.cpp -o ${folder%%/}/e1.exe -std=c++11 -O2;
	for i in `seq -w 1 10`;
	do
		timeout 2s ./${folder%%/}/e1.exe < $tests/e1.$i.in > a;
		command_code=$?;
		if [[ "$command_code" = "0" ]]
		then
			if [[ "`diff -w a $tests/e1.$i.sol`" = "" ]]
			then
				result=$(($result+10));
				text="$text  \x1b[32m✓\x1b[0m";
			else
				text="$text  \x1b[33m✗\x1b[0m";
			fi
		else
			if [[ "$command_code" = "139" ]]
			then
				text="$text  \x1b[31mF\x1b[0m";
			else
				if [[ "$command_code" = "134" ]]
				then
					text="$text \x1b[31mME\x1b[0m";
				else
					text="$text  \x1b[34mt\x1b[0m";
				fi
			fi
		fi
	done
	g++ ${folder%%/}/e2.cpp -o ${folder%%/}/e2.exe -std=c++11 -O2;
	text="$text | "
	for i in `seq -w 1 5`;
	do
		timeout 2s ./${folder%%/}/e2.exe < $tests/e2.0$i.in > a;
		command_code=$?;
		if [[ "$command_code" = "0" ]]
		then
			if [[ "`diff -w a $tests/e2.0$i.sol`" = "" ]]
			then
				result=$(($result+20));
				text="$text  \x1b[32m✓\x1b[0m";
			else
				text="$text  \x1b[33m✗\x1b[0m";
			fi
		else
			if [[ "$command_code" = "139" ]]
			then
				text="$text  \x1b[31mF\x1b[0m";
			else
				if [[ "$command_code" = "134" ]]
				then
					text="$text \x1b[31mME\x1b[0m";
				else
					text="$text  \x1b[34mt\x1b[0m";
				fi
			fi
		fi
	done
	printf "%3d\t%s\t$text\n" $result $folder >> results;
done
rm a;
