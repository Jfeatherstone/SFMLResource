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
sf::SoundBuffer
std::vector
std::filesystem
std::stringstream
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <filesystem>

/*

SPECIFICATIONS:
SFML 2.5.1
2018 Q4

This class has been created with the idea of increasing performance in a large
scale game application that references a large amount of textures. With the
implementation of this class, it will be easier to store references to all
textures used, such that no texture is loaded twice, wasting precious memory.
As of now, this class has been redisgned to hold sound files as well, with the
same intention of increasing performance as before

The basic structure of the class will be a map that holds the loaded references
and a method that will allow for the user to both access and create entries
fluidly.
*/

class ResourceManager {

private:
  /**
   * @brief This map will hold pointers to all of the textures necessary.
   * The key for the map will be the path to the file, such that we can not only access
   * the texture through this, but differentiate between similarly named files in 
   * different locations. It is defined as static such that no instance of the class 
   * needs to be created.
   */
  static std::map<std::string, sf::Texture*> m_textureMap;

  /**
   * @brief The map for storing sound buffer pointers. For more detail, see m_textureMap.
   */
  static std::map<std::string, sf::SoundBuffer*> m_soundMap;

  /**
   * @brief The map for storing font pointers. For more detail, see m_textureMap.
   */
  static std::map<std::string, sf::Font*> m_fontMap;

  /*
  We also want to be able to provide an invalid texture/sound/font if the actual file doesn't
  exist. The default location for this file will be in the same directory as the actual
  cpp files, but will be able to be set through a method below
  */
  const static std::string DEFAULT_INVALID_TEXTURE;
  const static std::string DEFAULT_INVALID_SOUND;
  const static std::string DEFAULT_INVALID_FONT;

  /**
   * @brief The current location of the texture that will be used if another texture isn't found.
   * See m_invalidSound and m_invalidFont for similar entries.
   */
  static std::string m_invalidTexture;
  /**
   * @brief The current location of the sound that will be used if another sound isn't found.
   * See m_invalidTexture and m_invalidFont for similar entries.
   */
  static std::string m_invalidSound;
  /**
   * @brief The current location of the font that will be used if another font isn't found.
   * See m_invalidTexture and m_invalidSound for similar entries.
   */
  static std::string m_invalidFont;

  /**
   * @brief A list of extensions that will be recognized as textures when pre loading a folder.
   * Currently contains: png, jpg, jpeg
   */
  const static std::vector<std::string> TEXTURE_EXTENSIONS;
  /**
   * @brief A list of extensions that will be recognized as sounds when pre loading a folder.
   * Currently contains: wav
   */
  const static std::vector<std::string> SOUND_EXTENSIONS;
  /**
   * @brief A list of extensions that will be recognized as fonts when pre loading a folder.
   * Currently contains: ttf
   */
  const static std::vector<std::string> FONT_EXTENSIONS;


public:

  /***************************
   *    TEXTURE METHODS 
   **************************/

  /**
   * @brief Get the Texture that is at the given file path. If this texture has been previously
   * loaded, a pointer to the previous object will be returned. Otherwise, a new pointer entry will be
   * created in the texture map and returned.
   * 
   * @param filePath The (relative to project folder or absolute) location of the texture file
   * @return sf::Texture* A pointer to the texture at the given file path
   */
  static sf::Texture* getTexture(const std::string filePath);

  /**
   * @brief Returns the size of the m_textureMap object
   * 
   * @return int The number of texture entries loaded in the resource manager
   */
  static int getNumberOfTextures();

  /**
   * @brief Load all of the files in a given folder (whose file extensions appear in TEXTURE_EXTENSIONS)
   * into the texture map.
   * 
   * @param folderPath The The (relative to project folder or absolute) location of the folder where textures
   * are to be loaded from
   * @param recurse Whether or not the manager should search for files recursively i.e. below the given folder.
   * Default is true
   */
  static void preLoadTextures(const std::string folderPath, bool recurse = true);

  /*
  We want to be able to change our invalid tile path to place with the rest of our
  textures in a larger project
  */

