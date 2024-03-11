# snake-in-console

Traditional ***Snake*** game for Windows console.

In an effort to get some practice in, I decided to create my own Snake game, which can be played within the the console Windows. The Snake game is rendered using only ASCII characters. You can play the game in command line, powershell or tabby and so on. You can play with your three friends so togeter can play up to four player with only one keyboard :-). Sources compilable with standard C++ libraries. C++ standard version 17. Compiled with GCC MinGW v13.2.

Extra function:
Up to 4 snakes for 4 players via Hot Seat (one keybard) !

To do:
Implementation of several more game mechanism and flying insect across the field environment!

Main welcome screen:

```
----------------------------------------
Welcome to the game
 ___              _
/ __| _ _   __ _ | |_____
\__ \| ' \ / _` || / / -_)
|___/|_||_|\__/_||_\_\___| in console
----------------------------------------
Copyright (c) 2024 Tomas Mark
tomas@digitalspace.name
Enjoy this example of OOP C++17 code!
build v0.0.3
Start immediately with default settings yes/no ?
```

Main game field

```
 ---------------------------------------------------------☺--------------------
|   : :        : ::::::  : :    :: :: :   :    : : ::  :: X        : :     ::: |
|   :  :     :   :   :  :     ::: :  : ::: :::    ::   :  X ::   :     : : :: :|
| :::  : :   : :: : ::   ::: ::  :  : ::      :::    :: ::X   ::: :  :   ::: ::|
|:   :: : :          :: :::        ::: :: ::  : :  :      X      ::::  :     ::|
|:::: :::::   : : :               :::::: :: ::        : ::X   :     : ::  ::   |
|  ::  :  : ::  :  ::   : : ::  ::::   : : :   : :   :::::X:: :   : :  : :  : :|
|  ::  :: :    ::   ::  : :::::: :::: :  :  :::      : :  X : :   :: :  :: : : |
|  : :: ::      :   : : :  : :: ::::         : :: ::: : ::X::::  :     :  : :  |
|::   :    :::  : :  :  :::     :::  :   :   : : ::::::: :X   :: : : :   :: : :|
| ::: : : : : :   : :: : :: : ::: : : :   : :  :   :::: : X:  :      :   :: : :|
|:  :     :    :::: : :::::: :  :   : :: :::     : :   :  X : :::    ::   :: : |
| :  :  :  ::::  :   :: ::   :   ::  ::: : ::::   :  : :  X       : :  :   :: :|
|    :: :: :: :: ::::  ::  ::      : : :    :::   : :  :::X:: : :::: :::  : :: |
| :   : :    : 000000000♦:  :: : : :: ::  : :: :: :   ::::X::  ::  :: :  ::::  |
|:  :  :::  : :0 :: :: ::  :  : :   :    : :::   :::   :: X  :    :::    ::::  |
| :  :: :  :: :0   : : :: : ::::: :   :: :     : :  ::   :X: ::   :: :  : : :: |
|  :::::     : 0000         :: :           ::   :         X :   :   ::: :    ::|
| : :  :      :         :: : :: : :  :    :: :: :   :: : ::    :::    :   :    |
|   ::: :    ::   :   :      ::  :::   :  :::     :: :   :    ::: :::  :      :|
| ::: :   :  ::  :::    :    :   :        :   :: :  : :   :::  : :::  :  :: :::|
|  : ::     :: :::   : :  :::   : ::: :   ::  :     :  ::  :::       :: :  :  :|
| :: : :  :  :    :  : :  : : :::   :: :  :  :  ::: : :  :::::: :  :   :  :::::|
|  ::: :: : ::: :     : :    : :          :   :: :  :  :    ::  : :   ::::: : :|
|  ::     ::::  :: ::: ::::  :: ::   :::  :     :   : : : :  : : : :  :  ::::  |
|:::   ::  ::: :    :: ::: ::     ::: : X: :   :  : :::     :     :   ::  :   :|
| :  :: :  : :  :: : : :::::   :    ::  X ::  :  :      : :::::::  :    :: ::  |
| : ::  :  : :  : :: ::   :  :::::: ::: X      :::   :  ::     :     : : : :  :|
|:        : ::       : :::   :: :    : :X::   :: :    : ::::: :::  ::::     :  |
|:: :    ::  : ♥0000000000   :          X::     :  :: :   :  :::   : :  :     :|
|:: :     : :  :: : :::  :::: : : :  :: X : :   :     : ::  ::::: :::  :::: :  |
| :: : :  ::::   : :: ::: ::::  :   ::: X      ::::  : : :   :   ::   :  ::   :|
|  :::::::: :::: :   :: ::::  :    :::::X:  : ::     :    ::   :  : :    : :   |
| :: :       ::   ::       :::  ::  :   X :::   : :    :   : : : : : :::  :: : |
 ---------------------------------------☻--------------------------------------
             Player with Snake Tomas Points: 187 was killed by wall
             Player with Snake writed Points: 99 was killed by wall
                     Player with Snake C++ Points: 110 lives
                    Player with Snake Snake Points: 165 lives
                                  Duration: 12s
                           (H)elp | (R)estart | e(X)it 
