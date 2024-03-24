## The ***SNAKE*** game.

Written in C++ / v. 17.

**Features:**

Graphics rendered in **ASCII** within Windows Terminal (powershell, tabby, etc.)

```**Single Player**``` - keyboard controls are W A S D

```**Hot Seat Player**``` - up to 4 players, keyboard control are W A S D - I J K L - [ ; ' \ - 8 4 5 3

```**Internet Network Multiplayer**``` via UDP protocol - up to 2 players

For UDP communication was used ```eNet``` library from: http://enet.bespin.org/ (you need it for compile Snake).

The ```C++ wrapper``` for eNet library is here: https://github.com/tomasmark79/server-client (you need it for compile Snake).

To start multiplayer game over internet, intranet or localhost:

Hosting player enter the IP address or FQDN and will host the game.

Client player enter the IP address or FQDN and will connect to the host.

Protocol used UDP, port used 7996.

https://github.com/tomasmark79/snake-in-console/assets/44719504/e8a7397a-390e-451c-8248-73bca63dce72

***Hot Seat***
Up to 4 players.

https://github.com/tomasmark79/snake-in-console/assets/44719504/b0a1e7e8-10b2-4ef8-bb4e-2cd7843d9454

***Single Player***
Peacefull solo game mode.

https://github.com/tomasmark79/snake-in-console/assets/44719504/18b0d478-8cb9-4583-9580-33f1d8a77a2b



