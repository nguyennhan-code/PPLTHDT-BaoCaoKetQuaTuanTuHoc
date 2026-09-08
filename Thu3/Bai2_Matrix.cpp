#include <iostream>
#include <cmath>
using namespace std;

class Matrix {
private:
    int n;          // Kích thước ma trận vuông n x n
    double** a;     // Con trỏ cấp 2 để cấp phát mảng 2 chiều

    // Hàm hỗ trợ tính định thức bằng đệ quy (ẩn bên trong lớp)
    double calcDet(double** mat, int size) {
        if (size == 1) return mat[0][0];
        if (size == 2) return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];

        double det = 0;
        // Tạo ma trận con để đệ quy
        double** subMat = new double* [size - 1];
        for (int i = 0; i < size - 1; i++) subMat[i] = new double[size - 1];

        for (int x = 0; x < size; x++) {
            int subI = 0;
            for (int i = 1; i < size; i++) {
                int subJ = 0;
                for (int j = 0; j < size; j++) {
                    if (j == x) continue;
                    subMat[subI][subJ] = mat[i][j];
                    subJ++;
                }
                subI++;
            }
            det += (pow(-1, x) * mat[0][x] * calcDet(subMat, size - 1));
        }
        // Giải phóng bộ nhớ ma trận con
        for (int i = 0; i < size - 1; i++) delete[] subMat[i];
        delete[] subMat;

        return det;
    }

public:
    // 1. Phương thức khởi tạo mặc định
    Matrix(int size = 2) {
        n = size;
        a = new double* [n];
        for (int i = 0; i < n; i++) {
            a[i] = new double[n];
            for (int j = 0; j < n; j++) {
                a[i][j] = 0.0;
            }
        }
    }

    // Phương thức khởi tạo sao chép (Bắt buộc phải có để gán / trả về Matrix)
    Matrix(const Matrix& other) {
        n = other.n;
        a = new double* [n];
        for (int i = 0; i < n; i++) {
            a[i] = new double[n];
            for (int j = 0; j < n; j++) {
                a[i][j] = other.a[i][j];
            }
        }
    }

    // 2. Phương thức hủy
    ~Matrix() {
        for (int i = 0; i < n; i++) {
            delete[] a[i]; // Giải phóng từng hàng
        }
        delete[] a;        // Giải phóng con trỏ cột
    }

    // 3. Hàm nhập ma trận
    void nhap() {
        cout << "Nhap cac phan tu cho ma tran vuong " << n << "x" << n << ":" << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << "a[" << i << "][" << j << "] = ";
                cin >> a[i][j];
            }
        }
    }

    // 4. Hàm xuất ma trận
    void xuat() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << a[i][j] << "\t";
            }
            cout << endl;
        }
    }

    // 5. Hàm cộng ma trận
    Matrix cong(Matrix other) {
        Matrix kq(n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                kq.a[i][j] = a[i][j] + other.a[i][j];
        return kq;
    }

    // 6. Hàm trừ ma trận
    Matrix tru(Matrix other) {
        Matrix kq(n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                kq.a[i][j] = a[i][j] - other.a[i][j];
        return kq;
    }

    // 7. Hàm nhân ma trận
    Matrix nhan(Matrix other) {
        Matrix kq(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                kq.a[i][j] = 0;
                for (int k = 0; k < n; k++) {
                    kq.a[i][j] += a[i][k] * other.a[k][j];
                }
            }
        }
        return kq;
    }

    // 8. Hàm gán ma trận
    void gan(Matrix other) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                a[i][j] = other.a[i][j];
    }

    // 9. Hàm tính định thức
    double tinhDinhThuc() {
        return calcDet(a, n);
    }

    // 10. Hàm tính ma trận nghịch đảo
    Matrix maTranNghichDao() {
        double det = tinhDinhThuc();
        Matrix inv(n);
        if (det == 0) {
            cout << "Ma tran khong co nghich dao (Dinh thuc = 0)!" << endl;
            return inv;
        }

        if (n == 1) {
            inv.a[0][0] = 1.0 / a[0][0];
            return inv;
        }

        double** subMat = new double* [n - 1];
        for (int i = 0; i < n - 1; i++) subMat[i] = new double[n - 1];

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int subI = 0;
                for (int r = 0; r < n; r++) {
                    if (r == i) continue;
                    int subJ = 0;
                    for (int c = 0; c < n; c++) {
                        if (c == j) continue;
                        subMat[subI][subJ] = a[r][c];
                        subJ++;
                    }
                    subI++;
                }
                // Ma trận phụ hợp (Adjugate) được tính và chuyển vị tại đây
                inv.a[j][i] = (pow(-1, i + j) * calcDet(subMat, n - 1)) / det;
            }
        }

        for (int i = 0; i < n - 1; i++) delete[] subMat[i];
        delete[] subMat;

        return inv;
    }
};

int main() {
    int size;
    cout << "Nhap kich thuoc ma tran vuong: ";
    cin >> size;

    // Tạo 2 đối tượng ma trận
    Matrix m1(size), m2(size);

    cout << "\n--- Nhap Ma Tran 1 ---" << endl;
    m1.nhap();

    cout << "\n--- Nhap Ma Tran 2 ---" << endl;
    m2.nhap();

    cout << "\n=> Ma Tran 1:" << endl;
    m1.xuat();

    cout << "\n=> Ma Tran 2:" << endl;
    m2.xuat();

    cout << "\n--- Tong 2 ma tran ---" << endl;
    Matrix m3 = m1.cong(m2);
    m3.xuat();

    cout << "\n--- Hieu 2 ma tran ---" << endl;
    Matrix m4 = m1.tru(m2);
    m4.xuat();

    cout << "\n--- Tich 2 ma tran ---" << endl;
    Matrix m5 = m1.nhan(m2);
    m5.xuat();

    cout << "\n--- Dinh thuc cua Ma tran 1 ---" << endl;
    cout << m1.tinhDinhThuc() << endl;

    cout << "\n--- Ma tran nghich dao cua Ma tran 1 ---" << endl;
    Matrix inv = m1.maTranNghichDao();
    inv.xuat();

    return 0;
}