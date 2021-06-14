# Functional tests

To test with valgrind, it is better to compile the server and the client with `make debug`

## Test server buffering and robustness

Run server with valgrind:

```
$ valgrind ./myteams_server_debug 2222
```

And simulates some clients:

```
$ for i in {1..25}; do timeout 0.2 cat /dev/urandom | nc localhost 2222 >& /dev/null; done
```

Result:

```
$ valgrind ./myteams_server_debug 2222
==22048== Memcheck, a memory error detector
==22048== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==22048== Using Valgrind-3.16.1 and LibVEX; rerun with -h for copyright info
==22048== Command: ./myteams_server_debug 2222
==22048== 
Run server on port: 2222

[...]

^CSIGINT received
Select failed: Interrupted system call
Exit server on port: 2222, close all sockets...
==22048== 
==22048== HEAP SUMMARY:
==22048==     in use at exit: 0 bytes in 0 blocks
==22048==   total heap usage: 6,077 allocs, 6,077 frees, 172,462,440 bytes allocated
==22048== 
==22048== All heap blocks were freed -- no leaks are possible
==22048== 
==22048== For lists of detected and suppressed errors, rerun with: -s
==22048== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

## Test client buffering and robustness

Simulate server:

```
$ cat /dev/urandom | nc -l 2222
```

And run client with valgrind:

```
$ valgrind ./myteams_cli_debug localhost 2222
```

And kill the server (with CTRL^C) when you want

Result after one minute:

```
$ valgrind ./myteams_cli_debug localhost 2222
==22048== Memcheck, a memory error detector
==22048== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==22048== Using Valgrind-3.16.1 and LibVEX; rerun with -h for copyright info
==22048== Command: ./myteams_server_debug 2222
==22048== 
Connected to server

[...]

Server closed, exit cli
==22637== 
==22637== HEAP SUMMARY:
==22637==     in use at exit: 0 bytes in 0 blocks
==22637==   total heap usage: 3,463,132 allocs, 3,463,132 frees, 882,441,649 bytes allocated
==22637== 
==22637== All heap blocks were freed -- no leaks are possible
==22637== 
==22637== For lists of detected and suppressed errors, rerun with: -s
==22637== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

## Test server and client on normal usage

```
./myteams_server --help
->
USAGE: ./myteams_server port
	port is the port number on which the server socket listens.
```

```
./myteams_cli --help
->
USAGE: ./myteams_cli ip port
	ip is the server ip address on which the server socket listens
	port is the port number on which the server socket listens
```

```
server:
./myteams_server 9090
->
Run server on port: 9090
```

```
client:
./myteams_cli 127.0.0.1 9090
->
client:
Connected to server
server:
Client connect
```

```
client:
/help
->
client:
    /help : show help
	/login [“user_name”] : set the user_name used by client
	/logout : disconnect the client from the server
	/users : get the list of all users that exist on the domain
	/user [“user_uuid”] : get information about a user
	/send [“user_uuid”] [“message_body”] : send a message to a user
	/messages [“user_uuid”] : list all messages exchange with an user
	/subscribe [“team_uuid”] : subscribe to the event of a team and its sub directories (enable reception of all events from a team)
	/subscribed ?[“team_uuid”] : list all subscribed teams or list all users subscribed to a team
	/unsubscribe [“team_uuid”] : unsubscribe from a team
	/use ?[“team_uuid”] ?[“channel_uuid”] ?[“thread_uuid”] : use specify a context team/channel/thread
	/create : based on what is being used create the sub resource
	/list : based on what is being used list all the sub resources
```

```
client (test):
/login "test"
->
client:
Client 97303a71-7b30-47f2-adac-9bf2f294d162 logged in with login test
server:
New user: test (97303a71-7b30-47f2-adac-9bf2f294d162).
User 97303a71-7b30-47f2-adac-9bf2f294d162 logged in.
```

```
client (test):
/users
->
client:
User "test" (97303a71-7b30-47f2-adac-9bf2f294d162): 1
```

```
client (2ndOne):
/login "2ndOne"
->
client:
Client 35e8e595-c614-40b0-8096-ae33c28491a8 logged in with login 2ndOne
other clients:
Client 35e8e595-c614-40b0-8096-ae33c28491a8 logged in with login 2ndOne
server:
New user: 2ndOne (35e8e595-c614-40b0-8096-ae33c28491a8).
User 35e8e595-c614-40b0-8096-ae33c28491a8 logged in.
```

