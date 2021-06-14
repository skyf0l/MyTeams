# MyTeams

A collaborative communication application like the well known Microsoft Teams

# Features

A collaborative communication application is a service able to manage severall communication teams, where discussion are organised like following:
 - threads (initial post and additional comments) in a specific channel
 - discussion (personnal messages)

Here are the features implemented :
 - Creating/Joining/Leaving a team
 - Creating a user
 - Creating a channel in a team
 - Creating a thread in a channel
 - Creating a comment in a thread
 - Saving & restoring users, teams, channels, threads & associated comments
 - Personnal discussion (from a user to an other)
 - Saving & restoring personnal discussion

# Build

Build all

```bash
$ make all
```

Or only build server / client

```bash
$ make server
$ make cli
```

# Run

Server:

```
$ ./run.sh ./myteams_server 2222
```

Client:

```
$ ./run.sh ./myteams_cli localhost 2222
```

# JSON database format:

```json
{
    "users": {
        uuid: {
            "timestamp": time,
            "name": name,
            "teams_sub": [team_uuid]
        }
    },
    "private_messages": [
        {
            "users": [uuid1, uuid2],
            "messages": {
                uuid: {
                    "timestamp": time,
                    "from": uuid_user,
                    "message": message
                }
            }
        }
    ],
    "teams": {
        uuid: {
            "timestamp": time,
            "name": name,
            "description": desc,
            "creator": uuid_user,
            "users_sub": [],
            "channels": {
                uuid: {
                    "timestamp": time,
                    "name": name,
                    "description": desc,
                    "creator": uuid_user,
                    "threads": {
                        uuid: {
                            "timestamp": time,
                            "name": name,
                            "description": desc,
                            "creator": uuid_user,
                            "messages": {
                                uuid: {
                                    "timestamp": time,
                                    "message":message,
                                    "from":uuid_user
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
```
