#ifndef _db_h
#define _db_h

#define DB_FILE "/home/rcao/sandbox/c/devpkg/db/dbfile"
#define DB_DIR "/home/rcao/sandbox/c/devpkg/db"

int DB_init();
int DB_list();
int DB_update(const char *url);
int DB_find(const char *url);

#endif
