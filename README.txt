1. On ubuntu 16.0.4, install wxWidgets 3.0.2, install MATLAB, install MYSQL 5.7, set the root password of MYSQL as "root123".
2. Type in "wx-config --cxxflags", use the output to replace the content of "INCLUDE1" in makefile.
3. Type in "wx-config --libs", use the output to replace the content of "LIBS1" in makefile.
4. sodu apt install libmysqlclient-dev
5. Type in "mysql_config --include" and "mysql_config --libs", use the outputs to replace the contents of "INCLUDE2" and "LIBS2" respectively.
6. Use "-I(matlab install directory)/extern/include" to replace the content of "INCLUDE3" in make file.
7. Use "-L(matlab install directory)/bin/glnxa64 -leng -lmx -lemx" or "-L(matlab install directory)/bin/glnx86 -leng -lmx -lemx"(depending on the processor architecture) to replace the content of "LIBS3" in the makefile.
8.Type in "make utopk.x"
9.Type in "./utopk.x" and run.
