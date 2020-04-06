# OpenMP_examples
My solutions for problems given in <a href="https://www.youtube.com/watch?v=nE-xN4Bf8XI&list=PLLX-Q6B8xqZ8n8bwjGdzBJ25X2utwnoEG" target="_blank">'Introduction to OpenMP' course by Tim Mattson</a>.
I do also recommend you check the <a href="https://www.openmp.org/wp-content/uploads/Intro_To_OpenMP_Mattson.pdf" >course slides</a> and <a href="https://www.youtube.com/redirect?redir_token=uu2vwOEKbSBDzcTbeTxF9LUOl-58MTU4NjI2ODg3NUAxNTg2MTgyNDc1&event=video_description&v=nE-xN4Bf8XI&q=http%3A%2F%2Fopenmp.org%2Fmp-documents%2FMattson_OMP_exercises.zip">exercise files<a/>.

I compiled all the programs on Mac OS with gcc compiler(version 9.2.*).

# Installing gcc with OpenMP on Mac OS
To use OpenMP I do recommend gcc compiler. You can easily install it with <a href="https://brew.sh/" target="_blank">Homebrew package manager</a>. 

1. Open new Terminal window and put:
```
brew install gcc
```

2. Verify installation with Homebrew:
```
brew info gcc
```

3. Check if gcc file exist in the Finder
Open Finder >> "Go" >> "Go to Folder" (Command+Shift+G)
and put: 
```
/usr/local/bin/
```
Check your gcc file. For example it was gcc-9 in my case.

# Running programs in gcc with OpenMP on Mac OS
Open new Terminal window in folder with cloned programs and put:

```
gcc-9 -fopenmp your_open_mp_program_name.c -o output_name
```

You can run your program in Terminal by putting:
```
./output_name 
```
(no  *.out extension required)

To run it more than once you can put bash commands:
```
for i in {1..10}; do ./output_name parameter_1 parameter_2; done;
```
  where  parameters parameter_1 and parameter_2 are optional

Compiling tips:
1. Don't forget to put '-fopenmp' after gcc declaration. Otherwise compiler won't recognize <omp.h>
2. gcc-9 is my compiler file(check installing gcc in previous section). Running it just as 'gcc -fopenmp...' doesn't work.
