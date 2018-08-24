#include <iostream>

class gauss_matrix
{
public:
    gauss_matrix()
    {
        std::cin >> num_str >> num_col;
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
    void output_matrix()
    {
        for(int i = 0; i < num_str * num_col; ++i)
        {
            if(!(i % num_col)) std::cout << std::endl;
            std::cout << matrix_array[i / num_col][i % num_col] << " ";
        }
    }
    void swap_lines(int const line_one, int const line_two)//номера строк считаются от нуля
    {
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
    void sum_str(int const num_source_str, int const num_dest_str, int start_position)//номера строк считаются от нуля, start_position показывает, с какого столбца начинать сложение
    {
        for(int i = start_position; i < num_col; ++i)
            matrix_array[num_dest_str][i] += matrix_array[num_source_str][i];
    }
    void sub_str(int const num_source_str, int const num_dest_str, int start_position)//номера строк считаются от нуля, из dest вычитается source
    {
        for(int i = start_position; i < num_col; ++i)
            matrix_array[num_dest_str][i] -= matrix_array[num_source_str][i];
    }
    void straight_run()
    {
        
    }
    int get_num_str()
    {
        return num_str;
    }
    int get_num_col()
    {
        return num_str;
    }
    ~gauss_matrix()
    {
        delete [] to_delete;
        delete [] matrix_array;
    }
private:
    void input_matrix()
    {
        for(int i = 0; i < num_str * num_col; ++i)
        {
            std::cin >> matrix_array[i / num_col][i % num_col];
        }
    }
    double** matrix_array;
    double* to_delete;
    int num_str;
    int num_col;
};

int main() {
    gauss_matrix matrix;

    return 0;
}