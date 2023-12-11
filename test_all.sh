#!/bin/bash

#=======================================================
#定数 color
#=======================================================
ESC=$(printf '\033') 
# RED=$(printf '[31m')
GREEN=$(printf '[32m')
YELLOW=$(printf '[33m')
BLUE=$(printf '[34m')
PURPLE=$(printf '[35m')
SKYBLUE=$(printf '[36m')
PINK=$(printf '[38;5;199m')
C1=$(printf '[38;5;197m')
WHITE=$(printf '[38;5;015m')
RED=$(printf '[38;5;196m')
BG_PINK=$(printf '[48;5;198m')
BG_WHITE=$(printf '[48;5;15m')

#=======================================================
# head
#=======================================================
echo "${ESC}${BG_PINK}"
echo ""
echo ""
echo ""
echo ""
echo "${ESC}[m"
echo "${ESC}${PINK}"
echo "======================================================="
echo "start minishell test"
echo "======================================================="
echo "${ESC}[m"

#=======================================================
# func
#=======================================================
test_echo(){
echo ${input} | ./minishell 1>./test/mini
echo ${input} | bash 1>./test/bash
# cat ./test/mini_tmp | sed -e 's/ .\/pretty_sh//g' > ./test/mini
sed '1d' ./test/mini
# diff -u ./test/mini ./test/bash &> /dev/null
if [ $? -eq 0 ]; then
	echo "${ESC}${GREEN} OK ${input}" "${ESC}[m"
elif [ $? -eq 1 ]; then
	echo "${ESC}${RED} NG ${input}" "${ESC}[m"
	echo "${ESC}${C1}"
	diff -u ./test/mini ./test/bash
	echo "${ESC}[m"
fi
}

test_expect_out_bash(){
/usr/bin/expect -c "
	set timeout 1
	spawn bash
	send \"${input}\"
	send \n
	expect eof exit 0
"
}
test_expect_out_mini(){
/usr/bin/expect -c "
	set timeout 1
	spawn ./minishell
	expect -re \".* $\"
	send \"${input}\"
	send \n
	expect eof exit 0
"
}
test_diff_expect(){
	# test_expect_out_bash
	test_expect_out_mini
}

# 左から順になるかテスト
test_path(){
	mkdir ./PATH1
	mkdir ./PATH2
	cp /bin/ls ./PATH1/
	mv ./PATH1/ls ./PATH1/test1
	cp /bin/date ./PATH2/
	mv ./PATH2/date ./PATH2/test1
	export PATH=./PATH1:./PATH2
	test1
	export PATH=./PATH2:./PATH1
	test1
}

assert() {
	# テストしようとしている内容をprint
	printf '%-30s:' "$1 \"$2\"	"

	# bashの出力をcmpに保存
	# stdout 確認
	echo -n -e "$2" | bash >./test/$1_bash_test 2>&-
	# bashのexit statusをexpectedに代入
	expected=$?
	# minishellの出力をoutに保存
	echo -n -e "$2" | ./minishell >./test/$1_minishell_test 2>&-
	# minishellのexit statusをactualに代入
	actual=$?
	diff ./test/$1_bash_test ./test/$1_minishell_test >/dev/null && echo -n "${ESC}${GREEN}"'  diff OK'"${ESC}[m" || echo -n "${ESC}${PINK}"'  diff NG'"${ESC}[m"

	# stderr 確認
	# echo -n -e "$2" | bash 2>./test/$1_bash_test 1>&-
	# expected=$?
	# echo -n -e "$2" | ./minishell 2>./test/$1_minishell_test 1>&-
	# actual=$?
	# diff ./test/$1_bash_test ./test/$1_minishell_test >/dev/null && echo -n '  diff OK' || echo -n '  diff NG'

	# bashとminishellのexit statusを比較
	if [ "$actual" = "$expected" ]; then
		echo -n "${ESC}${GREEN}"'  status OK'"${ESC}[m"
	else
		echo -n "${ESC}${PINK}""  status NG, expected $expected but got $actual""${ESC}[m"
	fi
	echo
}


