ls
vi syscall.c
vi process.c
make
vi process.c
make
vi process.c
make
ls
vi syscall.c
make
vi syscall.c
make
vi syscall.c
make
vi syscall.c
vi process.c
vi syscall.c
vi process.c
vi syscall.c
make
vi process.c
vi syscall.c
make
ls
cd process.c
vi process.c
vi syscall.c
make
ls
vi process.c
ls
vi syscall.c
make
ls
vi syscall.c
make
vi syscall.c
make
vi syscall.c
vi process.c
ls
cd ..
cd threas
cd threads/
ls
cd ..
cd userprog/
ls
vi syscall.c
make
ls
cd syscall.c
vi syscall.c
source "/home/$USER/.bashrc"
ls
cd pintos/src/
ls
cd userprog/
ls
vi process.c
make
vi process.c
make
cd ../threads/
ls
vi thread.
vi thread.c
make
cd ..
cd userprog/
make
cd build/
pintos --filesys-size=2 -p ../../examples/echo -a echo -- -f -q run 'echo x'
ls
make check
cd ..
make check
make clean
make check
make clean
make check
make clean
make check
ls
cd ..
ls
cd userprog/
ls
cd ..
cd tests/
ls
cd userprog/
ls
vi sc-bad-sp.c
ls
vi sc-bad-sp.c
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/sc-bad-sp -a sc-bad-sp -- -q  -f run sc-bad-sp < /dev/null 2> tests/userprog/sc-bad-sp.errors > tests/userprog/sc-bad-sp.output
perl -I../.. ../../tests/userprog/sc-bad-sp.ck tests/userprog/sc-bad-sp tests/userprog/sc-bad-sp.result
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/sc-bad-sp -a sc-bad-sp -- -q  -f run sc-bad-sp < /dev/null 2> tests/userprog/sc-bad-sp.errors > tests/userprog/sc-bad-sp.output
perl -I../.. ../../tests/userprog/sc-bad-sp.ck tests/userprog/sc-bad-sp tests/userprog/sc-bad-sp.result
pintos -v -k -T 60 --qemu  --filesys-size=2 -p ../../tests/userprog/sc-bad-sp -a sc-bad-sp -- -q  -f run sc-bad-sp < /dev/null 2> ../../tests/userprog/sc-bad-sp.errors > ../../tests/userprog/sc-bad-sp.output
perl -I../.. ../../tests/userprog/sc-bad-sp.ck ../../tests/userprog/sc-bad-sp ../../tests/userprog/sc-bad-sp.result
ls
vi sc-bad-sp.c
ls
vi sc-bad-sp.ck
vi sc-bad-arg.c
source "/home/$USER/.bashrc"
cd pintos/src/threads/
vi thread.h
ls
vi thread.c
vi thread.h
vi thread.c
make
source "/home/$USER/.bashrc"
ls
cd pintos/src/
cd userprog/
ls
vi syscall.c
make
vi syscall.c
fg
vi syscall.c
make
vi syscall.c
make
ls
cd process.c
vi syscall.c
cd ..
cd lib/user/
ls
cd .
cd ..
cd userprog/
ls
vi syscall.c
make
vi syscall.c
make
ls
vi syscall.c
make
vi syscall.c
make
vi syscall.c
make
vi syscall.c
make
ls
vi syscall.c
vi syscall.
vi syscall.c
make
vi syscall.c
make
vi syscall.c
make
vi syscall.c
make
vi syscall.c
make
vi syscall.c
make
vi syscall.c
make
vi syscall.c
make
vi syscall.c
make
ls
vi syscall.c
source "/home/$USER/.bashrc"
cd pintos/src/
cd userprog/build/
cd ..
vi process.c
make
vi process.c
make
vi process.c
make
vi process.c
make
ls
vi process.c
make
vi process.c
make
vi process.c
make
cd pintos/src/userprog/
vi process.c
ps -fU os17
kill -9 10509
source "/home/$USER/.bashrc"
ls
cd pintos/src/
ls
cd userprog/
ls
vi syscall.c
ps -fU os17
kill -9 14181
vi syscall.c
make
ls
vi syscall.c
make
vi syscall.c
make
vi syscall.c
cd ..
cd tests/
ls
cd userprog/
ls
vi Grading
lsa
ls
cd ..
cd userprog/
ls
cd ..
ls
cd threads
ls
vi thread.c
vi thread.h
vi thread.c
vi thread.h
vi thread.c
cd ..
cd userprog/
ls
vi process.c
source "/home/$USER/.bashrc"
cd pintos/src/
ls
cd userprog/
make check
vi syscall.c
make
vi syscall.c
cd build/
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/write-bad-ptr -a write-bad-ptr -p ../../tests/userprog/sample.txt -a sample.txt -- -q  -f run write-bad-ptr < /dev/null 2> tests/userprog/write-bad-ptr.errors > tests/userprog/write-bad-ptr.output
perl -I../.. ../../tests/userprog/write-bad-ptr.ck tests/userprog/write-bad-ptr tests/userprog/write-bad-ptr.result
make check
q
:q
ls
cd ..
ls
cd ..
cd threads/
ls
cd ..
cd tests/userprog/
ls
vi Grading
ls
vi syscall.c
cd ..
cd userprog/build/
cd ..
ls
vi syscall.c
vi process.c
cd ..
cd threads
ls
vi thread.h
source "/home/$USER/.bashrc"
cd pintos/src/
ls
cd userprog/
ls
make check
make clean
make check
make clean
make check
make clean
make check
ls
source "/home/$USER/.bashrc"
pintos --filesys-size=2 -p ../../examples/echo -a echo -- -f -q run 'echo x'
cd pintos/src/userprog/build/
pintos --filesys-size=2 -p ../../examples/echo -a echo -- -f -q run 'echo x'
cd ..
cd tests/
cd userprog/
ls
vi sc-bad-sp.c
vi sc-bad-sp.ck
ls
cd ..
cd ls
cd 
cd pintos/src/userprog/
vi process.c
cd build/
gcc -c ../../tests/userprog/sc-bad-sp.c -o tests/userprog/sc-bad-sp.o -g -msoft-float -O -fno-stack-protector -nostdinc -I../.. -I../../lib -I../../lib/user -I. -Wall -W -Wstrict-prototypes -Wmissing-prototypes -Wsystem-headers  -MMD -MF tests/userprog/sc-bad-sp.d
gcc -c ../../tests/main.c -o tests/main.o -g -msoft-float -O -fno-stack-protector -nostdinc -I../.. -I../../lib -I../../lib/user -I. -Wall -W -Wstrict-prototypes -Wmissing-prototypes -Wsystem-headers  -MMD -MF tests/main.d
gcc  -Wl,--build-id=none -nostdlib -static -Wl,-T,../../lib/user/user.lds tests/userprog/sc-bad-sp.o tests/main.o tests/lib.o lib/user/entry.o libc.a -o tests/userprog/sc-bad-sp
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/sc-bad-sp -a sc-bad-sp -- -q  -f run sc-bad-sp < /dev/null 2> tests/userprog/sc-bad-sp.errors > tests/userprog/sc-bad-sp.output
perl -I../.. ../../tests/userprog/sc-bad-sp.ck tests/userprog/sc-bad-sp tests/userprog/sc-bad-sp.result
gcc -c ../../tests/userprog/sc-bad-sp.c -o tests/userprog/sc-bad-sp.o -g -msoft-float -O -fno-stack-protector -nostdinc -I../.. -I../../lib -I../../lib/user -I. -Wall -W -Wstrict-prototypes -Wmissing-prototypes -Wsystem-headers  -MMD -MF tests/userprog/sc-bad-sp.d
gcc -c ../../tests/main.c -o tests/main.o -g -msoft-float -O -fno-stack-protector -nostdinc -I../.. -I../../lib -I../../lib/user -I. -Wall -W -Wstrict-prototypes -Wmissing-prototypes -Wsystem-headers  -MMD -MF tests/main.d
gcc  -Wl,--build-id=none -nostdlib -static -Wl,-T,../../lib/user/user.lds tests/userprog/sc-bad-sp.o tests/main.o tests/lib.o lib/user/entry.o libc.a -o tests/userprog/sc-bad-sp
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/sc-bad-sp -a sc-bad-sp -- -q  -f run sc-bad-sp < /dev/null 2> tests/userprog/sc-bad-sp.errors > tests/userprog/sc-bad-sp.output
perl -I../.. ../../tests/userprog/sc-bad-sp.ck tests/userprog/sc-bad-sp tests/userprog/sc-bad-sp.result
gcc -c ../../tests/userprog/sc-bad-sp.c -o tests/userprog/sc-bad-sp.o -g -msoft-float -O -fno-stack-protector -nostdinc -I../.. -I../../lib -I../../lib/user -I. -Wall -W -Wstrict-prototypes -Wmissing-prototypes -Wsystem-headers  -MMD -MF tests/userprog/sc-bad-sp.d
gcc -c ../../tests/main.c -o tests/main.o -g -msoft-float -O -fno-stack-protector -nostdinc -I../.. -I../../lib -I../../lib/user -I. -Wall -W -Wstrict-prototypes -Wmissing-prototypes -Wsystem-headers  -MMD -MF tests/main.d
gcc  -Wl,--build-id=none -nostdlib -static -Wl,-T,../../lib/user/user.lds tests/userprog/sc-bad-sp.o tests/main.o tests/lib.o lib/user/entry.o libc.a -o tests/userprog/sc-bad-sp
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/sc-bad-sp -a sc-bad-sp -- -q  -f run sc-bad-sp < /dev/null 2> tests/userprog/sc-bad-sp.errors > tests/userprog/sc-bad-sp.output
perl -I../.. ../../tests/userprog/sc-bad-sp.ck tests/userprog/sc-bad-sp tests/userprog/sc-bad-sp.result
gcc -c ../../tests/userprog/sc-bad-sp.c -o tests/userprog/sc-bad-sp.o -g -msoft-float -O -fno-stack-protector -nostdinc -I../.. -I../../lib -I../../lib/user -I. -Wall -W -Wstrict-prototypes -Wmissing-prototypes -Wsystem-headers  -MMD -MF tests/userprog/sc-bad-sp.d
gcc -c ../../tests/main.c -o tests/main.o -g -msoft-float -O -fno-stack-protector -nostdinc -I../.. -I../../lib -I../../lib/user -I. -Wall -W -Wstrict-prototypes -Wmissing-prototypes -Wsystem-headers  -MMD -MF tests/main.d
gcc  -Wl,--build-id=none -nostdlib -static -Wl,-T,../../lib/user/user.lds tests/userprog/sc-bad-sp.o tests/main.o tests/lib.o lib/user/entry.o libc.a -o tests/userprog/sc-bad-sp
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/sc-bad-sp -a sc-bad-sp -- -q  -f run sc-bad-sp < /dev/null 2> tests/userprog/sc-bad-sp.errors > tests/userprog/sc-bad-sp.output
perl -I../.. ../../tests/userprog/sc-bad-sp.ck tests/userprog/sc-bad-sp tests/userprog/sc-bad-sp.result
cd .
cd ..
make check
make clean
make check
make clean
make check
make checkgcc -c ../../tests/userprog/sc-bad-arg.c -o tests/userprog/sc-bad-arg.o -g -msoft-float -O -fno-stack-protector -nostdinc -I../.. -I../../lib -I../../lib/user -I. -Wall -W -Wstrict-prototypes -Wmissing-prototypes -Wsystem-headers  -MMD -MF tests/userprog/sc-bad-arg.d
gcc  -Wl,--build-id=none -nostdlib -static -Wl,-T,../../lib/user/user.lds tests/userprog/sc-bad-arg.o tests/main.o tests/lib.o lib/user/entry.o libc.a -o tests/userprog/sc-bad-arg
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/sc-bad-arg -a sc-bad-arg -- -q  -f run sc-bad-arg < /dev/null 2> tests/userprog/sc-bad-arg.errors > tests/userprog/sc-bad-arg.output
perl -I../.. ../../tests/userprog/sc-bad-arg.ck tests/userprog/sc-bad-arg tests/userprog/sc-bad-arg.result
ls
cd build/
gcc -c ../../tests/userprog/sc-bad-arg.c -o tests/userprog/sc-bad-arg.o -g -msoft-float -O -fno-stack-protector -nostdinc -I../.. -I../../lib -I../../lib/user -I. -Wall -W -Wstrict-prototypes -Wmissing-prototypes -Wsystem-headers  -MMD -MF tests/userprog/sc-bad-arg.d
gcc  -Wl,--build-id=none -nostdlib -static -Wl,-T,../../lib/user/user.lds tests/userprog/sc-bad-arg.o tests/main.o tests/lib.o lib/user/entry.o libc.a -o tests/userprog/sc-bad-arg
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/sc-bad-arg -a sc-bad-arg -- -q  -f run sc-bad-arg < /dev/null 2> tests/userprog/sc-bad-arg.errors > tests/userprog/sc-bad-arg.output
perl -I../.. ../../tests/userprog/sc-bad-arg.ck tests/userprog/sc-bad-arg tests/userprog/sc-bad-arg.result
cd pintos/src/
ls
source "/home/$USER/.bashrc"
ls
cd threds
cd threads
make
cd ..
cd userprog/
ls
make
make check
ls
cd syscall.c
ls
vi syscall.c
make
vi process.c
vi syscall.c
source "/home/$USER/.bashrc"
cd pintos/src/userprog/
make check
ls
source "/home/$USER/.bashrc"
ps -fU os17
kill -9 24614
ls
cd pintos/
cd src/
cd userprog/
ls
cd ..
cd threads/
ls
vi thread.h
vi thread.c
cd ..
cd userprog/
ls
vi syscall.c
vi process.
vi process.c
make
make check
cd ..
cd threads
make
cd ..
cd threads
make clean
make
cd ..
cd userprog/
ls
make clean
make
make check
ls
cd syscall.c
vi syscall.c
vi process.c
make
make check
vi process.c
ls
source "/home/$USER/.bashrc"
ls
cd pintos/src/
cd userprog/
ls
vi process.c
ps -fU os17
kill -9 18540
vi process.c
make
make check
ls
source "/home/$USER/.bashrc"
cd pintos/src/
cd userprog/
make check
ls
cd ..
ls
cd userprog/
ls
vi syscall.c
ls
cd process.c
ls
vi process.c
vi process.h
vi process.c
cd ..
cd threads
vi thread.h
vi thread.c
make
cd ..
cd process
make
cd userprog/
l
make
make check
source "/home/$USER/.bashrc"
cd pintos/src/threads/
ls
vi thread.h
cd ..
ls
cd userprog/
ls
vi syscall.c
vi process.h
vi exception.c
cd pintos/src/
ls
cd userprog/
ls
vi syscall.c
vi process.c
cd pintos/src/userprog/
ls
vi syscall.c
ls
ls
cd pintos/src/
ls
cd userprog/
ls
vi process.c
vi syscall.c
cd pintos/src/user
cd pintos/src/userprog/
ls
vi process.c
ls
cd pintos/
ls
cd src/userprog/
ls
vi process.c
vi syscall.c
ls
vi exception.c
l
ls
vi process.c
vi process.c
ls
cd pintos/src/
ls
cd userprog/
ls
vi pagedir.c
if config
ifconfig
