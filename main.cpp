#include <iostream>

class gauss_matrix
{
public:
    gauss_matrix()
    {
        std::cin >> num_str >> num_col;
        answer = new double [num_col];
        for(int i = 0; i < num_col; ++i)
            answer[i] = 0.0;
        num_col++;
        matrix_array = new double* [num_str];
        matrix_array[0] = new double [num_str * num_col];
        to_delete = matrix_array[0];//чтобы при свапе строк не потерять указатель на память, сохраняем его сразу
        for(int i = 1; i < num_str; ++i)
        {
            matrix_array[i] = matrix_array[i - 1] + num_col;
        }
        input_matrix();
    }
    void gauss_method()
    {
        straight_run();
        if(back_run())
            output_answer();
    }
    ~gauss_matrix()
    {
        delete [] to_delete;
        delete [] matrix_array;
        delete [] answer;
    }
private:
    void output_answer()
    {
        prepare_answer();
        std::cout << "YES\n";
        for(int i = 0; i < num_col - 2; ++i)
            std::cout << answer[i] << " ";
        std::cout << answer[num_col - 2];
    }
    void swap_lines(int const line_one, int const line_two)//номера строк считаются от нуля
    {
        if(line_one == line_two) return;
        double* temp = matrix_array[line_one];
        matrix_array[line_one] = matrix_array[line_two];
        matrix_array[line_two] = temp;
    }
    void mul_scalar_str(double const scalar, int const line_num)//номера строк считаются от нуля, скаляр не должен быть нулем
    {
        if(!scalar)
        {
            std::cout << "Error: scalar is zero" << std::endl;
            return;
        }
        for(int i = 0; i < num_col; ++i)
            matrix_array[line_num][i] *= scalar;
    }
    void sub_str(int const num_source_str, int const num_dest_str)//номера строк считаются от нуля, из dest вычитается source
    {
        for(int i = 0; i < num_col; ++i)
            matrix_array[num_dest_str][i] -= matrix_array[num_source_str][i];
    }
    void straight_run()
    {
        int N = std::min(num_str, num_col - 1);
        for(int i = 0; i < N; ++i)
        {
            int num_main_str = num_str_max_elem(i);
            if(num_main_str == -1)
                continue;
            swap_lines(i, num_main_str);
            for(int j = i; j < num_str; ++j)
                if(matrix_array[j][i] > eps || matrix_array[j][i] < -eps)
                {
                    mul_scalar_str(1 / matrix_array[j][i], j);
                    if(j != i)
                        sub_str(i, j);
                }
        }
    }
    int back_run()
    {
        int new_position = -1;
        for(int i = num_str - 1; i >= 0; --i)
        {
            if(!count_not_zeros(i))
            {
                if(matrix_array[i][num_col - 1] > eps || matrix_array[i][num_col - 1] < -eps)//правая часть ненулевая, а левая нулевая
                {
                    std::cout << "NO";
                    return 0;
                }
                else if(num_col - 1 > i + 1)//переменных больше, чем уравнений
                {
                    std::cout << "INF";
                    return 0;
                }
                else continue;
            }
            if(num_col - 1 > i + 1)//переменных больше, чем уравнений
            {
                std::cout << "INF";
                return 0;
            }
            new_position = i;//первая (снизу) ненулевая строка
            break;
        }
        if(new_position == -1)return 0;
        else
        {
            for(int i = new_position; i != -1; --i)
            {
                double semi_answer = 0;
                for(int j = num_col - 2; j > i; --j)
                    semi_answer += answer[j] * matrix_array[i][j];
                answer[i] = (matrix_array[i][num_col - 1] - semi_answer) / matrix_array[i][i];
            }
        }
        return 1;
    }
    int count_not_zeros(int num_of_str)//считает количество ненулевых элементов строки
    {
        int answer = 0;
        for(int i = 0; i < num_col - 1; ++i)
            if(matrix_array[num_of_str][i] > eps || matrix_array[num_of_str][i] < -eps)//числа с плавающей точкой плохо сравниваются с нулём
                ++answer;
        return answer;
    }
    void prepare_answer()//делает красивый нуль в ответе :-)
    {
        for(int i = 0; i < num_col - 1; ++i)
        {
            if(answer[i] < eps && answer[i] > - eps)
                answer[i] = 0.0;
        }
    }
    int num_str_max_elem(int const num_column)//ищет максимальный элемент в столбце, возвращает номер строки с ним
    {
        int answer = num_column;
        double max = matrix_array[num_column][num_column];
        for(int i = num_column; i < num_str; ++i)//строки с номерами от 0 до num_column уже обработаны
        {
            if(matrix_array[i][num_column] > max)
            {
                max = matrix_array[i][num_column];
                answer = i;
            }
        }
        if(!max) return -1;
        return answer;
    }
    void input_matrix()
    {
        for(int i = 0; i < num_str * num_col; ++i)
            std::cin >> matrix_array[i / num_col][i % num_col];
    }
    double** matrix_array;//матрциа СЛАУ
    double* to_delete;//указатель на память с матрицей СЛАУ, так как иначе он теряется при свапе строк
    double* answer;//массив с корнями СЛАУ
    double eps = 0.0000001;//точность вычислений, всё, что меньше по модулю, приравнивается к нулю
    int num_str;//количество строк в матрице СЛАУ
    int num_col;//количество столбцов в матрице СЛАУ
};

int main() {
    gauss_matrix matrix;
    matrix.gauss_method();
    return 0;
}