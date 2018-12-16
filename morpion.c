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
	var->choice = 0;
	var->game = 1;
}

void	ft_print_grid(t_morpion *var)
{
	ft_putchar(var->grid[0][0]);
	ft_putchar('|');
	ft_putchar(var->grid[0][1]);
	ft_putchar('|');
	ft_putchar(var->grid[0][2]);
	ft_putstr("\n-----\n");
	ft_putchar(var->grid[1][0]);
	ft_putchar('|');
	ft_putchar(var->grid[1][1]);
	ft_putchar('|');
	ft_putchar(var->grid[1][2]);
	ft_putstr("\n-----\n");
	ft_putchar(var->grid[2][0]);
	ft_putchar('|');
	ft_putchar(var->grid[2][1]);
	ft_putchar('|');
	ft_putchar(var->grid[2][2]);
	ft_putstr("\n\n");
}
/*
O|X|
-----
 | |
-----
 | |
*/

int	ft_end(t_morpion *var)
{
	if (var->grid[0][0] == var->grid[0][1] && var->grid[0][0] == var->grid[0][2] && var->grid[0][0] != ' ')
		return (1);
	if (var->grid[1][0] == var->grid[1][1] && var->grid[1][0] == var->grid[1][2] && var->grid[1][0] != ' ')
		return (1);
	if (var->grid[2][0] == var->grid[2][1] && var->grid[2][0] == var->grid[2][2] && var->grid[2][0] != ' ')
		return (1);
	if (var->grid[0][0] == var->grid[1][0] && var->grid[0][0] == var->grid[2][0] && var->grid[0][0] != ' ')
		return (1);
	if (var->grid[0][1] == var->grid[1][1] && var->grid[0][1] == var->grid[2][1] && var->grid[0][1] != ' ')
		return (1);
	if (var->grid[0][2] == var->grid[1][2] && var->grid[0][2] == var->grid[2][2] && var->grid[0][2] != ' ')
		return (1);
	if (var->grid[0][0] == var->grid[1][1] && var->grid[0][0] == var->grid[2][2] && var->grid[0][0] != ' ')
		return (1);
	if (var->grid[0][2] == var->grid[1][1] && var->grid[0][2] == var->grid[2][0] && var->grid[0][2] != ' ')
		return (1);
	return (0);
}

void	ft_AI_turn(t_morpion *var)
{
	
}

void	morpion(t_morpion *var)
{
	int firsttry;

	ft_print_grid(var);
	while (!(var->game = ft_end(var)))
	{
		var->turn = (var->turn == 'O' ? 'X' : 'O');
		if (var->turn == 'O')
		{
			firsttry = 1;
			while (firsttry == 1 ||
			var->grid[(var->choice - 1) / 3]
				[(var->choice - 1) % 3] != ' ')
			{
				firsttry = 1;
				while (var->choice < 1 || var->choice > 9 || firsttry == 1)
				{
					ft_putstr("Make your choose : ");
					firsttry = 0;
					get_next_line(1, &var->line);				//()
					var->choice = ft_atoi(var->line);
				}
			}
			var->grid[(var->choice - 1) / 3][(var->choice - 1) % 3] = 'O';	
		}
		else
		{
			ft_AI_turn(var);
			ft_putendl("AI has played :");
			ft_print_grid(var);
		}
	}
	if (var->turn == 'O')
		ft_print_grid(var);
	ft_putstr("Player win : ");
	ft_putchar(var->turn);
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
