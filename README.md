# The Uneven Prankster Examples
These are folders containing implementations of examples of things I am learning about, mainly to put to the test what I acquired and become smarter at all that stuff. I made them open source because you should be able to learn too, young me would love these.

### Planned Examples

* Chip-8 Emulator/Interpretor

The implementation of the programmer's first emulation/interpretation project. This should be a bit cleaner than my past attempts. Surprisingly only a few instructions actually pose any difficulty!

* DCPU-16 Emulator/Interpretor

The implementation of the programmer's second(?) emulation/interpretation project. A bit more tricky due to having a more complex RISC design of sorts than the Chip-8. It's lovely though and created originally by Mojang.

* Lua's C API

I already have quite some knowledge with it, but I want to do examples of all the stuff I love, and this is one of them. You can obviously also do reloading in this one, however I will mainly focus on more game-destined uses.

* CUDA C Programming

I have not touched Nvidia's CUDA other than one long time ago. GPU programming is all the rage these days so I am curious about what it can do! The example will be likely a raytracing one.

* MPEG-1 Decoding

Mainly examples on using `pl_mpeg.h` for OpenGL and SDL2's software-esque rendering, and empowering your program with crispy pixelated video! Amazing for retro games with FMV-esque sequences. Included will be a CC licensed example video made by me.

# Examples, Explained!

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

### Shader Reloading
*Difficulty: Weird*

*Utilized: Linux's stat functions/structs, OpenGL 4.6, GLAD*

Shader Reloading applies the topic in Hot Reloading to shaders, which are perfect for this sort of job. The idea I had was to make a similar env to ShaderToy, a popular free WebGL shader learning/programming website. I have had quite some experience with GL previously so I used a small framework I call 'Monroe' for this. It's MIT licensed like everything else.

However, I had issue with the reloading. The screen will go blank after reloading and even after hours of trying to solve it I just don't have a clue what happened. Currently it is a Heisenbug and it just does not work in my machine, yet it does in other people's. Well, I'll move on and forget this for the better. Ugh.
