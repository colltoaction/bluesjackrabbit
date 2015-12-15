#ifndef BLUESJACKRABBIT_COMMON_DIRECTORYREADER_H
#define BLUESJACKRABBIT_COMMON_DIRECTORYREADER_H

#include <dirent.h>
#include <vector>


class DirectoryReader {
 public:
  explicit DirectoryReader(std::string path);
  ~DirectoryReader();
  std::vector<std::string> files() const;

 private:
  DIR *dir_;
};


#endif  // BLUESJACKRABBIT_COMMON_DIRECTORYREADER_H
