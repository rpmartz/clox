# Chapter 14

* one of the problems with the design of the jlox interpreter is that since Java is a managed language, we have no control over memory layout. This means that we cannot optimize the program for spatial locality to take as much advantage of cpu caches as possible.
    + modern machines execute instructions faster than they can pull the data from RAM so they pull adjacent bytes from the sections they read from speculatively 

## 14.5 

* for small, fixed-size values like integers, many instruction sets store values directly after the opcode and are called **immediate instructions**
* This does not work for large, or variable sized, values like strings. In a native compiler to machine code, those bigger values get stored in a separate "constant data" region in the binary executable and the instruction to load the constant has an address or offset pointing to where the value is stored in that section
    + _clox_ will store all values in a constant pool, even simple integers
* consider the opcode for a constant - in addition to the instruction to load the constant, the vm needs an operand to know which constant to load 