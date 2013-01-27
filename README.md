AngelDust
=========

AngelDust is a window matching utility inspired by Devilspie

Scripts
=======

- Folder: $HOME/.config/angeldust/
- Format:

    <pre>"Window name"
    [
        "Function name": "Function parameters"
        ...
    ]</pre>

Functions
=========

<pre>center</pre>
- ***Parameters:*** no parameters
- Centers window on current workspace

-------------------------------------------------------------------------------------------------------------------

<pre>moveTo</pre> 
- ***Parameters:*** target workspace number
- Moves window to target workspace

-------------------------------------------------------------------------------------------------------------------

<pre>moveActivateTo</pre>
- ***Parameters:*** target workspace number
- Moves window and switches to target workspaces and gives focus to window

-------------------------------------------------------------------------------------------------------------------

<pre>move</pre>
- ***Parameters:*** target X and/or Y coordonates
- Moves window to (X,Y)
- ***Note:*** 

    to move a window only on one axis use '*' for the other axis
    
    ***Example:*** moving a window to Y = 50 without knowing X:
        <pre>"move": "* 50"</pre>

-------------------------------------------------------------------------------------------------------------------

<pre>setAbove</pre>
- ***Parameters:*** no parameters
- Sets the window above all other windows

-------------------------------------------------------------------------------------------------------------------

<pre>setBelow</pre>
- ***Parameters:*** no parameters
- Sets the window below all other windows

-------------------------------------------------------------------------------------------------------------------

<pre>setFullscreen</pre>
- ***Parameters:*** no parameters
- Sets the window fullscreen 
- ***Note:***
    window decorations will not be visible

-------------------------------------------------------------------------------------------------------------------

<pre>setMaximized</pre>
- ***Parameters:*** no parameters
- Maximizes the window

-------------------------------------------------------------------------------------------------------------------

<pre>close</pre>
- ***Parameters:*** no parameters
- Closes the window

-------------------------------------------------------------------------------------------------------------------

<pre>removeDecorations</pre>
- ***Parameters:*** no parameters
- Removes the window decorations

-------------------------------------------------------------------------------------------------------------------

<pre>addDecorations</pre>
- ***Parameters:*** no parameters
- Adds the window decorations

-------------------------------------------------------------------------------------------------------------------

<pre>tile</pre>
- ***Parameters:*** no parameters
- Adds the window to the tile group

