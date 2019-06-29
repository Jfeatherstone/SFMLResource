#include "ResourceManager.hpp"



/***************************
 *     DECLARATIONS 
 **************************/

/*
Since we are going to make sure the file we are reading in are pictures,
we want an array of the possible file extensions
*/
const std::vector<std::string> ResourceManager::TEXTURE_EXTENSIONS = {"png", "jpg", "jpeg"};
const std::vector<std::string> ResourceManager::SOUND_EXTENSIONS = {"wav"};
const std::vector<std::string> ResourceManager::FONT_EXTENSIONS = {".ttf"};

// Here we initialize all of the maps as empty
std::map<std::string, sf::Texture*> ResourceManager::m_textureMap;
std::map<std::string, sf::SoundBuffer*> ResourceManager::m_soundMap;
std::map<std::string, sf::Font*> ResourceManager::m_fontMap;

// Set the default invalid paths, just the name "invalid" + the proper extension
const std::string ResourceManager::DEFAULT_INVALID_TEXTURE = "invalid.png";
const std::string ResourceManager::DEFAULT_INVALID_SOUND = "invalid.wav";
const std::string ResourceManager::DEFAULT_INVALID_FONT = "invalid.ttf";


/***************************
 *    TEXTURE METHODS 
 **************************/

sf::Texture* ResourceManager::getTexture(const std::string filePath) {

  // Search through the map to see if there is already an entry
  for (auto element: m_textureMap) {
    //std::cout << element.first << " " << filePath << std::endl;

    // We also want to check that the path is not invalid, as otherwise it would just be
    // stuck as invalid, because it would technically have an entry in the map
    if (element.first == filePath && element.first != m_invalidTexture)
      return element.second;
  }

  // If the code has made it to this point, it hasn't found a matching entry
  // in the map. We use the new keyword because we want to store these variables
  // outside of the stack
  sf::Texture* texture = new sf::Texture();
  
  // If the texture doesn't load properly, we assign our invalid texture to it
  if (!texture->loadFromFile(filePath)) {
    texture->loadFromFile(m_invalidTexture);
  }

  m_textureMap[filePath] = texture;

  return m_textureMap[filePath];
}

int ResourceManager::getNumberOfTextures() {
  return m_textureMap.size();
}

void ResourceManager::preLoadTextures(const std::string folderPath, bool recurse) {
  // We want to iterate through every file in the current folder
  // If we are recursing, we use the recursive iterator
  // The code in each loop is the same, the first just will have more files to
  // process
  if (recurse) {
    for (auto& file: std::filesystem::recursive_directory_iterator(folderPath)) {
      // We have to use a stringstream to get the path as a string here
      std::stringstream ss;
      ss << file;
      //cout << ss.str() << endl;
      // We want to make sure the file is in fact a picuture, so we check the extension
      if (contains(TEXTURE_EXTENSIONS, ss.str().substr(ss.str().length() - 4, 3))) {
        sf::Texture* texture = new sf::Texture();
        // The substring nonsense in this next parameter is to remove extraneous quotes from ss
        // Since this returns a boolean as to whether or not it completed, we can use our invalid tile
        texture->loadFromFile(ss.str().substr(1, ss.str().length() - 2));
        m_textureMap[ss.str().substr(1, ss.str().length() - 2)] = texture;
        //out << getSize() << endl;
      }
    }
  } else {
    for (auto& file: std::filesystem::directory_iterator(folderPath)) {
      // We have to use a stringstream to get the path as a string here
      std::stringstream ss;
      ss << file;      // We want to make sure the file is in fact a picuture, so we check the extension
      if (contains(TEXTURE_EXTENSIONS, ss.str().substr(ss.str().length() - 3, 3))) {
        sf::Texture* texture = new sf::Texture();
        texture->loadFromFile(ss.str().substr(1, ss.str().length() - 2));
        m_textureMap[ss.str().substr(1, ss.str().length() - 2)] = texture;
        //cout << getSize() << endl;
      }
    }

  }
}

void ResourceManager::clearTextures() {

  // First we delete all of the pointers
  for (auto element: m_textureMap) {
    delete element.second;
  }

  // And now clear all of the entries
  m_textureMap.clear();
}

std::string ResourceManager::getInvalidTexturePath() {
  return m_invalidTexture;
}


/***************************
 *    SOUND METHODS 
 **************************/

sf::SoundBuffer* ResourceManager::getSoundBuffer(const std::string filePath) {
  // Search through the map to see if there is already an entry
  for (auto element: m_soundMap) {
    //cout << element.first << " " << filePath << endl;
    if (element.first == filePath && element.first != m_invalidSound)
      return element.second;
  }

  sf::SoundBuffer* sound = new sf::SoundBuffer();
  sound->loadFromFile(filePath);

  // If the sound doesn't load properly, we assign our invalid sound to it
  if (!sound->loadFromFile(filePath)) {
    sound->loadFromFile(m_invalidSound);
  }

  m_soundMap[filePath] = sound;

  return m_soundMap[filePath];
}

