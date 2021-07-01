#!/bin/bash






make && ./pipex infile cat wc outfile; cat outfile 
< infile cat | wc > bashout; cat bashout
diff outfile bashout

make && ./pipex infile cat "grep ft_is"  outfile; cat outfile 
< infile cat | grep ft_is > bashout; cat bashout
diff outfile bashout

make && valgrind ./pipex infile cat "grep ft_is"  outfile; cat outfile 
< infile cat | grep ft_is > bashout; cat bashout
diff outfile bashout

make && valgrind ./pipex infil cat "grep ft_is"  outfile 

make && valgrind ./pipex infile cac "grep ft_is"  outfile 

make && valgrind ./pipex infile cat "grp ft_is"  outfile 

make && valgrind ./pipex infile cat "grp ft_is" 

