# Chapter 14

* one of the problems with the design of the jlox interpreter is that since Java is a managed language, we have no control over memory layout. This means that we cannot optimize the program for spatial locality to take as much advantage of cpu caches as possible.
    + modern machines execute instructions faster than they can pull the data from RAM so they pull adjacent bytes from the sections they read from speculatively 
    