#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void initial();
void gotest();

const double duration = 10;
const double t0 = .00001;
const double G = 1;

typedef struct thing {
	double mass;
	double vector[3]; 
	double pos[3];
} thing; thing things[3];

typedef struct force {
	double strength;
} force; force F01, F02, F12;

double poslen(struct thing th1, struct thing th2) {
	double len = 0;
	len = sqrt(pow(th1.pos[0] - th2.pos[0], 2) + pow(th1.pos[1] - th2.pos[1], 2) + pow(th1.pos[2] - th2.pos[2], 2));
	if (len == 0)
		len = 0.00001;
	return len;
}

double speed(struct thing th) {
	double spd = .0;
	spd = sqrt(pow(th.vector[0], 2) + pow(th.vector[1], 2) + pow(th.vector[2], 2));
	return .0;
}

double forceSum(struct thing th1, struct thing th2) {
	double val = .0;
	val = G * th1.mass * th2.mass / pow(poslen(th1, th2), 2);
	return val;
}

// tmp
double getS() {
	return things[1].vector[0] * things[1].vector[0] + things[1].vector[1] * things[1].vector[1] + things[1].vector[2] * things[1].vector[2];
}


void initial() {
	FILE *fp1 = fopen("mass1.txt", "r");

	//things[0].mass = 10.0;
	fscanf(fp1, "%lf\n", &things[0].mass);
	//things[0].pos[0] = 0; things[0].pos[1] = 0, things[0].pos[2] = 0;
	fscanf(fp1, "%lf %lf %lf\n", &things[0].pos[0], &things[0].pos[1], &things[0].pos[2]);
	//things[0].vector[0] = 0; things[0].vector[1] = 0; things[0].vector[2] = 0;
	fscanf(fp1, "%lf %lf %lf", &things[0].vector[0], &things[0].vector[1], &things[0].vector[2]);
	fclose(fp1);

	FILE *fp2 = fopen("mass2.txt", "r");
	fscanf(fp2, "%lf\n", &things[1].mass);
	fscanf(fp2, "%lf %lf %lf\n", &things[1].pos[0], &things[1].pos[1], &things[1].pos[2]);
	fscanf(fp2, "%lf %lf %lf", &things[1].vector[0], &things[1].vector[1], &things[1].vector[2]);
	fclose(fp2);

	FILE *fp3 = fopen("mass3.txt", "r");
	fscanf(fp3, "%lf\n", &things[2].mass);
	fscanf(fp3, "%lf %lf %lf\n", &things[2].pos[0], &things[2].pos[1], &things[2].pos[2]);
	fscanf(fp3, "%lf %lf %lf", &things[2].vector[0], &things[2].vector[1], &things[2].vector[2]);
	fclose(fp3);

	F01.strength = 0;
	F02.strength = 0;
	F12.strength = 0;

	return;
}

void gotest() {
	double timepast = 0;
	double len01 = poslen(things[0], things[1]);
	double len02 = poslen(things[0], things[2]);
	double len12 = poslen(things[1], things[2]);
	int i = 0;

	FILE *fp = fopen("out.txt", "w");

	while (timepast <= duration) {
		F01.strength = forceSum(things[0], things[1]);
		F02.strength = forceSum(things[0], things[2]);
		F12.strength = forceSum(things[1], things[2]);


		things[0].pos[0] += things[0].vector[0] * t0;
		things[0].pos[1] += things[0].vector[1] * t0;
		things[0].pos[2] += things[0].vector[2] * t0;//
		things[1].pos[0] += things[1].vector[0] * t0;
		things[1].pos[1] += things[1].vector[1] * t0;
		things[1].pos[2] += things[1].vector[2] * t0;//
		things[2].pos[0] += things[2].vector[0] * t0;
		things[2].pos[1] += things[2].vector[1] * t0;
		things[2].pos[2] += things[2].vector[2] * t0;


		things[0].vector[0] += (F01.strength * (things[1].pos[0] - things[0].pos[0]) / len01 + F02.strength * (things[2].pos[0] - things[0].pos[0]) / len02) / things[0].mass * t0;
		things[0].vector[1] += (F01.strength * (things[1].pos[1] - things[0].pos[1]) / len01 + F02.strength * (things[2].pos[1] - things[0].pos[1]) / len02) / things[0].mass * t0;
		things[0].vector[2] += (F01.strength * (things[1].pos[2] - things[0].pos[2]) / len01 + F02.strength * (things[2].pos[2] - things[0].pos[2]) / len02) / things[0].mass * t0;//
		things[1].vector[0] += (F01.strength * (things[0].pos[0] - things[1].pos[0]) / len01 + F12.strength * (things[2].pos[0] - things[1].pos[0]) / len12) / things[1].mass * t0;
		things[1].vector[1] += (F01.strength * (things[0].pos[1] - things[1].pos[1]) / len01 + F12.strength * (things[2].pos[1] - things[1].pos[1]) / len12) / things[1].mass * t0;
		things[1].vector[2] += (F01.strength * (things[0].pos[2] - things[1].pos[2]) / len01 + F12.strength * (things[2].pos[2] - things[1].pos[2]) / len12) / things[1].mass * t0;//
		things[2].vector[0] += (F02.strength * (things[0].pos[0] - things[2].pos[0]) / len02 + F12.strength * (things[1].pos[0] - things[2].pos[0]) / len12) / things[2].mass * t0;
		things[2].vector[1] += (F02.strength * (things[0].pos[1] - things[2].pos[1]) / len02 + F12.strength * (things[1].pos[1] - things[2].pos[1]) / len12) / things[2].mass * t0;
		things[2].vector[2] += (F02.strength * (things[0].pos[2] - things[2].pos[2]) / len02 + F12.strength * (things[1].pos[2] - things[2].pos[2]) / len12) / things[2].mass * t0;

		len01 = poslen(things[0], things[1]);
		len02 = poslen(things[0], things[2]);
		len12 = poslen(things[1], things[2]);

		if (i == 5000) {
			fprintf(fp, "(%f,%f,%f),(%f,%f,%f),(%f,%f,%f),",
				things[0].pos[0], things[0].pos[1], things[0].pos[2],
				things[1].pos[0], things[1].pos[1], things[1].pos[2],
				things[2].pos[0], things[2].pos[1], things[2].pos[2]);
			//printf("(%f,%f),", .5 * things[1].mass * getS(), -1*10000*1 / (poslen(things[0], things[1]) * poslen(things[0], things[1])));
			i = 0;
		}

		timepast += t0;
		i++;
	}

	return;
}

int main() {
	
	initial(); //printf("%f", poslen(things[0].pos[0], things[1].pos[0], things[0].pos[1], things[0].pos[1]));
	gotest();
	return 0;
}
