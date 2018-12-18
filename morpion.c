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
	char	**savegrid;
	char	*line;
	int	size;
	int	AI;
	int	game;
	int	choice;
}		t_morpion;

typedef struct	s_AI
{
	int	step;
	int	nchoice;
	int	*choice;
}		t_AI;

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

int	ft_n_empty(char **grid)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = -1;
	while (grid[++i])
	{
		j = -1;
		while (grid[i][++j])
			if (grid[i][j] == ' ')
				count++;
	}
	return (count);
}

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

void	fill_i(t_morpion *var, int n, char player)
{
	int i;
	int j;
	int count;

	count = 1; 
	i = -1;
	while (var->grid[++i])
	{
		j = -1;
		while (var->grid[i][++j])
		{
			if (var->grid[i][j] == ' ' && count == n)
				var->grid[i][j] = player;
			else if (var->grid[i][j] == ' ')
				count++;
		}	
	}
}

int	ft_eval(t_morpion *var)
{

}

int	ft_previsions(t_morpion *var, char **grid, t_AI *AI, int choice)
{
	int	npos;
	int	sum;
	int	i;

	i = -1;
	sum = 0;
	npos = ft_n_empt(grid);
	AI->step++;
	while (++i < npos)
	{
		if (AI->step == var->AI)
			sum += ft_previsions(var, grid, AI, i);	
		else
			sum += ft_eval(var);
	}
	AI->step--;
	return (sum);
}

int	ft_AI_turn(t_morpion *var, t_AI *AI)
{
	int	i;

	i = -1;
	while (++i < AI->nchoice)
	{
		AI->step = 0;
		AI->savegrid 
		AI->choice[i] = previsions(var, var->grid, AI, i);
	}

}

void	morpion(t_morpion *var, t_AI *AI)
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
			AI->nchoice = ft_n_empty(var->grid);
			AI->choice = (int *)malloc(sizeof(int) * AI->pos);
			ft_AI_turn(var, AI);
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
	t_AI		AI;
	float		rand;

	if (ac == 2 && (var.AI = ft_atoi(av[1])) != 0 &&
	var.AI >= 1 && var.AI <= 5)
	{
		init(&var);
		var.turn = (random() % 2 ? 'X' : 'O');
		morpion(&var, &AI);
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
