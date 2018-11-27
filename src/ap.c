#include <stdio.h>
#include <string.h>
#include <errno.h>

#if defined (_WIN32)
#	include <direct.h>
#else
#	include <limits.h>
#	include <sys/stat.h>
#	include <sys/types.h>
#	include <stdint.h>
#   include <sys/wait.h>
#endif

#include "ap_defs.h"
#include "ap_str.h"
#include "ap_log.h"
#include "ap_version.h"
#include "ap.h"


typedef struct _AP_CTX
{
	char			*default_dir;

	char			*config_path;
	FILE			*config_file;

	char			*log_path;
	FILE			*log_file;

	BOOL			simulate;				

	char			*client_ip;
	char			*client_command;
} AP_CTX;


static void print_environment (AP_CTX *ctx)
{
	extern char **environ;
	char		**senviron	= NULL;

	if (environ == NULL)
	{
		ap_trace ("(%s) Can not get environment\n", ctx->client_ip);

		goto finish;
	}

	ap_trace ("(%s) +------------------------------------+\n", ctx->client_ip);
	ap_trace ("(%s) |          ENVIRONMENT START         |\n", ctx->client_ip);
	ap_trace ("(%s) +------------------------------------+\n", ctx->client_ip);

	senviron = environ;
	while (*senviron != NULL)
	{
		ap_trace ("(%s) | %s\n", ctx->client_ip, *senviron ++);
	}

	ap_trace ("(%s) +------------------------------------+\n", ctx->client_ip);
	ap_trace ("(%s) |          ENVIRONMENT END           |\n", ctx->client_ip);
	ap_trace ("(%s) +------------------------------------+\n", ctx->client_ip);

finish:
	return;
}


static void show_version ()
{
	fprintf (stdout, "\nauthprogs %d.%d.%d\n", AP_VERSION_MAJOR, AP_VERSION_MINOR, AP_VERSION_REVISION);
}


static void show_help ()
{
	fprintf (stdout, "\nUsage:\n");
	fprintf (stdout, "    authprogs [-c <config>] [-l <log_path|stdout|stderr>] [-e <log_level>] [-v] [-h]\n\n");
	fprintf (stdout, "    where:\n");
	fprintf (stdout, "        %-2s %-25s  %s", "-c", "config", "configuration file path\n");
	fprintf (stdout, "        %-2s %-25s  %s", "-l", "log_path|stdout|stderr", "log file path, stdout or stderr\n");
	fprintf (stdout, "        %-2s %-25s  %s", "-e", "log_level", "log level (0-quiet, 1-error, 2-denied commands, 3-allowed commands, 4-debug, 5-trace)\n");
	fprintf (stdout, "        %-2s %-25s  %s", "-v", "", "simulate (do not run any command)\n");
	fprintf (stdout, "        %-2s %-25s  %s", "-v", "", "show version\n");
	fprintf (stdout, "        %-2s %-25s  %s", "-h", "", "show help\n");
}


static int uninit (AP_CTX *ctx)
{
	if (ctx->default_dir != NULL)
	{
		free (ctx->default_dir);
	}

	if (ctx->config_path != NULL)
	{
		free (ctx->config_path);
	}

	if (ctx->config_file != NULL)
	{
		fclose (ctx->config_file);
	}

	if (ctx->log_path != NULL)
	{
		free (ctx->log_path);
	}

	if (ctx->log_file != NULL)
	{
		fclose (ctx->log_file);
	}

	if (ctx->client_ip != NULL)
	{
		free (ctx->client_ip);
	}

	if (ctx->client_command != NULL)
	{
		free (ctx->client_command);
	}

	memset (ctx, 0, sizeof (AP_CTX));

	return AP_NO_ERROR;
}


