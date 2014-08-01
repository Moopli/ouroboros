ouroboros
=========

A simple softbody physics engine, written in a day for the 2014 Waterloo Facebook Hackathon. 

As such, it cuts a lot of corners, and is currently quite incomplete. It does work, however.

It loads at least one mesh file type, and has some functions to generate chunks of mesh with different topologies. 

Next steps, if I ever pick this up again, are to:

1. Finish Lua integration
2. Parallelize solver (OpenCL, probably)
3. Expand generator system:
  * A tool to solidify the insides of meshes
  * Some basic CSG to define chunks of material

After that, we'll see.
