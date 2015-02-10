My program has a node class, which is used to create a scene graph from mygl.cpp. The node class has many constructors, based on what information is known to the user. The fields for a node include: geometry, parent node, children nodes, x, y, z coordinates for translation, x, y, z angles for rotation about each of those axis, and x, y, z scaling. 

The scene graph is drawn on screen using a traverse method, which starts at the parent node and explores all the children nodes, such that any transformations applied to the parent are applied to the children. Because of this, I built each of my limbs with a series of nodes: an unscale node (to undo transformations from the torso. This wasn’t totally necessary, but it was easier for me to work this way), a joint node (which places the limb relative to the torso or upper limb and rotates it as desired), and a limb node (which stores the actual geometry, and translates the pivot point as appropriate).


To move the whole figure: manipulate the tx, ty, tz fields of the constructor. Rx, ry, rz control angle of rotation about each respective axis. Sx, sy, sz control scaling about each respective axis. This let me animate the whole wizard to bounce up and down as if it was flying (changing the ty), and also to “bob” like being blown in the wind (changing rx and rz).

To move an entire limb: rotate the limb by manipulating the rx, ry, rz rotation of the joint node (hip or shoulder). To shift where the limb is placed, manipulate the translation fields (I wouldn’t recommend doing this though, leave them be).

To change the scale of the whole limb: change the scale fields of left_leg_upper or right_leg_upper (or arm). Don’t touch the translation, because this changes the pivot point so that the limb moves appropriately and doesn’t “break in half”

to move the lower part of a limb: rotate the lower part of the limb by manipulating the rx, ry, rz rotation of the lower joint node (elbow or knee). To shift where the lower limb is placed in relation to the upper limb, change the translation field. I wouldn’t recommend doing this.

To change the scale of the lower limb: Change the scale of the unsocial nodes. I wouldn’t recommend doing this.