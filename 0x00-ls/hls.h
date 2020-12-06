#ifndef _HLS_H_
#define _HLS_H_
/*--- C libs ---*/
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>

/**
 * struct option_s - Options send for user
 * @vertical: is vertical options
 * @hidden: show hidden files
 * @fullhidden: do not list implied . and ..
 */
typedef struct option_s
{
	int vertical;
	int hidden;
	int fullhidden;

} option_t;

typedef struct dirent read_t;

/**
 * struct listdir_s - list of directories with paths
 * @path: path
 * @dir: directory pointer
 * @next: points to the next node
 */
typedef struct listdir_s
{
	char *path;
	DIR *dir;
	struct listdir_s *next;
} listdir_t;

/**
 * struct listfile_s - list of files
 * @file: name of file
 * @next: points to the next node
 */
typedef struct listfile_s
{
	char *file;
	struct listfile_s *next;
} listfile_t;

/**
 * struct printdata_s - printdata struct
 * @listdir: is vertical options
 * @listfile: show hidden files
 * @countdir: counter of dir
 * @countfile: counter of file
 * @result: counter of result
 * @next: points to the next node
 */
typedef struct printdata_s
{
	listdir_t *listdir;
	listfile_t *listfile;
	int countdir;
	int countfile;
	int result;
	struct printdata_s *next;
} printdata_t;

#define OPTION_INIT {0, 0, 0}

/* nodes */
listfile_t *add_node_listfile(listfile_t **head, const char *file);
listdir_t *add_node_listdir(listdir_t **head, DIR *dir, const char *path);
unsigned int buildNodes(char *p, printdata_t *printdata);

/* print lists */
int print_list_dir(const listdir_t *h, printdata_t *printdata,
	option_t *options);
int print_list_file(const listfile_t *h, option_t *options);

/* error */
unsigned int ErrorHandler(char *path);

/* lib */
char *_strdup(const char *str);
void *_salloc(unsigned int nmemb, unsigned int size);

/* free */
void free_lists(listdir_t *listdir_head, listfile_t *listfile_head);

#endif