```
client (test):
/users
->
client:
User "test" (97303a71-7b30-47f2-adac-9bf2f294d162): 1
User "2ndOne" (35e8e595-c614-40b0-8096-ae33c28491a8): 1
```

```
client (2ndOne):
/logout
-> 
client:
Client 35e8e595-c614-40b0-8096-ae33c28491a8 logged out with login 2ndOne
Server closed, exit cli
other clients:
Client 35e8e595-c614-40b0-8096-ae33c28491a8 logged out with login 2ndOne
server:
Client disconnected
Client closed
```

```
client (test):
/users
->
client:
User "test" (97303a71-7b30-47f2-adac-9bf2f294d162): 1
User "2ndOne" (35e8e595-c614-40b0-8096-ae33c28491a8): 0
```

```
client (test):
/send "35e8e595-c614-40b0-8096-ae33c28491a8" "test message"
->
client:
Message sent successfully
other client:
New private message from 97303a71-7b30-47f2-adac-9bf2f294d162: [test message]
server:
Private message 97303a71-7b30-47f2-adac-9bf2f294d162->35e8e595-c614-40b0-8096-ae33c28491a8: test message
```

```
client (2ndOne):
/messages "97303a71-7b30-47f2-adac-9bf2f294d162"
->
client:
[Private] 97303a71-7b30-47f2-adac-9bf2f294d162 (Sun Jun  6 12:16:35 2021): test message
```

```
client (test):
/user "35e8e595-c614-40b0-8096-ae33c28491a8"
->
client:
User "2ndOne" (35e8e595-c614-40b0-8096-ae33c28491a8): 1
```

```
client (test):
/list
->
client:
No teams found
```

```
client (test):
/create "Team Test" "Test team creation"
->
client:
[Team cb90b26e-3434-47a0-b32d-a1700de72d69] Created Team Test, Test team creation
New team created event id cb90b26e-3434-47a0-b32d-a1700de72d69: Team Test (Test team creation)
other clients:
New team created event id cb90b26e-3434-47a0-b32d-a1700de72d69: Team Test (Test team creation)
server:
User 97303a71-7b30-47f2-adac-9bf2f294d162 created Team "Team Test" (cb90b26e-3434-47a0-b32d-a1700de72d69).
```

```
client (test):
/list
->
client:
Team "Team Test" (cb90b26e-3434-47a0-b32d-a1700de72d69): Test team creation
```

```
client (test):
/use "cb90b26e-3434-47a0-b32d-a1700de72d69"
->
```

```
client (test):
/list
->
client:
No chans found
```

```
client (test):
/create "Channel Test" "Test to create channel"
->
client:
[Channel 05244be0-679e-4556-9631-4fcb6978a23d] Created Channel Test, Test to create channel
server:
Channel "Channel Test" (05244be0-679e-4556-9631-4fcb6978a23d) created in team cb90b26e-3434-47a0-b32d-a1700de72d69.
```

```
client (2ndOne):
/subscribe "cb90b26e-3434-47a0-b32d-a1700de72d69"
->
client:
[Subscribed] 35e8e595-c614-40b0-8096-ae33c28491a8 to cb90b26e-3434-47a0-b32d-a1700de72d69
server:
User 35e8e595-c614-40b0-8096-ae33c28491a8 subscribed to cb90b26e-3434-47a0-b32d-a1700de72d69.
```

```
client (test):
/create "Sub Notif Test" "test if subscribed users get notif on channel creation"
->
client:
[Channel 0dbc29ca-23be-473b-ba19-a43ea0ace5a9] Created Sub Notif Test, test if subscribed users get notif on channel creation
server:
Channel "Sub Notif Test" (0dbc29ca-23be-473b-ba19-a43ea0ace5a9) created in team cb90b26e-3434-47a0-b32d-a1700de72d69.
```

