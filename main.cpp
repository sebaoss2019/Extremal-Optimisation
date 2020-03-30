#include "fun.h"

using namespace std;

int main(int argc, char const *argv[])
{
	int iteraciones, semilla, capacidad, it = 0, cont, val;
	float Tau, w;
	vi items;
	solution local_solution;
	solution best_solution;


	cout<<"\nValor de la semilla: ";
	cin>>semilla;
	cout<<"\nIteraciones: ";
	cin>>iteraciones;
	cout<<"\nTau: ";
	cin>>Tau;

	srand(semilla);

	Leer_archivo();
	local_solution = genera_Sinicial();
	best_solution = local_solution;
	w = 0;
	printf("Solucion inicial: ");
	for (int j = 0; j < local_solution.solucion.size(); ++j)
	{
		if (local_solution.solucion[j]==1)
		{
			w += peso[j];
			printf("%d ",j+1);
		}
	}
	printf("\n");
	printf("valor: %d, peso: %.0f\n",local_solution.value,w);
	genera_Parray(Tau);
	
	Fitness F = ranking();

	while(it < iteraciones && local_solution.value!=S.value)
	{		
		printf("%d: \n", it);
		if (factible(local_solution))
		{
			w = 0;
			val = 0;
			local_solution = agregar_item(local_solution, F.infact_fitness);
			printf("Solucion local: ");
			for (int j = 0; j < local_solution.solucion.size(); ++j)
			{
				if (local_solution.solucion[j]==1)
				{
					val += valor[j];
					w += peso[j];
					printf("%d ",j+1);
				}
			}
			local_solution.value = val;
			printf("\n");
			printf("valor: %d, peso: %.0f\n",local_solution.value,w);
			
			if (local_solution.value > best_solution.value && factible(local_solution))
			{
				best_solution = local_solution;
			}
		}
		else{
			w=0;
			val=0;
			local_solution = quitar_item(local_solution, F.fact_fitness);
			printf("Solucion local: ");
			for (int j = 0; j < local_solution.solucion.size(); ++j)
			{
				if (local_solution.solucion[j]==1)
				{
					val += valor[j];
					w += peso[j];
					printf("%d ",j+1);
				}
			}
			local_solution.value = val;
			printf("\n");
			printf("valor: %d, peso: %.0f\n",local_solution.value,w);
			if (local_solution.value > best_solution.value && factible(local_solution))
			{
				best_solution = local_solution;
			}
		}

		if (local_solution.value == S.value)
		{
			printf("\nla Solucion se encontro en la iteracion %d\n", it+1);
		}
		it++;
	}
	
	w = 0;
	val = 0;
	printf("\nMejor Solucion\n");
	for (int i = 0; i < best_solution.solucion.size(); ++i)
	{
		if(best_solution.solucion[i] == 1){
			printf("%d, peso: %.0f, valor: %.0f\n",i+1,peso[i],valor[i]);
			w += peso[i];
			val += valor[i];
		} 
	}
	printf("mejor Z: %d - Peso: %.0f\n", val, w);
	return 0;
}
