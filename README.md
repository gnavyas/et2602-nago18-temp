# assignment1
TCP Client Server Code
 ** More application details to be followed
 
Sample Runs:

$$ make clean
$$ make


$$ ./server 127.0.0.1:3333
% Server started successfully on 127.0.0.1:3333
% Waiting for the new client to connect
% New Client has connected
% Connected to the client
% SERVER sent OK
% Sending command to execute -- mul 17784 2140
% Client returned the value 38057760
% Closing client connection

% Waiting for the new client to connect
% New Client has connected
% Connected to the client
% SERVER sent OK
% Sending command to execute -- fsub 0.051097572 0.89908063
% Client returned the value -0.84798306
% Closing client connection

% Waiting for the new client to connect



$$ ./client 127.0.0.1:3333
% Connected to the server 127.0.0.1:3333
** SERVER sent TEXT TCP 1.0
** Server sent following command -- mul 17784 2140
** Sending answer 38057760 to server
% Server sent OK
** Processing server requests done. Closing connection

$$ ./client 127.0.0.1:3333
% Connected to the server 127.0.0.1:3333
** SERVER sent TEXT TCP 1.0
** Server sent following command -- fsub 0.051097572 0.89908063
** Sending answer -0.84798306 to server
% Server sent OK
** Processing server requests done. Closing connection

