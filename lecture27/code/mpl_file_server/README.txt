# a file server and file server client built atop the message passing layer (MPL) (libmpl.a) README
# from the mpl_file_server folder use the following commands:
./builAll - build everything: the message passing library (libmpl.a), the file server (cse384_file_server_executable.cpp),
            the file server client (cse384_client_executive.cpp), and the Receiver, and Sender test stubs: (ReceiverTest and SenderTest)
./buildFSserver - builds the file server (cse384_file_server_executive.cpp)
./buildFSclient - builds the file server client (cse384_client_executive.cpp)
./runServerTwoclients -  run the file server executable, and two clients (server file  storage: ./serverFiles), clients' file storage is 
                         ./client1Files and ./client2Files respectively)
./runTests - runs the MPL Receiver and Sender test stubs demonstrating the functionality of the MPL
  
cse384_client_executive.cpp -  the fs server client C++ code.
cse384_file_server_executable.cpp - the fs server C++ code.
Project2utils.h/cpp -  helper (utility) functions for the fs client and server code
