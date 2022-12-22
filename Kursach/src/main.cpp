#include <iostream>
#include <math.h>
#include <cassert>

class Gauss {
private:
    int n = 0, x_count;
    float temp;
    float** matrix_A;
    float** vector_B;
    float** matrix_answer;
    float** y;
    float** x;
    double max_value;
    int max_value_index;
public:
    Gauss() {
        n = 3;
        x_count = 0;
    };
    double f(int select, double x) {
        switch (select)
        {
        case 0:
            return 1;
            break;
        case 1:
            return x;
            break;
        case 2:
            return pow(exp(1), -1 * x);
            break;
        }
        return 0.0;
    }

    void out_matrix(float** mat, int n, int m) {
       
        for (int i = 0; i < n; i++) {
            std::cout << std::endl;
            for (int j = 0; j < m; j++) {
                std::cout << mat[i][j] << " ";
            }
        }
        std::cout << std::endl;
    }
    float** get_matrix(int n, int m) {
        float** matrix = new float* [n];
        for (int i = 0; i < n; i++) {
            matrix[i] = new float[m];
        }
        return matrix;
    };
    void sizematrix() {
        bool flag = true;
        std::cout << "Input count of X: ";
        std::cin >> x_count;
        x = get_matrix(x_count, 1);
        y = get_matrix(x_count, 1);
        for (int i = 0; i < x_count; i++) {
            std::cout << "x[" << i << "]: ";
            std::cin >> x[i][0];
        }
        for (int i = 0; i < x_count; i++) {
            std::cout << "y[" << i << "]: ";
            std::cin >> y[i][0];
        }
        matrix_A = get_matrix(n, n + 1);
        vector_B = get_matrix(n, 1);
        float phi_k, phi_l;
        for (int k = 0; k < n; k++) {
            for (int l = 0; l < n; l++) {
                temp = 0;
                for (int i = 0; i < x_count; i++) {
                    phi_k = f(k, x[i][0]);
                    phi_l = f(l, x[i][0]);
                    temp += phi_k * phi_l;
                }
                matrix_A[k][l] = temp;
            }
        }

        for (int k = 0; k < n; k++) {
            temp = 0;
            for (int i = 0; i < x_count; i++)
                temp += y[i][0] * f(k, x[i][0]);
            vector_B[k][0] = temp;
        }
        for (int i = 0; i < n; i++) {
            matrix_A[i][n] = vector_B[i][0];
        }
    };
    void matrix_up() {
        std::cout << "\nMatrix A: " << std::endl;
        out_matrix(matrix_A, n, n + 1);
    }
 
    void swap_rows(float** matrix, int n, int i, int j)
    {

        for (int k = 0; k <= n; k++)
            std::swap(matrix[i][k], matrix[j][k]);
    }

    void averse() {
        // Прямой ход Гаусса
        temp = 0;

        for (int k = 0; k < n; k++) {
            max_value = abs(matrix_A[k][k]);
            max_value_index = k;

            for (int i = k + 1; i < n; i++)
                if (abs(matrix_A[i][k]) > max_value) {
                    max_value = abs(matrix_A[i][k]);
                    max_value_index = i;
                }

            assert(matrix_A[max_value_index][k] != 0);

            if (k != max_value_index) {
                swap_rows(matrix_A, n, k, max_value_index);
            }


            for (int i = n; i >= k; i--) {
                matrix_A[k][i] /= matrix_A[k][k];
            }
            for (int i = k + 1; i < n; i++) {
                temp = matrix_A[i][k] / matrix_A[k][k];
                for (int j = k + 1; j <= n; j++) {
                    matrix_A[i][j] -= matrix_A[k][j] * temp;
                }
                matrix_A[i][k] = 0;
            }
           
        }
    };
    void reverse() {
        // Обратный ход Гаусса 
        matrix_answer = get_matrix(n, 1);
        matrix_answer[n - 1][0] = matrix_A[n - 1][n];
        for (int i = n - 2; i >= 0; i--)
        {
            matrix_answer[i][0] = matrix_A[i][n];
            for (int j = i + 1; j < n; j++) {
                matrix_answer[i][0] -= matrix_A[i][j] * matrix_answer[j][0];
            }
        }
        
        
    };
    void matrix_answer_out() {
        std::cout << "Matrix C\n";
        out_matrix(matrix_answer, n, 1);
    }


    void output_statistic() {
        float new_y, delta, max_delta, j = 0;
        int max_delta_index;
        
        for (int i = 0; i < x_count; i++) {
            new_y = 0;
            for (int k = 0; k < n; k++) {
                new_y += matrix_answer[k][0] * f(k, x[i][0]);
            }
            delta = fabs(new_y - y[i][0]);
            if (i == 0) {
                max_delta = delta;
                max_delta_index = i;
            }
            if (max_delta < delta) {
                max_delta = delta;
                max_delta_index = i;
            }
            j += delta * delta;
            std::cout << "new_y and delta: " << new_y << " " << delta << std::endl;
        }
        std::cout << "max_delta and X: " << max_delta << " " << x[max_delta_index][0];
        std::cout << std::endl << "J = " << j << std::endl;
    };

    float get_alg_addition(float** mat, int n, int x, int y) {
        float** algebric_addition = get_matrix(n - 1, n - 1);
        int now_row = 0, now_column = 0;
        for (int i = 0; i < n; i++) {
            if (i == x) continue;
            for (int j = 0; j < n; j++) {
                if (j == y) continue;
                algebric_addition[now_row][now_column] = mat[i][j];
                now_column++;
            }
            now_column = 0;
            now_row++;
        }
        float result = rec_determinant(algebric_addition, n - 1);
        del_matrix(algebric_addition, n - 1);
        if ((x + y) % 2 == 1) return -result;
        else return result;
    };
    float rec_determinant(float** mat, int n) {
        // рекурентное вычесление детерминанта
        if (n == 1)
            return mat[0][0];
        if (n == 2)
            return mat[0][0] * mat[1][1] - mat[1][0] * mat[0][1];
        float determinant = 0;
        for (int i = 0; i < n; i++) {
            float result = get_alg_addition(mat, n, i, 0);
            determinant += mat[i][0] * result;
        }
        return determinant;
    };
    void del_matrix(float** mat, int n) {
        for (int i = 0; i < n; i++) {
            delete[] mat[i];
        }
        delete[] mat;
        mat = nullptr;
    };
 
    ~Gauss() {
        del_matrix(matrix_A, n);
        del_matrix(vector_B, n);
        del_matrix(matrix_answer, n);
        del_matrix(y, n);
        del_matrix(x, n);
    };
};



int main() {
    Gauss* a = new Gauss;
    a->sizematrix();
    a->matrix_up();
    a->averse();
    a->reverse();
    std::cout << std::endl;

    a->matrix_answer_out();
    std::cout << std::endl;
    a->output_statistic();
}