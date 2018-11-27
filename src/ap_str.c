#include <string.h>
#include <stdlib.h>

#include "ap.h"
#include "ap_defs.h"
#include "ap_str.h"


char * ap_str_trim_head_from_set (char *str, const char *set)
{
	size_t			str_len;
	size_t			set_len;
	size_t			i;
	size_t			j;
	char			*p				= NULL;
	unsigned int	found			= 0;

	if (str == NULL || set == NULL)
	{
		goto finish;
	}

	str_len = strlen (str);
	set_len = strlen (set);

	if (str_len == 0 || set_len == 0)
	{
		goto finish;
	}

	p = str;

	for (i = 0; i < str_len; i ++)
	{
		found = 0;

		for (j = 0; j < set_len; j ++)
		{
			if (str[i] == set[j])
			{
				found = 1;
				p ++;

				break;
			}
		}

		if (found == 0)
		{
			break;
		}
	}

	if (p > str)
	{
		str_len = strlen (p);
		memmove (str, p, str_len + 1);
	}

finish:
	return str;
}


char * ap_str_trim_tail_from_set (char *str, const char *set)
{
	size_t			str_len;
	size_t			set_len;
	size_t			j;
	char			*p				= NULL;
	unsigned int	found			= 0;

	if (str == NULL || set == NULL)
	{
		goto finish;
	}

	str_len = strlen (str);
	set_len = strlen (set);

	if (str_len == 0 || set_len == 0)
	{
		goto finish;
	}

	p = str + str_len - 1;

	while (p >= str)
	{
		found = 0;

		for (j = 0; j < set_len; j ++)
		{
			if (*p == set[j])
			{
				found = 1;
				p --;

				break;
			}
		}

		if (found == 0)
		{
			break;
		}
	}

	p ++;

	*p = '\0';

finish:
	return str;
}


char * ap_str_trim_from_set (char *str, const char *set)
{
	if (str == NULL || set == NULL)
	{
		goto finish;
	}

	str = ap_str_trim_head_from_set (str, set);
	str = ap_str_trim_tail_from_set (str, set);

finish:
	return str;
}


char * ap_str_skip_word (char *str)
{
	if (str == NULL)
	{
		goto finish;
	}

	for (; *str != ' ' && *str != '\t' && *str != '\0'; str ++);

finish:
	return str;
}


int ap_str_to_hex (const char *str, char **hex_str)
{
	static unsigned char hex_tab[16] = "0123456789ABCDEF";

	int		rc			= AP_NO_ERROR;
	char	*s			= NULL;
	size_t	str_len;
	size_t	i;

	str_len = strlen (str);

	s = malloc (str_len * 2 + 1);
	if (s == NULL)
	{
		rc = AP_ERROR_NO_MEMORY;

		goto finish;
	}

	for (i = 0; i < str_len; i ++)
	{
		s[i * 2] = hex_tab[str[i] >> 4];
		s[i * 2 + 1] = hex_tab[str[i] & 0x0F];
	}

	s[str_len * 2] = '\0';

	*hex_str = s;

finish:
	return rc;
}


char * ap_str_find_first_char_from_set (char *str, const char *set)
{
	size_t str_len;
	size_t set_len;
	size_t i;
	size_t j;

	str_len = strlen (str);
	set_len = strlen (set);

	for (i = 0; i < str_len; i ++)
	{
		for (j = 0; j < set_len; j ++)
		{
			if (str[i] == set[j])
			{
				return str + i;
			}
		}
	}

	return NULL;
}


char * ap_str_shrink_spaces (char *str)
{
	size_t seg_len = 0;
	size_t str_len = strlen (str);

	char *pos = ap_str_find_first_char_from_set (str, "\t ");
	if (pos == NULL)
	{
		goto finish;
	}

	seg_len = strspn (pos, "\t ");
	if (seg_len > 1)
	{
		memmove (pos + 1, pos + seg_len, str_len + str - pos - seg_len + 1);

		ap_str_shrink_spaces (pos + 1);
	}

finish:
	return str;
}


