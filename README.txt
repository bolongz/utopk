1. On ubuntu 16.0.4, install wxWidgets 3.0.2, install MATLAB, install MYSQL 5.7, set the root password of MYSQL as "root123". Make sure that the "bin" directoryof MATLAB is shown in the "PATH" environment variable.
2. Type in "wx-config --cxxflags", use the output to replace the RHS(right hand of "=") of the line begining with "INCLUDE1" in makefile.
3. Type in "wx-config --libs", use the output to replace the RHS of the line begining with "LIBS1" in makefile.
4. Excute command "sodu apt install libmysqlclient-dev".
5. Type in "mysql_config --include" and "mysql_config --libs", use the outputs to replace the RHS of the line begining with "INCLUDE2" and "LIBS2" respectively.
6. Use "-I(matlab install directory)/extern/include" to replace the RHS of the line begining with "INCLUDE3" in make file.
7. Use "-L(matlab install directory)/bin/glnxa64 -leng -lmx -lemx" or "-L(matlab install directory)/bin/glnx86 -leng -lmx -lemx"(depending on the processor architecture) to replace the RHS of the line begining with"LIBS3" in the makefile.
8. Enter the directory of the project(for example, my directory is /home/tao/git/utopk/).
9. Excute the command "mkdir obj" if "obj" directory does not exist.
10. Excute "make utopk.x"
11. Type in "./utopk.x" and run.
12. Follow the instructions in the Section 5.3("presentation layer") of our final report.
13. When the data is dependent situation, we need to load the rules for the
tuples. (several possible rules has already list on the directory)
