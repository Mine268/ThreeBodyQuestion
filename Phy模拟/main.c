#include <stdio.h>
#include <math.h>

void initial();
void gotest();
double poslen();
double speed();

const double duration = .1;
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

void initial() {
	things[0].mass = 5.0;
	things[0].pos[0] = 0; things[0].pos[1] = 0, things[0].pos[2] = 1;
	things[0].vector[0] = 1; things[0].vector[1] = 0; things[0].vector[2] = 0;

	things[1].mass = 5.0;
	things[1].pos[0] = 1; things[1].pos[1] = 0; things[1].pos[2] = 0;
	things[1].vector[0] = 0; things[1].vector[1] = 5; things[1].vector[2] = 0;

	things[2].mass = 5.2;
	things[2].pos[0] = .5; things[2].pos[1] = .5; things[2].pos[2] = -0.5;
	things[2].vector[0] = 2; things[2].vector[1] = 2; things[2].vector[2] = 0;

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

	while (timepast <= duration) {
		F01.strength = things[0].mass * things[1].mass / (len01 * len01);
		F02.strength = things[0].mass * things[2].mass / (len02 * len02);
		F12.strength = things[1].mass * things[2].mass / (len12 * len12);


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

		if (i == 500) {
			printf("(%f,%f,%f),(%f,%f,%f),(%f,%f,%f),",
				things[0].pos[0], things[0].pos[1], things[0].pos[2],
				things[1].pos[0], things[1].pos[1], things[1].pos[2],
				things[2].pos[0], things[2].pos[1], things[2].pos[2]);
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
