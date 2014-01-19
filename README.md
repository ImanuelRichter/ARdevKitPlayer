ARdevKitPlayer
===============

The player can be used to show an AREL project which can be created with the <a href=https://github.com/Firebusa/ARdevKit>ARdevKitEditor</a>.
If the player is started from within the editor you can choose an image which will be passed to the player.
To test it with a video you need a virtual camera like <a href=http://download.manycam.com/>ManyCam</a>.
If no paths are specified the player will try to load the project from currentProject folder and use the camera as source so you can copy a project to his path and try your app with a mobile device.

Install Guide:
==============

After cloning/forking the repository, please downlaod the <a href=http://dev.metaio.com/>metaioSDK 5.2</a> and install it.
Go to the install folder of the SDK, then to _Windows -> metaioSDK -> bin and copy all the files (except *.exe) to the 
[project folder]\Debug (you may create the folders manually first, if you haven't tried to debug the project yet).

After that you should be able to compile and debug the project.