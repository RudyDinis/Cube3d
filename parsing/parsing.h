#ifndef PARSING
# define PARSING

#include "../libft/libft.h"
#include <limits.h>

typedef struct s_id {
	char **id;
	char **done;
}	t_id;

int check_xpm(char *texture, char *ID);
int check_identifier(int fd, t_id *id);

#endif
