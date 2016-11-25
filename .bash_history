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
ls
source "/home/$USER/.bashrc"
git remote add origin git@github.com:YunGyeore/pintos-project3.git
echo "# pintos-project3" >> README.md
git init
git add README.md
git commit -m "first commit"
git remote add origin git@github.com:YunGyeore/pintos-project3.git
git push -u origin masterls
ls
cd .git
ls
cd ..
ls
giit commit -m "first commit"
git commit -m "first commit"
git config --global user.email "ykre0827@gmail.com"s
git config --global user.name "YunGyeore"
git commit -m "first commit"
git remote add origin https://github.com/YunGyeore/pintos-project3.git
git push -u origin master
ls
cd ..
ls
cd ..
cd usr
ls
cd ..
cd home
ls
cd os17
ls
cd .git
ls
cd ..
cd ~/.ssh
ls
vi known_hosts
mkdir key_backup
cp id_rsa* key_backup
ls
ssh-keygen -t rsa -C "ykre0827@gmail.com"
vi id_rsa.pub
:q
cd ..
ls
cd pinso
cd pintos
git remote add origin git@github.com:YunGyeore/pintos-project3.git
git push -u origin master
ls
cd src
ls
cd ..
ls
l
ls src/
cd .
ls
cd ..
ls
cd .git
ls
cd ..
vi README.md 
ls
git remove -v
git remote -v
git push origin master
vi hi.p
vi hic.
vi hi.c
git push origin master
:ls
ls
git commit
git add
git add .
git commit
git push
cd pintos/src/
ls
cd userprog
ls
vi process.c
git commit
git add
git commit -a "test"
git commit
git add process.c
git push
ls
git add .
ls
git add
git add.
git commit
git push
git commit
git add.
git add .
git commit
git commit -a
source "/home/$USER/.bashrc"
ls
cd pintos/src/
ls
cd ..
ls
rm hi.c
ls
vi pintos
q
cd pintos/
ls
l
cd src/userprog/
l
svi process.c
cd ..
cd thread
ms
ls
cd threads/
ls
vi thread.c
ls
cd ..
cd userprog/
ls
vi process.c
source "/home/$USER/.bashrc"
cd pintos/src/
ls
cd vm
ls
source "/home/$USER/.bashrc"
ls
cd pintos/
ls
cd src/
ls
cd vm
ls
cd ..
ls
vi Makefile.build 
ls
cd vm
ls
vi frame.h
cd ..
ls
cd threads/
ls
vi thread.c
vi thread.h
cd ..
cd threads/
ls
vi thread.c
vi thread.h
cd ..
cd vm
ls
vi frame.h
ls
vi frame.c
vi frame.h
vi frame.c
vi frame.h
ls
vi frame.c
vi frame.h
vi frame.c
vi frame.h
source "/home/$USER/.bashrc"
ls
cd pintos/src/
ls
cd userprog/
ls
l
ls
cd ..
make
make clean
make
cd threads/
make
cd ..
cd use
cd userprog/
make
cd ..
cd vm
make
ls
cd build/
ls
cd ..
ls
cd filesys/
make
cd ..
cd threads/
ls
cd thr
cd ..
cd vm
ls
make
makefile
make
make clean
make
make check
cd ..
cd threads/
ls
make
vi thread.c
cd ..
cd vm
ls
vi frame.h
vi frame.c
cd ..
ls
vi Makefile.build
cd vm
ls
vi Makefile
cd ..
cd userprog/
vi Makefile
ls
vi Make.vars
cd vm
cd ..
cd vm
ls
make
make clean
make
ls
make
cd ..
cd threads/
vi threaad.c
vi thread.c
cd ..
cd vm
make
cd ..
cd threads/
vi thread.c
cd ..
cd vm
make
make check
ls
vi frame.c
make check
vi frame.c
cd ..
cd userprog.c
cd userprog/
ls
vi process.c
make
cd ..
cd vm
make
make check
cd ..
cd userprog/
vi userprog.c
vi process.c
cd ..
cd threads/
ls
vi init.c
make
cd ..
cd vm
make
make check
cd ..
cd userprog/
ls
cd ..
cd threads/
la
cd init.c
cd ..
cd threads/
ls
vi init.c
cd ..
cd vm
make
make check
cd ..
ls
cd ..
cd src/threads/
ls
vi init.c
cd ..
cd vm
ls
make
make check
ls
cd frame.c
ls
cd ..
cd vm
ls
make
make check
cd ..
ls
cd threads/
ls
vi thread.c
vi init.c
make
cd ..
cd vm
make
make check
cd ..
ls
cd vm
cd ..
make
cd v
cd vm
make check
cd ..
cd threads/
ls
vi init.c
make
cd ..
cd vm
make check
cd ..
cd vm
ls
vi frame.h
vi init.c
cd ..
ls
make check
cd vm
make check
make clean
make check
gcc  -Wl,--build-id=none -nostdlib -static -Wl,-T,../../lib/user/user.lds tests/userprog/args.o tests/lib.o lib/user/entry.o libc.a -o tests/userprog/args-none
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/args-none -a args-none --swap-size=4 -- -q  -f run args-none < /dev/null 2> tests/userprog/args-none.errors > tests/userprog/args-none.output
cd build/
gcc  -Wl,--build-id=none -nostdlib -static -Wl,-T,../../lib/user/user.lds tests/userprog/args.o tests/lib.o lib/user/entry.o libc.a -o tests/userprog/args-none
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/args-none -a args-none --swap-size=4 -- -q  -f run args-none < /dev/null 2> tests/userprog/args-none.errors > tests/userprog/args-none.output
perl -I../.. ../../tests/userprog/args-none.ck tests/userprog/args-none tests/userprog/args-none.result
cd .
cd ..
cd init.c
cd threads/
vi init.c
cd ..
cd vm
make
make check
vi build
cd build/
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/args-none -a args-none --swap-size=4 -- -q  -f run args-none < /dev/null 2> tests/userprog/args-none.errors > tests/userprog/args-none.output
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/args-none -a args-none --swap-size=4 -- -q  -f run args-none
source "/home/$USER/.bashrc"
cd pintos/src/
cd vm
ls
cd build/
ls
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/args-none -a args-none --swap-size=4 -- -q  -f run args-none
ls
source "/home/$USER/.bashrc"
cd pintos/src/
ls
cd vm
ls
cd build/
ls
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/use
source "/home/$USER/.bashrc"
cd pintos/src/vm
ls
make
cd build/
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/args-none -a args-none --swap-size=4 -- -q  -f run args-none
cd pintos/src/vm
source "/home/$USER/.bashrc"
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/args-none -a args-none --swap-size=4 -- -q  -f run args-none
ls
cd build/
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/args-none -a args-none --swap-size=4 -- -q  -f run args-none
cd pintos/src/vm
ls
source "/home/$USER/.bashrc"
cd build/
make
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/args-none -a args-none --swap-size=4 -- -q  -f run args-none
source "/home/$USER/.bashrc"
cd pintos/src/
cd vm
ls
vi frame.c
make
ls
cd ..
cd threads/
ls
vi thread.c
cd ..
cd vm
make
vi frame.c
cd ..
cd threads/
ls
vi thread.c
cd ..
cd vm
make
ls
cd frame.c
vi frame.c
cd ..
cd threads/
ls
vi thread.c
ls
cd ..
cd vm
cd build/
ls
pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/args-none -a args-none --swap-size=4 -- -q  -f run args-none
source "/home/$USER/.bashrc"
ls
cd pintos/src/
ls
cd vm
ls
ps -fU os17
vi frame.h
ps -fU os17
kill -9 31837
vi frame.h
ls
cd ..
ls
cd vm
lls
vi frame.h
vi frame.c
vi frame.h
vi frame.c
ls
vi frame.h
vi frame.c
ls
cd ..
cd threads/
ls
vi thread.c
ls
cd ..
ls
vi Makefile.build 
cd userprog
ls
vi process.c
cd ..
make
cd thread
cd threads/
ls
make
cd ..
ls
cd vm
ls
vi frame.h
vi frame.c
ls
cd ..
cd threads/
ls
vi thread.c
cd ..
ls
cd vm
ls
make
cd frame.c
vi frame.c
make
vi frame.c
make
vi frame.c
fg
make
vi frame.c
make
vi frame.c
fg
make
vi frame.c
make
vi frame.c
make
vi frame.c
make
cd ..
ls
cd threads/
make
vi thread.c
cd ..
ls
cd vm
ls
vi frame.h
vi frame.c
cd ..
ls
cd threads/
ls
vi thread.c
cd ..
cd userprog/
make
make clean
make
cd ..
ls
vi Makefile
vi Makefile.build
make
cd Makefile.build
vi Makefile.build
cd vm
ls
cd ..
ls
cd vm
ls
vi frame.h
make
cd ..
cd threads/
make
cd ..
cd threads/
ls
vi thread.c
make clean
make
cd ..
ls
cd vm
ls
vi Makefile
vi Make.vars
vi Makefile
cd ..
ls
vi Makefile.kernel 
vi Makefile.build
vi Makefile
ls
cd threads/
ls
vi thread.c
vi thread.h
vi thread.c
ls
cd ..
