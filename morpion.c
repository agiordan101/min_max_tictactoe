//IA pour un morpion en arbre

#include "libft.h"
#include <time.h>
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

void	init(t_morpion *var, t_AI *AI)
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
	AI->savegrid = NULL;
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
	//printf("CASES VIDES : %i\n", ft_n_empty(grid));
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

	//printf("Placement d'un symbole, n = %i, turn : %c\n", n, turn);
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
	*grid = NULL;
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
		{
			if (grid[i][j] == 'O' || grid[i][j] == 'X')
			{
				sign = (grid[i][j] == 'O' ? -1 : 1);
				if ((i == 0 && (j == 0 || j == 2)) || (i == 2 && (j == 0 || j == 2)))
					grade += 3 * sign;
				else if ((j == 1 && (i == 0 || i == 2)) || (i == 1 && (j == 0 || j == 2)))
					grade += 2 * sign;
				else
					grade += 5* sign;
				/*if (grid[i][j] == 'O')
				{
					//Test 2 align
					//Puis attribu le point selon le 3
				}*/
			}
			
		}
	}
	//printf("Final grade : %i\n", grade);
	//grade = 0;
	return (grade);
}

int	ft_previsions(t_morpion *var, char **grid, t_AI *AI, char turn)
{
	char	**savegrid;
	int	npos;
	int	sum;
	int	i;

	//printf("Debut recursive\n");
	turn = (turn == 'O' ? 'X' : 'O');
	AI->step++;
	npos = ft_n_empty(grid);
	savegrid = ft_gridcpy(grid);
	sum = 0;
	i = -1;
	if (AI->step == var->AI || npos == 0)
	{
		//printf("Map recu pour l'evaluation : \n");
		//ft_print_grid(var);
		sum = ft_eval(grid);
	}
	else
		while (++i < npos)
		{
			fill_i(&grid, i + 1, turn);
			if (ft_end(grid))
				sum += (turn == 'O' ?
				-10000 / (AI->step * AI->step * AI->step + 0.2) :
				10000 / (AI->step * AI->step * AI->step + 0.2));
			else
				sum += ft_previsions(var, grid, AI, turn);	
			//ft_griddel(&grid);
			grid = ft_gridcpy(savegrid);
		}
	AI->step--;
	//printf("Fin d'une recursive\n");
	return (sum);
}

void	ft_AI_turn(t_morpion *var, t_AI *AI)
{
	int	i;
	int	best;
	int	besti;

	//printf("Debut reflexion IA, savegrid : %p\n", AI->savegrid);
	if (AI->savegrid)
		ft_griddel(&AI->savegrid);	
	AI->savegrid = ft_gridcpy(var->grid);
	AI->step = -1;
	i = -1;
	while (++i < AI->nchoice)
	{
		//printf("Pos. numéro : %i\t-\tNiveau reflexion : %i\n", i + 1, AI->step);
		fill_i(&var->grid, i + 1, 'X');
		if (ft_end(var->grid))
			AI->choices[i] = 1000000; //!8/8 = 5040 simulations ~= 30.000 grade. 50.000 > 30.000
		else
			AI->choices[i] = ft_previsions(var, var->grid, AI, var->turn);
		if (AI->choices[i] > best || i == 0)
		{
			best = AI->choices[i];
			besti = i;
		}
		//printf("Score de la branche : %i\n", AI->choices[i]);
		ft_griddel(&var->grid);
		var->grid = ft_gridcpy(AI->savegrid);
	}
	//printf("Tout les scores : \n");
	i = -1;
	//while (++i < AI->nchoice)
		//printf("Cases n°%i : %i\n", i, AI->choices[i]);
	fill_i(&var->grid, besti + 1, 'X');
}

int	morpion(t_morpion *var, t_AI *AI, int mode)
{
	int firsttry;

	ft_print_grid(var);
	srand(time(NULL));
	var->turn = (random() % 2 ? 'X' : 'O');
	while (!(var->game = ft_end(var->grid)) && ft_n_empty(var->grid))
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
					firsttry = 0;
					if (mode == 1)
					{
						ft_putstr("Make your choose : ");
						get_next_line(1, &var->line);
						var->choice = ft_atoi(var->line);
					}
					else
						var->choice = random() % 10;
				}
			}
			var->grid[(var->choice - 1) / 3][(var->choice - 1) % 3] = 'O';	
		}
		else
		{
			//printf("Debut tour IA\n");
			AI->nchoice = ft_n_empty(var->grid);
			AI->choices = (int *)malloc(sizeof(int) * AI->nchoice);
			ft_AI_turn(var, AI);
			ft_putendl("AI has played :\n");
			ft_print_grid(var);
		}
	}
	if (var->turn == 'O')
		ft_print_grid(var);
	if (!ft_n_empty(var->grid) && !ft_end(var->grid))
		ft_putendl("Equality !");
	else
	{
		ft_putstr("Player win : ");
		ft_putstr(var->turn == 'O' ? "You" : "AI");
	}
	return (var->turn == 'O' ? 0 : 1);
}

int	main(int ac, char **av)
{
	t_morpion	var;
	t_AI		AI;
	int		i;
	int		pAI;
	int		prandom;

	pAI = 0;
	prandom = 0;
	i = -1;
	if (ac == 2 && ft_strlen(av[1]) == 1 && ((var.AI = av[1][0] - '0') == 0
	|| (var.AI = ft_atoi(av[1])) != 0) && var.AI >= 0 && var.AI <= 8)
	{	
		init(&var, &AI);
		pAI = morpion(&var, &AI, 1);
	}
	else if (ac == 3 && ft_strlen(av[1]) == 1 && ((var.AI = av[1][0] - '0') == 0
	|| (var.AI = ft_atoi(av[1])) != 0) && var.AI >= 0 && var.AI <= 8 && 
	ft_atoi(av[2]) != 0)
	{
		while (++i < ft_atoi(av[2]))
		{
			init(&var, &AI);
			if (morpion(&var, &AI, 2))
				pAI++;
			else
				prandom++;
			ft_putstr("\nPoints IA : ");
			ft_putnbr(pAI);
			ft_putstr("\nPoints random : ");
			ft_putnbr(prandom);
		}
	}
	else
		ft_putstr("usage: ./morpion_AI strenght_of_AI[0;5] [n_match]");
	ft_putchar('\n');
	return (0);
}


/*
			while (!ft_strequ(get_next_line(1, &var->line), "O")
			&& !ft_strequ(get_next_line(1, &var->line), "X"))
			{
				ft_putendl("");
			}*/
