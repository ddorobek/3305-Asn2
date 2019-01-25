/******************************************************************************
* 
* Name: 	Zaid Albirawi
* Email: 	zalbiraw@uwo.ca
*
* tokenize.c tokenizes the input lines. sperates commands by '<', '>' and '|'
*
******************************************************************************/

#include "tokenize.h"

void process_io_redirection_commands(short cmd, char *command_line,
	struct linked_list *command, int start, int other_start, int len)
{

	/**************************************************************************
	* find length of 
	**************************************************************************/
	if (other_start != -1 && other_start > start)
		len = other_start - start - 1;
	else len -= start;

	char *io_argument = trim(command_line + start, len);

	len = CMD_LENGTH + strlen(io_argument) + 1;

	/**************************************************************************
	* add cat/out/tee command to commands 
	**************************************************************************/
	char* value = malloc(len + 1);

	if (cmd == CAT_CMD) memcpy(value, CAT, CMD_LENGTH);
	else if (cmd == OUT_CMD) memcpy(value, OUT, CMD_LENGTH);
	else if (cmd == TEE_CMD) memcpy(value, TEE, CMD_LENGTH);

	memcpy(value + CMD_LENGTH, " ", 1);
	memcpy(value + CMD_LENGTH + 1, io_argument, len - CMD_LENGTH - 1);
	value[len] = '\0';

	command->value = (void*)value;

	free(io_argument);
}

struct linked_list* extract_command(char *command_line,
	struct linked_list *command, int len, int *number_of_commands, short last)
{

	int input_start = -1, input_len = -1, output_start = -1, output_len = -1,
		command_len = len;

	/**************************************************************************
	* find any IO redirections and only keep the last one; find command length
	* if there exsits an IO redirection
	**************************************************************************/
	for(int i = 0; i < len; ++i)
	{
		if (command_line[i] == INPUT_REDIRECTION ||
			command_line[i] == OUTPUT_REDIRECTION)
		{
			if(command_line[i] == INPUT_REDIRECTION) input_start = i + 1;
			if(command_line[i] == OUTPUT_REDIRECTION) output_start = i + 1;
			if(command_len == len) command_len = i - 1;
		}
	}

	/**************************************************************************
	* find length of input redirection and add command to commands 
	**************************************************************************/
	if (input_start != -1)
	{
		process_io_redirection_commands(CAT_CMD, command_line,
			command, input_start, output_start, len);

		command->next = init_linked_list();
		command = command->next;

		*number_of_commands += 1;
	}


	/**************************************************************************
	* add command to commands
	**************************************************************************/
	command->value = (void*)trim(command_line, command_len);

	if (!last || output_start != -1)
	{
		command->next = init_linked_list();
		command = command->next;
	}

	/**************************************************************************
	* find length of input redirection and add command to commands 
	**************************************************************************/
	if (output_start != -1)
	{
		if (!last)
		{
			process_io_redirection_commands(TEE_CMD, command_line, command,
				output_start, input_start, len);

			command->next = init_linked_list();
			command = command->next;
		} else 
			process_io_redirection_commands(OUT_CMD, command_line, command,
				output_start, input_start, len);

		*number_of_commands += 1;
	}

	return command;
}

char*** tokenize(char* command_line)
{
	int i = -1, j = 0,
		number_of_commands = 1;

	struct linked_list 
		*commands = init_linked_list(),
		*command = commands;

	/**************************************************************************
	* splits commands on pipes
	**************************************************************************/
	while (command_line[++i] != '\0')
	{
		if (command_line[i] == PIPE)
		{
			command = extract_command(command_line + j, command,
				i - j, &number_of_commands, FALSE);

			j = i + 1;
			++number_of_commands;
		}

	}
	/**************************************************************************
	* exctracts the last command
	**************************************************************************/
	extract_command(command_line + j, command, i - j,
		&number_of_commands, TRUE);

	return transform_linked_list_to_3d_char(commands, number_of_commands);
}
