#include <iostream>
#include <vector>
#include <algorithm>

long int const INF = 1e6 + 10;

int main() {
    int count_node;
    std::cin >> count_node;
    int count_edge;
    std::cin >> count_edge;
    std::vector<std::vector<int>> graph(count_node + 1);
    for (int i = 0; i <= count_node; ++i) {
        for (int j = 0; j <= count_node; ++j) {
            graph[i].push_back(0);
        }
    }
    int u, v, w;
    for (int i = 0; i < count_edge; ++i) {  // ��������� ������� ��������� ��� �����
        std::cin >> u >> v >> w;
        graph[u][v] = w;
        graph[v][u] = w;
    }
    std::vector<int> permutations;  // � std::vector<int> permutations ���������� � ������ ������������ ������������ ���� ������ �� 1 �� count_node 
    for (int i = 0; i < count_node; ++i) {  // ��������� ��������� ������������������ �� 1 �� node_count
        permutations.push_back(i + 1);
    }
    int min_sum_with_return = INF;
    int min_sum_without_return = INF;
    int cur_sum;
    do {
        cur_sum = 0;  // ����� ���� ��� ������� ������������ ������
        for (int i = 1; i < count_node; ++i) {
            int I = permutations[i];  // i - �� �������� � ������� ������������
            int I_ = permutations[i - 1];  // (i - 1) - �� �������� � ������� ������������
            if (!graph[I][I_]) {  // ���� ��� ����� ����� i � (i-1) ��������, ���� �� ���������� 
                cur_sum = INF;
                break;
            }
            else {
                cur_sum += graph[I][I_];  
            }
        }
        int last_node = permutations[count_node-1];  // ���������
        int first_node = permutations[0];  // � ������ ������� � ������� i - �� ������������
        if (graph[first_node][last_node]) {  // ���� ���� ����� ����� ��������� � ������ ��������� � ������� ������������
            if (cur_sum + graph[first_node][last_node] < min_sum_with_return) {  // ���� �����, �������� ����� ������������ ���� � ���������
                min_sum_with_return = cur_sum + graph[first_node][last_node];
            }
        }
        else {  // ���� ����� ���
            if (cur_sum + graph[first_node][last_node] < min_sum_without_return) {  // ���� �����, �������� ����� ������������ ���� ��� ��������
                min_sum_without_return = cur_sum + graph[first_node][last_node];
            }
        }
    } while (std::next_permutation(permutations.begin(), permutations.end()));
    if (min_sum_without_return == INF && min_sum_with_return == INF) {
        std::cout << "the way does not exist\n";
    }
    else if (min_sum_without_return == INF) {
        std::cout << "the length of the way with return " << min_sum_with_return << "\n";
    }
    else {
        std::cout << "the length of the way without return " << min_sum_without_return << "\n";
    }
}

/*
3
3
1 2 10
1 3 1
2 3 1
*/
/*
4
6
1 2 10
1 3 3
1 4 3
2 3 2
2 4 1
3 4 5
*/
/*
4
4
1 2 10
1 3 3
2 3 2
3 4 5
*/