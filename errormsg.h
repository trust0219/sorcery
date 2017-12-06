#ifndef _ERRORMSG_H_
#define _ERRORMSG_H_

#include <iostream>
#include <string>

void invalidArgumentError(std::string &message) {
  std::cerr << "Invalid Argument Error:  " << message << std::endl;
  std::cerr << "Terminating sorcery" << std::endl;
  exit(1);
}

void invalidFileError(std::string &fname) {
  std::cerr << "Invalid File:  " << fname << std::endl;
  std::cerr << "Terminating sorcery" << std::endl;
  exit(1);
}

#endif
