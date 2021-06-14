# Packets

Packet format:

```
|--------------------------|--------------------|--------------------------
| Payload length (2 bytes) | Packet ID (1 byte) | Payload
```

## Endianness of the packets

Every packets must be using little endian

## Compression / Encryption priority

A sended packet must be compress and then encrypted

A received packet must be decrypted and then uncompressed

## Compression

```
|------------------------------------|--------------------|--------------------------
| Compressed packet length (2 bytes) | Packet ID (1 byte) | Compressed payload
```

## Encryption

The packet ID is encrypted with the payload to give more security

```
|------------------------------------|-----------------------------------------------
| Encrypted packet length (2 bytes)  | Encrypted packet ID (1 byte) + payload
```

## Client bound packets

| ID | Needs login | Name | Payload | Description
| :- | :---------- | :--- | :------ | :----------
| 0 | No | Login | Username (32) | Login
| 1 | yes | Disconnect | | Disconnect
| 2 | Yes | Users | | Get all users
| 3 | Yes | User | Client UUID (16) | Get informations about a user
| 4 | Yes | Send | Client UUID (16) / Message body (512) | Send a message to a user
| 5 | Yes | Messages | Client UUID (16) | List all messages with a user
| 6 | Yes | Subscribe | Team UUID (16) | Subscribe to a team
| 7 | Yes | Subscribed in team | Team UUID (16) | List all subscribed users of a team
| 8 | Yes | Subscribed teams | | List all subscribed teams
| 9 | Yes | Unsubscribe | Team UUID (16 bytes) | Unsubscribe from a team
| 10 | Yes | Create team | Team name (32) / Team description (255) | Create a new team
| 11 | Yes | Create channel | Team UUID (16) / Channel name (32) / Channel description (255) | Create a new channel
| 12 | Yes | Create a new thread | Team UUID (16) / Channel UUID (16) / Thread title (32) / Thread message (512) | Create a new thread
| 13 | Yes | Create reply | Team UUID (16) / Channel UUID (16) / Thread UUID (16) / Reply message (512) | Create a reply to a thread
| 14 | Yes | List | | List all teams
| 15 | Yes | List chans | Team UUID (16) | List all channels in team
| 16 | Yes | List threads | Team UUID (16) / Channel UUID (16) | List all threads in channel
| 17 | Yes | List replies | Team UUID (16) / Channel UUID (16) / Thread UUID (16) | List all replies of a thread
| 18 | Yes | Info | | List logged user infos
| 19 | Yes | Info team | Team UUID (16) | List teams info
| 20 | Yes | Info chan | Team UUID (16) / Channel UUID (16) | List channel info
| 21 | Yes | Info thread | Team UUID (16) / Channel UUID (16) / Thread UUID | List thread info
| 22 | No | Ping | | Ping
| 23 | No | Set compression | Compression ID (1) | Set the used compression algorithm
| 24 | No | Set encryption | Encryption ID (1) / Key length (4) | Set the used encryption algorithm
| ?? | ?? | Reserved | | Reserved for future uses

## Server bound packets

| ID | Name | Payload | Description
| :- | :--- | :------ | :----------
| 0 | Error | Error Code (1) / Message (1024) | Error throwing
| 1 | Success | | Generic success
| 2 | Info user | User UUID (16) / Username (32) / Status (1) | Get user info
| 3 | Status | Version (Char 64) / Uptime (Int 64) / Clients Connected (Int 64) / Max Clients (Int 64) / MOTD (Char 1024) | Status of the server
| 4 | Subscription | User UUID (16) / Team UUID (16) | User subscribe to a team
| 5 | Unsubscribe | User UUID (16) / Team UUID (16) | Unsubscribe
| 6 | Info team | Team UUID (16) / Team Name (32) / Team description (255) | Get teams info
| 7 | Info chan | Channel UUID (16) / Channel Name (32) / Channel description (255) | Get channel info
| 8 | Info thread | Thread UUID (16) / User UUID (16) / Thread Timestamp (8) / Thread Title (32) / Thread Body (512) | Get thread info
| 9 | Info reply | Team UUID (16) / Thread UUID (16) / Sender UUID (16) / Timestamp (8) / Message (512) | Get message info
| 10 | Info message | Sender UUID (16) / Timestamp (8) / Message (512) | Get message info
| 11 | List header | Number expected packets (2) / Expected packet ID (1) | Number of packets to expect with specific ID
| 12 | Set encryption - AES | Key length (4) / Key (512) | Enable encryption and set encryption key
| 13 | Receive notification | Expected packet ID (1) | Notification with expected packet ID followed by expected packet
| 14 | Error UUID not found | Error Not Found Type (1) / UUID Not Found (16) | Error when UUID is not found
| ?? | Reserved | | Reserved for future uses

## Error codes

| ID | Name
| :- | :---
| 0 | Internal server error
| 1 | Not found
| 2 | No permission
| 3 | Empty field
| 4 | Not implemented
| 5 | Already exist

## Error UUID not found

| ID | Name
| :- | :---
| 0 | User not found
| 1 | Team not found
| 2 | Chanel not found
| 3 | Thread not found

## Answer logic

```
An internal server error must be sent in case
something goes wrong on server side

-> 0
    2 Success
    0 Error
-> 1
    1 Success
-> 2
    11 - 2 Success
    0 Error - No permission
-> 3
    2 Success
    14 Error UUID Not found
    0 Error - No permission
-> 4
    10 Success
    14 Error UUID Not found
    0 Error - No permission
    0 Error - Empty message
-> 5
    11 - 10 Success
    14 Error UUID Not found
    0 Error - No permission
-> 6
    4 Success
    14 Error UUID Not found
    0 Error - No permission
-> 7
    11 - 2 Success
    14 Error UUID Not found
    0 Error - No permission
-> 8
    11 - 4 Success
    0 Error - No permission
-> 9
    5 Success
    0 Error - Not subscribed
    14 Error UUID Not found
    0 Error - No permission
-> 10
    6 Success
    0 Error - Empty name
    0 Error - No permission
    0 Error - Already exist
-> 11
    7 Success
    14 Error UUID Not found
    0 Error - Empty name
    0 Error - No permission
    0 Error - Already exist
-> 12
    8 Success
    14 Error UUID Not found
    0 Error - Empty title
    0 Error - No permission
    0 Error - Already exist
-> 13
    1 Success
    14 Error UUID Not found
    0 Error - Empty message
    0 Error - No permission
-> 14
    11 - 6 Success
    0 Error - No permission
-> 15
    11 - 7 Success
    14 Error UUID Not found
    0 Error - No permission
-> 16
    11 - 8 Success
    14 Error UUID Not found
    0 Error - No permission
-> 17
    11 - 9 Success
    14 Error UUID Not found
    0 Error - No permission
-> 18
    2 Success
    0 Error - No permission
-> 19
    6 Success
    14 Error UUID Not found
    0 Error - No permission
-> 20
    7 Success
    14 Error UUID Not found
    0 Error - No permission
-> 21
    8 Success
    14 Error UUID Not found
    0 Error - No permission
-> 22
    3 Status
-> 23
    2 Success
    0 Error - Not found
-> 24
    12 Success
    0 Error - Not found

-> async
    13 - 2 Success
    13 - 7 Success
    13 - 8 Success
    13 - 9 Success
    13 - 10 Success
```
