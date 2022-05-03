function test {
	input="./test/$1.txt"
	while IFS= read -r line
	do
		echo "$line >> result_bash" >> tmp_bash
		echo "$line >> result_mini" >> tmp_mini
	done < "$input"
	bash -i < tmp_bash
	./minishell < tmp_mini

	name="result_$1.diff"
	diff -u -s result_bash result_mini > $name
	rm tmp_bash tmp_mini result_bash result_mini
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