# snake-in-console

Play ***Snake*** within Windows console.

I wrote the traditional Snake game in an object-oriented way in the C++ programming language.
In an effort to get some practice in, I decided to create my own Snake game in my spare time, which can be played right in the console window. The game is rendered using only ASCII characters and runs under Windows. You can play the game in command line, powershell or tabby and so on. The source code is compilable against the C++ standard libraries. C++ standard version 17. I compile with GCC MinGW v13.2

Extra function:

Up to 4 snakes for 4 players via Hot Seat!

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
Enjoy this example of OOP C++ code!

Start immediately with default settings yes/no ?
```
```

 ----------------------¦-------------------------------------------------------
|::: :    :            X::  :::          :  ::::     :  :      :  ::     :   : |
|:: :::: :: ::  : ::  :X :     ::    :  :::: :     :: :::  :  :     :    :     |
|  ::::::     ::   :   X :       : :  :::  : :  ::: :: :      ::  ::        : :|
| :  ::     ::: :::  : X::  ::    :  :  :  ::  : : : : :   :::: ::: :::   : :  |
|  :: : :: :     :  :::X              :   :           :    :  :      00000000: |
|:::::::  ::: :   :: : X::::   :  :   ::    :    : ::::: :   ::   : :   ::  0  |
|   :::  :::::::  :::  X: : : ::: ::: ::  :  :: : :  : :  :  : : :: ::   :::0 :|
|::   :::      : :   : X:   ::     :: :    ::   :   ::::::: :::    ::  :    0 :|
|: ::   :: : : :   ::::XXXX :       :     ::: ::::   ::  ::    : :  :: ::   0  |
|     :::::    : :  ::  :  : :   ::       ::: :   :  : :  :: :  :: :::  :: :0 :|
| :: : ::     :   : : :   : : :::      :   ::: ::  ::   :   : :  :  :  : : :0  |
|:::: :   :: :         :::   :    :  :    :  ::  : : ::    :  :: : :  : : ::0 :|
|:: :: :  :  :: :::::     ::   : :  : :  : ::   :   ::::  :  :::::    : :  :0  |
|    ::      : ::   :   :   :: : : : :    :::::     :: : : : ::: ::  : :    0::|
|:: :   :  : :::::: :::      ::  :  ::  :   ::  ::   ::: : : : :    :: ::   0::|
|:   : : :: ::::  :::  ::    : :   : ::  :: : : : ¢00000000000000000000000  0  |
¢XXXXXXXXXXXX : :    :                  :::  :  :    :  :::  :   ::  :: :0  0  |
|:: ::: : ::  :    :::   : ::: ::  :  :  : :  ::: : : :  : : : :::      :0::0: |
|  :              :     : : :: ::  : :  :    ::::: : :  :  :::  : :    : 0: 0: |
| : :: :   ::  :: : :::: ::  ::::: : :::     :::: :: ::    :: :: ::::    0 :0 :|
|::   XXXXXXXXXXXXXXXXXXXXXXXXXXXXX:  :  :  :  :    :::  :    :  : :: :::0 :0  |
|: : :X :    : : : :::       ::  :X           :: ::   :  ::  : :::::: :  0 :0  |
|   XXX  :    ::: ::  : :: :  :   X    :    :: :: ::::  : :::      :: :::0::0  |
| ::X :  ::  ::: :  ::  :::  :  : X: :   :: :::  ::    :  : :   :: ::: : 0000::|
|: : : ::: : : :  :  ::: ::   :   X  :   :: :   : :    ::: : :    :  :    : : :|
| : :: :        :     :          :X :      :    ::     :::    :  :: ::::: : : :|
|::  ::  :    : :  :  :  :::: :: :X:  : :::: : :   :    ::   :: :   :::: : : : |
|   :: :: :  : :: :::::      : :: X  : ::: :  : :        : :::     :  :  ::: : |
|::   ::::: ::: ::  : :::     ::  X : :  :  :  :    :   :: : :::  :::: :  : :::|
| :   ::  ::: : : :               X    :  : : : ::  :::       :  :: ::  : : :: |
|:  :   :: ::  :  :      ::  :::  X:   :: :: :   ::   : : ::: :::::  :     ::  |
|   :: :   :: :  :: : :   ::      X : : :   : :  ::   : :  ::: :  : ::  :  :: :|
| : :::   : :   : : :: :  ::: :  :X ::    :::   ::    : : :::::  ::   :: :  :::|
 ---------------------------------¦--------------------------------------------
                            Player Tomas Points: 671
                         Player writed Points: 132 Dead
                          Player C++ Points: 132 Dead
                         Player Snake Points: 506 Dead
                                  Duration: 36s
                           (H)elp | (R)estart | e(X)it
                          Copyright (c) 2024 Tomas Mark
```

```



                    ----------------------------------------
                    Welcome to the game
                       ___              _
                      / __| _ _   __ _ | |_____
                      \__ \| ' \ / _` || / / -_)
                      |___/|_||_|\__/_||_\_\___| in console
                    ----------------------------------------

                          Copyright (c) 2024 Tomas Mark
                       Enjoy this example of OOP C++ code!

                            Snake 1 - 'w' 's' 'a' 'd'
                            Snake 2 - 'i' 'k' 'j' 'l'
                            Snake 3 - '[' ''' ';' '\'
                            Snake 4 - '8' '5' '4' '3'

                             PRESS ENTER TO CONTINUE

```

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
