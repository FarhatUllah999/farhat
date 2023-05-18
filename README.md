1. Create a directory e.g. "build" for Makefiles and objects
    mkdir build
2. Run below command to run CMake to create make files
    cmake -S . -B build
3. Goto "build" directory
    cd build
4. Run make command to compile the code
    make
5. It will compile the code and create a binary file with the name "my_project"
6. Run the binary object with
    ./my_object
