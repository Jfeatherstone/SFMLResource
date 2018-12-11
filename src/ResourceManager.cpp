#include "ResourceManager.hpp"

/*
Since we are going to make sure the file we are reading in are pictures,
we want an array of the possible file extensions
*/
const static vector<string> TEXTURE_EXTENSIONS = {"png", "jpg"};
const static vector<string> SOUND_EXTENSIONS = {"wav"};

map<string, Texture*> ResourceManager::m_textureMap;
map<string, SoundBuffer*> ResourceManager::m_soundMap;

string ResourceManager::m_defaultInvalidPath = "invalid.png";

bool contains(vector<string> vec, string str);

/*** TEXTURE METHODS ***/

Texture* ResourceManager::getTexture(const string filePath) {
  // Search through the map to see if there is already an entry
  for (auto element: ResourceManager::m_textureMap) {
    cout << element.first << " " << filePath << endl;
    if (element.first == filePath)
      return element.second;
  }
  // If the code has made it to this point, it hasn't found a matching entry
  // in the map
  // We use the new keyword because we want to store these variables ourside of
  // the stack
  Texture* texture = new Texture();
  texture->loadFromFile(filePath);
  ResourceManager::m_textureMap[filePath] = texture;

  return ResourceManager::m_textureMap[filePath];
}

void ResourceManager::preLoadTextures(const string folderPath, bool recurse) {
  // We want to iterate through every file in the current folder
  // If we are recursing, we use the recursive iterator
  // The code in each loop is the same, the first just will have more files to
  // process
  if (recurse) {
    for (auto& file: fs::recursive_directory_iterator(folderPath)) {
      // We have to use a stringstream to get the path as a string here
      stringstream ss;
      ss << file;
      //cout << ss.str() << endl;
      // We want to make sure the file is in fact a picuture, so we check the extension
      if (contains(TEXTURE_EXTENSIONS, ss.str().substr(ss.str().length() - 4, 3))) {
        Texture* texture = new Texture();
        // The substring nonsense in this next parameter is to remove extraneous quotes from ss
        texture->loadFromFile(ss.str().substr(1, ss.str().length() - 2));
        m_textureMap[ss.str().substr(1, ss.str().length() - 2)] = texture;
        //out << getSize() << endl;
      }
    }
  } else {
    for (auto& file: fs::directory_iterator(folderPath)) {
      // We have to use a stringstream to get the path as a string here
      stringstream ss;
      ss << file;      // We want to make sure the file is in fact a picuture, so we check the extension
      if (contains(TEXTURE_EXTENSIONS, ss.str().substr(ss.str().length() - 3, 3))) {
        Texture* texture = new Texture();
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

SoundBuffer* ResourceManager::getSoundBuffer(const string filePath) {
  // Search through the map to see if there is already an entry
  for (auto element: ResourceManager::m_soundMap) {
    //cout << element.first << " " << filePath << endl;
    if (element.first == filePath)
      return element.second;
  }

  SoundBuffer* sound = new SoundBuffer();
  sound->loadFromFile(filePath);
  ResourceManager::m_soundMap[filePath] = sound;

  return ResourceManager::m_soundMap[filePath];
}

void ResourceManager::preLoadSoundBuffers(const string folderPath, bool recurse) {
  // We want to iterate through every file in the current folder
  // If we are recursing, we use the recursive iterator
  // The code in each loop is the same, the first just will have more files to
  // process

  if (recurse) {
    for (auto& file: fs::recursive_directory_iterator(folderPath)) {
      stringstream ss;
      ss << file;
      //cout << ss.str() << endl;

      if (contains(SOUND_EXTENSIONS, ss.str().substr(ss.str().length() - 4, 3))) {
        SoundBuffer* sound = new SoundBuffer();
        // The substring nonsense in this next parameter is to remove extraneous quotes from ss
        sound->loadFromFile(ss.str().substr(1, ss.str().length() - 2));
        ResourceManager::m_soundMap[ss.str().substr(1, ss.str().length() - 2)] = sound;
      }
    }
  } else {
    for (auto& file: fs::directory_iterator(folderPath)) {
      // We have to use a stringstream to get the path as a string here
      stringstream ss;
      ss << file;      // We want to make sure the file is in fact a picuture, so we check the extension
      if (contains(SOUND_EXTENSIONS, ss.str().substr(ss.str().length() - 3, 3))) {
        SoundBuffer* sound = new SoundBuffer();
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

bool contains(vector<string> vec, string str) {
  for (string s: vec) {
    if (s == str)
      return true;
  }
  return false;
}
