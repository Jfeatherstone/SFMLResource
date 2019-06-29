#include "ResourceManager.hpp"

/*
Since we are going to make sure the file we are reading in are pictures,
we want an array of the possible file extensions
*/
const static std::vector<std::string> TEXTURE_EXTENSIONS = {"png", "jpg"};
const static std::vector<std::string> SOUND_EXTENSIONS = {"wav"};

std::map<std::string, sf::Texture*> ResourceManager::m_textureMap;
std::map<std::string, sf::SoundBuffer*> ResourceManager::m_soundMap;

std::string ResourceManager::m_defaultInvalidPath = "invalid.png";

bool contains(std::vector<std::string> vec, std::string str);

/*** TEXTURE METHODS ***/

sf::Texture* ResourceManager::getTexture(const std::string filePath) {
  // Search through the map to see if there is already an entry
  for (auto element: ResourceManager::m_textureMap) {
    std::cout << element.first << " " << filePath << std::endl;
    if (element.first == filePath)
      return element.second;
  }
  // If the code has made it to this point, it hasn't found a matching entry
  // in the map
  // We use the new keyword because we want to store these variables ourside of
  // the stack
  sf::Texture* texture = new sf::Texture();
  
  // If the texture doesn't load properly, we assign our invalid texture to it
  if (!texture->loadFromFile(filePath)) {
    texture->loadFromFile(m_defaultInvalidPath);
  }

  ResourceManager::m_textureMap[filePath] = texture;

  return ResourceManager::m_textureMap[filePath];
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

int ResourceManager::getNumberOfTextures() {
  return ResourceManager::m_textureMap.size();
}

/*** SOUND METHODS ***/
/*
As stated in the header file, these are very similar to their texture counterparts,
so I won't include too much documentation in this section
*/

sf::SoundBuffer* ResourceManager::getSoundBuffer(const std::string filePath) {
  // Search through the map to see if there is already an entry
  for (auto element: ResourceManager::m_soundMap) {
    //cout << element.first << " " << filePath << endl;
    if (element.first == filePath)
      return element.second;
  }

  sf::SoundBuffer* sound = new sf::SoundBuffer();
  sound->loadFromFile(filePath);
  ResourceManager::m_soundMap[filePath] = sound;

  return ResourceManager::m_soundMap[filePath];
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
        ResourceManager::m_soundMap[ss.str().substr(1, ss.str().length() - 2)] = sound;
      }
    }
  } else {
    for (auto& file: std::filesystem::directory_iterator(folderPath)) {
      // We have to use a stringstream to get the path as a string here
      std::stringstream ss;
      ss << file;      // We want to make sure the file is in fact a picuture, so we check the extension
      if (contains(SOUND_EXTENSIONS, ss.str().substr(ss.str().length() - 3, 3))) {
        sf::SoundBuffer* sound = new sf::SoundBuffer();
        // The substring nonsense in this next parameter is to remove extraneous quotes from ss
        sound->loadFromFile(ss.str().substr(1, ss.str().length() - 2));
        ResourceManager::m_soundMap[ss.str().substr(1, ss.str().length() - 2)] = sound;
      }
    }
  }
}

int ResourceManager::getNumberOfSoundBuffers() {
  return ResourceManager::m_soundMap.size();
}

bool contains(std::vector<std::string> vec, std::string str) {
  for (std::string s: vec) {
    if (s == str)
      return true;
  }
  return false;
}

void ResourceManager::clearSoundBuffers() {

  // First we delete all of the pointers
  for (auto element: m_soundMap) {
    delete element.second;
  }

  // And now clear all of the entries
  m_soundMap.clear();
}

void ResourceManager::clearTextures() {

  // First we delete all of the pointers
  for (auto element: m_textureMap) {
    delete element.second;
  }

  // And now clear all of the entries
  m_textureMap.clear();
}
