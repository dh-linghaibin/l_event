cc=gcc
target=app
obj=app.o event.o stime.o
$(target):$(obj)
	$(cc) $(obj) -Wall -o $(target)
app.o:app.c
	$(cc) -c app.c
event.o:event.c
	$(cc) -c event.c
stime.c:stime.c
	$(cc) -c stime.c
	
.PHONY:clean
	$(RM) *.o $(target)
