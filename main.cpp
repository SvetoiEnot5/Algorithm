#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <ctime>

bool isReachable(const std::vector<std::vector<int>>& matrix, int src, int dest, int n)
{
	--src;
	--dest;
	// чтобы отслеживать, открыта вершина или нет
	std::vector<bool> discovered(n);
	// создаем queue, где будут соседи
	std::queue<int> q;
	// помечаю исходную вершину как обнаруженную
	discovered[src] = true;
	// поставил исходную вершину в queue
	q.push(src);
	// цикл до тех пор, пока queue не станет пустой
	while (!q.empty())
	{
		// удалил передний узел из очереди
		int v = q.front();
		q.pop();
		if (v == dest) {
			return true;
		}
		// для каждой вершины смотрю соседей
		for (size_t u = 0; u < n; ++u)
		{
			if (!discovered[u] && matrix[v][u] != 0)
			{
				// помечаю ее как обнаруженную и ставлю в queue
				discovered[u] = true;
				q.push(u);
			}
		}
	}
	return false;
}

bool NextSet(std::vector<int>& vertex, int n)
{
	int j = n - 2;
	while (j != -1 && vertex[j] >= vertex[j + 1]) j--;
	if (j == -1)
		return false; // больше перестановок нет
	int k = n - 1;
	while (vertex[j] >= vertex[k]) k--;
	std::swap(vertex[j], vertex[k]);
	int l = j + 1, r = n - 1; // сортируем оставшуюся часть последовательности
	while (l < r)
		std::swap(vertex[l++], vertex[r--]);
	return true;
}

int main(int argc, char* argv[]) {
	int start = clock();
	int n = 0;
	std::string str;
	std::ifstream f_in(argv[1]);
	std::ofstream f_out(argv[2]);
	f_in >> str; // первое число в файле -- количество вершин
	for (size_t k = 0; k < str.size(); ++k) {
		if (str[k] > '9' || str[k] < '0') {
			return 0;
		}
	}
	n = std::stoi(str);
	//создание двумерного массива для хранения данных
	std::vector<std::vector<int>> matrix;
	std::vector<int> some_vec;
	// Чтение матрицы смежности из файла
	// 0 -- не связаны, остальные числа -- вес пути
	for (size_t i = 0; i < n; ++i) {
		for (size_t j = 0; j < n; ++j) {
			f_in >> str;
			for (size_t k = 0; k < str.size(); ++k) {
				if (str[k] > '9' || str[k] < '0' || str[0] == '-') {
					return 0;
				}
			}
			some_vec.push_back(std::stoi(str));
		}
		matrix.push_back(some_vec);
		some_vec.clear();
	}
	if (argc == 4) {
		return 0;
	}
	std::vector<int> vertex;
	for (size_t i = 1; i <= n; ++i) {
		vertex.push_back(i);
	}
	int counter_possible = 0;
	std::vector<int> path;
	bool flag = true;
	for (int i = 0; i < vertex.size() - 1; ++i) {
		if (!isReachable(matrix, vertex[i], vertex[i + 1], n)) {
			flag = false;
			break;
		}
	}
	while (NextSet(vertex, n)) {
		flag = true;
		for (int i = 0; i < vertex.size()-1; ++i) {
			if (!isReachable(matrix, vertex[i], vertex[i + 1], n)) {
				flag = false;
				break;
			}
		}
		if (flag == true) {
			break;
		}
	}
	if (flag == true) {
		for (auto& x : vertex) {
			f_out << x << " ";
		}
		f_out << std::endl;
	}
	else {
		f_out << "Path doesn't exist" << std::endl;
	}
	f_in.close();
	f_out.close();
	int end = clock();
	std::cout << (static_cast<double>(end) - static_cast<double>(start)) /
		CLOCKS_PER_SEC << std::endl;
	return 0;
}