static int parse_command_line (AP_CTX *ctx, int argc, char *argv[])
{
	int				rc				= AP_NO_ERROR;
	AP_LOG_LEVEL	log_level;
	size_t			log_level_len;
	char			*next_arg		= NULL;

	switch (argc)
	{
		case 0:
		{
			fprintf (stdout, "argv[0] is missing\n");
			rc = AP_ERROR_CMDLINE;

			break;
		}
			
		case 1:
		{
			break;
		}

		default:
		{
			if (argc > 8)
			{
				fprintf (stdout, "Too many arguments\n");
				show_help ();
				rc = AP_ERROR_CMDLINE;

				break;
			}
			
			argv ++;
			while (*argv != NULL)
			{
				next_arg = *(argv + 1);

				if (strcmp (*argv, "-c") == 0)
				{
					if (next_arg != NULL)
					{
						ctx->config_path = strdup (next_arg);
						if (ctx->config_path == NULL)
						{
							fprintf (stdout, "Cannot allocate memory for 'ctx->config_path'\n");
							rc = AP_ERROR_NO_MEMORY;
							
							break;
						}

						argv += 2;
					}
					else
					{
						fprintf (stdout, "'%s' requires an argument\n", *argv);
						show_help ();
						rc = AP_ERROR_CMDLINE;

						break;
					}
				}
				else if (strcmp (*argv, "-l") == 0)
				{
					if (next_arg != NULL)
					{
						ctx->log_path = strdup (next_arg);
						if (ctx->log_path == NULL)
						{
							fprintf (stdout, "Cannot allocate memory for 'ctx->log_path'\n");
							rc = AP_ERROR_NO_MEMORY;
							
							break;
						}

						argv += 2;
					}
					else
					{
						fprintf (stdout, "'%s' requires an argument\n", *argv);
						show_help ();
						rc = AP_ERROR_CMDLINE;

						break;
					}
				}
				else if (strcmp (*argv, "-e") == 0)
				{
					if (next_arg != NULL)
					{
						log_level_len = strlen (next_arg);
						if (log_level_len != 1)
						{
							fprintf (stdout, "Invalid log level '%s'\n", next_arg);
							show_help ();
							rc = AP_ERROR_CMDLINE;

							break;
						}

						if (next_arg[0] < '0' || next_arg[0] > '5')
						{
							fprintf (stdout, "Invalid log level '%s'\n", next_arg);
							show_help ();
							rc = AP_ERROR_CMDLINE;

							break;
						}

						log_level = next_arg[0] - '0';

						ap_log_set_level (log_level);

						argv += 2;
					}
					else
					{
						fprintf (stdout, "'%s' requires an argument\n", *argv);
						show_help ();
						rc = AP_ERROR_CMDLINE;

						break;
					}
				}
				else if (strcmp (*argv, "-s") == 0)
				{
					ctx->simulate = TRUE;

					argv += 1;
				}
				else if (strcmp (*argv, "-v") == 0)
				{
					show_version ();
					rc = AP_ERROR_VERSION;

					goto finish;
				}
				else if (strcmp (*argv, "-h") == 0)
				{
					show_help ();
					rc = AP_ERROR_HELP;

					goto finish;
				}
				else
				{
					fprintf (stdout, "Invalid argument '%s'\n", *argv);
					show_help ();
					rc = AP_ERROR_CMDLINE;

					goto finish;
				}
			}
		}
	}

finish:
	if (rc != AP_NO_ERROR && rc != AP_ERROR_VERSION && rc != AP_ERROR_HELP)
	{
		uninit (ctx);
	}

	return rc;
}


static int get_default_directory (AP_CTX *ctx)
{
	int			rc					= AP_NO_ERROR;
	const char	*var				= NULL;
	size_t		size;

#	if defined (_WIN32)
	var = getenv ("USERPROFILE"); 
#	else
	var = getenv ("HOME"); 
#	endif
	if (var == NULL)
	{
		ap_error ("Can not get HOME environment variable\n");
		rc = AP_ERROR_ENVIRONMENT;

		goto finish;
	}

	if (*var == '\0')
	{
		ap_error ("Empty HOME environment variable\n");
		rc = AP_ERROR_ENVIRONMENT;

		goto finish;
	}

	size = strlen (var) + sizeof ("/.ssh") + 1;

	ctx->default_dir = calloc (1, size);
	if (rc != AP_NO_ERROR)
	{
		ap_error ("Can not allocate memory for 'dir'\n");
		rc = AP_ERROR_NO_MEMORY;

		goto finish;
	}

	ap_str_strlcpy (ctx->default_dir, var, size);
	ap_str_strlcat (ctx->default_dir, "/.ssh", size);

finish:
	if (rc != AP_NO_ERROR)
	{
		if (ctx->default_dir != NULL)
		{
			free (ctx->default_dir);
		}
	}

	return rc;
}


