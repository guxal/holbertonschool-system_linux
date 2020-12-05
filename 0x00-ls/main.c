#include "hls.h"


/**
 * setOptions - setter options to struct
 * @option: struct options
 * @param: char params
 * Return: (Not Return)
 */
void setOptions(option_t *option, char *param)
{
	while (*++param)
	{
		switch (*param)
		{
			case '1':
				/* code */
				option->vertical = 1;
				break;

			case 'a':
				option->hidden = 1;
				break;

			case 'A':
				option->fullhidden = 1;
				break;

			default:
				/**error mal parametro */
				fprintf(stderr, "hls: invalid option -- '%c'\n", *param);
				fprintf(stderr, "Try '%s --help' for more information.\n", "ls");
				exit(2);
				break;
		}
	}
}

/**
 * main - Entry point
 * @argc: count arg
 * @argv: array arg
 * Return: Always 0 (Success)
 */
int main(int argc, char *argv[])
{
	option_t options = OPTION_INIT;
	printdata_t *printdata = NULL;

	int result = 0, tmp = 0, inc = 1;
	int count_listfile = 0;
	int count_listdir = 0;

	printdata = _salloc(1, sizeof(printdata_t));
	if (printdata == NULL)
		return (2);

	while (inc != argc)
	{
		tmp = 0;
		if (argv[inc][0] == '-' && argv[inc][1] != 0)
			setOptions(&options, argv[inc]);
		else
			tmp = buildNodes(argv[inc], printdata);
		if (tmp != 0)
			result = tmp;
		inc++;
	}

	if (result == 2)
		printdata->countdir++;

	/*print lists */
	count_listfile = print_list_file(printdata->listfile, &options);
	count_listdir = print_list_dir(printdata->listdir, printdata, &options);
	if (count_listfile == 0 && count_listdir == 0 && result != 2)
	{
		result = buildNodes(".", printdata);
		print_list_dir(printdata->listdir, printdata, &options);
	}
	free_lists(printdata->listdir, printdata->listfile);
	free(printdata);
	return (result);
}
