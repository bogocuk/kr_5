
#include <iostream>
using namespace std;

/*==========================================
        ШАБЛОННЫЙ КЛАСС МНОЖЕСТВА
==========================================*/
template <class T>
class Set
{
private:
    T arr[100];
    int size;

public:
    Set()
    {
        size = 0;
    }

    void add(T x)
    {
        if (!(*this > x))
            arr[size++] = x;
    }

    // > принадлежит ли элемент множеству
    bool operator>(T x) const
    {
        for (int i = 0; i < size; i++)
            if (arr[i] == x)
                return true;

        return false;
    }

    // * пересечение множеств
    Set operator*(const Set& other) const
    {
        Set result;

        for (int i = 0; i < size; i++)
            if (other > arr[i])
                result.add(arr[i]);

        return result;
    }

    // < подмножество
    bool operator<(const Set& other) const
    {
        for (int i = 0; i < size; i++)
            if (!(other > arr[i]))
                return false;

        return true;
    }

    void print() const
    {
        cout << "{ ";
        for (int i = 0; i < size; i++)
            cout << arr[i] << " ";
        cout << "}" << endl;
    }
};


/*==========================================
            БАЗОВЫЙ КЛАСС MATRIX
==========================================*/
class Matrix
{
private:
    int rows;
    int cols;

protected:
    int** a;
    static int total;

public:
    Matrix(int r, int c)
    {
        rows = r;
        cols = c;

        a = new int* [rows];
        for (int i = 0; i < rows; i++)
            a[i] = new int[cols];

        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                a[i][j] = 0;

        total += rows * cols;
    }

    virtual ~Matrix()
    {
        for (int i = 0; i < rows; i++)
            delete[] a[i];

        delete[] a;

        total -= rows * cols;
    }

    int getRows() const { return rows; }
    int getCols() const { return cols; }

    void input()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                // Выводим (i + 1) и (j + 1), чтобы пользователь видел 1 вместо 0
                cout << "Строка " << i + 1 << ", Столбец " << j + 1 << " = ";
                cin >> a[i][j];
            }
            cout << endl; // Добавим пустую строку для красоты между рядами
        }
    }


    static int getTotal()
    {
        return total;
    }

    virtual void print() const = 0;
    virtual int sum() const = 0;

    bool operator==(const Matrix& other) const
    {
        return rows == other.rows &&
            cols == other.cols &&
            sum() == other.sum();
    }
};

int Matrix::total = 0;


/*==========================================
            ОБЫЧНАЯ МАТРИЦА
==========================================*/
class SimpleMatrix : public Matrix
{
public:
    SimpleMatrix(int r, int c) : Matrix(r, c) {}

    void print() const override
    {
        cout << "SimpleMatrix:\n";

        for (int i = 0; i < getRows(); i++)
        {
            for (int j = 0; j < getCols(); j++)
                cout << a[i][j] << " ";

            cout << endl;
        }
    }

    int sum() const override
    {
        int s = 0;

        for (int i = 0; i < getRows(); i++)
            for (int j = 0; j < getCols(); j++)
                s += a[i][j];

        return s;
    }
};


/*==========================================
            КВАДРАТНАЯ МАТРИЦА
==========================================*/
class SquareMatrix : public Matrix
{
public:
    SquareMatrix(int n) : Matrix(n, n) {}

    void print() const override
    {
        cout << "SquareMatrix:\n";

        for (int i = 0; i < getRows(); i++)
        {
            for (int j = 0; j < getCols(); j++)
                cout << a[i][j] << " ";

            cout << endl;
        }
    }

    int sum() const override
    {
        int s = 0;

        for (int i = 0; i < getRows(); i++)
            s += a[i][i];

        return s;
    }
};


/*==========================================
    СПЕЦИАЛИЗАЦИЯ МНОЖЕСТВА ДЛЯ MATRIX*
==========================================*/
template <>
class Set<Matrix*>
{
private:
    Matrix* arr[100];
    int size;

public:
    Set()
    {
        size = 0;
    }

    void add(Matrix* x)
    {
        if (!(*this > x))
            arr[size++] = x;
    }

    bool operator>(Matrix* x) const
    {
        for (int i = 0; i < size; i++)
            if (*arr[i] == *x)
                return true;

        return false;
    }

    Set operator*(const Set& other) const
    {
        Set result;

        for (int i = 0; i < size; i++)
            if (other > arr[i])
                result.add(arr[i]);

        return result;
    }

    bool operator<(const Set& other) const
    {
        for (int i = 0; i < size; i++)
            if (!(other > arr[i]))
                return false;

        return true;
    }

    void print() const
    {
        for (int i = 0; i < size; i++)
        {
            arr[i]->print();
            cout << endl;
        }
    }
};


/*==========================================
                MAIN
==========================================*/
int main()
{
    setlocale(0, "");

    // ---------- Числа ----------
    Set<int> A, B;

    A.add(1);
    A.add(2);
    A.add(3);

    B.add(2);
    B.add(3);
    B.add(4);

    cout << "A = ";
    A.print();

    cout << "B = ";
    B.print();

    cout << "2 принадлежит A? ";
    cout << (A > 2 ? "Да" : "Нет") << endl;

    cout << "A * B = ";
    (A * B).print();

    cout << "A подмножество B? ";
    cout << (A < B ? "Да" : "Нет") << endl;


    // ---------- Символы ----------
    Set<char> C1, C2;

    C1.add('a');
    C1.add('b');
    C1.add('c');

    C2.add('b');
    C2.add('c');
    C2.add('d');

    cout << "\nC1 = ";
    C1.print();

    cout << "C2 = ";
    C2.print();

    cout << "C1 * C2 = ";
    (C1 * C2).print();


    // ---------- Матрицы ----------
    Matrix* m1 = new SimpleMatrix(2, 2);
    Matrix* m2 = new SquareMatrix(3);

    cout << "\nВведите элементы обычной матрицы:\n";
    m1->input();

    cout << "\nВведите элементы квадратной матрицы:\n";
    m2->input();

    Set<Matrix*> M;

    M.add(m1);
    M.add(m2);

    cout << "\nМножество матриц:\n";
    M.print();

    cout << "Всего элементов во всех матрицах: ";
    cout << Matrix::getTotal() << endl;

    delete m1;
    delete m2;

    return 0;
}