static int create_directory (const char *dir)
{
	int			rc				= AP_NO_ERROR;
	int			rc_os;

	AP_VALIDATE_PTR_ARGUMENT (dir);

	if (*dir == '\0')
	{
		ap_error ("Empty path\n");
		rc = AP_ERROR_INVALID_ARGUMENT;

		goto finish;
	}

#	if defined (_WIN32)
	rc_os = _mkdir (dir);
#	else
	rc_os = mkdir (dir, 0700);
#	endif
	if (rc_os != 0)
	{
		if (errno != EEXIST)
		{
			ap_error ("Can not create directory '%s', error: '%s'\n", dir, strerror (errno));
			rc = AP_ERROR_ENVIRONMENT;

			goto finish;
		}
	}

finish:
	return rc;
}


static int init_config_path (AP_CTX *ctx)
{
	int				rc								= AP_NO_ERROR;
	size_t			size;
	BOOL			allocated_in_this_function		= FALSE;
	
	if (ctx->config_path == NULL)
	{
		if (ctx->default_dir == NULL)
		{
			rc = get_default_directory (ctx);
			if (rc != AP_NO_ERROR)
			{
				goto finish;
			}

			rc = create_directory (ctx->default_dir);
			if (rc != AP_NO_ERROR)
			{
				goto finish;
			}
		}

		allocated_in_this_function = TRUE;

		size = strlen (ctx->default_dir) + sizeof ("/") + sizeof (AP_DEFAULT_CONFIG_FILENAME) + 1;

		ctx->config_path = (char *) calloc (1, size);
		if (ctx->config_path == NULL)
		{
			ap_error ("(%s) Can not allocate memory for 'ctx->config_path'\n", ctx->client_ip);
			rc = AP_ERROR_NO_MEMORY;

			goto finish;
		}

		ap_str_strlcpy (ctx->config_path, ctx->default_dir, size);
		ap_str_strlcat (ctx->config_path, "/", size);
		ap_str_strlcat (ctx->config_path, AP_DEFAULT_CONFIG_FILENAME, size);
	}

finish:
	if (rc != AP_NO_ERROR)
	{
		if (allocated_in_this_function == TRUE)
		{
			if (ctx->config_path != NULL)
			{
				free (ctx->config_path);
			}
		}
	}

	return rc;
}


static int open_config (AP_CTX *ctx)
{
	int		rc			= AP_NO_ERROR;
	
	ctx->config_file = fopen (ctx->config_path, "rt");
	if (ctx->config_file == NULL)
	{
		ap_error ("(%s) Can not open configuration file '%s', error: '%s'\n", ctx->client_ip, ctx->config_path, strerror (errno));
		rc = AP_ERROR_CONFIG_FILE;

		goto finish;
	}

finish:
	return rc;
}


static int init_log_path (AP_CTX *ctx)
{
	int				rc								= AP_NO_ERROR;
	size_t			size;
	BOOL			allocated_in_this_function		= FALSE;

	if (ctx->log_path == NULL)
	{
		if (ctx->default_dir == NULL)
		{
			rc = get_default_directory (ctx);
			if (rc != AP_NO_ERROR)
			{
				goto finish;
			}

			rc = create_directory (ctx->default_dir);
			if (rc != AP_NO_ERROR)
			{
				goto finish;
			}
		}

		allocated_in_this_function = TRUE;

		size = strlen (ctx->default_dir) + sizeof ("/") + sizeof (AP_DEFAULT_LOG_FILENAME) + 1;

		ctx->log_path = (char *) calloc (1, size);
		if (ctx->log_path == NULL)
		{
			ap_error ("Can not allocate memory for 'ctx->log_path'\n");
			rc = AP_ERROR_NO_MEMORY;

			goto finish;
		}

		ap_str_strlcpy (ctx->log_path, ctx->default_dir, size);
		ap_str_strlcat (ctx->log_path, "/", size);
		ap_str_strlcat (ctx->log_path, AP_DEFAULT_LOG_FILENAME, size);
	}

finish:
	if (rc != AP_NO_ERROR)
	{
		if (allocated_in_this_function == TRUE)
		{
			if (ctx->log_path != NULL)
			{
				free (ctx->log_path);
			}
		}
	}

	return rc;
}