#=======================================================
# run case
#=======================================================
echo "${ESC}${PINK}"
echo "==test c=="
echo "${ESC}[m"

# チェスト文 手入力
# ls| grep a|grep t;cat
# cat | cat | ls ; ls | grep test
# cat <<abc; cat <<abc <<abc
# cat <<''
# export val==abc==
#  \t　を引数に入れる pwd \tとか
# builtin単体の入力　export, unset, env
# assert 16 'ls ||| ls'
# env | grep PWD
# CTRL +Cだけ

# redirectのテスト
# chmod 0 out5
# cat <out5
# ls >out5
# ls >>out5
# echo hello の終了ステータス

assert 1 'echo "a bc"d'
assert 2 'echo a"$HOME"$HOME"$HOME"a'
assert 3 'echo a'"$HOME"'b"'$HOME'"'
assert 4 'cd | pwd'
assert 5 'cd|pwd'
assert 6 'ls | grep a | grep t ; ls'
assert 7 'ls|grep a|grep t;ls'
assert 8 'cat <test/infile'
assert 9 'ls|grep t;ls|grep p'
assert 10 'ls|grep t;ls|grep p|grep t && cat <test/1_bash_test'
assert 11 'ls;ls'
assert 12 'ls|grep 2>out'
assert 13 'pretty 2>out'
assert 14 'ls|grep t&&ls|grep ||ls |cat'
assert 15 'ls | grep a 10>out'
assert 16 'ls;'
assert 17 'lsa;'
assert 18 'echo hello'
assert 19 'echo "a  b$HOME'"cd$HOME' $HOME'"' "'$HOME%e'"f$HOME"'
assert 20 '<out'
assert 21 '<out | cat'
assert 22 '/bin/ls'
assert 23 '/bin/ls la'
assert 24 'echo a a a'
assert 25 'echo -n a a'
assert 26 'cd ; pwd'
assert 27 'export val=123 ; env | grep val'
assert 28 'export val2=456 ; env | grep val2; unset val2; env | grep val2'
assert 29 'export | head -n 8'
assert 30 'export +123 val4=012 val5 val6=; env | val6'
assert 31 'cd ; env | grep PWD='
assert 32 'unset OLDPWD; unset SHLVL; export'
assert 33 'cd ; unset SHLVL; export AAA ;export BBB ; export 1AAAA ;export _B ;export'
# test_path

# リダイレクト
# input='v'; test_echo; 
# input='cat <test/infile | grep a >>test/outfile; echo abc'; test_echo; 
# input='ls|ls;ls&&ls||ls'; test_echo; 

# sample quote　手入力
# echo ' $HOME'
# echo echo "a  b$HOME"cd$HOME' $HOME'" "'$HOME%e'"#f+=g&$HOME"
# echo a$HOME ; echo b$HOMEb ; echo $HOMEc ;
# echo "d d$HOMEd" ; echo 'e $HOME'; echo f"f f$HOME" ; echo "g g$HOME"g ; echo "a  b$HOME"cd$HOME' $HOME'" "'$HOME%e'"#f+=g&$HOME"
# echo "a  b$HOME"cd$HOME' $HOME'" "'$HOME%e'"#f+=g&$HOME"
# echo $HOME'a$HOME'b$HOME'c$HOMEd'$HOMEe
# echo "$HOME'"a$HOME'"b$HOME'c$HOMEd'$HOMEe'
# echo '"$HOME'$HOMEe | ./minishell; 
# echo '"$HOME'"a$HOME'"b$HOME'c$HOMEd'$HOMEe| ./minishell; 

#=======================================================
# foot
#=======================================================
echo "${ESC}${PINK}"
echo "==end=="
echo "${ESC}[m"

# size_t n = UINT_MAX;
#   n += 10;
#   char *str = malloc(sizeof(char) * (n + 1));
#   memset(str, 'a', n);
#   memset(str + n - 4, 'x', 4);
#   str[n] = '\0';
#   printf("\"%s\"\n", ft_strtrim(str, "a"));

#---memo
# tty="/dev/ttys004"
# echo -e "abc\n" >${tty}