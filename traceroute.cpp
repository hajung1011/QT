#include "traceroute.h"

TraceRoute::TraceRoute()
{
    this->_size = DEFAULT_SIZE;
    this->init_vari();
}

TraceRoute::TraceRoute(int size)
{
    this->_size = size;
    this->init_vari();
}

TraceRoute::~TraceRoute()
{
    for (int i = 0; i < this->_size; i++)
    {
        //free(this->weight[i]);
        //free(this->_path[i].check);
        //free(this->_path[i].distance);
        //free(this->_path[i].found);
        delete[] this->weight[i];
        delete[] this->_path[i].check;
        delete[] this->_path[i].distance;
        delete[] this->_path[i].found;
        for (int j = 0; j < this->_size; j++)
        {
            delete[] this->_path[i].path[j];
        }
        delete[] this->_path[i].path;
    }
    delete[] this->weight;
    delete[] this->_path;
}

void TraceRoute::init_vari()
{
    //this->weight = (int**)malloc(sizeof(int*) * this->_size);
    this->weight = new int*[this->_size];
    for (int i = 0; i < this->_size; i++)
    {
        //this->weight[i] = (int*)malloc(sizeof(int) * this->_size);
        this->weight[i] = new int[this->_size];
    }
    //this->_path = (path_Queue*)malloc(sizeof(path_Queue) * this->_size);
    this->_path = new path_Queue[this->_size];
    for (int i = 0; i < this->_size; i++)
    {
        //this->_path[i].distance = (int*)malloc(sizeof(int) * this->_size);
        this->_path[i].distance = new int[this->_size];
        this->_path[i].found = new int[this->_size];
        this->_path[i].check = new int[this->_size];
        this->_path[i].path = new int*[this->_size];
        for (int j = 0; j < this->_size; j++)
        {
            //this->_path[i].path[j] = (int*)malloc(sizeof(int) * this->_size * 2);
            this->_path[i].path[j] = new int[this->_size * 2];
        }
    }
}

void TraceRoute::set_matrix(int** matrix)
{
    this->weight = matrix;
    this->shortest_path();
}

void TraceRoute::path_init()
{
    int i, j, k;
    for (i = 0; i < this->_size; i++)
        for (j = 0; j < this->_size; j++)
            for (k = 0; k < this->_size; k++)
                this->_path[i].path[j][k] = INF;

}



int TraceRoute::choose(int* distance, int n, int* found) {
    int i, min, minpos;
    min = INT_MAX;
    minpos = -1;
    for (i = 0; i < n; i++)
        if (distance[i] < min && !found[i]) {
            min = distance[i];
            minpos = i;
        }
    return minpos;
}

void TraceRoute::shortest_path()
{

    int i, j, u, w, start;
    for (start = 0; start < this->_size; start++)
    {
        for (i = 0; i < this->_size; i++) {
            this->_path[start].distance[i] = this->weight[start][i];
            this->_path[start].found[i] = false;
            this->_path[start].check[i] = 1;
            this->_path[start].path[i][0] = start;
            for (j = 1; j < this->_size * 2; j++)
            {
                this->_path[start].path[i][j] = -1;
            }
        }
        this->_path[start].found[start] = true;
        this->_path[start].distance[start] = 0;
        for (i = 0; i < this->_size - 2; i++) {
            u = this->choose(this->_path[start].distance, this->_size, this->_path[start].found);
            this->_path[start].found[u] = true;
            for (w = 0; w < this->_size; w++) {
                if (!this->_path[start].found[w]) {
                    if (this->_path[start].distance[u] + this->weight[u][w] < this->_path[start].distance[w]) {
                        if (i == 0) {
                            this->_path[start].path[w][this->_path[start].check[w]] = u;
                            this->_path[start].check[w]++;
                        }
                        else {
                            for (j = 0; j < (this->_path[start].check[u] + 1); j++) {
                                this->_path[start].path[w][j] = this->_path[start].path[u][j];
                                this->_path[start].path[w][j + 1] = u;
                                this->_path[start].check[w]++;
                            }
                        }
                        this->_path[start].distance[w] = this->_path[start].distance[u] + this->weight[u][w];
                    }
                }
            }
        }
    }
}

void TraceRoute::print_path(int start)
{
    for (int i = 0; i < this->_size; i++) {
        if (this->_path[start].distance[i] > 0 && this->_path[start].distance[i] < INF)
        {
            printf("Route : %d -> %d  ", start, i);

            for (int j = 0; j < this->_size * 2; j++) {

                if (this->_path[start].path[i][j] >= 0 && this->_path[start].path[i][j] < this->_size) {

                    printf("%d->", this->_path[start].path[i][j]);

                }

            }
            printf("%d , Distance : %d\n", i, this->_path[start].distance[i]);
        }
        else if (this->_path[start].distance[i] >= INF)
        {
            printf("no Route : %d->%d \n", start, i);
        }
    }
}

int* TraceRoute::result(int start, int end, int * _count)
{
    int count = 0;
    int recount = this->_path[start].distance[end] +1;
    if (recount >= INF)
    {
        *_count = 1;
        return 0;
    }
    int* result = new int[recount];
    //int* result = (int*)malloc(sizeof(int)*this->_size);

    if (start != end)
    {
        for (int i = 0; i < this->_size * 2; i++)
        {
            if (this->_path[start].path[end][i] >= 0 && this->_path[start].path[end][i] < this->_size)
            {

                result[count] = this->_path[start].path[end][i];
                count++;
            }
        }
        result[count] = end;
        count++;
    }
    else
    {
        return nullptr;

    }
    //realloc(result, sizeof(int) * count);
    *_count = recount;

    return result;
    // result_ = result;
}

int* TraceRoute::return_result()
{
    return result_;
}

int TraceRoute::distance(int start, int end)
{
    return this->_path[start].distance[end];
}
void TraceRoute::print_size()
{
    printf("Size : %d\n", this->_size);

}
