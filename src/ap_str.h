#ifndef _AP_STR_UTIL_H_
#define _AP_STR_UTIL_H_


#include <stdlib.h>


char *	ap_str_trim_head_from_set			(char *str, const char *set);
char *	ap_str_trim_tail_from_set			(char *str, const char *set);
char *	ap_str_trim_from_set				(char *str, const char *set);
char *	ap_str_skip_word					(char *str);
int		ap_str_to_hex						(const char *str, char **hex_str);
char *	ap_str_find_first_char_from_set		(char *str, const char *set);
char *	ap_str_shrink_spaces				(char *str);
size_t	ap_str_strlcpy						(char *dst, const char *src, size_t size);
size_t	ap_str_strlcat						(char *dst, const char *src, size_t size);
int		ap_str_match						(char *str, const char *pattern, const char *invalid_chars);


#endif
