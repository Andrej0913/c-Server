#include <netinet/in.h> //structure for storing address information
#include <sys/socket.h> // for socked APIs
#include <sys/types.h>
#include <stdint.h>

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <pthread.h>

#include <error.h>
#include <errno.h>

#include <sqlite3.h>

#include "massage_helper.h"
#include "socket_helper.h"
#define PORT 9001

//static void manu ()

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

int main(int argc, char const* argv[]) {
  bool exists = false;
  sqlite3 *db;
  int rc;
  char *sql;
  char *z_err_msg;

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


  sqlite3_close(db);

  int servSockD = cr_serv_socket(PORT);
  // listen for connections
  listen(servSockD, 1);

  // integer to hold clent socket.
  int clientSocket = accept(servSockD, NULL, NULL);
  printf("Connection established\n");

  pthread_t thread_1;
  pthread_t thread_2;
  pthread_create(&thread_1, NULL, recv_massage, (void*)(intptr_t)clientSocket);
  pthread_create(&thread_2, NULL, send_massage, (void*)(intptr_t)clientSocket);

  pthread_join(thread_1,NULL);
  pthread_join(thread_2,NULL);
  return 0;
}