static int open_log (AP_CTX *ctx)
{
	int		rc					= AP_NO_ERROR;

	if (strcmp (ctx->log_path, "stdout") == 0)
	{
		ap_log_set_output (stdout);
	}
	else if (strcmp (ctx->log_path, "stderr") == 0)
	{
		ap_log_set_output (stderr);
	}
	else
	{
		ctx->log_file = fopen (ctx->log_path, "at");
		if (ctx->log_file == NULL)
		{
			ap_error ("Can not open log file '%s', error: '%s'\n", ctx->log_path, strerror (errno));
			rc = AP_ERROR_LOG_FILE;

			goto finish;
		}

		ap_log_set_output (ctx->log_file);
	}

finish:
	return rc;
}


static int init_client_ip (AP_CTX *ctx)
{
	int			rc				= AP_NO_ERROR;
	const char	*var			= NULL; 
	char		*p				= NULL;
	char		*state			= NULL;

	var = getenv ("SSH_CLIENT"); 
	if (var == NULL)
	{
		ap_error ("Can not get SSH_CLIENT environment variable\n");
		rc = AP_ERROR_ENVIRONMENT;

		goto finish;
	}

	if (*var == '\0')
	{
		ap_error ("Empty SSH_CLIENT environment variable\n");
		rc = AP_ERROR_ENVIRONMENT;

		goto finish;
	}

	ctx->client_ip = strdup (var);
	if (ctx->client_ip == NULL)
	{
		ap_error ("Can not allocate memory for 'ctx->client_ip'\n");
		rc = AP_ERROR_NO_MEMORY;

		goto finish;
	}

	p = strtok_r (ctx->client_ip, " \t", &state);
	if (p == NULL)
	{
		ap_error ("Invalid SSH_CLIENT variable\n");
		rc = AP_ERROR_ENVIRONMENT;

		goto finish;
	}
	
finish:
	if (rc != AP_NO_ERROR)
	{
		if (ctx->client_ip != NULL)
		{
			free (ctx->client_ip);
		}
	}

	return rc;
}


static int init_client_command (AP_CTX *ctx)
{
	int			rc				= AP_NO_ERROR;
	const char	*var			= NULL;
	char		*hex_str		= NULL;

	var = getenv ("SSH_ORIGINAL_COMMAND");
	if (var == NULL)
	{
		ap_error ("(%s) Can not get SSH_ORIGINAL_COMMAND environment variable\n", ctx->client_ip);
		rc = AP_ERROR_ENVIRONMENT;

		goto finish;
	}

	if (*var == '\0')
	{
		ap_error ("(%s) Empty SSH_ORIGINAL_COMMAND environment variable\n", ctx->client_ip);
		rc = AP_ERROR_ENVIRONMENT;

		goto finish;
	}

	ap_debug ("(%s) Client command '%s'\n", ctx->client_ip, var);

	if (ap_log_get_level () == AP_LOG_LEVEL_TRACE)
	{
		rc = ap_str_to_hex (var, &hex_str);
		if (rc != AP_NO_ERROR)
		{
			goto finish;
		}

		ap_trace ("(%s) Client command in hexadecimal '%s'\n", ctx->client_ip, hex_str);

		free (hex_str);
	}

	ctx->client_command = strdup (var);
	if (ctx->client_command == NULL)
	{
		ap_error ("(%s) Can not allocate memory for 'ctx->client_command'\n", ctx->client_ip);
		rc = AP_ERROR_NO_MEMORY;

		goto finish;
	}

	ap_str_trim_head_from_set (ctx->client_command, " \t");
	ap_str_trim_tail_from_set (ctx->client_command, " \t\r\n");
	ap_str_shrink_spaces (ctx->client_command);

finish:
	return rc;
}


