#include "graph.h"

Graph::Graph()
{
    VertexHead = nullptr;
    VertexCount = 0;
    MaxEdgeCount = -1;
}

Graph::~Graph()
{
}

bool Graph::EmptyVertex()
{
    return(VertexCount == 0);
}

bool Graph::EmptyEdge(Vertex* vertex)
{
    return(vertex->nEdgeCount == 0);
}

bool Graph::FullVertex()
{
    return(VertexCount == MAX_VERTEX);
}

bool Graph::FullEdge(Vertex* vertex)
{
    return(vertex->nEdgeCount == MaxEdgeCount);
}

void Graph::InitGraph()
{
    VertexCount = 0;
    VertexHead = nullptr;
}

void Graph::InitVertex(Vertex* vertex)
{
    vertex->nVertex = -1;
    vertex->Next = nullptr;
    vertex->EdgeHead = nullptr;
    vertex->nEdgeCount = 0;
}

void Graph::InitEdge(Edge* edge)
{
    edge->FromVertex = nullptr;
    edge->TargetVertex = nullptr;
    edge->Next = nullptr;
    edge->weight = -1;
}

Vertex* Graph::CreateVertex(int data)
{
    Vertex* NewVertex = new Vertex;
    InitVertex(NewVertex);
    NewVertex->nVertex = data;
    return NewVertex;
}

Edge* Graph::CreateEdge(int from, int target, int weight)
{
    Edge* NewEdge = new Edge;
    InitEdge(NewEdge);
    NewEdge->FromVertex = FindVertex(from);
    NewEdge->TargetVertex = FindVertex(target);
    NewEdge->weight = weight;
    return NewEdge;
}

Vertex* Graph::FindVertex(int data)
{
    Vertex* find_vertex = VertexHead;
    if (EmptyVertex())
    {
        return nullptr;
    }
    while (find_vertex)
    {
        if (find_vertex->nVertex == data)
        {
            break;
        }
        find_vertex = find_vertex->Next;
    }
    return find_vertex;
}

Edge* Graph::FindEdge(int from, int target)
{
    Vertex* from_vertex = FindVertex(from);
    Vertex* target_vertex = FindVertex(target);
    if (EmptyEdge(from_vertex))
    {
        return nullptr;
    }

    Edge* find_edge = from_vertex->EdgeHead;
    while (find_edge)
    {
        if ((find_edge->FromVertex == from_vertex) && (find_edge->TargetVertex == target_vertex))
        {
            return find_edge;
        }
        find_edge = find_edge->Next;
    }

    return nullptr;
}

int Graph::ExistEdge(int from, int target, int weight)
{
    Vertex* from_vertex = FindVertex(from);
    Vertex* target_vertex = FindVertex(target);
    int w = weight;
    int temp = 0;

    Edge* cursor = from_vertex->EdgeHead;

    for (int i = 0; i < from_vertex->nEdgeCount; i++)
    {
        if (cursor->TargetVertex == target_vertex)
        {
            if (cursor->weight == w)
            {
                temp = 2;
                break;
            }
            else
            {
                temp = 1;
                break;
            }
        }
        cursor = cursor->Next;
    }
    return temp;
}

void Graph::AddVertex(int data)
{
    if (FullVertex())
    {
        cout << "최대정점수 초과" << endl;
        return;
    }

    Vertex* new_vertex = CreateVertex(data);
    Vertex* vertex_list = VertexHead;

    if (EmptyVertex())
    {
        VertexHead = new_vertex;
    }

    else
    {
        while (vertex_list->Next != nullptr)
        {
            vertex_list = vertex_list->Next;
        }
        vertex_list->Next = new_vertex;
    }
    VertexCount++;
}

void Graph::DeleteVertex(int vertex)
{
    Vertex* delete_vertex = FindVertex(vertex);

    if (delete_vertex == nullptr)
    {
        return;
    }

    Vertex* vertex_list = VertexHead;
    if (EmptyVertex())
    {
        return;
    }
    while (vertex_list)
    {
        DeleteEdge(vertex_list->nVertex, vertex);
        vertex_list = vertex_list->Next;
    }

    vertex_list = VertexHead;
    if (vertex_list == delete_vertex)
    {
        VertexHead = vertex_list->Next;
    }
    else
    {
        while (vertex_list)
        {
            if (vertex_list->Next == delete_vertex)
            {
                vertex_list->Next = vertex_list->Next->Next;
                break;
            }
            vertex_list = vertex_list->Next;
        }
    }

    delete delete_vertex;
    VertexCount--;
}

void Graph::AddEdge(int from, int target, int weight)
{
    Vertex* from_vertex = FindVertex(from);
    if (FullEdge(from_vertex))
    {
        cout << "최대간선수 초과"<< endl;
        return;
    }

    Edge* new_edge = CreateEdge(from, target, weight);
    Edge* edge_list = from_vertex->EdgeHead;

    if (EmptyEdge(from_vertex))
    {
        from_vertex->EdgeHead = new_edge;
        from_vertex->nEdgeCount++;
    }

    else
    {
        int exist = -1;
        int input = 2;

        exist = ExistEdge(from, target, weight);
        switch (exist)
        {

        case 0:
            while (edge_list->Next != nullptr)
            {
                edge_list = edge_list->Next;
            }
            edge_list->Next = new_edge;
            from_vertex->nEdgeCount++;
            break;

        case 1:
            cout<< "이미 간선이 존재합니다." << endl;
            cout << "가중치를 변경하시겠습니까?" << endl;
            cout << "변경 O = 1, 변경 X = 0 입력:" << endl;
            cin >> input;
            if (input == 0)
            {
                while (edge_list->TargetVertex->nVertex != target)
                {
                    edge_list = edge_list->Next;
                }
                edge_list->weight = weight;
            }
            else
            {
            }
            break;

        case 2:
            break;
        default:
            break;
        }
    }
}

