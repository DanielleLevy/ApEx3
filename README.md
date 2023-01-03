# ApEx3
## How to compile:
write the following in the terminal , after each one press enter:

1. git clone git@github.com:DanielleLevy/ApEx3.git
2. cd ApEx3
3. make

## How to run:
### The Server(first):
1. make sure youre in ApEx3. if not write cd ApEx3
2. write :
./server.out pathfile port
3. press enter

### The Client(after the server):
1. make sure youre in ApEx3. if not write cd ApEx3
2. write :
./client.out ip port
3. press enter
4. write:
vector distance matric K 
5. press enter
6. steps 4-5 again and again
7. if you want to stop write -1.

## Description:
This is the third exercise out of 4 exercises in the "Advanced Programming 1" course. The exercise is a continuation of the first two exercises in the course. In this part of the exercise we divided the work between us, each of us performed several departments and functions as detailed below:

1. Server class - we created a "server" class (in the cpp file and the h file). The class is initialized by port and file and creates a socket. We created a socket initialization function (returns 0 if the socket is initialized correctly), a handling function and link between the server and the client by the socket (which listens, receives from the client, checks the input, creates the solution and sends it to the client) - returns 0 if everything is normal, a function that checks the input received from the client (saves the vector, the K and the distance function and returns 0 if everything is correct), a function that calculates the answer according to the KNN algorithm and returns it.

2. Client class - we created a "client" class (in the cpp file and the h file). The class is initialized by port and ip and creates a socket. We have created functions that return TRUE if the port and ip are normal, a handling function and a link between the server and the client via the socket (which receives input from the user, checks the input, sends it to the server, receives the solution from it - and if it is normal, prints it) - returns 0 if everything is normal, a function which checks the input received from the user (returns 0 if everything is normal).

Additional Comments:
1. The work was carried out according to the guidelines and rules of object-oriented programming in the CPP language.
2. Each of the classes - server and client, has its own main function (which contains tests) that will allow you to run the file according to the instructions above.
3. The input from the user is composed as follows: in each vector the numbers are separated by a single space. From the last number in the vector to the distance function there is also a single space and from the distance function to K there is also a single space.
4. After receiving the answer about a specific vector, the user can continue to enter a string of vector, distance function, and K and get another answer
5. You can finish and exit the program by entering -1 by the user.
6. This program was written in the CPP language, developed in the CLION development environment and adapted to run on Bar Ilan University servers (U2/PLANET), as requested.
