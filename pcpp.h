#include <iostream>
#include <vector>
#include "string.h"
#include "termios.h"

class PostCPP {
public:
  //Used to initialize db connection
  struct user_session_variables {
    //Helpers object to use
    //helpers *H = new helpers;
    //username variable
    unsigned char *user = (unsigned char *)calloc('\0', 24);
    //password variable
    unsigned char *pass = (unsigned char *)calloc('\0', 32);
    //db variable
    unsigned char *db = (unsigned char *)calloc('\0', 24);
    //port number
    unsigned short int *port = (unsigned short int *)calloc('\0', 5);
  }USV;

  //DB, Port, username, and password
  PostCPP(unsigned char *d, unsigned short int *po, unsigned char *u, unsigned char *p){
    strcat((char *)this->USV.db, (char *)d);
    strcat((char *)this->USV.port, (char *)po);
    strcat((char *)this->USV.user, (char *)u);
    strcat((char *)this->USV.pass, (char *)p);
  };
  //Just DB, port, and username
  PostCPP(unsigned char *d, unsigned short int *po, unsigned char *u){
    strcat((char *)this->USV.db, (char *)d);
    strcat((char *)this->USV.port, (char *)po);
    strcat((char *)this->USV.user, (char *)u);
  };
  //Just DB and port used
  PostCPP(unsigned char *d, unsigned char *po){
    strcat((char *)this->USV.db, (char *)d);
    strcat((char *)this->USV.port, (char *)po);
  };
  std::vector<unsigned char *> *getInfo(std::vector<unsigned char *> *rv);
};

class create : protected PostCPP{
public:
  using PostCPP::PostCPP;
  using PostCPP::getInfo;
};

class alter : protected PostCPP{
public:
  using PostCPP::PostCPP;
};

class query : protected PostCPP{
public:
  using PostCPP::PostCPP;

//Information used for each tablesearch entry
struct tableSearch {
  //Database name
  char *db = (char *)calloc(1, '\0');
  //Table name
  std::vector<char *> *tables = new std::vector<char *>(16);
  //char *table = (char *)calloc(1, '\0');
  //Set columns for specific search
  std::vector<std::vector<char *>> *columns = new std::vector<std::vector<char *>>(16);
  //Set WHERE string
  char *whereString = (char *)calloc(64, '\0');
  //Set full search string
  char *searchString = (char *)calloc(64, '\0');
}TBL;
//Used to get info from given database
struct query_data {
  //Set tables for specific search
  std::vector<char *> *tables = new std::vector<char *>(16);
  //Query per each table
  std::vector<tableSearch> *tableQuery = new std::vector<tableSearch>(16);
  //Set similar terms to search for
  std::vector<char *> *stringz = new std::vector<char *>(24);
  //Set query to search db for
  char *query;
}QRY;
//Dummy var
char *FALSE;
//Get query from user
void getQuery();
//Set query by user
void setQuery(char *query, char *database);
//Set tables
void setTable(std::vector<char *> *tables);
//Set columns
void setColmn(std::vector<std::vector<char *>> *column);
//Set raw where
void setWhere(char *whereStatement);
//Where clause builder
char *WHERE(char *column, char* operator_symbol, char *comparison);
//Combined where statements
char *where_combination(bool include_where, std::vector<char *> *collection_of_statements, std::vector<bool> *and_or_array);
//Find table that contains column being searched for
char findTable(char *column);
//QUERIES
  //Build Query
  void bldQuery();
  //Query database using given initialization values
  void runQuery();
};

class destroy : protected PostCPP{
public:
  using PostCPP::PostCPP;
};
