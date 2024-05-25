# file-system-management-and-methods-multiplexed-input-output

(17.10.2022)

Part 1: Serial I/O Functions. Make a program that:

1. Gets two file names as command line arguments 
2. The first file is opened for reading, the second for rewriting, or creates, if it is 
does not exist (use attributes 0644 to create) 
3. Sequentially reads data from the first file with buffers of a fixed volume (for example 
512 bytes) and writes to the second. 
4. Before writing with the contents of the buffer, it performs the following transformation - all string letters 
of the Latin alphabet converts to the corresponding capital letters. To do this, calculate 
the corresponding shift according to the ASCII table (see man ascii). 
5. In the process of overwriting, counts the overwritten bytes, and at the end 
outputs the total amount of overwritten data to the output stream.

Part 2: Functions of Multiplexed I/O. Make a program that:

1. Gets an arbitrary string identifier as a command line argument. 
2. Configures the select system call to wait for a read in the input stream ( 
file descriptor STDIN_FILENO ) with a timeout of 5 seconds. 
3. When receiving the ability to read, read from the stream a buffer with a length of no more 
1024 bytes and output it to the output stream with a mark in the form of the identifier of item 1. 
4. When the timeout pops up, display a message about this in the error stream with a y mark 
in the form of the identifier item 1 and configure the select system call again (item 2). 
5. Test the operation of the program by receiving input results from the input stream 
keyboard
