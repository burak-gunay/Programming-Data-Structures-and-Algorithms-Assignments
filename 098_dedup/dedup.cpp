#include <dirent.h>
#include <sys/types.h>

#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
typedef std::unordered_map<int, std::string> stringMap;

void read_reg_file(stringMap & myMap, std::string & pathname) {
  //std::cout << "Filename is = " << pathname << std::endl;
  std::ifstream ifs;
  ifs.open(pathname);
  if (!ifs.is_open()) {
    std::cerr << "Error opening the file, terminating" << std::endl;
    exit(EXIT_FAILURE);
  }
  //std::cout << "Opened file's name is = " << pathname << std::endl;
  std::string content;
  std::string current;
  //std::getline(ifs, current);
  while (ifs.good()) {
    std::getline(ifs, current);
    content.append(current);
  }
  if (!ifs.eof()) {
    std::cerr << "Could not reach the end of the file, terminating" << std::endl;
    exit(EXIT_FAILURE);
  }

  ifs.close();  //opens and closes reg_file stream

  std::hash<std::string> str_hash;
  int hash_val = str_hash(content);
  std::string error1("/var/dedup/d001/message1.bin");

  std::pair<int, std::string> hashval_pathname(hash_val, pathname);
  std::unordered_map<int, std::string>::iterator it = myMap.find(hashval_pathname.first);
  if (pathname == error1) {
    //std::cout << "error1 hash= " << hash_val << std::endl;
  }
  if (it != myMap.end()) {
    // if (it->second == error1) {
    //   std::cout << "Error1 caught with hash=" << hash_val << std::endl;
    // }
    //  if (myMap.count(hash_val) > 0) {
    //std::vector<std::pair<std::string, std::string> > tempVector = myMap[hash_val];
    std::cout << "#Removing " << pathname << " (duplicate of" << it->second << ")." << std::endl
              << "rm " << pathname << std::endl;
    return;
  }
  else {
    myMap.insert(hashval_pathname);
  }
}

void opendirectory(stringMap & myMap, DIR * dirstream, std::string & pathname) {
  if (dirstream == NULL) {
    //std::cerr << "Directory could not be opened with this ERRNO=" << errno << std::endl;
    exit(EXIT_FAILURE);
  }
  struct dirent * dirorfile;
  while ((dirorfile = readdir(dirstream)) != NULL) {
    std::string copy_pathname;
    copy_pathname = pathname;
    copy_pathname.append(dirorfile->d_name);

    if ((dirorfile->d_type == DT_DIR) && ((strcmp(dirorfile->d_name, ".")) != 0) &&
        (strcmp(dirorfile->d_name, "..") != 0)) {  // if file is directory&&NOT . OR ..
      copy_pathname.append("/");
      DIR * dirsubstream = opendir(copy_pathname.c_str());  //opendir stream with dir name

      opendirectory(myMap, dirsubstream, copy_pathname);  // calling function again with new stream
    }

    else if (dirorfile->d_type == DT_REG) {  // if file is reg file
      read_reg_file(myMap, copy_pathname);
    }
    else {  // if file is anything else(no care)
    }
  }
  closedir(dirstream);  // if no directory, closes in a single run.
  //if directory , closes recursive directories as well
}

int main(int argc, char ** argv) {  //taking in directory names
  std::cout << "#!/bin/bash" << std::endl;
  if (argc <= 1) {
    std::cout << "Invalid number of inputs, terminating" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::unordered_map<int, std::string> myMap;

  for (int i = 1; i < argc; i++) {       //loop of directories
    DIR * dirstream = opendir(argv[i]);  //dont forget to close at end
    std::string pathname;
    pathname.append(argv[i]);
    pathname.append("/");  // filename/
    opendirectory(myMap, dirstream, pathname);
  }

  return EXIT_SUCCESS;
}
