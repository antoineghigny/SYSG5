all: PwnKit

PwnKit:
	gcc -shared exploit.c -o exploit -Wl,-e,entry -fPIC

clean:
	rm PwnKit 
