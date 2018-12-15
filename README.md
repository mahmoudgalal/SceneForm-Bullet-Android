# SceneForm-Bullet
Sceneform-Bullet is an integration between Google [Sceneform Framework](https://developers.google.com/ar/develop/java/sceneform/) 
and the [Bullet Physics engine](https://pybullet.org/wordpress/).<br/>
This integration enables you to add Physics simulation for your 3D rendered world either it is AR-related or nor AR related.<br/>
Currently the integration allows you to create simple geometric primitives colliders i.e: Box,Cylinder and Spehre. 
You can also apply a force to any created body. The API is very simple and straightforward.
<br/>
### How to Build:<br/>
The integration depends on the "Bullet" android build so you need to build the Bullet engine yourself for the android platform
which is a very simple process .You will find aan android subfolder in the bullet src that contains the <b>"android.mk"</b> 
that can be used easily with [<b>"Android NDK"</b>](https://developer.android.com/ndk/) to build the <b>bullet static library</b>.
seen NDK documentation for instructions on how to build a native Library using mk files.

Once you have bullet built for your prefered ABI ,just copy it under the proper subfolder in <b>"bullet_android"</b> directory.
For your convenience,a pre-built bullet Lib is provided for the <b>arm64</b> ABI only to start right away .

You are now ready to build the integration,just open the project in android studio and see it working.

### Using The Demo:<br/>
- Click the light-blue circular Button to Throw a random physical body: Sphere,Cylinder or a Cube.
- Tap on any body in the scene to apply an upward force to it.

![](https://github.com/mahmoudgalal/SceneForm-Bullet/blob/master/ScreenShots/device-2018-12-15-193507.png)
![](https://github.com/mahmoudgalal/SceneForm-Bullet/blob/master/ScreenShots/device-2018-12-15-193547.png)
![](https://github.com/mahmoudgalal/SceneForm-Bullet/blob/master/ScreenShots/device-2018-12-15-193708.png)



If you have any concerns ,or willing to participate, i'll be very delighted to help:<br/>
mahmoudgalal57@yahoo.com
