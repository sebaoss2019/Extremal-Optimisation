#include <bits/stdc++.h>
#include <cstring>

using namespace std;

typedef vector <int> vi;
typedef vector <float> vf;
typedef long long int lli;
typedef pair <float,int> fi;
typedef vector<fi> vfi;

struct f
{
	vf fact_fitness;
	vf infact_fitness;
};

struct sol
{
	int value; 
	vi solucion; 
};

typedef struct f Fitness;
typedef struct sol solution;

lli capacidad;
vf peso;
vf valor;
vi answer;
vf prob_seleccion;

solution S;

void Leer_archivo()
{
	int pos, items, it=0, s;
	float time, val, p;
	char sentence [30], texto[30], str [30];
  	char a, b, c;

	//abriendo archivo de texto
	FILE *f;
	f = fopen("knapPI_1_50_1000.txt","r");
	while(feof(f) == 0)					//Lectura del archivo
	{
		fgets(sentence,30,f);
		if (it == 0){
			strcpy(texto,sentence);
			
		}
		if (it == 1){
			sscanf (sentence,"%s %d",str,&items);
		
		}
		else if (it == 2){
			sscanf (sentence,"%s %lld",str,&capacidad);
			cout<<"C: "<<capacidad<<endl;
		}
		else if (it == 3){
			sscanf (sentence,"%s %d",str,&S.value);
			cout<<"Z: "<<S.value<<endl;
		}
		else if (it == 4)
		{
			sscanf (sentence,"%s %f",str,&time);
			printf("time: %.2f\n",time );
		}
		else if(it > 4 && it < items+5)
		{
			sscanf(sentence,"%d %c %f  %c %f %c %d",&pos,&a,&val,&b,&p,&c,&s);
			
			peso.push_back(p);
			valor.push_back(val);
			S.solucion.push_back(s);
		}
		it++;
	}
}

solution genera_Sinicial()
{
	vfi si;
	lli cap = 0;
	solution answer;
	answer.solucion.resize(peso.size(),0);
	answer.value = 0;

	for (int i = 0; i < peso.size(); ++i)
	{
		si.push_back(make_pair(peso[i],i));
	}
	sort(si.begin(), si.end());
	for (int i = 0; i < si.size(); ++i)
	{
		if (cap+si[i].first <= capacidad)
		{
			answer.solucion[si[i].second] = 1;
			cap += si[i].first;
			answer.value += valor[si[i].second];
		}
		
	}
	
	return answer;
}

void genera_Parray(float tau)
{
	float prob;

	for (int i = 0; i < peso.size(); ++i)
	{
		prob = pow(i+1,-tau);
		prob_seleccion.push_back(prob);
	}
}

//Fitness factible e infactible
Fitness ranking()
{
	Fitness fit;
	float rank;

	for (int i = 0; i < peso.size(); ++i)
	{
		rank = peso[i]/valor[i];
		fit.fact_fitness.push_back(rank); 
		rank = valor[i]/peso[i];
		fit.infact_fitness.push_back(rank); 
	}
	return fit;
}

//selecct item por ruleta
int ruleta(vi v, vf rank, bool fact)
{
	int pos;
	vfi rankeo;
	vf roulette;

	float total = 0, proporcion, num, prob;

	for (int i = 0; i < rank.size(); ++i)
	{
		if (fact)
		{
			if (v[i] == 0)
			{
				rankeo.push_back(make_pair(rank[i],i));
			}
		}
		else{
			if (v[i] == 1)
			{
				rankeo.push_back(make_pair(rank[i],i));
			}
		}
	}
	

	sort(rankeo.rbegin(), rankeo.rend());
	roulette.resize(rankeo.size(),0);
	
	for (int i = 0; i < rankeo.size(); ++i)
	{
		total += prob_seleccion[i];
	}

	for (int i = 0; i < roulette.size(); ++i)
	{
		if (i == 0)
		{
			roulette[i] = (prob_seleccion[i] / total);
		}
		else{
			roulette[i] = (prob_seleccion[i] / total) + roulette[i-1];
		}
	}

	num = 1+rand()%100;
	prob = num+rand()%((int)num+50);
	prob = num/prob;
	

	for (int i = 0; i < roulette.size(); ++i)
	{
		if (prob > roulette[i])
		{
			pos = i;
		
		}
		else if(i == 0){
			pos = 0;
		}
	}

	
	if (pos == roulette.size()-1 || pos == 0)
	{
		pos = rankeo[pos].second;
	}
	else{
		pos = rankeo[pos+1].second;
	}
	roulette.clear();
	rankeo.clear();
	return pos;
}

bool factible(solution local_solution)
{
	lli weight = 0;
	
	for (int i = 0; i < local_solution.solucion.size(); ++i)
	{
		if (local_solution.solucion[i] == 1)
		{
			
			weight += peso[i];
		}
	}
	if (weight <= capacidad)
	{
		return true;
	}
	else{
		return false;
	}
}

solution agregar_item(solution &solve, vf fit)
{
	int j = ruleta(solve.solucion, fit, true);
	solve.solucion[j] = 1;
	return solve; 
}

solution quitar_item(solution &solve, vf fit)
{
	int j = ruleta(solve.solucion, fit, false);
	solve.solucion[j] = 0;
	return solve; 
}
