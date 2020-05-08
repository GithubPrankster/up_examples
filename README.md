# The Uneven Prankster Examples
These are folders containing implementations of examples of things I am learning about, mainly to put to the test what I acquired and become smarter at all that stuff. I made them open source because you should be able to learn too, young me would love these.

### Hot Reloading
*Difficulty: Tricky*

*Utilized: Linux's stat functions/structs, Tiny C Compiler Library*

This is mainly about being able to make the program reload certain code so as to have the latest additions you made on the fly. Very useful for scripting and the likes. `libtcc.h` makes available features to compile C sources, give them the needed libraries and headers, and not only run them but get symbols like functions and variables which your main program can make use of. 

In the SDL2 example (currently being finalized) `stat` and its main struct are used to give the last time the file has been modified. Every frame, that is again called to check if the time is now different. If it is, the TCC state is reloaded along with the file, and a function pointer (to the lone `foo` function in the C program) is also reloaded too. By pressing A a funny text is currently called. Modify it and try pressing A again :0

### Multithreading
*Difficulty: Complicated*

*Utilized: Linux's pthread*

Multithreading makes use of the threads inside your CPU to run functions in parallel. One can describe it as having multiple `main`s running at once! However synchronization is necessary to keep them from accessing variables at the same time.

The current example showcases 3 threads being spawned, and safely incrementing a variable using mutexes, a sort of thread lock variable, along with keeping a previous copy to let you know later the thread. The incremented variable doubles as the time in seconds for the thread to sleep for, which after that it'll then inform itself. The threads end after that, and the main one as well.
