#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

//#define MAX_DATA 512
//#define MAX_ROWS 100

struct Address {
	int id;
	int set;
	//char name[MAX_DATA];
	char *name;
	//char email[MAX_DATA];
	char *email;
};

struct Database {
	int MAX_ROWS;
	int MAX_DATA;
	//struct Address rows[MAX_ROWS];
	struct Address **rows;
};

struct Connection {
	FILE *file;
	struct Database *db;
};

void Database_close(struct Connection *conn);

void die(const char *message, struct Connection *conn)
{
	if(errno) {
		perror(message);
	} else {
		printf("ERROR: %s\n", message);
	}

	Database_close(conn);
	exit(1);
}

void Address_print(struct Address *addr)
{
	printf("%d %s %s\n",
			addr->id, addr->name, addr->email);
}

void Database_load(struct Connection *conn)
{
	int i = 0;
	fread(&conn->db->MAX_ROWS, sizeof(int), 1, conn->file);
	fread(&conn->db->MAX_DATA, sizeof(int), 1, conn->file);
	conn->db->rows = (struct Address **) malloc(sizeof(struct Address *) * conn->db->MAX_ROWS);
	for(i = 0; i < conn->db->MAX_ROWS; i++) {
		conn->db->rows[i] = (struct Address *) malloc(sizeof(struct Address));
		struct Address *row = conn->db->rows[i];
		fread(&row->id, sizeof(int), 1, conn->file);
		fread(&row->set, sizeof(int), 1, conn->file);
		row->name = malloc(sizeof(char) * conn->db->MAX_DATA);
		row->email = malloc(sizeof(char) * conn->db->MAX_DATA);
		fread(row->name, conn->db->MAX_DATA * sizeof(char), 1, conn->file);
		fread(row->email, conn->db->MAX_DATA * sizeof(char), 1, conn->file);
	}
	/*int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
	if(rc != 1) die("Failed to load database.", conn);*/
}

struct Connection *Database_open(const char *filename, char mode)
{
	struct Connection *conn = malloc(sizeof(struct Connection));
	if(!conn) die("Memory error.", conn);

	conn->db = malloc(sizeof(struct Database));
	if(!conn->db) die("Memory error.", conn);

	if(mode == 'c') {
		conn->file = fopen(filename, "w");
	} else {
		conn->file = fopen(filename, "r+");
	
		if(conn->file) {
			Database_load(conn);
		}
	}

	if(!conn->file) die("Failed to open the file.", conn);

	return conn;
}

void Database_close(struct Connection *conn)
{
	if(conn) {
		if(conn->file) fclose(conn->file);
		if(conn->db) {
			if(conn->db->rows) {
				int i = 0;
				for(i = 0; i < conn->db->MAX_ROWS; i++) {
					if(conn->db->rows[i]) {
						if(conn->db->rows[i]->name) {
							free(conn->db->rows[i]->name);
						}
						if(conn->db->rows[i]->email) {
							free(conn->db->rows[i]->email);
						}
						free(conn->db->rows[i]);
					}
				}
				free(conn->db->rows);
			}
			free(conn->db);
		}
		free(conn);
	}
}

void Database_write(struct Connection *conn)
{
	rewind(conn->file);

	int i = 0;
	fwrite(&conn->db->MAX_ROWS, sizeof(int), 1, conn->file);
	fwrite(&conn->db->MAX_DATA, sizeof(int), 1, conn->file);
	for(i = 0; i < conn->db->MAX_ROWS; i++) {
		struct Address *row = conn->db->rows[i];
		fwrite(&row->id, sizeof(int), 1, conn->file);
		fwrite(&row->set, sizeof(int), 1, conn->file);
		fwrite(row->name, sizeof(char) * conn->db->MAX_DATA, 1, conn->file);
		fwrite(row->email, sizeof(char) * conn->db->MAX_DATA, 1, conn->file);
	}

	/*int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
	if(rc != 1) die("Failed to write database", conn);*/

	if(fflush(conn->file) == -1) die("Cannot flush database", conn);
}

void Database_create(struct Connection *conn, int MAX_ROWS, int MAX_DATA)
{
	int i = 0;
	conn->db->MAX_ROWS = MAX_ROWS;
	conn->db->MAX_DATA = MAX_DATA;
	conn->db->rows = (struct Address **) malloc(conn->db->MAX_ROWS * (sizeof(struct Address *)));
	
	for(i = 0; i < conn->db->MAX_ROWS; i++) {
		conn->db->rows[i] = (struct Address *) malloc(sizeof(struct Address));
		conn->db->rows[i]->id = i + 1;
		conn->db->rows[i]->set = 0;
	}
}

void Database_set(struct Connection *conn, int id, const char *name, const char *email)
{
	struct Address *addr = conn->db->rows[id];
	if(addr->set) die("Already set, delete it first", conn);

	addr->id = id;
	addr->set = 1;
	addr->name = malloc(sizeof(char) * conn->db->MAX_DATA);
	addr->email = malloc(sizeof(char) * conn->db->MAX_DATA);

	char *res = strncpy(addr->name, name, conn->db->MAX_DATA);
	int change = strlen(addr->name);
	if(change == conn->db->MAX_DATA) {
		change--;
	}
	addr->name[change] = '\0';
	if(!res) die("Name copy failed", conn);

	res = strncpy(addr->email, email, conn->db->MAX_DATA);
	change = strlen(addr->email);
	if(change == conn->db->MAX_DATA) {
		change--;
	}
	addr->email[change] = '\0';
	if(!res) die("Email copy failed", conn);
}

void Database_get(struct Connection *conn, int id)
{
	struct Address *addr = conn->db->rows[id];

	if(addr->set) {
		Address_print(addr);
	} else {
		die("ID is not set", conn);
	}
}

void Database_delete(struct Connection *conn, int id)
{
	conn->db->rows[id]->id = id;
	conn->db->rows[id]->set = 0;
}

void Database_list(struct Connection *conn)
{
	int i = 0;
	struct Database *db = conn->db;

	for(i = 0; i < db->MAX_ROWS; i++) {
		struct Address *cur = db->rows[i];

		if(cur->set) {
			Address_print(cur);
		}
	}
}

int main(int argc, char *argv[])
{
	if(argc < 3) die("USAGE: ex17 <dbfile> <action> [action params]", NULL);

	char *filename = argv[1];
	char action = argv[2][0];
	struct Connection *conn = Database_open(filename, action);
	int id = 0;

	if((argc > 3) && (action != 'c')) id = atoi(argv[3]);
	//if(id >= conn->db->MAX_ROWS) die("There's not that many records.", conn);

	switch(action) {
		case 'c':
			Database_create(conn, atoi(argv[3]), atoi(argv[4]));
			Database_write(conn);
			break;

		case 'g':
			if(argc != 4) die("Need an id to get", conn);

			Database_get(conn, id);
			break;

		case 's':
			if(argc != 6) die("Need id, name, email to set", conn);

			Database_set(conn, id, argv[4], argv[5]);
			Database_write(conn);
			break;

		case 'd':
			if(argc != 4) die("Need an id to delete", conn);

			Database_delete(conn, id);
			Database_write(conn);
			break;

		case 'l':
			Database_list(conn);
			break;
		default:
			die("Invalid action, only: c=create, g=get, s=set, d=delete, l=list", conn);
	}

	Database_close(conn);

	return 0;
}