static int init_options (AP_CTX *ctx)
{
	int				rc					= AP_NO_ERROR;

	rc = init_log_path (ctx);
	if (rc != AP_NO_ERROR)
	{
		goto finish;
	}

	rc = open_log (ctx);
	if (rc != AP_NO_ERROR)
	{
		goto finish;
	}

	rc = init_client_ip (ctx);
	if (rc != AP_NO_ERROR)
	{
		goto finish;
	}

	rc = init_client_command (ctx);
	if (rc != AP_NO_ERROR)
	{
		goto finish;
	}

	rc = init_config_path (ctx);
	if (rc != AP_NO_ERROR)
	{
		goto finish;
	}

	rc = open_config (ctx);
	if (rc != AP_NO_ERROR)
	{
		goto finish;
	}

finish:
	return rc;
}


static int init (AP_CTX *ctx, int argc, char *argv[])
{
	int		rc				= AP_NO_ERROR;

	ap_log_init ();

	rc = parse_command_line (ctx, argc, argv);
	if (rc != AP_NO_ERROR)
	{
		goto finish;
	}

	rc = init_options (ctx);
	if (rc != AP_NO_ERROR)
	{
		goto finish;
	}

finish:
	return rc;
}


static uint32_t prefix_to_netmask (unsigned int prefix)
{
	if (prefix == 0)
	{
		return ~ ((uint32_t) -1);
	}
	else
	{
		return ~ ((1 << (32 - prefix)) - 1);
	}
}


static int ip_str_to_ip (AP_CTX *ctx, const char *ip_str, uint32_t *ip)
{
    int				rc				= AP_NO_ERROR;
	int				rc_os;
	unsigned int	ip_bytes[4];
	unsigned int	i;

	*ip = 0;

	rc_os = sscanf (ip_str, "%u.%u.%u.%u", &ip_bytes[0], &ip_bytes[1], &ip_bytes[2], &ip_bytes[3]);
    if (rc_os != 4)
	{
		ap_error ("(%s) Invalid ip address '%s'\n", ctx->client_ip, ip_str);
		rc = AP_ERROR_IP_NOT_VALID;
        
		goto finish;
	}
 
	for (i = 0; i < 4; i ++)
	{
		if (ip_bytes[i] > 255)
		{
			ap_error ("(%s) Invalid ip address '%s'\n", ctx->client_ip, ip_str);
			rc = AP_ERROR_IP_NOT_VALID;
        
			goto finish;
		}

		*ip = (*ip << 8) | ip_bytes[i];
	}

finish:
    return rc;
}


static int check_ip (AP_CTX *ctx, const char *ip_str, char *network_with_prefix_str, BOOL *in_range)
{
	int				rc				= AP_NO_ERROR;
	uint32_t		ip;
	char			*network_str	= NULL;
    uint32_t		network;
    uint32_t		netmask;
	char			*prefix_str		= NULL;
	uint32_t		prefix;
	unsigned long	prefix_ul;
	uint32_t		lower_limit;
	uint32_t		upper_limit;
	char			*state			= NULL;

	*in_range = FALSE;

	network_str = strtok_r (network_with_prefix_str, "/", &state);
	if (network_str == NULL)
	{
		ap_error ("(%s) Invalid network address '%s'\n", ctx->client_ip, network_with_prefix_str);
		rc = AP_ERROR_IP_NETWORK_NOT_VALID;

		goto finish;
	}

	prefix_str = strtok_r (NULL, "/", &state);
	if (prefix_str == NULL)
	{
		prefix_str = "32";
	}

	prefix_ul = strtoul (prefix_str, NULL, 10);
	if ((prefix_ul == ULONG_MAX) || (prefix_ul > 32))
	{
		ap_error ("(%s) Invalid prefix '%s'\n", ctx->client_ip, prefix_str);
		rc = AP_ERROR_IP_PREFIX_NOT_VALID;

		goto finish;
	}

	prefix = prefix_ul;

	rc = ip_str_to_ip (ctx, ip_str, &ip);
	if (rc != AP_NO_ERROR)
	{
		goto finish;
	}

	rc = ip_str_to_ip (ctx, network_str, &network);
	if (rc != AP_NO_ERROR)
	{
		goto finish;
	}

	netmask = prefix_to_netmask (prefix);

    lower_limit = (network & netmask);
    upper_limit = (lower_limit | (~ netmask));
 
    if (ip >= lower_limit && ip <= upper_limit)
	{
		*in_range = TRUE;
	}

finish:
	return rc;
}


