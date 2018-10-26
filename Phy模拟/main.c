#include <stdio.h>
#include <math.h>

void initial();
void gotest();
double poslen();
double speed();

const double duration = 1;
const double t0 = .0001;
const double G = 1;

struct thing {
	double mass;
	double vector[3]; 
	double pos[3];
} things[3];

struct force {
	double strength;
	double ang[2];
} F01, F02, F12;

double poslen(double x1, double x2, double y1, double y2) {
	double len = 0;
	len = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
	return len;
}

double speed(double vx, double vy) {
	double spd = .0;
	spd = sqrt(pow(vx, 2) + pow(vy, 2));
	return .0;
}

void initial() {
	things[0].mass = 5.0;
	things[0].pos[0] = 0; things[0].pos[1] = 0;
	things[0].vector[0] = 1; things[0].vector[1] = 0;

	things[1].mass = 5.0;
	things[1].pos[0] = 1; things[1].pos[1] = 0;
	things[1].vector[0] = 0; things[1].vector[1] = 5;

	things[2].mass = 5;
	things[2].pos[0] = .5; things[2].pos[1] = .5;
	things[2].vector[0] = 2; things[2].vector[1] = 2;

	F01.strength = 0;
	F01.ang[0] = 0; F01.ang[1] = 0;
	F02.strength = 0;
	F02.ang[0] = 0; F02.ang[1] = 0;
	F12.strength = 0;
	F12.ang[0] = 0; F12.ang[1] = 0;

	return;
}

void gotest() {
	double timepast = 0;
	double len01 = poslen(things[0].pos[0], things[1].pos[0], things[0].pos[1], things[1].pos[1]);
	double len02 = poslen(things[0].pos[0], things[2].pos[0], things[0].pos[1], things[2].pos[1]);
	double len12 = poslen(things[1].pos[0], things[2].pos[0], things[1].pos[1], things[2].pos[1]);
	int i = 0;

	while (timepast <= duration) {
		F01.strength = things[0].mass * things[1].mass / (len01 * len01);
		F02.strength = things[0].mass * things[2].mass / (len02 * len02);
		F12.strength = things[1].mass * things[2].mass / (len12 * len12);

		things[0].pos[0] += things[0].vector[0] * t0;
		things[0].pos[1] += things[0].vector[1] * t0;
		things[1].pos[0] += things[1].vector[0] * t0;
		things[1].pos[1] += things[1].vector[1] * t0;
		things[2].pos[0] += things[2].vector[0] * t0;
		things[2].pos[1] += things[2].vector[1] * t0;

		things[0].vector[0] += (F01.strength * (things[1].pos[0] - things[0].pos[0]) / len01 + F02.strength * (things[2].pos[0] - things[0].pos[0]) / len02) / things[0].mass * t0;
		things[0].vector[1] += (F01.strength * (things[1].pos[1] - things[0].pos[1]) / len01 + F02.strength * (things[2].pos[1] - things[0].pos[1]) / len02) / things[0].mass * t0;
		things[1].vector[0] += (F01.strength * (things[0].pos[0] - things[1].pos[0]) / len01 + F12.strength * (things[2].pos[0] - things[1].pos[0]) / len12) / things[1].mass * t0;
		things[1].vector[1] += (F01.strength * (things[0].pos[1] - things[1].pos[1]) / len01 + F12.strength * (things[2].pos[1] - things[1].pos[1]) / len12) / things[1].mass * t0;
		things[2].vector[0] += (F02.strength * (things[0].pos[0] - things[2].pos[0]) / len02 + F12.strength * (things[1].pos[0] - things[2].pos[0]) / len12) / things[2].mass * t0;
		things[2].vector[1] += (F02.strength * (things[0].pos[1] - things[2].pos[1]) / len02 + F12.strength * (things[1].pos[1] - things[2].pos[1]) / len12) / things[2].mass * t0;

		len01 = poslen(things[0].pos[0], things[1].pos[0], things[0].pos[1], things[1].pos[1]);
		len02 = poslen(things[0].pos[0], things[2].pos[0], things[0].pos[1], things[2].pos[1]);
		len12 = poslen(things[1].pos[0], things[2].pos[0], things[1].pos[1], things[2].pos[1]);

		if (i == 50) {
			printf("(%f,%f),(%f,%f),(%f,%f),", things[0].pos[0], things[0].pos[1], things[1].pos[0], things[1].pos[1], things[2].pos[0], things[2].pos[1]);
			//printf("(%f,%f),", things[2].pos[0], things[2].pos[1]);
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