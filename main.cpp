#include <iostream>
#include <fstream>
#include <unistd.h>

bool create_world(bool **&arr, int rows, int cols) {
    arr = new bool *[rows]();
    for (int i = 0; i < rows; ++i) {
        arr[i] = new bool[cols]();
    }
    return true;
}

bool delete_array(bool **&arr, int rows) {
    for (int i = 0; i < rows; ++i) {
        delete[] arr[i];
    }
    delete[] arr;
    arr = nullptr;
    return true;
}

bool read_galaxy_size(std::ifstream &f, int &rows, int &cols) {

    if (f.is_open()) {
        f >> rows;
        f >> cols;
    } else {
        std::cout << "I couldn't open the file!" << std::endl;
        return false;
    }
    return true;
}

bool read_cells(std::ifstream &f, bool **arr, int rows, int cols) {
    for (int i, j; (f >> i) && (f >> j);) {
        if (((0 <= i) && (i < rows)) && ((0 <= j) && (j < cols))) {
            arr[i][j] = true;
        }
    }
    return true;
}

void print_array(bool **arr, int rows, int cols) {
    std::system("clear");
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << (arr[i][j] ? "*" : "-")
                      << (j < (cols - 1) ? " " : "\n");
        }
    }
}

void print_generation(int num) {
    std::cout << "Generation: " << num << " \t";
}

void print_alive_cells(int cells) {
    std::cout << "Alive cells: " << cells << std::endl;
    sleep(1);
}

void print_result(int cells, bool ch_temp) {
    if (!ch_temp) {
        std::cout << "The world has stagnated. Game over." << std::endl;
    }
    if (cells == 0) {
        std::cout << "All cells are dead. Game over." << std::endl;
    }
}

int count_alive_cells(bool **arr, int rows, int cols) {
    int cells = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cells += arr[i][j];
        }
    }
    return cells;
}

void checking_neighboring(bool **arr, bool **arr_swap, int i, int j, int alives, bool &ch_temp) {
    if (alives < 2 || (3 < alives)) {
        arr[i][j] ? (arr_swap[i][j] = !(arr[i][j]), ch_temp = true) : arr[i][j];
    } else if (alives == 3) {
        arr[i][j] ? arr[i][j] : (arr_swap[i][j] = !(arr[i][j]), ch_temp = true);
    }
}

int aliving_neighbors(bool **arr, int rows, int cols, int i, int j) {
    int alives = 0;
    for (int x = (i - 1); x <= (i + 1); x++) {
        if ((x < 0) || (x > (rows - 1))) {
            continue;
        }
        for (int y = (j - 1); y <= (j + 1); y++) {
            if ((y < 0) || (y > (cols - 1))) {
                continue;
            }
            if ((x == i) && (y == j)) {
                continue;
            }
            alives += arr[x][y];
        }
    }
    return alives;
}

int main(int argc, char **argv) {

    int rows;
    bool **arr = nullptr;
    bool **arr_swap = nullptr;
    std::ifstream f("in.txt");
    int cols;
    int cells = -1;
    bool ch_temp;

    if (!read_galaxy_size(f, rows, cols)) {
        return 0;
    }
    create_world(arr, rows, cols);
    read_cells(f, arr, rows, cols);
    create_world(arr_swap, rows, cols);


    for (int num = 1, count = 0; ((cells != 0) && (count < 2)); num++) {
        ch_temp = false;
        cells = count_alive_cells(arr, rows, cols);
        print_array(arr, rows, cols);
        print_generation(num);
        print_alive_cells(cells);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                arr_swap[i][j] = arr[i][j];
                int alives = aliving_neighbors(arr, rows, cols, i, j);
                checking_neighboring(arr, arr_swap, i, j, alives, ch_temp);
            }
        }
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                arr[i][j] = arr_swap[i][j];
            }
        }
        if (!ch_temp) {
            count++;
        }
    }
    print_result(cells, ch_temp);

    delete_array(arr_swap, rows);
    delete_array(arr, rows);

    f.close();

    return 0;
}
