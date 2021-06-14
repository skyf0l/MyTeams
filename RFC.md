# Documentation RFC - MY TEAMS

###### Tom RORATO, Léo BAZOT, Pauline FAURÉ
###### Epitech TOULOUSE - Promotion 2024


## SOMMAIRE

* ### Format d'un paquet
* ### Paquets liés au client
* ### Paquets liés au serveur

## Format d'un paquet

Un paquet est composé de la taille des données sur 2 bytes, puis de l'ID du paquet et enfin des données.

La taille maximale d'un paquet est donc de 65539 bytes (3 bytes pour l'entête et 65536 pour les données).

Format:
```
| Entête du paquet ----------------------------------- | Données ...
| Taille des données (2 bytes) | ID du paquet (1 byte) | Données ...
```

## Paquets liés au client

Toutes les commandes peuvent échouer du côté du seveur, dans ce cas, le paquet 0 du serveur sera retourné avec le code 0 (erreur interne).

* ### Login
Le paquet `login` possède l'ID 0. Il prend en paramètre un nom d'utilisateur et permet de se connecter au serveur.

Format des données du paquet:
```
| Nom d'utilisateur (32 bytes)
```

En cas de succès, le paquet d'informations relatives à l'utilisateur sera retourné (ID 2).

* ### Disconnect
Le paquet `disconnect` possède l'ID 1. Il déconnecte un utilisateur du serveur.

Format des données du paquet:
```
| Vide
```

* ### Users
Le paquet `users` possède l'ID 2. In ne prend aucun paramètre et consiste à lister tous les utilisateurs enregistrés.

Format des données du paquet:
```
| Vide
```

En cas de succès, le paquet 11 sera retourné, suivit d'un certain nombre (détaillé dans le paquet 11) de paquets 2.

* ### User
Le paquet `user` possède l'ID 3. Il prend en paramètre l'UUID d'un utilisateur existant afin d'en fournir les informations.

Format des données du paquet:
```
| UUID de l'utilisateur (16 bytes)
```

En cas de succès, le paquet 2 sera retourné.

Si l'utilisateur n'existe pas, le paquet 14 sera retourné.

* ### Send
Le paquet `send` possède l'ID 4. Il prend l'UUID d'un utilisateur connecté ainsi qu'un message. L'objectif de ce paquet est d'envoyer un message à un utilisateur.

Format des données du paquet:
```
| UUID de l'utilisateur (16 bytes) | Message (512 bytes)
```

Si l'utilisateur n'existe pas, le paquet 14 sera retourné.

* ### Messages

Le paquet `messages` possède l'ID 5. L'UUID d'un utilisateur est passé en paramètre. ce paquet liste tous les messages échangés avec l'utilisateur indiqué.

Format des données du paquet:
```
| UUID de l'utilisateur (16 bytes)
```

En cas de succès, le paquet 11 sera retourné, suivit d'un certain nombre (détaillé dans le paquet 11) de paquets 10.

Si l'utilisateur n'existe pas, le paquet 14 sera retourné.

* ### Subscribe
Le paquet `subscribe` possède l'ID 6. Il prend en paramètre l'identifiant d'une équipe. Le paquet permet de soucrire à l'équipe souhaitée.

Format des données du paquet:
```
| UUID de l'équipe (16 bytes)
```

En cas de succès, le paquet 4 sera retourné.

Si l'équipe n'existe pas, le paquet 14 sera retourné.

* ### Subscribed in team
Le paquet `subscribed in team` possède l'ID 7. Elle prend en paramètre l'UUID d'une équipe déjà existante. Ce paquet consiste à lister les utilisateurs abonnés à l'équipe mentionnée.

Format des données du paquet:
```
| UUID de l'équipe (16 bytes)
```

En cas de succès, le paquet 11 sera retourné, suivit d'un certain nombre (détaillé dans le paquet 11) de paquets 2.

Si l'équipe n'existe pas, le paquet 14 sera retourné.

* ### Subscribed teams
Le paquet `subscribed` possède l'ID 8. Elle liste toutes les équipes auxquelles l'utilisateur s'est abonné.

Format des données du paquet:
```
| Vide
```

En cas de succès, le paquet 11 sera retourné, suivit d'un certain nombre (détaillé dans le paquet 11) de paquets 4.

* ### Unsubscribe
Le paquet `unsubscribe` possède l'ID 9. Il prend l'UUID d'une équipe en paramètre. Son utilisation permet de se désabonner de l'équipe stipulée.

Format des données du paquet:
```
| UUID de l'équipe (16 bytes)
```