```

Battle! And  

```
 ---------------------------------------------------------☺--------------------
|   : :        : ::::::  : :    :: :: :   :    : : ::  :: X        : :     ::: |
|   :: :     :   :   :  :     ::: :  : ::: :::    ::   :  X ::   :     : : ::::|
| :::  : :   : :: : ::   ::: ::  :  : ::      :::    :: ::X   ::: :  :   ::: ::|
|:   :: : :          :: :::        ::: :: ::  : :  :      X      ::::  :     ::|
|:::: :::::   : : :   :           :::::: :: ::        : ::X   :     : ::  ::   |
|  ::  :  : ::  :  ::   : : ::  ::::   : : :   : :   :::::X:: : : : :  : :  : :|
|  ::  :: :    ::   ::  : :::::: :::: :  :  :::      : :  X : :   :: :  :: : : |
|  : :: ::      :   : : :  : :: ::::         : :: ::: : ::X::::  :     :  : :  |
|::  ::    ::: _____ _____ _____ _____    _____ _____ _____ _____: : :   :: : :|
| ::: : : : : |   __|  _  |     |   __|  |     |  |  |   __| __  |   :   :: : :|
|:  :     :   |  |  |     | | | |   __|  |  |  |  |  |   __|    -|   ::   :: : |
| :  :  :  :::|_____|__|__|_|_|_|_____|  |_____|\___/|_____|__|__|: :  :   :: :|
|    :: :: :: :: ::::  ::  :: :    : : :   ::::   :::  :::X:::: :::: :::  : :: |
| :   : :    :     :         :    000000000000000000000000000000000000000000000♦
|:  :  :::  : :  :: :: ::  :  : :   :    : :::   :::   :: X  :  : :::    ::::  |
| :  :: :  :: :    : : :: : ::::: :   :: :     : :  ::  ::X: ::   :: :  : : :: |
|  :::::     :              :PRESS ENTER TO CONTINUE      X :   :   ::: :    ::|
| : :  :      :         :: : :: : :  :    :: :: :   :: : ::    :::    :   :    |
|   ::: :    ::   :   :      ::  :::   :  :::     :: ::  :    ::: :::  :      :|
| ::: :   :  ::  :::    :    :   :        :   :: :  : :   :::  : :::  :  :: :::|
|::: :: :   :: :::   : :  :::   : ::: :   ::  :     :  ::  :::       :: :  :  :|
| :: : : ::  :    :  : :  : : :::   :: :  :  :  ::: : :  :::::: :  :   :  :::::|
|  ::: :: : ::: :     : :    : :    :     :   :: :  :  :    ::  : :   ::::: : :|
|  ::     ::::  :: ::: ::::  :: ::   :::  :     :   : : : :  : : : :  :  ::::  |
|:::   ::  ::: :    :: ::: ::     ::: : X: :   :  : ::: :   :     :   ::  :  ::|
| :  :: :  : :  :: : : :::::   :    ::  X ::  :  :      : :::::::  :    :: ::  |
| : ::  :  : :  : :: ::   :  :::::: ::: X      :::   :  ::     :     : : : :  :|
|:        : ::       : :::   :: :    : :X::   :: :    : ::::: :::  ::::     :  |
♥XXXXXXXXXXXXXXXX            :          X::     :  :: :   :  :::   : :  :     :|
|:: :     : :  :: : :::  :::: : : :  :: X : :   :     : ::  ::::: :::  :::: :  |
| :: : :  ::::   : :: ::: ::::  :   ::: X      ::::  : : :   :   ::   :  ::   :|
|  :::::::: :::: :   :: ::::  :    :::::X:  : ::     :    ::   :  : :    : :   |
| :: :       ::   ::      ::::  ::  :   X :::   : :    :   : : : : : :::  :: : |
 ---------------------------------------☻--------------------------------------
             Player with Snake Tomas Points: 187 was killed by wall
             Player with Snake writed Points: 99 was killed by wall
              Player with Snake C++ Points: 176 was killed by wall
             Player with Snake Snake Points: 495 was killed by wall
                                  Duration: 33s
                           (H)elp | (R)estart | e(X)it
```

Help screen with keyobard layout

```
----------------------------------------
Welcome to the game
 ___              _
/ __| _ _   __ _ | |_____
\__ \| ' \ / _` || / / -_)
|___/|_||_|\__/_||_\_\___| in console
----------------------------------------
Copyright (c) 2024 Tomas Mark
tomas@digitalspace.name
Enjoy this example of OOP C++17 code!
build v0.0.3


                            -------keyb control------
                            Snake 1 - 'w' 's' 'a' 'd'
                            Snake 2 - 'i' 'k' 'j' 'l'
                            Snake 3 - '[' ''' ';' '\'
                            Snake 4 - '8' '5' '4' '3'

                             PRESS ENTER TO CONTINUE
```

//MIT License
//
//Copyright (c) 2024 Tomas Mark
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE. 
```
