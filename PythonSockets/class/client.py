import socket

# Server's IP address
SERVER_IP = "127.0.0.1"
#So I am connecting to a server at 127.0.0.1 and I'm connecting to port 1235
# The server's port number
SERVER_PORT = 1235

# The client's socket
cliSock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
  #socket.AF_INET means that I am using IPV 4 ip addresses. 
  #socket.SOCK_Stream enables the client to receive messages, I think

# Attempt to connect to the server
cliSock.connect((SERVER_IP, SERVER_PORT))

# Send the message to the server
msg = input("Please enter a message to send to the server: ") #This is basically printf in c. I am asking the client what he or she 
#wants to say to the server.

# Send the message to the server
# NOTE: the user input is of type string
# Sending data over the socket requires.
# First converting the string into bytes.
# encode() function achieves this.
cliSock.send(msg.encode())

# Receive the response from the server
servMsg = cliSock.recv(1024)

response = servMsg.decode()

print(response)





#So now we want to modify the code such that the following happens:

#1) The client sends the entered string to the server.
#2) The server RCV the string, capitilize the string, and send it back to cl.
#3)The client recovers the string and prints it