En cas de succès, le paquet 5 sera retourné.

Si l'équipe n'existe pas, le paquet 14 sera retourné.

* ### Create team
Le paquet `create team` possède l'ID 10. Il prend un nom et une description. Il permet de créer une équipe.

Format des données du paquet:
```
| Titre (32 bytes | Description (255 bytes)
```

Si l'équipe est créée, le paquet numéro 6 sera retourné.

Si une équipe existe déjà avec le même titre, le paquet 0 sera retourné avec le code 5 (existe déjà).

* ### Create channel
Le paquet `create chan` possède l'ID 11. Il prend l'UUID de l'équipe dans laquelle il doit être créé, un nom et une description en paramètres. Il permet de créer un cannal.

Format des données du paquet:
```
| UUID de l'équipe (16 bytes) | Titre (32 bytes) | Description (255 bytes)
```

Si le canal est créé, le paquet numéro 7 sera retourné.

Si l'équipe n'existe pas, le paquet 14 sera retourné.

Si un canal existe déjà avec le même titre, le paquet 0 sera retourné avec le code 5 (existe déjà)

* ### Create thread
Le paquet `create thread` possède l'ID 12. Il prend l'UUID de l'équipe, puis du cannal dans laquelle il doit être créé, une titre et un message en paramètres. Il permet de créer une discussion.

Format des données du paquet:
```
| UUID de l'équipe (16 bytes) | UUID du cannal (16 bytes) | Titre (32 bytes) | Message (512 bytes)
```

Si la discussion est créée, le paquet numéro 8 sera retourné.

Si l'équipe ou le cannal n'existent pas, le paquet 14 sera retourné.

Si un canal existe déjà avec le même titre, le paquet 0 sera retourné avec le code 5 (existe déjà)

* ### Create reply
Le paquet `create reply` possède l'ID 13. Il prend l'UUID de l'équipe, puis du cannal, puis de la discussion dans laquelle il doit être créé et un message en paramètres. Il permet de répondre à une discussion

Format des données du paquet:
```
| UUID de l'équipe (16 bytes) | UUID du cannal (16 bytes) | UUID de la discussion (16 bytes) | Message (512 bytes)
```

Si la réponse est créée, le paquet numéro 9 sera retourné.

Si l'équipe, le cannal ou la discussion n'existent pas, le paquet 14 sera retourné.

* ### List teams
Le paquet `list teams` possède l'ID 14. Il ne prend aucuns paramètres. Il va permettre de récupérer toutes les équipes.

Format des données du paquet:
```
| Vide
```

En cas de succès, le paquet 11 sera retourné, suivit d'un certain nombre (détaillé dans le paquet 11) de paquets 6.

* ### List chans
Le paquet `list chans` possède l'ID 15. Il prend l'UUID d'une équipe en paramètres. Il va permettre de récupérer tous les cannaux d'une équipe.

Format des données du paquet:
```
| UUID de l'équipe (16 bytes)
```

En cas de succès, le paquet 11 sera retourné, suivit d'un certain nombre (détaillé dans le paquet 11) de paquets 7.

* ### List threads
Le paquet `list threads` possède l'ID 16. Il prend l'UUID d'une équipe, puis d'un cannal en paramètres. Il va permettre de récupérer toutes les discussions d'un cannal.

Format des données du paquet:
```
| UUID de l'équipe (16 bytes) | UUID du cannal (16 bytes)
```

En cas de succès, le paquet 11 sera retourné, suivit d'un certain nombre (détaillé dans le paquet 11) de paquets 8.

* ### List replies
Le paquet `list replies` possède l'ID 17. Il prend l'UUID d'une équipe, puis d'un cannal, puis d'une discussion en paramètres. Il va permettre de récupérer tous les messages d'une discussion.

Format des données du paquet:
```
| UUID de l'équipe (16 bytes) | UUID du cannal (16 bytes) | UUID de la discussion (16 bytes)
```

En cas de succès, le paquet 11 sera retourné, suivit d'un certain nombre (détaillé dans le paquet 11) de paquets 9.

* ### Info
Le paquet `info teams` possède l'ID 18. Il ne prend aucuns paramètres. Il va récupérer les informations relatives à l'utilisateur connecté.

Format des données du paquet:
```
| Vide
```

En cas de succès, le paquet 2 sera retourné.

* ### Info team
Le paquet `info teams` possède l'ID 19. Il prend l'UUID d'une équipe en paramètres. Il va récupérer les informations relatives à une équipe.

Format des données du paquet:
```
| UUID de l'équipe (16 bytes)
```