int ResourceManager::getNumberOfSoundBuffers() {
  return m_soundMap.size();
}

void ResourceManager::preLoadSoundBuffers(const std::string folderPath, bool recurse) {
  // We want to iterate through every file in the current folder
  // If we are recursing, we use the recursive iterator
  // The code in each loop is the same, the first just will have more files to
  // process

  if (recurse) {
    for (auto& file: std::filesystem::recursive_directory_iterator(folderPath)) {
      std::stringstream ss;
      ss << file;
      //cout << ss.str() << endl;

      if (contains(SOUND_EXTENSIONS, ss.str().substr(ss.str().length() - 4, 3))) {
        sf::SoundBuffer* sound = new sf::SoundBuffer();
        // The substring nonsense in this next parameter is to remove extraneous quotes from ss
        sound->loadFromFile(ss.str().substr(1, ss.str().length() - 2));
        m_soundMap[ss.str().substr(1, ss.str().length() - 2)] = sound;
      }
    }
  } else {
    for (auto& file: std::filesystem::directory_iterator(folderPath)) {
      // We have to use a stringstream to get the path as a string here
      std::stringstream ss;
      ss << file;      // We want to make sure the file is in fact a sound, so we check the extension
      if (contains(SOUND_EXTENSIONS, ss.str().substr(ss.str().length() - 3, 3))) {
        sf::SoundBuffer* sound = new sf::SoundBuffer();
        // The substring nonsense in this next parameter is to remove extraneous quotes from ss
        sound->loadFromFile(ss.str().substr(1, ss.str().length() - 2));
        m_soundMap[ss.str().substr(1, ss.str().length() - 2)] = sound;
      }
    }
  }
}

void ResourceManager::clearSoundBuffers() {

  // First we delete all of the pointers
  for (auto element: m_soundMap) {
    delete element.second;
  }

  // And now clear all of the entries
  m_soundMap.clear();
}

std::string ResourceManager::getInvalidSoundPath() {
  return m_invalidSound;
}


/***************************
 *    FONT METHODS 
 **************************/

sf::Font* ResourceManager::getFont(const std::string filePath) {

  // Search through the map to see if there is already an entry
  for (auto element: m_fontMap) {
    //cout << element.first << " " << filePath << endl;
    if (element.first == filePath && element.first != m_invalidFont)
      return element.second;
  }

  sf::Font* font = new sf::Font();
  font->loadFromFile(filePath);

  // If the sound doesn't load properly, we assign our invalid sound to it
  if (!font->loadFromFile(filePath)) {
    font->loadFromFile(m_invalidFont);
  }

  m_fontMap[filePath] = font;

  return m_fontMap[filePath];

}

int ResourceManager::getNumberOfFonts() {
  return m_fontMap.size();
}

void ResourceManager::preLoadFonts(const std::string folderPath, bool recurse) {
  // We want to iterate through every file in the current folder
  // If we are recursing, we use the recursive iterator
  // The code in each loop is the same, the first just will have more files to
  // process

  if (recurse) {
    for (auto& file: std::filesystem::recursive_directory_iterator(folderPath)) {
      std::stringstream ss;
      ss << file;
      //cout << ss.str() << endl;

      if (contains(FONT_EXTENSIONS, ss.str().substr(ss.str().length() - 4, 3))) {
        sf::Font* font = new sf::Font();
        // The substring nonsense in this next parameter is to remove extraneous quotes from ss
        font->loadFromFile(ss.str().substr(1, ss.str().length() - 2));
        m_fontMap[ss.str().substr(1, ss.str().length() - 2)] = font;
      }
    }
  } else {
    for (auto& file: std::filesystem::directory_iterator(folderPath)) {
      // We have to use a stringstream to get the path as a string here
      std::stringstream ss;
      ss << file;      // We want to make sure the file is in fact a font, so we check the extension
      if (contains(FONT_EXTENSIONS, ss.str().substr(ss.str().length() - 3, 3))) {
        sf::Font* font = new sf::Font();
        // The substring nonsense in this next parameter is to remove extraneous quotes from ss
        font->loadFromFile(ss.str().substr(1, ss.str().length() - 2));
        m_fontMap[ss.str().substr(1, ss.str().length() - 2)] = font;
      }
    }
  }
}

std::string ResourceManager::getInvalidFontPath() {
  return m_invalidFont;
}

void ResourceManager::clearFonts() {

  // First we delete all of the pointers
  for (auto element: m_fontMap) {
    delete element.second;
  }

  // And now clear all of the entries
  m_fontMap.clear();
}


/******************************
 *           MISC
 *****************************/

bool ResourceManager::contains(std::vector<std::string> vec, std::string str) {
  for (std::string s: vec) {
    if (s == str)
      return true;
  }
  return false;
}

