AngelDust
=========

AngelDust is a window matching utility inspired by Devilspie

Scripts
=======

- Folder: $HOME/.config/angeldust/
- Format:
```"Window name"
[
	"Function name": "Function parameters"
	...
]```

Functions
=========

```center``` 
- Parameters: no parameters
- Centers window on current workspace

```moveTo``` 
- Parameters: target workspace number
- Moves window to target workspace

```moveActivateTo```
- Parameters: target workspace number
- Moves window and switches to target workspaces and gives focus to window

```move```
- Parameters: target X and/or Y coordonates
- Moves window to (X,Y)
- Note: 
	to move a window only on one axis use '*' for the other axis
	Example: moving a window to Y = 50 without knowing X:
		```"move": "* 50"```

```setAbove```
- Parameters: no parameters
- Sets the window above all other windows

```setBelow```
- Parameters: no parameters
- Sets the window below all other windows

```setFullscreen```
- Parameters: no parameters
- Sets the window fullscreen 
- Noted:
	window decorations will not be visible

```setMaximized```
- Parameters: no parameters
- Maximizes the window

```close```
- Parameters: no parameters
- Closes the window

```removeDecorations```
- Parameters: no parameters
- Removes the window decorations

```addDecorations```
- Parameters: no parameters
- Adds the window decorations

```tile```
- Parameters: no parameters
- Adds the window to the tile group

