#include "resources.h"

int main(int argc, char **argv){

  create *cr = new create((unsigned char *)"DB_NAME", (unsigned short int*)15, (unsigned char *)"US_NAME", (unsigned char *)"US_PASS");
  std::vector<char *> *newValues = new std::vector<char *>(3);
  //newValues = cr->getInfo(newValues);
  //for(int i = 0; i < newValues->size(); i++) std::printf("%s\n", newValues->at(i));


  return 0;
};
