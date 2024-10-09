# Code on C++ for programming Wave Algorithm
  This is my university homework. For the start I only know a C syntax and trying to use my knowledge for programming it in C++. The only problem that I didn't use a STL references, so just pure C++ with Qt framework. It was a good project to learn some C++ stuff, but I think I did it only on 70%, cause I don't know how to check Qt applications on leaks using valgrind. Anyway, structure of project will be described in next sentences and you can try to run it on your machine. 

## Raw C code.
  For raw C code the goal was to make a console app creating something like this:
  
  ![image](https://github.com/user-attachments/assets/109236f5-454b-4df8-adac-8e89c8ac4966)
  ![image](https://github.com/user-attachments/assets/e6251a00-3cfb-41a9-9038-29b8bffd14f0)
  
  On screenshots you can see a problem of this representation: on the mazes it can't show a path and maze stuff in one text. It made me do this:
  
  ![image](https://github.com/user-attachments/assets/cafd1e52-af55-4dd2-b435-18a755f20e19)

  To install my console app you can write a ```make all``` in [this directory](/MazeProject1/project_on_raw_c/src/)
  Also in this directory you can see four files: [main.c](/MazeProject1/project_on_raw_c/src/main.c), [matrix_funcs.c](/MazeProject1/project_on_raw_c/src/matrix_funcs.c), [path_planning_algs.c](/MazeProject1/project_on_raw_c/src/path_planning_algs.c) and [maze_gen_funcs.c](/MazeProject1/project_on_raw_c/src/maze_gen_funcs.c). 