static int validate_ip (AP_CTX *ctx, char *ip, BOOL *ip_match)
{
	int		rc				= AP_NO_ERROR;

	*ip_match = FALSE;

	ap_debug ("(%s) IP '%s'\n", ctx->client_ip, ip);

	if (strncmp (ip, "ALL", 3) == 0)
	{
		*ip_match = TRUE;
		ap_debug ("(%s) IP match\n", ctx->client_ip);

		goto finish;
	}
	else
	{
		rc = check_ip (ctx, ctx->client_ip, ip, ip_match);
		if (rc != AP_NO_ERROR)
		{
			goto finish;
		}

		if (*ip_match == TRUE)
		{
			ap_debug ("(%s) IP match\n", ctx->client_ip);
		}
		else
		{
			ap_debug ("(%s) IP doesn't match\n", ctx->client_ip);
		}
	}
	
finish:
	return rc;
}


static int parse_ip_list (AP_CTX *ctx, char *line, BOOL *ip_match)
{
	int				rc				= AP_NO_ERROR;
	size_t			len;
	char			*token			= NULL;
	char			*state			= NULL;

	*ip_match = FALSE;

	len = strlen (line);

	// remove '[' and ']' from section header line
	line [len - 1] = '\0';
	line ++;

	line = ap_str_trim_from_set (line, " \t");

	ap_debug ("(%s) Parsing ip list '%s'\n", ctx->client_ip, line);

	token = strtok_r (line, " \t", &state);

	while (token != NULL)
	{
		ap_debug ("(%s) Token '%s'\n", ctx->client_ip, token);

		rc = validate_ip (ctx, token, ip_match);
		if (rc != AP_NO_ERROR)
		{
			goto finish;
		}

		if (*ip_match == TRUE)
		{
			goto finish;
		}

		token = strtok_r (NULL, " \t", &state);
	}

finish:
	return rc;
}


static int parse_command (AP_CTX *ctx, char *line, BOOL *command_match)
{
	int			rc				= AP_NO_ERROR;
	const char	*invalid_chars	= ";{}|`()&";
	
	*command_match = FALSE;

	rc = ap_str_match (ctx->client_command, line, invalid_chars);
	if (rc != AP_NO_ERROR)
	{
		switch (rc)
		{
			case AP_ERROR_STR_INVALID_CHARS:
			{
				ap_debug ("(%s) Invalid characters '%s' in command '%s', not allowed in the substring matched by '*'\n", ctx->client_ip, invalid_chars, ctx->client_command);
				rc = AP_NO_ERROR;

				goto finish;

				break;
			}

			default:
			{
				ap_debug ("(%s) Command doesn't match\n", ctx->client_ip);

				rc = AP_NO_ERROR;

				goto finish;

				break;
			}
		}
	}

	ap_debug ("(%s) Command matched by config line '%s'\n", ctx->client_ip, line);
	*command_match = TRUE;
	
finish:
	return rc;
}


