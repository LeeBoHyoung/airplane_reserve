#define _CRT_SECURE_NO_WARNINGS
#include "final.h"

planes_p pp = NULL;


void add_planes(char *flight_num, char* depart, char *destination,
	int depart_t, int destination_t, int cost, int distance) {
	planes_p temp = pp;
	planes_p newp = (planes_p)malloc(sizeof(planes_Node));
	strcpy(newp->flight_num, flight_num);
	strcpy(newp->depart, depart);
	strcpy(newp->destination, destination);
	newp->depart_t = depart_t;
	newp->destination_t = destination_t;
	newp->flight_time = hour_count(depart_t, destination_t);
	newp->cost = cost;
	newp->distance = distance;
	if (pp == NULL) {
		pp = newp;
		newp->link = pp;
	}
	else {
		while (temp->link != pp)
			temp = temp->link;
		temp->link = newp;
		newp->link = pp;
	}
}

void planes_infor() {
	add_planes("I1", "Incheon", "Jeju", 6, 7, 150, 150);
	add_planes("I2", "Incheon", "Osaka", 16, 18, 600, 500);
	add_planes("I3", "Incheon", "Beijing", 14, 16, 400, 300);
	add_planes("I4", "Incheon", "Gimpo", 14, 15, 100, 100);
	add_planes("J1", "Jeju", "Incheon", 13, 14, 150, 150);
	add_planes("J2", "Jeju", "Kobe", 9, 11, 200, 200);
	add_planes("K1", "Kobe", "Jeju", 12, 14, 200, 200);
	add_planes("K2", "Kobe", "Osaka", 18, 19, 150, 150);
	add_planes("O1", "Osaka", "Incheon", 13, 15, 600, 500);
	add_planes("O2", "Osaka", "Kobe", 11, 12, 150, 150);
	add_planes("O3", "Osaka", "LosAngeles", 9, 19, 900, 500);
	add_planes("O4", "Osaka", "NewYork", 8, 20, 1000, 1000);
	add_planes("L1", "LosAngeles", "Osaka", 17, 7, 900, 500);
	add_planes("L2", "LosAngeles", "Alaska", 12, 14, 200, 200);
	add_planes("A1", "Alaska", "LosAngeles", 14, 16, 200, 200);
	add_planes("A2", "Alaska", "NewYork", 17, 19, 100, 100);
	add_planes("N1", "NewYork", "Osaka", 18, 6, 1000, 1000);
	add_planes("N2", "NewYork", "Alaska", 12, 14, 100, 100);
	add_planes("N3", "NewYork", "Madrid", 20, 1, 400, 400);
	add_planes("N4", "NewYork", "Copenhagen", 2, 10, 850, 750);
	add_planes("M1", "Madrid", "NewYork", 11, 16, 400, 400);
	add_planes("M2", "Madrid", "Edinburgh", 17, 19, 150, 150);
	add_planes("E1", "Edinburgh", "Madird", 11, 16, 150, 150);
	add_planes("E2", "Edinburgh", "Copenhagen", 20, 22, 200, 200);
	add_planes("C1", "Copenhagen", "Edinburgh", 15, 17, 200, 200);
	add_planes("C2", "Copenhagen", "NewYork", 3, 11, 850, 750);
	add_planes("C3", "Copenhagen", "Frankfurt", 23, 1, 200, 200);
	add_planes("C4", "Copenhagen", "Beijing", 15, 24, 1000, 1000);
	add_planes("F1", "Frankfurt", "Copenhagen", 8, 10, 200, 200);
	add_planes("F2", "Frankfurt", "Delhi", 2, 6, 400, 400);
	add_planes("D1", "Delhi", "Frankfurt", 11, 15, 400, 400);
	add_planes("D2", "Delhi", "Beijing", 7, 10, 300, 300);
	add_planes("B1", "Beijing", "Copenhagen", 12, 17, 1000, 1000);
	add_planes("B2", "Beijing", "Delhi", 15, 18, 300, 300);
	add_planes("B3", "Beijing", "Hongkong", 11, 12, 100, 100);
	add_planes("B4", "Beijing", "Incheon", 16, 17, 400, 300);
	add_planes("H1", "Hongkong", "Beijing", 17, 18, 100, 100);
	add_planes("H2", "Hongkong", "Gimpo", 13, 14, 100, 100);
	add_planes("G1", "Gimpo", "Hongkong", 9, 10, 100, 100);
	add_planes("G2", "Gimpo", "Incheon", 15, 16, 100, 100);
}

void print_planes() {
	planes_p temp;
	temp = pp;
	printf("Flight Num\tDepart\t\t\tDestination\tFlight Time\t Cost\t  Distance\n");
	do {
		printf("%s", temp->flight_num);
		printf("%17s(%d : 00)", temp->depart, temp->depart_t);
		printf("%17s(%d : 00)\t", temp->destination, temp->destination_t);
		printf("%2d hours", temp->flight_time);
		printf("         $%-4d", temp->cost);
		printf("      %dKM\n", temp->distance);
		temp = temp->link;
	} while (temp != pp);
}