```
client (test):
/create "Thread test" "test to create thread"
->
client:
[Thread 9dd71abd-726c-4b0d-8eeb-7c4ad16e8618] Created created by 97303a71-7b30-47f2-adac-9bf2f294d162 (Sun Jun  6 12:51:26 2021): Thread test [test to create thread]
server:
New thread 9dd71abd-726c-4b0d-8eeb-7c4ad16e8618 in channel 05244be0-679e-4556-9631-4fcb6978a23d.
New reply in thread Thread test (9dd71abd-726c-4b0d-8eeb-7c4ad16e8618) from 97303a71-7b30-47f2-adac-9bf2f294d162: test to create thread
```

```
client (2ndOne):
/unsubscribe "cb90b26e-3434-47a0-b32d-a1700de72d69"
->
client:
[Unsubscribed] 35e8e595-c614-40b0-8096-ae33c28491a8 to cb90b26e-3434-47a0-b32d-a1700de72d69
server:
User 35e8e595-c614-40b0-8096-ae33c28491a8 unsubscribe from cb90b26e-3434-47a0-b32d-a1700de72d69.
```

```
client (2ndOne):
/logout
->
client:
Client 35e8e595-c614-40b0-8096-ae33c28491a8 logged out with login 2ndOne
Server closed, exit cli
other clients:
Client 35e8e595-c614-40b0-8096-ae33c28491a8 logged out with login 2ndOne
server:
User 35e8e595-c614-40b0-8096-ae33c28491a8 logged out.
Client disconnected
Client closed
```

```
server:
^C
->
server:
SIGINT received
Select failed: Interrupted system call
Exit server on port: 9090, close all sockets...
clients:
Server closed, exit cli
```

```
client (test):
/use "cb90b26e-3434-47a0-b32d-a1700de72d69" "05244be0-679e-4556-9631-4fcb6978a23d" "9dd71abd-726c-4b0d-8eeb-7c4ad16e8618"
->
```

```
client (test):
/list
->
No replies found
```

```
client (test):
/create "Just a test message"
->
server:
New reply in thread (9dd71abd-726c-4b0d-8eeb-7c4ad16e8618) from 97303a71-7b30-47f2-adac-9bf2f294d162: Just a test message
```

```
client (2ndOne):
/use "cb90b26e-3434-47a0-b32d-a1700de72d69" "05244be0-679e-4556-9631-4fcb6978a23d"
->
```

```
client (2ndOne):
/list
->
client:
[Thread 9dd71abd-726c-4b0d-8eeb-7c4ad16e8618] Created by 97303a71-7b30-47f2-adac-9bf2f294d162 (Sun Jun  6 12:51:26 2021): Thread test [test to create thread]
```

```
client (test):
/info
->
client
User "test" (97303a71-7b30-47f2-adac-9bf2f294d162): 1
```

```
client (test):
/use "cb90b26e-3434-47a0-b32d-a1700de72d69"
/info
->
client:
Team "Team Test" (cb90b26e-3434-47a0-b32d-a1700de72d69): Test team creation
```

```
client (test):
/use "cb90b26e-3434-47a0-b32d-a1700de72d69" "05244be0-679e-4556-9631-4fcb6978a23d"
/info
->
client:
Channel "Channel Test" (05244be0-679e-4556-9631-4fcb6978a23d): Test to create channel
```

```
client (2ndOne):
/use "cb90b26e-3434-47a0-b32d-a1700de72d69" "05244be0-679e-4556-9631-4fcb6978a23d" "9dd71abd-726c-4b0d-8eeb-7c4ad16e8618"
/info
->
client:
Thread "05244be0-679e-4556-9631-4fcb6978a23d" created by 97303a71-7b30-47f2-adac-9bf2f294d162 (Sun Jun  6 12:51:26 2021): Thread test [test to create thread]
```

## Test server error handling

```
server:
./myteams_server
->
myteams_server: invalid number of arguments: got 0 expected 1
Try './myteams_server --help' for more information.
```

```
./myteams_server test
->
myteams_server: invalid port: 'test'
Try './myteams_server --help' for more information.
```

## Test cli error handling

```
./myteams_cli
->
myteams_cli: invalid number of arguments: got 1 expected 3
Try './myteams_cli --help' for more information.
```

```
./myteams_cli 127.0.0.1 test
->
myteams_cli: invalid port: '127.0.0.1'
Try './myteams_cli --help' for more information.
```

```
./myteams_cli test 9090
->
Invalid address
```

```
client (not logged in):
/users
->
client:
Unauthorized: action prohibited
server:
Packet error: user is not logged in
```