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
	int	choice;
	int	size;
	int	AI;
	int	game;
}		t_morpion;

typedef struct	s_AI
{
	int	step;
	int	nchoice;
	int	*choices;
	char	**savegrid;
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

int	ft_end(char **grid)
{
	if (grid[0][0] == grid[0][1] && grid[0][0] == grid[0][2] && grid[0][0] != ' ')
		return (1);
	if (grid[1][0] == grid[1][1] && grid[1][0] == grid[1][2] && grid[1][0] != ' ')
		return (1);
	if (grid[2][0] == grid[2][1] && grid[2][0] == grid[2][2] && grid[2][0] != ' ')
		return (1);
	if (grid[0][0] == grid[1][0] && grid[0][0] == grid[2][0] && grid[0][0] != ' ')
		return (1);
	if (grid[0][1] == grid[1][1] && grid[0][1] == grid[2][1] && grid[0][1] != ' ')
		return (1);
	if (grid[0][2] == grid[1][2] && grid[0][2] == grid[2][2] && grid[0][2] != ' ')
		return (1);
	if (grid[0][0] == grid[1][1] && grid[0][0] == grid[2][2] && grid[0][0] != ' ')
		return (1);
	if (grid[0][2] == grid[1][1] && grid[0][2] == grid[2][0] && grid[0][2] != ' ')
		return (1);
	return (0);
}

void	fill_i(char ***grid, int n, char turn)
{
	int i;
	int j;
	int count;

	printf("Placement d'un symbole, n = %i, turn : %c\n", n, turn);
	count = 1; 
	i = -1;
	while ((*grid)[++i])
	{
		j = -1;
		while ((*grid)[i][++j])
			if ((*grid)[i][j] == ' ')
			{
				if (count == n)
					(*grid)[i][j] = turn;
				count++;		
			}
	}
}

char	**ft_gridcpy(char **grid)
{
	char	**savegrid;
	int	i;

	savegrid = (char **)malloc(sizeof(char *) * (3 + 1));
	savegrid[3] = NULL;
	i = -1;
	while (++i < 3)
	{
		savegrid[i] = ft_strnew(3);
		ft_strcpy(savegrid[i], grid[i]);
	}
	return (savegrid);
}

void	ft_griddel(char ***grid)
{
	int	i;

	i = -1;
	while (++i < 3)
		ft_strdel(*grid + i);
	free(*grid);
	grid = NULL;
}

int	ft_eval(char **grid)
{
	int	grade;
	int	sign;
	int	i;
	int	j;

	grade = 0;
	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
			if (grid[i][j] == 'O' || grid[i][j] == 'X')
			{
				sign = (grid[i][j] == 'O' ? -1 : 1);
				if ((i == 0 && (j == 0 || j == 2)) || (i == 2 && (j == 0 || j == 2)))
					grade += 3 * sign;
				else if ((j == 1 && (i == 0 || i == 2)) || (i == 1 && (j == 0 || j == 2)))
					grade += 2 * sign;
				else
					grade += 5* sign;
			}
	}
	printf("Final grade : %i\n", grade);
	return (grade);
}

int	ft_previsions(t_morpion *var, char **grid, t_AI *AI, char turn)
{
	char	**savegrid;
	int	npos;
	int	sum;
	int	i;

	printf("Debut recursive\n");
	turn = (turn == 'O' ? 'X' : 'O');
	AI->step++;
	npos = ft_n_empty(grid);
	savegrid = ft_gridcpy(grid);
	sum = 0;
	i = -1;
	if (AI->step == var->AI)
	{
		printf("Map recu pour l'evaluation : \n");
		ft_print_grid(var);
		sum = ft_eval(grid);
	}
	else
		while (++i < npos)
		{
			printf("Nouvelle posibilite\n");
			fill_i(&grid, i, turn);
			if (ft_end(grid))
				sum += (turn == 'O' ? -50 : 50);
			else
				sum += ft_previsions(var, grid, AI, turn);	
			ft_griddel(&grid);
			grid = ft_gridcpy(savegrid);
		}
	AI->step--;
	printf("Fin d'une recursive\n");
	return (sum);
}

void	ft_AI_turn(t_morpion *var, t_AI *AI)
{
	int	i;
	int	best;
	int	besti;

	printf("Debut reflexion IA\n");
	if (AI->savegrid)
		ft_griddel(&AI->savegrid);	
	AI->savegrid = ft_gridcpy(var->grid);
	AI->step = -1;
	best = -50;
	i = -1;
	while (++i < AI->nchoice)
	{
		printf("Pos. numéro : %i\t-\tNiveau reflexion : %i\n", i, AI->step);
		fill_i(&var->grid, i + 1, 'X');
		if (ft_end(var->grid))
			AI->choices[i] = 50;
		else
			AI->choices[i] = ft_previsions(var, var->grid, AI, var->turn);
		if (AI->choices[i] > best)
		{
			best = AI->choices[i];
			besti = i;
			printf("Best case : %i\n", besti + 1);
		}
		printf("Score de la branche : %i\n", AI->choices[i]);
		ft_griddel(&var->grid);
		var->grid = ft_gridcpy(AI->savegrid);
	}
	printf("Best case : %i\n", besti + 1);
	fill_i(&var->grid, besti + 1, 'X');
}

void	morpion(t_morpion *var, t_AI *AI)
{
	int firsttry;

	ft_print_grid(var);
	while (!(var->game = ft_end(var->grid)))
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
			printf("Debut tour IA\n");
			AI->nchoice = ft_n_empty(var->grid);
			AI->choices = (int *)malloc(sizeof(int) * AI->nchoice);
			ft_AI_turn(var, AI);
			ft_putendl("AI has played :\n");
			ft_print_grid(var);
		}
	}
	if (var->turn == 'O')
		ft_print_grid(var);
	ft_putstr("Player win : ");
	ft_putstr(var->turn == 'O' ? "You" : "AI");
}

void	ft_test()
{
	char **tab;
	char **savetab;
	int i = -1;

	tab = (char **)malloc(sizeof(char *) * 4);
	tab[0] = ft_strdup(" O ");
	tab[1] = ft_strdup("O O");
	tab[2] = ft_strdup(" O ");
	tab[3] = NULL;
	while (++i < 3)
		printf("%s\n", tab[i]);
	
	savetab = ft_gridcpy(tab);
	
	tab[1][1] = 'X';

	i = -1;
	while (++i < 3)
		printf("%s\n", tab[i]);
	
	ft_griddel(&tab);
	tab = ft_gridcpy(savetab);

	fill_i(&tab, 2, 'A');
	i = -1;
	while (++i < 3)
		printf("%s\n", tab[i]);
}

int	main(int ac, char **av)
{
	t_morpion	var;
	t_AI		AI;
	
	//ft_test();
	//return (0);
	if (ac == 2 && ft_strlen(av[1]) == 1 && ((var.AI = av[1][0] - '0') == 0
	|| (var.AI = ft_atoi(av[1])) != 0) && var.AI >= 0 && var.AI <= 5)
	{
		init(&var);
		var.turn = (random() % 2 ? 'X' : 'O');
		morpion(&var, &AI);
	}
	else
		ft_putstr("usage: ./morpion_AI strenght_of_AI[0;5]");
	ft_putchar('\n');
	return (0);
}


/*
			while (!ft_strequ(get_next_line(1, &var->line), "O")
			&& !ft_strequ(get_next_line(1, &var->line), "X"))
			{
				ft_putendl("");
			}*/
