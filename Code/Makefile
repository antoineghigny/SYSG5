all: PwnKit

PwnKit:
	gcc -shared PwnKit.c -o PwnKit -Wl,-e,entry -fPIC

clean:
	rm PwnKit 