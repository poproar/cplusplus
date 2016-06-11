I started to refactor this program yesterday.
Trying to wrap my head around headers and multiple files.
WOndering when an object becomes an object.

As I try to set up the login function I am finding that
the goto x,y screen layout is just a waste of time, effort and system resources
so now I am going to simplify this process although I do think colors are helpful

#### day 2
I successfully moved the login funtion to its own file
instead of horsing around with _getch which I read was deprecated and showing a star
i opted for changing the input color which in this case is the same
Now I am begining to set up the menus and have yet to decide how the should be spread out
Also I because i am often changing the console text color and found compile errors with duplicated 
```
HANDLE hConsole
```
I am wondering if I can make this a separate file and call it as global function like
```
color(RED);
```
