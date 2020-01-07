#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// #define INT_MAX 2147483647

#define DEFAULT_SIZE 10

#define INF 1000

using namespace std;
class Dialog;

struct path_Queue {
    int* distance;
    int* found;
    int* check;
    int** path;
};

class TraceRoute {
    //Public Methods
public:
    TraceRoute();
    TraceRoute(int _size);
    ~TraceRoute();
    void set_matrix(int** matrix);
    void print_path(int start);
    void print_size();
    int* result(int start, int end, int* _count);
    int distance(int start, int end);


    // Hajung
    int* return_result();
    //Private Methods
private:
    void init_vari();
    void path_init();
    int choose(int* distance, int n, int* found);
    void shortest_path();

//Private Variables
private:
    int** weight;
    int _size;
    struct path_Queue* _path;
    // Hajung
    int* result_;

};
