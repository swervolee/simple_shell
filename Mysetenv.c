#include "shell.h"

/*int set_env(const char *name, const char *value, int overwrite, SHELL *shell_s)
{
	size_t name_len = 0, value_len = 0, len, env_name_len;
	const char *name_ptr = name, *value_ptr = value;
	char *temp, *temp_ptr, **environ_ptr, *env_var, **new_environ;
	int env_count, result;

	if (!name || !value)
		return -1;
	if (overwrite || getenv(name) == NULL)
	{
		while (*name_ptr++)
			name_len++;
		while (*value_ptr++)
			value_len++;
		len = name_len + value_len + 2;
		temp = (char *)malloc(len);
		if (!temp)
			return -1;
		temp_ptr = temp;
		while (*name)
			*temp_ptr++ = *name++;
		*temp_ptr++ = '=';
		while (*value)
			*temp_ptr++ = *value++;
		*temp_ptr = '\0';
		environ_ptr = shell_s->_environ;
		env_var = *environ_ptr;
		env_name_len = name_len;

		while (env_var)
		{
			env_name_len = Strlen(env_var);
			if (strncmp(env_var, name, env_name_len) == 0 && env_var[env_name_len] == '=')
			{
				if (overwrite)
				{
					free(*environ_ptr);
					*environ_ptr = temp;
					result = 0;
				}
				else
					result = -1;
				break;
			}
			environ_ptr++;
			env_var = *environ_ptr;
		}
		if (!env_var)
		{
			env_count = 0;
			while (*environ_ptr++)
				env_count++;
			new_environ = (char **)malloc((env_count + 2) * sizeof(char *));
			if (!new_environ)
			{
				free(temp);
				return -1;
			}
			memcpy(new_environ, environ, env_count * sizeof(char *));
			new_environ[env_count] = temp;
			new_environ[env_count + 1] = NULL;
			environ = new_environ;
			result = 0;
		}
	}
	else
		result = 0;
		
	return result;
}*/


int set_env(const char *name, const char *value, int overwrite, SHELL *shell_s __attribute__((unused)))
{
	char *existing_value;
	int result;

	if (!name || !value)
		return -1;
	existing_value = getenv(name);
	if (existing_value && !overwrite)
		return 0;
	result = setenv(name, value, 1);
	return result;
}
