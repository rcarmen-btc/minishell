#!/bin/bash

printf "\033c"
echo -e "			\e[38;5;198m\=============-------=================\\"
echo -e "			 \=============-START-=================\\"
echo -e "			  \=============-------=================\\ \e[0m"
echo -e "\e[41minfile:\e[0m"
cat infile
echo -e "\n\e[101m ===========Test 1============ \e[0m\n"
echo -e "\e[44m ---> \e[0m ./pipex infile cat wc outfile; cat outfile:"
./pipex infile cat wc outfile; cat outfile 
echo -e "\e[30;102m ---> \e[0m < infile cat | wc > bashout; cat bashout:"
< infile cat | wc > bashout; cat bashout
echo -e "\e[30;105m ---> \e[0m diff outfile bashout:"
diff outfile bashout

echo -e "\n\e[101m ===========Test 2============ \e[0m\n"
echo -e "\e[44m ---> \e[0m ./pipex infile cat \"grep ft_is\"  outfile; cat outfile:"
./pipex infile cat "grep ft_is"  outfile; cat outfile 
echo -e "\e[30;102m ---> \e[0m < infile cat | grep ft_is > bashout; cat bashout:"
< infile cat | grep ft_is > bashout; cat bashout
echo -e "\e[30;105m ---> \e[0m diff outfile bashout:"
diff outfile bashout

echo -e "\n\e[101m ===========Test 3============ \e[0m\n"
echo -e "\e[44m ---> \e[0m ./pipex infile cat \"grep ft_str\"  outfile; cat outfile:"
valgrind ./pipex infile cat "grep ft_str"  outfile; cat outfile 
echo -e "\e[30;102m ---> \e[0m < infile cat | grep ft_str > bashout; cat bashout:"
< infile cat | grep ft_str > bashout; cat bashout
echo -e "\e[30;105m ---> \e[0m diff outfile bashout:"
diff outfile bashout

echo -e "\n\e[101m ===========Test 4============ \e[0m\n"
echo -e "\e[44m ---> \e[0m valgrind ./pipex infil cat \"grep ft_is\"  outfile:"
valgrind ./pipex infil cat "grep ft_is"  outfile 

echo -e "\n\e[101m ===========Test 5============ \e[0m\n"
echo -e "\e[44m ---> \e[0m valgrind ./pipex infile cac \"grep ft_is\"  outfile:"
valgrind ./pipex infile cac "grep ft_is"  outfile 

echo -e "\n\e[101m ===========Test 6============ \e[0m\n"
echo -e "\e[44m ---> \e[0m valgrind ./pipex infile cat \"grp ft_is\"  outfile:"
valgrind ./pipex infile cat "grp ft_is"  outfile 

echo -e "\n\e[101m ===========Test 7============ \e[0m\n"
echo -e "\e[44m ---> \e[0m valgrind ./pipex infile cat \"grp ft_is\":"
valgrind ./pipex infile cat "grp ft_is" 