static int parse_config (AP_CTX *ctx, BOOL *ip_command_match)
{
	int				rc					= AP_NO_ERROR;
	char			buf[AP_STR_SIZE];
	size_t			len;
	char			*p					= NULL;
	BOOL			ip_match			= FALSE;
	BOOL			command_match		= FALSE;
	
	*ip_command_match = FALSE;

	while (fgets(buf, AP_STR_SIZE, ctx->config_file) != NULL)
	{
		p = ap_str_trim_head_from_set (buf, " \t");
		ap_str_trim_tail_from_set (p, " \t\r\n");
		ap_str_shrink_spaces (p);

		ap_debug ("(%s) Parsing line '%s'\n", ctx->client_ip, p);
		
		len = strlen (p);

		//skip comments and empty lines
		if ((p[0] == '#') || (p[0] == ';') || (len == 0)	||
			((p[0] == '[') && (p[len - 1] != ']'))			||
			((p[0] != '[') && (p[len - 1] == ']')))
		{
			continue;
		}

		if ((p[0] == '[') && (p[len - 1] == ']'))
		{
			ip_match = FALSE;

			rc = parse_ip_list (ctx, p, &ip_match);
			if (rc != AP_NO_ERROR)
			{
				goto finish;
			}

			continue;
		}
		
		if (ip_match)
		{
			rc = parse_command (ctx, p, &command_match);
			if (rc != AP_NO_ERROR)
			{
				goto finish;
			}

			if (command_match == TRUE)
			{
				*ip_command_match = TRUE;

				goto finish;
			}
		}
	}

finish:
	return rc;
}


static int run_command (AP_CTX *ctx, int *exit_code)
{
	int			rc			= AP_NO_ERROR;
	int			rc_os;

	if (ctx->simulate)
	{
		rc_os = 0;

		ap_allowed ("(%s) Successfully executed command '%s', exit code '%d'\n", ctx->client_ip, ctx->client_command, rc_os);

		*exit_code = rc_os;

		goto finish;
	}

	rc_os = system (ctx->client_command);
	switch (rc_os)
	{
		case -1:
		{
			ap_error ("(%s) Can not execute the shell for command '%s'\n", ctx->client_ip, ctx->client_command);
			rc = AP_ERROR_EXECUTE_COMMAND;

			goto finish;

			break;
		}

		default:
		{
#			if !defined (_WIN32)
			rc_os = WEXITSTATUS (rc_os);
#			endif

			if (rc_os == 127)
			{
				ap_error ("(%s) Can not execute command, shell was executed, but the command inside the shell wasn't '%s'\n", ctx->client_ip, ctx->client_command);
				rc = AP_ERROR_EXECUTE_COMMAND;

				goto finish;
			}
			else
			{
				ap_allowed ("(%s) Successfully executed command '%s', exit code '%d'\n", ctx->client_ip, ctx->client_command, rc_os);

				*exit_code = rc_os;
			}

			break;
		}
	}

finish:
	return rc;
}


int main (int argc, char *argv[])
{
	int				rc							= AP_NO_ERROR;
	AP_CTX			ctx;
	BOOL			ip_command_match			= FALSE;
	int				exit_code;
	BOOL			exit_code_set				= FALSE;
	
	if (argv == NULL)
	{
		fprintf (stdout, "Invalid argument: argv\n");
		rc = AP_ERROR_INVALID_ARGUMENT;

		goto finish;
	}

	memset (&ctx, 0, sizeof (AP_CTX));

	rc = init (&ctx, argc, argv);
	if (rc != AP_NO_ERROR)
	{	
		goto finish;
	}

	if (ap_log_get_level () == AP_LOG_LEVEL_TRACE)
	{
		print_environment (&ctx);
	}
	
	rc = parse_config (&ctx, &ip_command_match);
	if (rc != AP_NO_ERROR)
	{
		goto finish;
	}
	
	if (ip_command_match == TRUE)
	{
		rc = run_command (&ctx, &exit_code);
		if (rc != AP_NO_ERROR)
		{
			goto finish;
		}

		exit_code_set = TRUE;
	}
	else
	{
		ap_denied ("(%s) Is not allowed to execute command '%s'\n", ctx.client_ip, ctx.client_command);
		fprintf (stderr, "(%s) Is not allowed to execute command '%s'\n", ctx.client_ip, ctx.client_command);
	}
	
finish:
	if (rc == AP_NO_ERROR)
	{
		if (exit_code_set == TRUE)
		{
			rc = exit_code;
		}
	}
	else
	{
		if (rc == AP_ERROR_VERSION || rc == AP_ERROR_HELP)
		{
			rc = AP_NO_ERROR;
		}
		else
		{
			fprintf (stderr, "authprogs denied your access, please check the log on server (default: '~/.ssh/authprogs.log')\n");
		}
	}

	uninit (&ctx);

	return rc;
}