void Graph::DeleteEdge(int from, int target)
{
    Vertex* from_vertex = FindVertex(from);
    Edge* delete_edge = FindEdge(from, target);
    Edge* edge_list = from_vertex->EdgeHead;

    if (delete_edge == nullptr)
    {
        return;
    }

    if (edge_list == delete_edge)
    {
        from_vertex->EdgeHead = edge_list->Next;
    }

    else
    {
        while (edge_list)
        {
            if (edge_list->Next == delete_edge)
            {
                edge_list->Next = edge_list->Next->Next;
            }
            edge_list = edge_list->Next;
        }
    }

    delete delete_edge;
    from_vertex->nEdgeCount--;
}


void Graph::DeleteVertexList()
{
    Vertex* vertex_list = VertexHead;
    if (EmptyVertex())
    {
        return;
    }

    Vertex* delete_vertex = nullptr;
    while (vertex_list)
    {
        delete_vertex = vertex_list;
        vertex_list = vertex_list->Next;	// NEXT 포인터 저장
        DeleteEdgeList(delete_vertex);		// 간선 리스트 먼저 제거
        delete delete_vertex;				// 제거
        VertexCount--;						// 갯수 감소
    }
    VertexHead = nullptr;
}

void Graph::DeleteEdgeList(Vertex* vertex)
{
    Edge* edge_list = vertex->EdgeHead;
    // 엣지 리스트 확인
    if (EmptyEdge(vertex))
    {
        return;
    }

    Edge* delete_edge = nullptr;
    while (edge_list)
    {
        delete_edge = edge_list;
        edge_list = edge_list->Next;		// NEXT 포인터 저장
        delete delete_edge;					// 제거
        vertex->nEdgeCount--;				// 갯수 감소
    }
    vertex->EdgeHead = nullptr;
}

int Graph::GetVertexCount()
{
    return VertexCount;
}

int Graph::GetEdgeCount(Vertex *vertex)
{
    return vertex->nEdgeCount;
}

void Graph::SetVertex(int data)
{
    if (data > MAX_VERTEX)
    {
        printf("최대 정점 개수 초과\n");
        return;
    }
    for (int i = 0; i < data; i++)
    {
        AddVertex(i);
    }
    MaxEdgeCount = VertexCount - 1;
}

void Graph::SetEdge()
{
    AddEdge(0,7,1);AddEdge(0,9,1);
    AddEdge(1,7,1);AddEdge(1,20,1);
    AddEdge(2,7,1);AddEdge(2,20,1);
    AddEdge(3,7,1);AddEdge(3,20,1);
    AddEdge(4,8,1);
    AddEdge(5,8,1);
    AddEdge(6,8,1);
    AddEdge(7,0,1); AddEdge(7,1,1); AddEdge(7,2,1); AddEdge(7,3,1); AddEdge(7,20,1);AddEdge(7,9,1); AddEdge(7,10,1);
    AddEdge(8,4,1); AddEdge(8,5,1); AddEdge(8,6,1); AddEdge(8,12,1); AddEdge(8,20,1);
    AddEdge(9,0,1);AddEdge(9,7,1);
    AddEdge(10,7,1); AddEdge(10,11,1); AddEdge(10,13,1);
    AddEdge(11,10,1);
    AddEdge(12,8,1);
    AddEdge(13,10,1); AddEdge(13,14,1); AddEdge(13,15,1); AddEdge(13,16,1); AddEdge(13,17,1);AddEdge(13,18,1);
    AddEdge(14,20,1);AddEdge(14,7,1); AddEdge(14,13,1);AddEdge(14,17,1);AddEdge(14,18,1); AddEdge(14,19,1); AddEdge(14,21,1);
    AddEdge(15,13,1);
    AddEdge(16,13,1);
    AddEdge(17,13,1);AddEdge(17,14,1);
    AddEdge(18,13,1);AddEdge(18,14,1);
    AddEdge(19,14,1);
    AddEdge(20,7,1); AddEdge(20,2,1); AddEdge(20,3,1); AddEdge(20,8,1); AddEdge(20,14,1);
    AddEdge(21,14,1);
}

void Graph::SetMatrix()
{
    int column, row = 0;
    column = VertexCount;
    row = VertexCount;

    // 2 dimensional array
    int **mat = nullptr;
    mat = new int*[column];
    for (int i = 0; i < row; i++)
    {
        mat[i] = new int[row];
    }

    // init
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            mat[i][j] = INF;
        }
    }

    // input
    Vertex* vertex = VertexHead;
    Edge* edge = nullptr;

    for (int i = 0; i < row; i++)
    {
        edge = vertex->EdgeHead;
        int idx = 0;
        for (int j = 0; j < vertex->nEdgeCount; j++)
        {
            idx = edge->TargetVertex->nVertex;
            mat[i][idx] = edge->weight;
            edge = edge->Next;
        }
        vertex = vertex->Next;
    }
    Matrix = mat;
}

void Graph::PrintMatrix()
{
    int column, row = 0;
    column = VertexCount;
    row = VertexCount;

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            printf("%2d", Matrix[i][j]);
        }
        printf("\n");
    }
}
