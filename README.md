# Texture Man

This is an SFML based texture utility to hopefully improve performance in large applications. The basic idea is that instead of creating a new object for every texture in the game, you can instead gather a map of texture pointers, which can then be reused over and over again. I haven't done any benchmark testing, but this is something I'm hoping to work on in the future

# Example code:

The following code will create a texture variable in the class and assign it to some sprite

```
#include "TextureMan.hpp"
...

...
// We first want to define where the image is located
string path = "path/to/some/image.png";
//Now we will access our texture manager, using the path as the key
Texture texture = *TextureMan::getTexture(path);
// Note that we have to dereference the value, because it is stored as a pointer

// We can now use this texture for some sprite or whatever else
someSprite.setTexture(texture);
...

...
// When we are setting up our game and load levels and whatnot, we can also preload our textures
string folder = "folder/where/images/are/stored";
TextureMan::preLoadTextures(folder);
// This will read in the images all at once, and should hopefully increase performance
...

```

# Options

There is only one optional parameter for the preLoadTextures, which is whether or not to recurse through all directories below the given one. This is automatically enabled, but can disabled by using:

`TextureMan::preLoadTextures("some/folder/path", false);`

# Other SFML Utilities

[AnimationManager](https://github.com/Jfeatherstone/SFMLAnimation)
