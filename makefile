INCLUDE1=-I/usr/local/lib/wx/include/gtk3-unicode-static-3.0 -I/usr/local/include/wx-3.0 -D_FILE_OFFSET_BITS=64 -D__WXGTK__ -pthread
LIBS1=-L/usr/local/lib -pthread   /usr/local/lib/libwx_gtk3u_xrc-3.0.a /usr/local/lib/libwx_gtk3u_qa-3.0.a /usr/local/lib/libwx_baseu_net-3.0.a /usr/local/lib/libwx_gtk3u_html-3.0.a /usr/local/lib/libwx_gtk3u_adv-3.0.a /usr/local/lib/libwx_gtk3u_core-3.0.a /usr/local/lib/libwx_baseu_xml-3.0.a /usr/local/lib/libwx_baseu-3.0.a -lgthread-2.0 -pthread -lX11 -lXxf86vm -lSM -lgtk-3 -lgdk-3 -lpangocairo-1.0 -lpango-1.0 -latk-1.0 -lcairo-gobject -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0 -lpng -lexpat -lwxregexu-3.0 -lwxtiff-3.0 -lwxjpeg-3.0 -lz -ldl -lm 
INCLUDE2=-I/usr/include/mysql
LIBS2=-L/usr/lib/x86_64-linux-gnu -lmysqlclient -lpthread -lz -lm -lrt -ldl
INCLUDE3=-I/home/tao/local/matlab2017/extern/include
LIBS3=-L/home/tao/local/matlab2017/bin/glnxa64/ -leng -lmx -lmex
MYINCLUDE =  -I./src/include

CC = g++ -std=c++11  -Wall

OBJS = main.o menu.o check_dependent.o Dialog_de.o Dialog_Inde.o show_list.o query.o dataset.o db.o loadgraph.o creategraph.o createg6to9.o \
		caller.o launch.o indenpukrank.o indenputopk.o state.o tuple.o ukrank.o utopk.o
SUB=$(OBJS:%.o=obj/%.o)

utopk.x: $(SUB)
	$(CC) -o utopk.x $(INCLUDE1) $(INCLUDE2) $(INCLUDE3) $(SUB) $(LIBS1) $(LIBS2) $(LIBS3) 
obj/%.o: src/%.cpp
	$(CC) $(INCLUDE1) $(INCLUDE2) $(INCLUDE3) $(MYINCLUDE) -c $< -o $@
clean:
	rm utopk.x ./obj/*.o
