ARdevKitPlayer
===============

The player can be used to show an AREL project which can be created with the <a href=https://github.com/Firebusa/ARdevKit>ARdevKitEditor</a>.
If the player is started from within the editor you can choose an image or video to test your project with.
You can also use a virtual camera like <a href=http://download.manycam.com/>ManyCam</a> as source for the player.
Moreover you can decide to start a debug terminal as well to show you some additional information.

If no paths are specified the player will try to load the project from .\currentProject and use the camera  (if available) as source. Due to this you can just copy a project to his path and try your app with a mobile device.

Install Guide:
==============

1. Clone/fork the repository
2. Downlaod the <a href=http://dev.metaio.com/>metaioSDK 5.2</a> and install it.
3. Copy all files from [metaio sdk install folder]/_Windows/metaioSDK/bin to [project folder]\Debug (you may create the folders manually first, if you haven't tried to debug the project yet).
4. Copy the folder "metaioSDK" from [metaio sdk install folder]/_Windows/metaioSDK/include/ to [project folder]\include

After that you should be able to compile and debug the project.