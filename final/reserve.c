#define _CRT_SECURE_NO_WARNINGS
#include "final.h"

planes_p pp;
reserve_p rp = NULL;
char arr_city[30][20];
int r;
//티켓 예약 함수
void Reserve_ticket() {
	reserve_p new = (reserve_p)malloc(sizeof(reserve_Node));
	printf("Enter ID : "); scanf("%s", new->id);
	printf("\nEnter full name(No space) : "); scanf("%s", new->name);
	Print_airport();
	Input_airport(new);
	DFS_route(new->depart[0], new->destination[0]);
	route_sorting(arr_city, 0, r);
	Search_planes();
	Select_plane(new);
	var_init();
}

void Print_airport() {
	printf("-----------------------------Airport List----------------------------------\n");
	printf("%-10s\t%-10s\t%-10s\t%-10s\t%-10s\n", "Alaska", "Beijing", "Copenhagen", "Delhi", "Edinburgh");
	printf("%-10s\t%-10s\t%-10s\t%-10s\t%-10s\n", "Frankfurt", "Gimpo", "Hongkong", "Incheon", "Jeju");
	printf("%-10s\t%-10s\t%-10s\t%-10s\t%-10s\n", "Kobe", "LosAngeles", "Madrid", "NewYork", "Osaka");
	printf("---------------------------------------------------------------------------\n");
}

void Input_airport(reserve_p new) {
	planes_p temp = pp;
	while (1) {
		printf("\nDeparture : "); scanf("%s", new->depart);
		while (temp->link != pp) {
			//printf("%s", temp->depart);
			//printf("%s", new->depart);
			if (strcmp(temp->depart, new->depart) == 0)
				break;
			else
				temp = temp->link;
		}
		if (temp->link == pp) {
			printf("Entered something wrong, Please enter again.\n");
			temp = pp;
		}
		else
			break;
	}
	temp = pp;
	while (1) {
		printf("\nDestination : "); scanf("%s", new->destination);
		while (temp->link != pp) {
			if (strcmp(temp->destination, new->destination) == 0)
				break;
			else
				temp = temp->link;
		}
		if (temp->link == pp) {
			printf("Entered something wrong, Please enter again.\n");
			temp = pp;
		}
		else
			break;
	}
}

void Search_planes() {
	planes_p temp; int i = 0, j = 0, time_sum = 0; //i는 출발지에서 도착지로 가는 루트의 수, j는 거치는 나라의 수
	temp = (planes_p)malloc(sizeof(planes_Node));
	temp = pp;

	printf("\n");
	while (arr_city[i][j] != '\0') { //루트 정보가 없을 때까지 반복
		printf("\tFlight #\t    Departure\t Destination\tFlight time\tCost\tDistance\n");
		printf("-------------------------------------------------------------------------------------------------\n");
		while (arr_city[i][j + 1] != '\0') {
			//비행기 정보 데이터에서 출발지,도착지의 첫 글자와 그래프에 저장된 나라명이 일치할 때
			if (temp->depart[0] == arr_city[i][j] && temp->destination[0] == arr_city[i][j + 1]) {
				Print_planes(temp);
				time_sum = time_sum + hour_count(temp->depart_t, temp->destination_t);
				temp = pp;
				j++;

			}
			else
				temp = temp->link;
		} // 출발지에서 도착지로 가는 한가지 루트를 출력

		i++;
		j = 0;
		printf("Travel time is %d:00\n", time_sum);
		printf("-------------------------------------------------------------------------------------------------\n");
		time_sum = 0;
	} // 출발지에서 도착지로 가는 모든 루트를 출력
}

void Print_planes(planes_p infor) {
	//printf("Flight #\tDeparture\tDestination\tFlight time\tCost\n");
	printf("%s(%10s->%10s)   ", infor->flight_num, infor->depart, infor->destination);
	printf("%-2d : 00   ", infor->depart_t);
	printf("%5d : 00   ", infor->destination_t);
	printf("\t%3d hours   ", infor->flight_time);
	printf("\t$%-4d", infor->cost);
	printf("\t%5dKM\n", infor->distance);
}

planes_p Search_Flightnum(char *flightnum) {
	planes_p temp;
	temp = pp;
	do {
		if (strcmp(temp->flight_num, flightnum) == 0) {
			break;
		}
		else
			temp = temp->link;
	} while (temp != pp);
	return temp;
}

void Select_plane(reserve_p new) {
	char sel; reserve_p temp = rp;
	Input_flight(new);
	printf("\n");
	Select_seat(new);
	planes_p pdata = Search_Flightnum(new->flight_num); // 입력받은 비행기 번호에 맞는 노드를 pdata에 불러옴
	new->depart_t = pdata->depart_t; //예약정보 노드에 비행기 출발 시간 정보 입력
	new->destination_t = pdata->destination_t; //예약정보 노드에 비행기 도착 시간 정보 입력
	new->flight_time = hour_count(new->depart_t, new->destination_t);
	printf("\n");
	while (temp->link != rp) {
		if (strcmp(temp->id, new->id) == 0)
			break;
		else
			temp = temp->link;
	}
	if (strcmp(temp->id, new->id) == 0)
		insert_id(new);
	else
		insert(new);
	Reservation_confirm(new);

	while (1) {
		getchar();
		printf("Do you want other ticket?(y/n) : "); scanf("%c", &sel);
		if (sel == 'y')
			id_add(new);
		else
			return;
	}
}

