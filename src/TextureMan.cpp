#include "TextureMan.hpp"

/*
Since we are going to make sure the file we are reading in are pictures,
we want an array of the possible file extensions
*/
const static vector<string> FILE_EXTENSIONS = {"png", "jpg"};

map<string, Texture*> TextureMan::m_map;

bool contains(vector<string> vec, string str);

Texture* TextureMan::getTexture(const string filePath) {
  // Search through the map to see if there is already an entry
  for (auto element: TextureMan::m_map) {
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
  TextureMan::m_map[filePath] = texture;

  return TextureMan::m_map[filePath];
}

void TextureMan::preLoadTextures(const string folderPath, bool recurse) {
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
      if (contains(FILE_EXTENSIONS, ss.str().substr(ss.str().length() - 4, 3))) {
        Texture* texture = new Texture();
        // The substring nonsense in this next parameter is to remove extraneous quotes from ss
        texture->loadFromFile(ss.str().substr(1, ss.str().length() - 2));
        m_map[ss.str().substr(1, ss.str().length() - 2)] = texture;
        //out << getSize() << endl;
      }
    }
  } else {
    for (auto& file: fs::directory_iterator(folderPath)) {
      // We have to use a stringstream to get the path as a string here
      stringstream ss;
      ss << file;      // We want to make sure the file is in fact a picuture, so we check the extension
      if (contains(FILE_EXTENSIONS, ss.str().substr(ss.str().length() - 3, 3))) {
        Texture* texture = new Texture();
        texture->loadFromFile(ss.str().substr(1, ss.str().length() - 2));
        m_map[ss.str().substr(1, ss.str().length() - 2)] = texture;
        //cout << getSize() << endl;
      }
    }

  }
}

int TextureMan::getSize() {
  return TextureMan::m_map.size();
}

bool contains(vector<string> vec, string str) {
  for (string s: vec) {
    if (s == str)
      return true;
  }
  return false;
}
