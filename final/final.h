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


void printTitle(); //Ÿ��Ʋ ���� ���
void menu(); // UI �޴� ���

void Reserve_ticket(); // Ƽ�� ���� �Լ�
void Search_planes(); // �Է��� �����/�������� �´� ����뼱 ��ġ
void Print_planes(planes_p); //��ġ�� �뼱 ���
void insert(reserve_p); // ���� ������ �Էµ� ��� ����
void Select_seat(reserve_p); // �¼� ���� �Լ�
planes_p Search_Flightnum(char*); // ������ flight #�� �´� ���� �̵�
void Print_seat(planes_p); // ������ �� �ִ� �¼�ǥ ���
void Save_seat(planes_p, char*); // ������ �¼��� �ٽ� ���� ���ϵ��� ����
void Input_flight(reserve_p new);
void Input_airport(reserve_p new);
void Print_airport();
void Select_plane(reserve_p new);
void id_add(reserve_p);
void insert_id(reserve_p new);

void Check_reservation(); // id�Է½� �������� ���
void Reservation_confirm(reserve_p); // ���� ���� Ȯ��

void Cancel_reservation(); // ���� ���
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