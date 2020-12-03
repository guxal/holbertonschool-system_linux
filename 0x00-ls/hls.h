#ifndef _HLS_H_
#define _HLS_H_
/*--- C libs ---*/
#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>

/**
 * struct Option - Options send for user
 * @vertical: is vertical options
 * @hidden: show hidden files
 */
typedef struct Option
{
	int vertical;
	int hidden;
	int fullhidden;

} Option;

#define OPTION_INIT {0, 0, 0}

#endif
