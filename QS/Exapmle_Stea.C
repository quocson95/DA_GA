#include <ga/std_stream.h>
#include <ga/ga.h>
#include <math.h>

#define cout STD_COUT
#define cerr STD_CERR
#define endl STD_ENDL
#define ofstream STD_OFSTREAM

float Objective (GAGenome & ); //Caculator Fitness[i];

int main(int argc, char **argv) {
	cout << "This is Example GASteadyStateGA \n ";
	cout <<"This program try caculator MAX of F(x,y,z,t) = (3*sinx +cos(y) - 2cos(z)sin(t) + 1)/(2 - sinz + 2cos3t ) in rage [0:1000]\n";
	cout <<"Using 2DBinaryStringGenome and GASteadyStateGA and Roulette Wheel Selection\n";
	cout <<"This program is using OpenMP for parallel\n";
	//Using seed from terminal, if not, using system PID
	int seed = 0;
	for(int ii=1; ii<argc; ii++) {
	    if(strcmp(argv[ii++],"seed") == 0) {
	      seed = (unsigned int)atoi(argv[ii]);
	    }
	  }
	  GARandomSeed(seed);
	// Declare variables for the GA parameters and set them to some default values.
	  int width    = 4; //
	  int height   = 10;
	  int popsize  = 300000;
	  int ngen     = 40;
	  float pmut   = 0.01;
	  float pcross = 0.9;
	  GABin2DecPhenotype map;
	  for(int i=0; i<4; i++)
		  map.add(16, -100, 100);
	  GABin2DecGenome genome(map, Objective);
	  genome.initializer();
	  for (int i = 0; i < genome.nPhenotypes();i++){
	  		printf("genome.phenotype(%d)%f\n",i,genome.phenotype(i) );
	  	}
	  printf("\n");
	  GASimpleGA ga(genome);
	  ga.populationSize(popsize);
	  ga.nGenerations(ngen);
	  ga.pMutation(pmut);
	  ga.pCrossover(pcross);
	  ga.flushFrequency(100);
	  ga.evolve();
	  //Display Result---best fitness
	  cout << "The GA found:\n" << ga.statistics().bestIndividual() << "\n";
	 // That's it!
	  return 0;
}

//F(x,y,z,t) = (3*sinx +cos(y) - 2cos(z)sin(t) + 1)/(2 - sinz + 2cos3t)
float Objective(GAGenome & ge){
	GABin2DecGenome & genome = (GABin2DecGenome &) ge;
	static float tuso,mauso,score;
	static float x,y,z,t;
	x = genome.phenotype(0);
//	genome.gene()
	y = genome.phenotype(1);
	z = genome.phenotype(2);
	t = genome.phenotype(3);

	tuso = 3*sin(x) + cos(y) - 2*cos(z)*sin(t) + 1;
	mauso = 2 - sin(z) + 2*cos(3*t)+10;
	score = (float)(tuso/mauso);
	//cout << score<<"\n";
	if (score <0) score = 0;
	return score;
}

void
Initializer(GAGenome& g)
{
  GA1DArrayGenome<float>& genome = (GA1DArrayGenome<float>&)g;
  for (int i = 0; i < genome.length(); i ++ )
  genome.gene(i, GARandomFloat(00.0, 10000.0));
}
