#include <iostream>

int ** convert(const int * t, size_t n, const size_t * lns, size_t rows);
void rm(int **mtx, int r);
void output(const int*const* mtx, const size_t * lns, int rows);

int main(){
    int ** mtx = nullptr;
    int n = 12;
    int t[12] = {5, 5, 5, 5, 6, 6, 7, 7, 7, 7, 7, 8};
    int rows = 4;
    size_t lns[4] = {4, 2, 5, 1};
    try{
        mtx = convert(t, n, lns, rows);
        output(mtx, lns, rows);
    }catch (const std::bad_alloc &){
        return 2;
    }
    rm(mtx, rows);
}

int ** convert(const int * t, size_t n, const size_t * lns, size_t rows){
    int ** mtx = new int* [rows];
    for(size_t i = 0; i < rows; ++i){
        try{
            mtx[i] = new int[lns[i]];
        }catch(const std::bad_alloc &){
            rm(mtx, i);
            throw;
        }
    }

    size_t k = 0;
    size_t rows_check = 0;
    for(size_t i = 0; i < n; ++i){
        if(rows_check < lns[k]){
            mtx[k][rows_check] = t[i];
        }
        rows_check += 1;
        if(rows_check == lns[k]){
            rows_check = 0;
            k += 1;
        }
    }
    return mtx;
}

void rm(int **mtx, int r){
    for(size_t i = 0; i < r; ++i){
        delete[] mtx[i];
    }
    delete[] mtx;
}

void output(const int*const* mtx, const size_t * lns, int rows){
    for(size_t i = 0; i < rows; ++i){
        for(size_t j = 0; j < lns[i]; ++j){
            std::cout << mtx[i][j] << " ";
        }
        std::cout << "\n";
    }
}