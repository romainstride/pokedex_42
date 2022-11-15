/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstride <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:47:44 by rstride           #+#    #+#             */
/*   Updated: 2022/11/09 15:15:58 by rstride          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

struct poke
{
	char *name;
	char *type1;
	char *type2;
	char *hp;
	char *att;
	char *def;
	char *leg;
	char *descr;
};

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

char **create_db();
void free_db(char **data);
int	fill_db(struct poke *lst_pkm);
int	select_pkm(struct poke *data, int pkmn_nbr);
void print_pokemon(int n_pokemon);
void my_delay(int i);

void read_csv(int row, int col, char *filename, double **data);


int main(int argc, char const *argv[])
{
	int pkmn_nbr;
	char **pkm_db;
	int	nb_pkm;
	struct poke *lst_pkm;
	int nb_of_poke = 200;



	lst_pkm = malloc(sizeof(struct poke) * nb_of_poke);

	for (int i = 0; i < nb_of_poke; i++)
	{
		lst_pkm[i].name = malloc(sizeof(char) * 25);
		lst_pkm[i].type1 = malloc(sizeof(char) * 20);
		lst_pkm[i].type2 = malloc(sizeof(char) * 20);
		lst_pkm[i].hp = malloc(sizeof(char) * 4);
		lst_pkm[i].att = malloc(sizeof(char) * 4);
		lst_pkm[i].def = malloc(sizeof(char) * 4);
		lst_pkm[i].leg = malloc(sizeof(char) * 10);
		lst_pkm[i].descr = malloc(sizeof(char) * 400);
	}

	//compile_error();
	//logo(argv[1]);
	system("clear");
	write(1, "\n\t   Lecture de la base de donnees", 33);
	for (int i = 0; i < 3; i ++)
	{
		write(1, ".", 1);
		my_delay(1000);	//700
	}
	//pkm_db = create_db();
	
	nb_pkm = fill_db(lst_pkm);
	printf("\n");
	printf("\t     \033[1m%d\033[0m pokémons enregistrés\n\n\n", nb_pkm - 2);
	my_delay(2500);	//2000

	pkmn_nbr = 1;
	while (pkmn_nbr != 0)
	{
		system("clear");
		printf("\033[1m\n\t  *** Bienvenue sur le Pokedex ***\n\t    Entrez un numero de Pokemon\n\033[0m\t\t   > ");

		scanf("%d", &pkmn_nbr);
		//printf("%d", pkmn_nbr);
		system("clear");
		if (pkmn_nbr > 0 && pkmn_nbr <= 154)
		{
			select_pkm(lst_pkm, pkmn_nbr);
			if (pkmn_nbr <= 151)
			{
				char nbr[5];
				sprintf(nbr, "%d", pkmn_nbr);
				char cri[100] = "paplay voices/Cri_4_d_";
				if (pkmn_nbr < 10)
					strcat(cri, "00");
				else if (pkmn_nbr < 100)
					strcat(cri, "0");
				strcat(cri, nbr);
				strcat(cri, "*");
				//printf("%s", cri);
				system(cri);
			}
			printf("\n\t\t\t\tAppuyez sur entree pour continuer");
			getchar();
			getchar();
		}
	}
	//free_db(pkm_db);

	for (int i = 0; i < nb_of_poke - 1; i++)
	{
		free(lst_pkm[i].name);
		free(lst_pkm[i].type1);
		free(lst_pkm[i].type2);
		free(lst_pkm[i].hp);
		free(lst_pkm[i].att);
		free(lst_pkm[i].def);
		free(lst_pkm[i].leg);
		free(lst_pkm[i].descr);
	}
	free(lst_pkm);
	
	return 0;
}

void my_delay(int i)    /*Pause l'application pour i ms*/
{
    clock_t start,end;
    start=clock();
    while(((end=clock())-start)<=((i*CLOCKS_PER_SEC)/1000));
}
