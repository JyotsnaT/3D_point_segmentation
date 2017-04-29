CC = g++
CFLAGS = -g

default : segment

segment : knn.o kdtree.o point.o priority_queue.o
	$(CC) $(CFLAGS) -o segment knn.o kdtree.o point.o priority_queue.o -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_objdetect
	
knn.o : knn.cpp point.h vrml.h
	$(CC) $(CFLAGS)  -c knn.cpp heapsort.h imgio.h 
	
#graph.o : graph.cpp graph.h
#	$(CC) $(CFLAGS) -c graph.cpp
	
point.o : point.cpp point.h
	$(CC) $(CFLAGS) -c point.cpp

kdtree.o : kdtree.cpp kdtree.h
	$(CC) $(CFLAGS) -c kdtree.cpp

priority_queue.o : priority_queue.cpp priority_queue.h
	$(CC) $(CFLAGS) -c priority_queue.cpp
	
clean: 
	$(RM) segment *.o *~
	
