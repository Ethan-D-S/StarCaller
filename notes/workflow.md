## Using Rayblib
Raylib is extremely easy to use. The primary variables used for raylib are Vector2 and Rectangle. These are both structs that hold 2 and 4 floats respectively.
If I want to draw a rectangle I would look for DrawRectangle in the [raylib cheatsheet](https://www.raylib.com/cheatsheet/cheatsheet.html).

Drawing a rectangle has several functions but I want one that just outlines based on a defined rectangle struct.
I can create a rectangle struct using:
```Rectangle exampleRectangle = (Rectangle) {100, 100, 300, 200}```
and then I can call:
```DrawRectangleRec(exampleRectangle, GREEN);```
which will create a green rectangle at (100, 100) with a width of 300 and a height of 200. Similarily I can create a Vector2 with:
```Vector2 exampleVector2 = (Vector2) {100, 200};```
which a struct with two floats of 100 and 200 values. This is most often used as coordinates.

## main.cpp
```
    - preprocessor includes
    - declare variables
    - declare functions
    
    - main()
        - initialzation code
        - while(game window is open, do this every frame)
            - update screen()
            - draw screen()
            - check if button is hovered()
            - if mouse is clicked: register button()

        - unload textures

    - initGame()
        - load textures from resource folder
        - set some variables to 0
        - set status bar attributes
		
    - update screen(), draw screen(), and check button collision()
	// these three functions operate in the same way and could be merged but are seperate for readability 
	- switch (based on current screen)
		- do action based on screen

		//update screen() runs timers and switches to a different screen based on events
		//draw screen() draws all of the shapes and text
		//check button collision() changes the variable btnHovered based on which button your mouse is colliding with
	
    - register button()
	-switch (based on current button hovered)
		- do action relative to button pressed
```
