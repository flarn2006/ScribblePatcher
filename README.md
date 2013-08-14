ScribblePatcher
===============

As you most likely know, Scribblenauts Unlimited is a game created by 5th Cell in which you can summon almost any object you can think of to accomplish tasks. You do so by typing the name of the object in a text box. This text box normally doesn't allow you to type numbers and most special characters. However, doing so can be useful as the game has several objects and adjectives used internally that have names beginning with `@` (and occasionally `$`). Because of this, they can't be directly spawned. Until now, that is.

There have always been workarounds to type these characters. The most common method was to exploit [a glitch][1] involving the object editor and that button that fills in the last thing you typed, and became known as the "@ Method". This works on the PC version as well as the Wii U version, but not the 3DS due to the lack of an object editor. PC users have some more options—before I was aware of that glitch (fun fact: I actually found that glitch on my own before I found out it had already been discovered) I used Cheat Engine to search for and edit the typed text in memory. But I wanted a better way, so I searched through the game's code using IDA Pro and Cheat Engine to find the code that stops other characters from being typed.

As it turns out, one of the checks Scribblenauts Unlimited does is check if the character's ASCII code lies between `A` and `Z`. If so, it lets you type it. All I had to do was replace the `A` with an exclamation point, which includes a much larger range of characters, including the `@` and `$` characters, as well as the digits 0-9. I published my findings on the Scribblenauts wiki on Wikia, and gave information on how to use a hex editor to patch it manually. But not everyone knows how to use a hex editor. If someone wants to modify it and asks how, giving them an automated patching tool would be much easier than explaining the basics of using a hex editor. That's why I wrote this program.

Usage
-----

Using the patching tool is simple. Just follow these steps:

1. Double-click ScribblePatcher.exe.
2. Navigate to your Scribblenauts install directory if it's not already there. (Try `C:\Program Files\Steam\SteamApps\Common\Scribblenauts` if not.)
3. Double-click Scribble.exe in the window.

A message will appear showing the status of the patch. If it says the version isn't supported, just post an issue on [Github][2]—I'll do my best to update it. (But first please check if one has already been submitted recently.)

Have fun!

  [1]: http://scribblenauts.wikia.com/wiki/The_@_Method
  [2]: https://github.com/flarn2006/ScribblePatcher
