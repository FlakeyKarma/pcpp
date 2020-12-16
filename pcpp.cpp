#include "resources.h"

std::vector<unsigned char *> *PostCPP::getInfo(std::vector<unsigned char *> *retValz){
  *retValz = {this->USV.db, this->USV.user, this->USV.pass};
  return retValz;
}

//CREATE
//ALTER
//QUERY
//Get query from user
void query::getQuery(){
  char db[16];
  char query[120];

  //Get database name
  //std::printf("%d %d EFF\n\n\n", strlen(this->TBL.db), !strlen(this->TBL.db));
  //this->USV.H->getInfo((char *)"Database:", db, 16);

  //Get full query
  //this->USV.H->getInfo((char *)"Query:", query, 120);

  //Set full query
  this->setQuery(query, db);
}

//Set query info to struct
void query::setQuery(char *qry, char *db){
  if(db[strlen(db)-1] == '\n'){
    db[strlen(db)-1] = '\0';
  }
  this->TBL.db = db;
  this->QRY.query = qry;
}

//Build query with given info
void query::bldQuery(){
  //Query
  char *query;
  query = (char *)malloc(128 * sizeof(char *));
  strncpy(query, "SELECT ", strlen("SELECT "));

  //Set database
  char db[16] = "\0";

  //Set tables for specific search
  std::vector<char *> *tables = (this->USV.H->sets[4] ? this->TBL.tables : new std::vector<char *>(16));

  //Set similar terms to search for
  char *WHERE = (char *)0;
  //Length of each vector
  char lengths;

  //Database name
  if(!this->USV.H->sets[0]) this->USV.H->getInfo((char *)"Database:", db, 16);
  if(!this->USV.H->sets[4]){
    std::printf("Enter `END` if you are done entering info.\n");

    //Set tables
    for(int i = 0; i < 16; i++){
      std::printf("Enter tables to be searched #[%d/16]: ", i+1);
      std::fgets(tables->at(i) = new char[16], 16, stdin);
      tables->at(i)[strlen(tables->at(i))-1] = '\0';
      std::printf("\n");
      lengths = i;
      if(!strcmp(tables->at(i), "END")) break;
    }
  }

  if(this->USV.H->sets[5]) lengths = this->TBL.columns->size();
  //Set up lengths for each column
  char column_lengths[lengths] = {0};
  //Set up new vector of columns for each table
  std::vector<std::vector<char *>> *columns = (this->USV.H->sets[5] ? this->TBL.columns : new std::vector<std::vector<char *>>(lengths));

  if(!this->USV.H->sets[5]){

    std::printf("Enter `END` if you are done entering info.\n");


    //For each column in the table
    for(int j = 0; j < (int)lengths; j++){
      //Set columns
      for(int i = 0; i < 16; i++){
        std::printf("Enter columns to be searched for table %s #[%d/16]: ", tables->at(j), i+1);
        columns->at(j).push_back(new char[16]);
        std::fgets(columns->at(j).at(i), 16, stdin);
        columns->at(j).at(i)[strlen(columns->at(j).at(i))-1] = '\0';
        std::printf("\n");
        column_lengths[j] = i;
        if(!strcmp(columns->at(j).at(i), "END")) break;
      }
    }
  } else for(int i = 0; i < columns->size(); i++) for(int j = 0; j < columns->at(i).size(); j++){
    column_lengths[i] = j+1;
  }

  char table_column[64] = {'\0'};
  //Forming SELECT query section
  for(int i = 0; i < lengths; i++){
    for(int j = 0; j < column_lengths[i]; j++){
      std::sprintf(table_column, "%s.%s ", tables->at(i), columns->at(i).at(j));
      for(int k = 0; k < strlen(table_column); k++){
      }
      strcat(query, table_column);
    }
  }

  //Set tables to select FROM
  strcat(query, "FROM ");


  //Set up FROM section of query
  for(int i = 0; i < lengths; i++){
    std::sprintf(query, "%s%s ", query, tables->at(i));
  }

  if(!this->USV.H->sets[6]){
    std::printf("Enter `END` if you are done entering info.\n");

    //Set WHERE
    std::printf("Enter full `WHERE` statement desired:\n");
    std::fgets(WHERE, 120, stdin);
    WHERE[strlen(WHERE)-1] = '\0';
    std::printf("\n");
  }

  //Set WHERE for query
  std::sprintf(query, "%s%s", query, (this->USV.H->sets[6] ? this->TBL.whereString : WHERE));
  //query += std::string((this->USV.H->sets[6] ? this->TBL.whereString : WHERE));

  this->setQuery(query, (this->USV.H->sets[0] ? this->USV.database : db));

  this->runQuery();
}

//Run query for database
void query::runQuery(){
  char *CMD;

  CMD = (char *)malloc(strlen(this->QRY.query)+24);
  //Assuming that there isn't a username involved
  sprintf(CMD,"psql -d %s -U -w -c \"%s\"", this->TBL.db, this->QRY.query);
  //This is to print the command that will be entered to the terminal once ready
  std::printf("CMD:::\n\t%s\nCMD:::\n", CMD);
  //system(this->QRY.query);
}
//DESTROY
