# Chapter 14

* one of the problems with the design of the jlox interpreter is that since Java is a managed language, we have no control over memory layout. This means that we cannot optimize the program for spatial locality to take as much advantage of cpu caches as possible.
    + modern machines execute instructions faster than they can pull the data from RAM so they pull adjacent bytes from the sections they read from speculatively 

## 14.5 

* for small, fixed-size values like integers, many instruction sets store values directly after the opcode and are called **immediate instructions**
* This does not work for large, or variable sized, values like strings. In a native compiler to machine code, those bigger values get stored in a separate "constant data" region in the binary executable and the instruction to load the constant has an address or offset pointing to where the value is stored in that section
    + _clox_ will store all values in a constant pool, even simple integers
* consider the opcode for a constant - in addition to the instruction to load the constant, the vm needs an operand to know which constant to load 

## 14.6 Line Info

* in jlox, the tokens in the AST contained their original line numbers
* clox will store the line numbers in an array in the `Chunk` struct. 
    + This is inefficient from a memory standpoint
    + one good part about this design is that it keeps the line numbers out of the bytecode instructions, which means we are not taking up memory that could be used for other instructions for data (line numbers) that will only be used when we need to display an error (which is hopefully infrequently)
    
# Chapter 16 Scanning on Demand

* in clox we do not include the actual literal value of the strings in the tokens, just pointers to the start and end 
 
## Identifiers

* in jlox, we could rely on a hashtable to differentiate keywords from identifiers because it was built in to the Java runtime. C doesn't have a built in data structure like that. We could build it, but it's overkill for this. We can use a trie, which minimizes the amount of work to determine if a string matches another (only needs to check minimum number, not consume the whole string to compute the hash code the way a hash table does).    