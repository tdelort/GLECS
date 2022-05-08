# GLECS

A collection of classes and methods I developped to make my life easier when using OpenGL

## Conventions

Just to make my life easier and so that I don't need to look everywhere to find them, here is a small list of conventions I use:  

`camelCase` for functions  
`snake_case` for variables and namespaces  
`PascalCase` for classes  

Most classes will be found in the `nbop::glecs` namespace.

### Shaders

By default, the following uniforms will be automatically set:

* `u_model`: the model matrix  
* `u_view`: the view matrix  
* `u_projection`: the projection matrix  

TODO :

* `u_time`: the time in seconds since the program started  
* `u_delta_time`: the time in seconds since the last frame  
* `u_resolution`: the resolution of the window

And the vertex data cn be accessed with the following attributes:

* `v_position`: the vertex position
* `v_color`: the vertex color

## Concessions

Since it will mostly used with OpenGL, I will use `glm` structures and functions to represent vectors, matrices, etc, instead of implementing them myself.

## Misc

Some informations I ALWAYS ask myself and I don't want to forget:

With `glm` matrices being in column-major order, in `C = B * A`, A is "applied first", then B.

## TODO / IDEAS

A way to require Components when creating a Component. For example, a Renderer requires a Mesh and a Transform.  

Check encapsulation for example with the Shader class.  

Limits the access level on a lot of methods. Right now, anyone can just `bind` a Mesh for example.  
