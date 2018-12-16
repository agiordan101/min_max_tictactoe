//IA pour un morpion en arbre

#include "libft/libft.h"
#include <stdio.h>

/*# define TRUE 1
# define FALSE 0
typedef	int	boolean;*/

typedef struct	s_morpion
{
	char	turn;
	char	**grid;
	char	*line;
	int	size;
	int	AI;
	int	game;
	int	choice;
}		t_morpion;

void	init(t_morpion *var)
{
	int	i;
	
	var->size = 3;
	var->grid = (char **)malloc(sizeof(char *) * (var->size + 1));
	i = -1;
	while (++i < var->size)
	{
		var->grid[i] = ft_strnew(var->size);
		ft_strfill(var->grid[i], ' ', var->size);
	}
	var->grid[var->size] = NULL;
	var->line = NULL;
	var->choice = 6;
	var->game = 1;
}

int	ft_end(t_morpion *var)
{
	if (var->grid[0][0] == var->grid[0][1] == var->grid[0][2])
		return (1);
	return (0)
}

void	ft_AI_turn(t_morpion *var)
{

}

void	morpion(t_morpion *var)
{
	//var->turn = 'O';
	while (game)
	{
		var->turn = (var->player == 'O' ? 'X' : 'O');
		if (var->turn == 'O')
		{
			while (var->choice >= 0 && var->choice <= 9 &&
			var->grid[var->choice / 3][var->choice % 3] != ' ')
			{
				ft_putstr("Make your choose : ");
				get_next_line(1, &var->line);				//()
				var->choice = ft_atoi(var->line);
			}
			var->grid[var->choice / 3][var->choice % 3] = 'O';	
		}
		else
		{
		}
		game = ft_end(var);
	}
}

int	main(int ac, char **av)
{
	t_morpion	var;
	float		rand;

	if (ac == 2 && (var.AI = ft_atoi(av[1])) != 0 &&
	var.AI >= 1 && var.AI <= 5)
	{
		init(&var);
		var.turn = (random() % 2 ? 'X' : 'O');
		morpion(&var);
		printf("%i\n", var.game);
	}
	else
		ft_putstr("usage: ./morpion_AI strenght_of_AI[1;5]");
	ft_putchar('\n');
	return (0);
}
/*
			while (!ft_strequ(get_next_line(1, &var->line), "O")
			&& !ft_strequ(get_next_line(1, &var->line), "X"))
			{
				ft_putendl("");
			}*/
