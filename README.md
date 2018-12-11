# Resource Manager

This is an SFML based texture utility to hopefully improve performance in large applications. The basic idea is that instead of creating a new object for every texture or sound in the game, you can instead gather a map of pointers, which can then be reused over and over again. I haven't done any benchmark testing, but this is something I'm hoping to work on in the future

# Example code:

The following code will reference a texture/sound variable in the class and assign it to some sprite

```
#include "ResourceManager.hpp"
...

...
// We first want to define where the image is located
string texturePath = "path/to/some/image.png";
//Now we will access our resource manager, using the path as the key
Texture texture = *ResourceManager::getTexture(texturePath);
// Note that we have to dereference the value, because it is stored as a pointer

// We can now use this texture for some sprite or whatever else
someSprite.setTexture(texture);

// We can do the same process with a sound file:
string soundPath = "path/to/some/sound.wav";
SoundBuffer sound = *ResourceManager::getSoundBuffer(soundPath);

someSound.setBuffer(sound);
...

...
// When we are setting up our game and load levels and whatnot, we can also preload our textures or sounds
string textureFolder = "folder/where/images/are/stored";
ResourceManager::preLoadTextures(textureFolder);

string soundFolder = "folder/where/sounds/are/stored";
ResourceManager::preLoadSoundBuffers(soundFolder);

// This will read in the images/sounds all at once, and should hopefully increase performance
...

```

# Options

There is only one optional parameter for the preLoadTextures/preLoadSoundBuffers, which is whether or not to recurse through all directories below the given one. This is automatically enabled, but can disabled by using:

`ResourceManager::preLoadTextures("some/folder/path", false);`

# Other SFML Utilities

[AnimationManager](https://github.com/Jfeatherstone/SFMLAnimation)