En cas de succès, le paquet 6 sera retourné.

Si l'équipe n'existe pas, le paquet 14 sera retourné.

* ### Info chan
Le paquet `info teams` possède l'ID 20. Il prend l'UUID d'une équipe, puis d'un cannal en paramètres. Il va récupérer les informations relatives à un cannal.

Format des données du paquet:
```
| UUID de l'équipe (16 bytes) | UUID du cannal (16 bytes)
```

En cas de succès, le paquet 7 sera retourné.

Si l'équipe ou le cannal n'existent pas, le paquet 14 sera retourné.

* ### Info thread
Le paquet `info teams` possède l'ID 11. Il prend l'UUID d'une équipe, puis d'un cannal, puis d'une discussion en paramètres. Il va récupérer les informations relatives à une discussion.

Format des données du paquet:
```
| UUID de l'équipe (16 bytes) | UUID du cannal (16 bytes) | UUID de la discussion (16 bytes)
```

En cas de succès, le paquet 8 sera retourné.

Si l'équipe, le cannal ou la discussion n'existent pas, le paquet 14 sera retourné.

* ### Ping
Le paquet ping porte l'identifiant 22 et ne prend pas de paramètre. Il renvoie les informations du serveur.

Format des données du paquet:
```
| Vide
```

En cas de succès, le paquet 3 sera retourné.

## Paquets liés au serveur

* ### Error
En cas d'erreur, le packet 0 est renvoyé.

Ce paquet retourne un code d'erreur (1 byte).

Codes d'erreur:

 - Erreur interne = 0
 - Ressource non trouvée = 1
 - Pas assez de permissions = 2
 - Champ vide = 3
 - Commande non implémentée = 4
 - Resource déjà existante = 5

* ### Success
En cas de succès, le packet 1 est renvoyé.

Ce paquet ne retourne aucunes données

* ### Info user
ID : 2

Ce paquet retourne l'UUID (16 bytes) et un nom (32 bytes) d'utilisateur ainsi qu'un statut (1 byte).

Status:

 - Déconnecté = 0
 - Connecté = 1

* ### Status
ID : 3

Ce paquet renvoie la version du serveur (32 bytes), le nombre de secondes écoulées depuis le lancement du server (8 bytes), le nombre de clients connectés (8 bytes), le nombre maximum de clients (8 bytes) et un message (512 bytes).

* ### Suscription
ID : 4

Ce paquet renvoie les UUID's (16 bytes) d'un utilisateur et d'une équipe.

* ### Unsubscribe
ID : 5

Ce paquet retourne les UUID's (16 bytes) d'un utilisateur et d'une équipe.

* ### Info team
ID : 6

Ce paquet retourne l'UUID (16 bytes), le nom (32 bytes) et la description (255 bytes) d'une équipe.

* ### Info chan
ID : 7

Ce paquet retourne l'UUID (16 bytes), le nom (32 bytes) et la description (255 bytes) d'un canal de communication.

* ### Info thread
ID : 8

Ce paquet retourne les UUID's (16 bytes) d'un fil de communication et de utilisateur qui l'a créé. Il renvoie également la date de création (8 bytes), le titre (32 bytes) et le corps (512 bytes) du fil de communication.

* ### Info reply
ID : 9

Ce paquet renvoie les UUID's (16) d'une équipe, d'un fil de communication et de l'expéditeur, la date (8 bytes) et le message (512 bytes).

* ### Info messages
ID : 10

Ce paquet renvoie l'UUID (16 bytes) de l'expéditeur, la date (8 bytes) et le message (512 bytes).

* ### List header
ID : 11

Ce paquet retourne le nombre de paquet attendus (2 bytes) et l'identifiant du paquet attendu (1 byte).

* ### Set encryption - AES
ID : 12

Ce paquet renvoie la taille de la clé (4 bytes) et la clé (512 bytes).

* ### Receive notification
ID : 13

Ce paquet retourne l'identifiant du paquet attendu (1 byte).

* ### Error UUID not found
ID : 14

Ce paquet renvoie le type d'UUID non trouvée (1 byte) et l'UUID non trouvé (16 bytes).

Type d'UUID non trouvée:

 - Utilisateur non trouvé = 0
 - Equipe non trouvé = 1
 - Cannal non trouvé = 2
 - Discussion non trouvé = 3

## Dépôts de travail

[My_teams](https://github.com/EpitechIT2020/B-NWP-400-TLS-4-1-myteams-pauline.faure)

[Architecture commune](https://github.com/huntears/my_teams_rfc)
