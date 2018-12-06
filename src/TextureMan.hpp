/*
MIT License

Copyright (c) 2018 Jack Featherstone

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

DEPENDENCIES:
std::string
std::map
sf::Texture

*/

#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <iostream>
#include <filesystem>
#include <sstream>

using namespace std;
using namespace sf;
namespace fs = std::filesystem;

/*

SPECIFICATIONS:
SFML 2.5.1
2018 Q4

This class has been created with the idea of increasing performance in a large
scale game application that references a large amount of textures. With the
implementation of this class, it will be easier to store references to all
textures used, such that no texture is loaded twice, wasting precious memory.

The basic structure of the class will be a map that holds the loaded references
and a method that will allow for the user to both access and create entries
fluidly.
*/

class TextureMan {

private:
  /*
  The crux of this class is the map defined below, that will hold references
  to all of the sprites necessary

  The key for the map will be the path to the file, such that we can not only
  access the texture through this, but differentiate between similarly named
  files in different locations

  It is defined as static such that no instance of the class needs to be created
  */
  static map<string, Texture*> m_map;

public:
  /*
  The most important method is the getTexture(string path) because it will both
  create and access entries in our map. As for the former, if it does not already
  find an entry under the path, it will create one and return the reference.
  */

  static Texture* getTexture(const string filePath);

  /*
  For basic debugging, we also want to be able to know how many textures
  are held in the map
  */
  static int getSize();
  /*
  Just to save some memory while the game is running, we will also create a
  function that loads all files in a given directory, with the option of doing
  the same recursively.
  */
  static void preLoadTextures(const string folderPath, bool recurse = true);
};
