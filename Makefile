CC=gcc
CFLAGS=-g -O0 -fcommon -I.

DEPS = ray.h vec3.h utils.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

rtracer:	main.o utils.o ray.o vec3.o
	 $(CC) -o rtracer main.o utils.o vec3.o ray.o -lm

clean:
	rm -f rt rtracer.o out.ppm out.jpg