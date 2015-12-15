#include "DirectoryException.h"
#include "DirectoryReader.h"

DirectoryReader::DirectoryReader(std::string path)
    : dir_(opendir(path.c_str())) {
  if (dir_ == NULL) {
    throw DirectoryException("Can't open directory");
  }
}

DirectoryReader::~DirectoryReader() {
  closedir(dir_);
}

std::vector<std::string> DirectoryReader::files() const {
  std::vector<std::string> files;
  struct dirent *ent;
  while ((ent = readdir(dir_)) != NULL) {
    if (ent->d_type == DT_REG) {  // regular file
      files.push_back(ent->d_name);
    }
  }

  return files;
}
