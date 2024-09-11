import socket

####### A SIMPLE ILLUSTRATION OF THE TCP SERVER #######

# The port number on which to listen for incoming
# connections.
PORT_NUMBER = 1235

# Create a socket
serverSock = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 

# Associate the socket with the port
serverSock.bind(('', PORT_NUMBER)) # The server is listening on port 1235

# Start listening for incoming connections (we can have
# at most 100 connections waiting to be accepted before
# the server starts rejecting new connections)
serverSock.listen(100) #So the server is now listening for calls from the client. I can have a queue no more of 100 people. 
#Now If one ddoss this server, the server crashes cus the connections exceeds 100?

# Keep accepting connections forever
while True:

	print("Waiting for clients to connect...")
	
	# Accept a waiting connection
	cliSock, cliInfo = serverSock.accept() #Three way handshake applies here but in simple words, this line of code means 
	#if a client is waiting, accept them and communicate with them. The CliSock is used to open a session for the client and CliInfo allows
	#them to communicate with the server.
	
	print("Client connected from: " + str(cliInfo)) #gets where they connected from
	
	# Receive the data the client has to send.
	# This will receive at most 1024 bytes
	cliMsg = cliSock.recv(1024)
	
	# The string containing the uppercased message. What is upper cased message? 
	upperMsgStr = cliMsg.decode().upper()
	
	print("Client sent " + str(cliMsg.decode()))

	# Send the upper-cased string back to the client
	capString = cliMsg.decode().upper()

 #Before I send the clients message, I need to encode it cus it needs to be encrypted when going across the data link?
	cliSock.send(capString.encode())
	
	# Hang up the client's connection
	cliSock.close()


#It adds a b to indicate that it is bytes. It adds this b because we said cliSock.send(capString.encode())