size_t ap_str_strlcpy (char *dst, const char *src, size_t size)
{
	char		*d		= dst;
	const char	*s		= src;
	size_t		n		= size;

	/* Copy as many bytes as will fit */
	if (n != 0)
	{
		while (--n != 0)
		{
			if ((*d++ = *s++) == '\0')
			{
				break;
			}
		}
	}

	/* Not enough room in dst, add NUL and traverse rest of src */
	if (n == 0)
	{
		if (size != 0)
		{
			*d = '\0'; /* NUL-terminate dst */
		}
		
		while (*s++);
	}

	return(s - src - 1); /* count does not include NUL */
}


size_t ap_str_strlcat (char *dst, const char *src, size_t size)
{
	char		*d		= dst;
	const char	*s		= src;
	size_t		n		= size;
	size_t		dlen;

	/* Find the end of dst and adjust bytes left but don't go past end */
	while (n-- != 0 && *d != '\0')
	{
		d++;
	}

	dlen = d - dst;
	n = size - dlen;

	if (n == 0)
	{
		return (dlen + strlen (s));
	}
	
	while (*s != '\0')
	{
		if (n != 1)
		{
			*d++ = *s;
			n--;
		}
		
		s++;
	}
	
	*d = '\0';

	return (dlen + (s - src)); /* count does not include NUL */
}


static BOOL check_if_invalid_char (char c, const char *invalid_chars)
{
	const char *pos = NULL;

	for (pos = invalid_chars; *pos != '\0'; pos++)
	{
		if (c == *pos)
		{
			return TRUE;
		}
	}

	return FALSE;
}


int ap_str_match (char *str, const char *pattern, const char *invalid_chars)
{
#	define		EOS			'\0'

	int			rc			= AP_NO_ERROR;
	char		c;
	char		test;

	if (str == NULL || pattern == NULL)
	{
		rc = AP_ERROR_INVALID_ARGUMENT;

		goto finish;
	}

	for ( ; ; )
	{
		switch (c = *pattern++)
		{
			case EOS:
			{
				if (*str == EOS)
				{
					rc = AP_NO_ERROR;
				}
				else
				{
					rc = AP_ERROR_STR_NO_MATCH;
				}

				goto finish;

				break;
			}

			case '?':
			{
				if (*str == EOS)
				{
					rc = AP_ERROR_STR_NO_MATCH;

					goto finish;
				}

				if (check_if_invalid_char (*str, invalid_chars) == TRUE)
				{
					rc = AP_ERROR_STR_INVALID_CHARS;

					goto finish;
				}
				
				str++;

				break;
			}

			case '*':
			{
				c = *pattern;

				// Multiple *
				while (c == '*')
				{
					pattern++;
					c = *pattern;
				}

				if (c == EOS)
				{
					if (ap_str_find_first_char_from_set (str, invalid_chars) != NULL)
					{
						rc = AP_ERROR_STR_INVALID_CHARS;

						goto finish;
					}

					rc = AP_NO_ERROR;

					goto finish;
				}

				while ((test = *str) != EOS)
				{
					if (check_if_invalid_char (*str, invalid_chars) == TRUE)
					{
						rc = AP_ERROR_STR_INVALID_CHARS;

						goto finish;
					}

					rc = ap_str_match (str, pattern, invalid_chars);
					if (rc == AP_NO_ERROR)
					{
						goto finish;
					}

					str++;
				}

				rc = AP_ERROR_STR_NO_MATCH;

				goto finish;

				break;
			}

			default:
			{
				if (c == *str)
				{
				}
				else
				{
					rc = AP_ERROR_STR_NO_MATCH;

					goto finish;
				}

				str++;

				break;
			}
		}
	}

	// should not reach
	rc = AP_ERROR_STR_NO_MATCH;

finish:
	return rc;
}