  /**
   * @brief Set the Invalid Texture Path to a new value. Can be relative to the project folder or
   * an absolute path.
   * 
   * @param filePath The new file that will be referenced when a texture is not found.
   */
  static void setInvalidTexturePath(const std::string filePath);

  /**
   * @brief Get the Invalid Texture Path.
   * 
   * @return std::string The file that will be referenced when a texture is not found.
   */
  static std::string getInvalidTexturePath();

  /**
   * @brief Delete all of the pointers held in m_textureMap and clear the respective entries
   */
  static void clearTextures();

  /***************************
   *    SOUND METHODS 
   **************************/

  /**
   * @brief Get the SoundBuffer that is at the given file path. If this sound has been previously
   * loaded, a pointer to the previous object will be returned. Otherwise, a new pointer entry will be
   * created in the sound map and returned.
   * 
   * @param filePath The (relative to project folder or absolute) location of the sound file
   * @return sf::SoundBuffer* A pointer to the sound at the given file path
   */
  static sf::SoundBuffer* getSoundBuffer(const std::string filePath);

  /**
   * @brief Returns the size of the m_soundMap object
   * 
   * @return int The number of sound entries loaded in the resource manager
   */
  static int getNumberOfSoundBuffers();

  /**
   * @brief Load all of the files in a given folder (whose file extensions appear in SOUND_EXTENSIONS)
   * into the sound map.
   * 
   * @param folderPath The The (relative to project folder or absolute) location of the folder where sounds
   * are to be loaded from
   * @param recurse Whether or not the manager should search for files recursively i.e. below the given folder.
   * Default is true
   */
  static void preLoadSoundBuffers(const std::string folderPath, bool recurse = true);

  /**
   * @brief Set the Invalid Sound Path to a new value. Can be relative to the project folder or
   * an absolute path.
   * 
   * @param filePath The new file that will be referenced when a sound is not found.
   */
  static void setInvalidSoundPath(const std::string filePath);

  /**
   * @brief Get the Invalid Sound Path.
   * 
   * @return std::string The file that will be referenced when a sound is not found.
   */
  static std::string getInvalidSoundPath();

  /**
   * @brief Delete all of the pointers held in m_soundMap and clear the respective entries
   */
  static void clearSoundBuffers();


  /***************************
   *    FONT METHODS 
   **************************/

  /**
   * @brief Get the Font that is at the given file path. If this sound has been previously
   * loaded, a pointer to the previous object will be returned. Otherwise, a new pointer entry will be
   * created in the font map and returned.
   * 
   * @param filePath The (relative to project folder or absolute) location of the font file
   * @return sf::Font* A pointer to the font at the given file path
   */
  static sf::Font* getFont(const std::string filePath);

  /**
   * @brief Returns the size of the m_fontMap object
   * 
   * @return int The number of font entries loaded in the resource manager
   */
  static int getNumberOfFonts();

  /**
   * @brief Load all of the files in a given folder (whose file extensions appear in FONT_EXTENSIONS)
   * into the sound map.
   * 
   * @param folderPath The The (relative to project folder or absolute) location of the folder where fonts
   * are to be loaded from
   * @param recurse Whether or not the manager should search for files recursively i.e. below the given folder.
   * Default is true
   */
  static void preLoadFonts(const std::string folderPath, bool recurse = true);

  /**
   * @brief Set the Invalid Font Path to a new value. Can be relative to the project folder or
   * an absolute path.
   * 
   * @param filePath The new file that will be referenced when a font is not found.
   */
  static void setInvalidFontPath(const std::string filePath);

  /**
   * @brief Get the Invalid Font Path.
   * 
   * @return std::string The file that will be referenced when a font is not found.
   */
  static std::string getInvalidFontPath();
  
  /**
   * @brief Delete all of the pointers held in m_fontMap and clear the respective entries
   */
  static void clearFonts();


  /************************
   *        MISC
   ************************/

  /**
   * @brief A simple method to find whether a string is contained in a vector
   * 
   * @param vec The vector of reference strings
   * @param str The string that may or may not be present in the vector
   * @return true The string is found in the vector
   * @return false The string is not found in the vector
   */
  static bool contains(std::vector<std::string> vec, std::string str);
};