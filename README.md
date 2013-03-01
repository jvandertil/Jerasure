# About #
This is the Jerasure project, by James S. Plank, Scott Simmerman, and
Catherine D. Schuman.  More details can be found at
[http://web.eecs.utk.edu/~plank/plank/papers/CS-08-627.html](http://web.eecs.utk.edu/~plank/plank/papers/CS-08-627.html)

See technical report CS-08-627 for a description of the code.  

There are two directories:

* The project home directory contains the jerasure code.
* The Examples directory contains the example programs. 

A Visual Studio 2012 solution for compiling on Windows (x86/x64) is included, as well as a coupling with Java through the Java Native Interface (JNI). 
These were added by Jos van der Til

## Hints ##
* It is assumed that GNU make is being used.
* When using the JNI coupling, be sure to include the JAR file in your java.library.path. 
  * You can also set the library path using: java -Djava.library.path={path}
