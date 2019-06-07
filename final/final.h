#include <stdio.h>
#include <Windows.h>
#include <string.h>
#include <stdlib.h>

typedef struct reserve_Node* reserve_p;
typedef struct reserve_Node {
	char id[10];
	char name[20];
	char flight_num[20];
	char flight_class[10];
	char Seat[10];
	char depart[10];
	char destination[10];
	int depart_t;
	int destination_t;
	int flight_time;
	reserve_p link;
	reserve_p id_link;
}reserve_Node;

typedef struct planes_Node* planes_p;
typedef struct planes_Node {
	char flight_num[20];
	char flight_class[10];
	char Seat[3][7];
	char depart[20];
	char destination[20];
	int depart_t;
	int destination_t;
	int flight_time;
	int distance;
	int cost;
	char direction[4];
	planes_p link;
}planes_Node;

typedef struct node* graph;
typedef struct node {
	char vertex;
	int weight;

	graph edge_link;
	graph vertex_link;
}node;


void printTitle(); //타이틀 제목 출력
void menu(); // UI 메뉴 출력

void Reserve_ticket(); // 티켓 예약 함수
void Search_planes(); // 입력한 출발지/도착지에 맞는 비행노선 서치
void Print_planes(planes_p); //서치된 노선 출력
void insert(reserve_p); // 예약 정보가 입력될 노드 생성
void Select_seat(reserve_p); // 좌선 선택 함수
planes_p Search_Flightnum(char*); // 선택한 flight #에 맞는 노드로 이동
void Print_seat(planes_p); // 선택할 수 있는 좌석표 출력
void Save_seat(planes_p, char*); // 선택한 좌석은 다시 선택 못하도록 저장
void Input_flight(reserve_p new);
void Input_airport(reserve_p new);
void Print_airport();
void Select_plane(reserve_p new);
void id_add(reserve_p);
void insert_id(reserve_p new);

void Check_reservation(); // id입력시 예약정보 출력
void Reservation_confirm(reserve_p); // 예약 내용 확인

void Cancel_reservation(); // 예약 취소
void delete_node(char*);
void cancel_seat(reserve_p);

int hour_count(int, int);

void add_planes(char *flight_num, char* depart, char *destination,
	int depart_t, int destination_t, int cost, int distance);
void planes_infor();
void print_planes();

void make_graph();
void DFS_route(char, char);

void Initialize();
void add_reserve(char* id, char* name, char* flight_num, char* flight_class,
	char* Seat, char* depart, char* destination, int depart_t, int destination_t);
void var_init();
void route_sorting();