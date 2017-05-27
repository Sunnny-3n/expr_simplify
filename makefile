cc = clang
prom = calc
cflag = -Wall -g -O3
deps = $(shell find ./ -name "*.h")
src = $(shell find ./ -name "*.c")
obj = $(src:%.c=%.o)

$(prom): $(obj)
	$(cc) $(cflag) -o $(prom) $(obj)

%.o: %.c $(deps)
	$(cc) $(cflag) -c $< -o $@

clean:
	rm -rf $(obj) $(prom)