void Input_flight(reserve_p new) {
	planes_p temp = pp;
	while (1) {
		printf("\nEnter Flight # : "); scanf("%s", new->flight_num);
		do {
			if (strcmp(temp->flight_num, new->flight_num) == 0)
				break;
			else
				temp = temp->link;
		} while (temp != pp);
		if (temp == pp && strcmp(temp->flight_num, new->flight_num) != 0) {
			printf("Entered something wrong, Please enter again.\n");
		}
		else
			break;
	}
}

void Select_seat(reserve_p seat) {
	planes_p fn = Search_Flightnum(seat->flight_num); //입력받은 비행기 번호 노드를 불러옴
	Print_seat(fn);
	while (1) {
		printf("Business(+$100) : A, B\nEconomy : others\n");
		printf("Enter your Seat(ex. A1, C2) : ");
		scanf("%s", seat->Seat); // 자리 입력 받기
		int i, j;
		for (i = 0; i < 6; i++) {
			if (fn->Seat[0][i] == seat->Seat[0])
				break;
		}
		if (i<6 && seat->Seat[1] == '1' && strlen(seat->Seat) == 2)
			j = 1;
		else if (i<6 && seat->Seat[1] == '2' && strlen(seat->Seat) == 2)
			j = 2;
		else {
			printf("Input Error.. please select again.\n\n");
			continue;
		}
		if (fn->Seat[j][i] == 0) { //입력 받은 자리에 0이 포함되면 이미 예약된 자리
			printf("already reserve, select another seat\n\n"); continue;
		}
		else {
			if ((seat->Seat[0] == 'A' || seat->Seat[0] == 'B') && (seat->Seat[1] == '1' || seat->Seat[1] == '2')) { // 에약 정보에 비행기 좌석 클래스를 저장
				strcpy(seat->flight_class, "Business"); break;
			}
			else if ((seat->Seat[0] == 'C' || seat->Seat[0] == 'D' || seat->Seat[0] == 'E' || seat->Seat[0] == 'F') && (seat->Seat[1] == '1' || seat->Seat[1] == '2')) {
				strcpy(seat->flight_class, "Economy"); break;
			}
			else {
				printf("Input Error.. please select seat again\n\n"); continue;
			}
		}
	}
	Save_seat(fn, seat->Seat);
}

void Print_seat(planes_p fn) {
	//A  B  C  D  E  F
	//1  1  1  1  1  1
	//2  2  2  2  2  2
	// 위 형식으로 출력. 
	if (fn->Seat[0][0] == 'A') {
		printf("<Seleting a Seat>\n");
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 6; j++) {
				printf("%c  ", fn->Seat[i][j]);
			}
			printf("\n");
		}
		printf("\n");
	}
	else {
		strcpy(fn->Seat[0], "ABCDEF");
		strcpy(fn->Seat[1], "111111");
		strcpy(fn->Seat[2], "222222");
		printf("<Seleting a Seat>\n");
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 6; j++) {
				printf("%c  ", fn->Seat[i][j]);
			}
			printf("\n");
		}
		printf("\n");
	}
}

void Save_seat(planes_p fn, char* seat) {
	int i = 0;
	while (fn->Seat[0][i] != seat[0]) {
		i++;
	}
	if (seat[1] == '1')
		fn->Seat[1][i] = 0;
	else
		fn->Seat[2][i] = 0;
	//선택한 자리는 0으로 바뀌어 선택하지 못하게 함.
}

void id_add(reserve_p new) {
	reserve_p temp = new;
	reserve_p id_add = (reserve_p)malloc(sizeof(reserve_Node));
	strcpy(id_add->id, new->id);
	strcpy(id_add->name, new->name);
	Input_flight(id_add);
	printf("\n");
	Select_seat(id_add);
	planes_p pdata = Search_Flightnum(id_add->flight_num); // 입력받은 비행기 번호에 맞는 노드를 pdata에 불러옴
	id_add->depart_t = pdata->depart_t; //예약정보 노드에 비행기 출발 시간 정보 입력
	id_add->destination_t = pdata->destination_t; //예약정보 노드에 비행기 도착 시간 정보 입력
	id_add->flight_time = hour_count(id_add->depart_t, id_add->destination_t);
	printf("\n");
	if (new->id_link == NULL) {
		new->id_link = id_add;
		id_add->id_link = NULL;
	}
	else {
		while (temp->id_link != NULL)
			temp = temp->id_link;
		temp->id_link = id_add;
		id_add->id_link = NULL;
	}
	Reservation_confirm(id_add);

}

void insert(reserve_p new) { // reservation 할 때 노드를 생성(circular LL)
	reserve_p temp;
	temp = rp;

	if (temp == NULL) {
		rp = new;
		new->link = rp;
		new->id_link = NULL;
	}
	else {
		while (temp->link != rp) {
			temp = temp->link;
		}
		temp->link = new;
		new->link = rp;
		new->id_link = NULL;
	}
}

void insert_id(reserve_p new) {
	reserve_p temp = rp;
	while (temp->link != rp) {
		if (strcmp(temp->id, new->id) == 0)
			break;
		else
			temp = temp->link;
	}
	reserve_p idtemp = temp;
	if (idtemp->id_link == NULL) {
		idtemp->id_link = new;
		new->id_link = NULL;
	}
	else {
		while (idtemp->id_link != NULL) {
			idtemp = idtemp->id_link;
		}
		idtemp->id_link = new;
		new->id_link = NULL;
	}
}
