function test {
	input="./test/$1.txt"
	while IFS= read -r line
	do
		if [ $1 == "env" ]
		then
			echo "export TEST=BLA" > tmp
			echo "$line >> result_bash" >> tmp
			bash -i < tmp
			echo "export TEST=BLA" > tmp
			echo "$line >> result_mini" >> tmp
			./minishell < tmp
		else
			echo "$line >> result_bash" > tmp
			bash -i < tmp
			echo "$line >> result_mini" > tmp
			./minishell < tmp
		fi
	done < "$input"

	name="result_$1.diff"
	diff -u -s result_bash result_mini > $name
	rm tmp result_bash result_mini
}

make re
ls ./test | grep txt | sed s/.txt//g > test_files
files="test_files"
while IFS= read -r file
do
	echo $file
	test "$file"
done < "$files"

rm test_files
make fclean


