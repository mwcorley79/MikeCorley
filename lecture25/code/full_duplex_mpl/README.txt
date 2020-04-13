#  This README describes how to build and run the (full duplex version) of the Message Passing Library MPL)
#  with network (file) copy transfer service and client as an example.  This example illustrates a full duplex
#  client/server application to transfer files one a block at time using message passing
 
./buildAll -- builds the libmpl.a and all tests

# build the network file transfer service
g++ -o net_cp_service netCopyService.cpp libmpl.a -lpthread  

# build the network copy client
g++ -o net_cp_client  netCopyClient.cpp libmpl.a -lpthread

# running the file transfer service example
1. open a new terminal and type: ./net_cp_service ./serverFiles/ 127.0.0.1 5050
   -- ./serverFiles/ -- the servers rooted-path (file storage folder)
   -- 127.0.0.1  5050 -- servers listening endpoint

# running the file transfer client
./net_cp_client ./clientFiles/mpl_file_server_example.tar.gz 50000 127.0.0.1 5050
  	-- path of file to transfer
        -- block size
        -- end point of the server to transmit to
	

