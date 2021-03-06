## Shared Library

We would like to create a shared link library containing the object code of the 
sum() and mul() functions written into mymath.c source file, which can be 
called from different C programs.

1. Compile Position Independent Code (PIC) mymath.o: 
```
$ gcc -c -fPIC mymath.c
```

2. Create shared link library `libmymath.so` from `mymath.o`: 
```
$ gcc -shared -o libmymath.so mymath.o
```

3. Generate the executable a.out using libmymath.so: 
```
$ gcc main.c -L. -lmymath
```
or 
```
$ gcc main.c libmymath.so
```

4. Now we must informing the dynamic linker that a shared library doesn't reside 
in the standard directories - `/lib /usr/lib tipically`. We can do that by setting
the `LD_LIBRARY_PATH` environment variable:
```
LD_LIBRARY_PATH=./ ./a.out
```
or
```
$ export LD_LIBRARY_PATH=./
```
Now the executable is ready to be executed:
```
$ ./a.out
```

### Naming conventions

library filename = `lib` + library name + `.so` + `Major version` + `minor version` + `patch version`

i.e.: `libgnustep-base.so.1.25.1`
