#include <iostream>
using namespace std;

// ---------------------------------------------------------
// BƯỚC 1: KHAI BÁO TRƯỚC (FORWARD DECLARATION)
// Phải khai báo trước để các lớp nhận diện được nhau
// ---------------------------------------------------------
class Matrix;
class Vector;

// ---------------------------------------------------------
// BƯỚC 2: ĐỊNH NGHĨA LỚP VECTOR
// ---------------------------------------------------------
class Vector {
private:
    double* coords; // Mảng chứa tọa độ
    int n;          // Số chiều của vector

public:
    Vector() { n = 0; coords = NULL; }

    Vector(int N, double x) { // tạo vector có N chiều, mỗi ô có giá trị x
        n = N;
        coords = new double[n];
        for (int i = 0; i < n; i++) coords[i] = x;
    }

    Vector(const Vector& a) {
        n = a.n;
        coords = new double[n];
        for (int i = 0; i < n; i++) coords[i] = a.coords[i];
    }

    ~Vector() {
        if (coords != NULL) delete[] coords;
    }

    void nhap() {
        cout << "Nhap so chieu cua Vector: "; cin >> n;
        coords = new double[n];
        for (int i = 0; i < n; i++) {
            cout << "Toa do [" << i << "] = ";
            cin >> coords[i];
        }
    }

    void xuat() {
        cout << "( ";
        for (int i = 0; i < n; i++) cout << coords[i] << " ";
        cout << ")" << endl;
    }

    int cong(const Vector& a) { // return 1 nếu cộng được
        if (n != a.n) return 0;
        for (int i = 0; i < n; i++) coords[i] += a.coords[i];
        return 1;
    }

    int tru(Vector a) { // return 1 nếu trừ được
        if (n != a.n) return 0;
        for (int i = 0; i < n; i++) coords[i] -= a.coords[i];
        return 1;
    }

    void nhank(const double& k) {
        for (int i = 0; i < n; i++) coords[i] *= k;
    }

    double tichVoHuong(const Vector& a) {
        if (n != a.n) return 0;
        double sum = 0;
        for (int i = 0; i < n; i++) sum += coords[i] * a.coords[i];
        return sum;
    }

    // Khai báo hàm bạn: Cho phép hàm này truy cập vào private của Vector
    friend Vector multiply(const Matrix& a, const Vector& b);
};

// ---------------------------------------------------------
// BƯỚC 3: ĐỊNH NGHĨA LỚP MATRIX
// ---------------------------------------------------------
class Matrix {
private:
    int m; // dòng
    int n; // cột
    double** elements;

public:
    Matrix() { m = 0; n = 0; elements = NULL; }

    ~Matrix() {
        if (elements != NULL) {
            for (int i = 0; i < m; i++) delete[] elements[i];
            delete[] elements;
        }
    }

    Matrix(const Matrix& a) {
        m = a.m; n = a.n;
        elements = new double* [m];
        for (int i = 0; i < m; i++) {
            elements[i] = new double[n];
            for (int j = 0; j < n; j++) elements[i][j] = a.elements[i][j];
        }
    }

    void nhap() {
        cout << "Nhap so dong m: "; cin >> m;
        cout << "Nhap so cot n: "; cin >> n;
        elements = new double* [m];
        for (int i = 0; i < m; i++) {
            elements[i] = new double[n];
            for (int j = 0; j < n; j++) {
                cout << "Phan tu [" << i << "][" << j << "] = ";
                cin >> elements[i][j];
            }
        }
    }

    void xuat() {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) cout << elements[i][j] << "\t";
            cout << endl;
        }
    }

    int cong(const Matrix& a) { // return 1 nếu cộng được
        if (m != a.m || n != a.n) return 0;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                elements[i][j] += a.elements[i][j];
        return 1;
    }

    void nhank(const double& k) { // nhân với 1 số k
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                elements[i][j] *= k;
    }

    int nhan(const Matrix& a) { // nhân với 1 CMatrix, return 1 nếu nhân được
        if (n != a.m) return 0;

        // Tạo mảng tạm để chứa kết quả nhân
        double** temp = new double* [m];
        for (int i = 0; i < m; i++) {
            temp[i] = new double[a.n];
            for (int j = 0; j < a.n; j++) {
                temp[i][j] = 0;
                for (int k = 0; k < n; k++) temp[i][j] += elements[i][k] * a.elements[k][j];
            }
        }

        // Xóa mảng cũ và gán mảng mới
        for (int i = 0; i < m; i++) delete[] elements[i];
        delete[] elements;

        n = a.n;
        elements = temp;
        return 1;
    }

    // Khai báo hàm bạn: Cho phép hàm này truy cập vào private của Matrix
    friend Vector multiply(const Matrix& a, const Vector& b);
};

// ---------------------------------------------------------
// BƯỚC 4: CÀI ĐẶT HÀM BẠN (FRIEND FUNCTION)
// Hàm này đứng độc lập bên ngoài, không thuộc lớp nào cả
// ---------------------------------------------------------
Vector multiply(const Matrix& a, const Vector& b) {
    // Điều kiện nhân: Số cột của Ma trận (a.n) phải BẰNG số chiều của Vector (b.n)
    if (a.n != b.n) {
        cout << "\n[LOI] So cot cua Ma tran khac so chieu cua Vector. Khong the nhan!" << endl;
        return Vector();
    }

    // Kết quả phép nhân là 1 Vector mới có số chiều bằng số dòng của Ma trận (a.m)
    Vector kq(a.m, 0.0);

    for (int i = 0; i < a.m; i++) {
        kq.coords[i] = 0;
        for (int j = 0; j < a.n; j++) {
            // Nhờ là hàm bạn (friend), ta có thể chọc thẳng vào a.elements và b.coords
            kq.coords[i] += a.elements[i][j] * b.coords[j];
        }
    }
    return kq;
}

// ---------------------------------------------------------
// HÀM MAIN KIỂM TRA
// ---------------------------------------------------------
int main() {
    cout << "--- 1. NHAP MA TRAN ---" << endl;
    Matrix mat;
    mat.nhap();

    cout << "\n--- 2. NHAP VECTOR ---" << endl;
    Vector vec;
    vec.nhap();

    cout << "\nMa tran vua nhap:" << endl;
    mat.xuat();

    cout << "\nVector vua nhap:" << endl;
    vec.xuat();

    cout << "\n--- KET QUA NHAN MA TRAN VOI VECTOR ---" << endl;
    Vector ketQua = multiply(mat, vec);

    // Xuất kết quả nếu nhân thành công (số chiều > 0)
    ketQua.xuat();

    return 0;
}