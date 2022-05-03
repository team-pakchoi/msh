function test {
	input="./test/$1.txt"
	while IFS= read -r line
	do
		echo "$line >> result_bash" > tmp
		bash -i < tmp
		echo "$line >> result_mini" > tmp
		./minishell < tmp
	done < "$input"

	name="result_$1.diff"
	diff -u result_bash result_mini > $name
	rm tmp result_bash result_mini
}

ls ./test | grep txt | sed s/.txt//g > test_files
files="test_files"
while IFS= read -r file
do
	echo $file
	test "$file"
done < "$files"

rm test_files
