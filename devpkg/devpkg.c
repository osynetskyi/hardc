#include <stdio.h>
#include <apr_general.h>
#include <apr_getopt.h>
#include <apr_strings.h>
#include <apr_lib.h>

#include "dbg.h"
#include "db.h"
#include "commands.h"

int main(int argc, char *argv[])
{
	apr_pool_t *p = NULL;
	apr_pool_initialize();
	apr_pool_create(&p, NULL);

	apr_getopt_t *opt;
	apr_status_t rv;

	char ch = '\0';
	const char *optarg = NULL;
	const char *config_opts = NULL;
	const char *install_opts = NULL;
	const char *make_opts = NULL;
	const char *url = NULL;
	enum CommandType request = COMMAND_NONE;

	rv = apr_getopt_init(&opt, p, argc, (const char * const *) argv);

	while(apr_getopt(opt, "I:L:c:m:i:d:S:F:B:R:", &ch, &optarg) == APR_SUCCESS) {
		switch(ch) {
			case 'I':
				request = COMMAND_INSTALL;
				url = optarg;
				break;

			case 'L':
				request = COMMAND_LIST;
				break;

			case 'c':
				config_opts = optarg;
				break;

			case 'm':
				make_opts = optarg;
				break;

			case 'i':
				install_opts = optarg;
				break;

			case 'S':
				request = COMMAND_INIT;
				break;

			case 'F':
				request = COMMAND_FETCH;
				url = optarg;
				break;

			case 'B':
				request = COMMAND_BUILD;
				url = optarg;
				break;
			
			case 'R':
				request = COMMAND_REMOVE;
				url = optarg;
				break;
		}
	}

	switch(request) {
		case COMMAND_INSTALL:
			check(url, "You must at least give an URL.");
			Command_install(p, url, config_opts, make_opts, install_opts);
			break;

		case COMMAND_LIST:
			DB_list();
			break;

		case COMMAND_FETCH:
			check(url != NULL, "You must give an URL.");
			Command_fetch(p, url, 1);
			log_info("Downloaded to %s and in /tmp/", BUILD_DIR);
			break;

		case COMMAND_BUILD:
			check(url, "You must at least give an url.");
			Command_build(p, url, config_opts, make_opts, install_opts);
			break;

		case COMMAND_INIT:
			rv = DB_init();
			check(rv == 0, "Failed to make the database.");
			break;

		case COMMAND_REMOVE:
			check(url, "You must at least give an url.");
			Command_remove(p, url, config_opts); 
			break;

		default:
			sentinel("Invalid command given.");
	}


	return 0;

error:
	return 1;
}
