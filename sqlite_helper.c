#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include <errno.h>

#include <sqlite3.h>

#include "sqlite_helper.h"

static int callback(void* data, int argc, char** argv, char** az_col_name) {
  int i;

  *(bool*) data = true;
  printf("callback");
  for(i = 0; i<argc; i++) {
    printf("%s = %s\n", az_col_name[i], argv[i] ? argv[i] : "NULL");
  }
  printf("\n");
  return 0;
}

sqlite3* open_db(sqlite3* db) {
  int rc;
  //rc = sqlite3_open("test.db", &db);
  rc = sqlite3_open_v2("file:test.db", &db, SQLITE_OPEN_URI | SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
  if( rc ) {
    perror("Error whiel creating/opening .db file\n");
    printf("Sqlite error massage: %s", sqlite3_errmsg(db));
    printf(": %i\n", errno);
    printf("rc: %i\n", rc);
  } else {
    printf("Database successfull opened\n");
  }

  return db;
}

void init_db(sqlite3* db) {
  bool exists = false;
  int rc;
  char* sql;
  char* z_err_msg;

  //Check if database exist
  sql = "SELECT name FROM sqlite_master WHERE name='Users'";
  rc = sqlite3_exec(db, sql, callback, (void*)(intptr_t)&exists, &z_err_msg);
  if ( rc != SQLITE_OK ) {
    printf("Boolean: %i\n", exists);
    printf("SQL error: %s\n", z_err_msg);
    sqlite3_free(z_err_msg);
    printf("rc: %i\n", rc);
  }
  if(exists) {
    printf("Table Users allrady exists\n");
  } else {
    printf("Table User will be created\n");
    /* Create SQL statement */
    sql = "CREATE TABLE Users(" \
    "PersonalID int PRIMERY KEY   NOT NULL," \
    "Username       TEXT          NOT NULL," \
    "Email          TEXT          NOT NULL," \
    "Password       CHAR(20)      NOT NULL);";
    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, 0, &z_err_msg);
    if( rc != SQLITE_OK ) {
      printf("SQL error: %s\n", z_err_msg);
      sqlite3_free(z_err_msg);
      printf("rc: %i\n", rc);
    } else {
      printf("Table created successfully\n");
    }
  }
}
