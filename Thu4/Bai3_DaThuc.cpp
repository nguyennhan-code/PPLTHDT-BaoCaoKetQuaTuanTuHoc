#include <iostream>
#include <cmath> // Dùng cho hàm pow (tính lũy thừa) và abs (lấy trị tuyệt đối)
using namespace std;

class DaThuc {
private:
    int bac;        // Bậc của đa thức
    double* heso;   // Con trỏ để cấp phát mảng chứa các hệ số

public:
    // 1. Phương thức khởi tạo mặc định gán đa thức bằng 0
    DaThuc() {
        bac = 0;
        heso = new double[1];
        heso[0] = 0.0;
    }

    // 2. Phương thức khởi tạo có tham số (mảng hệ số và bậc)
    DaThuc(int b, double* hs) {
        bac = b;
        heso = new double[bac + 1];
        for (int i = 0; i <= bac; i++) {
            heso[i] = hs[i];
        }
    }

    // Khởi tạo sao chép (Giúp sao chép mảng động an toàn khi gán/truyền tham số)
    DaThuc(const DaThuc& other) {
        bac = other.bac;
        heso = new double[bac + 1];
        for (int i = 0; i <= bac; i++) {
            heso[i] = other.heso[i];
        }
    }

    // 3. Phương thức hủy (Giải phóng mảng động)
    ~DaThuc() {
        delete[] heso;
    }

    // 4. Hàm nhập đa thức
    void nhap() {
        cout << "Nhap bac cua da thuc: ";
        cin >> bac;

        delete[] heso; // Xóa mảng cũ nếu có
        heso = new double[bac + 1];

        cout << "Nhap cac he so tu bac cao xuong bac thap:" << endl;
        for (int i = bac; i >= 0; i--) {
            cout << "He so cua x^" << i << " = ";
            cin >> heso[i];
        }
    }

    // 4. Hàm xuất đa thức
    void xuat() {
        if (bac == 0 && heso[0] == 0) {
            cout << "0" << endl;
            return;
        }
        for (int i = bac; i >= 0; i--) {
            if (heso[i] != 0) {
                // In dấu cộng/trừ
                if (i != bac && heso[i] > 0) cout << " + ";
                else if (heso[i] < 0) cout << " - ";
                else if (i == bac && heso[i] < 0) cout << "-";

                // In hệ số
                cout << abs(heso[i]);

                // In x và số mũ
                if (i > 0) cout << "x^" << i;
            }
        }
        cout << endl;
    }

    // 5. Hàm cộng hai đa thức
    DaThuc cong(DaThuc other) {
        int bacMax = (bac > other.bac) ? bac : other.bac;
        double* hsMoi = new double[bacMax + 1];

        for (int i = 0; i <= bacMax; i++) {
            double h1 = (i <= bac) ? heso[i] : 0.0;
            double h2 = (i <= other.bac) ? other.heso[i] : 0.0;
            hsMoi[i] = h1 + h2;
        }

        DaThuc kq(bacMax, hsMoi);
        delete[] hsMoi; // Xóa mảng tạm
        return kq;
    }

    // 5. Hàm trừ hai đa thức
    DaThuc tru(DaThuc other) {
        int bacMax = (bac > other.bac) ? bac : other.bac;
        double* hsMoi = new double[bacMax + 1];

        for (int i = 0; i <= bacMax; i++) {
            double h1 = (i <= bac) ? heso[i] : 0.0;
            double h2 = (i <= other.bac) ? other.heso[i] : 0.0;
            hsMoi[i] = h1 - h2;
        }

        DaThuc kq(bacMax, hsMoi);
        delete[] hsMoi;
        return kq;
    }

    // 5. Hàm nhân hai đa thức
    DaThuc nhan(DaThuc other) {
        int bacMoi = bac + other.bac;
        double* hsMoi = new double[bacMoi + 1];
        for (int i = 0; i <= bacMoi; i++) hsMoi[i] = 0.0; // Khởi tạo mảng = 0

        for (int i = 0; i <= bac; i++) {
            for (int j = 0; j <= other.bac; j++) {
                hsMoi[i + j] += heso[i] * other.heso[j];
            }
        }
        DaThuc kq(bacMoi, hsMoi);
        delete[] hsMoi;
        return kq;
    }

    // 6. Hàm gán (=)
    void gan(DaThuc other) {
        delete[] heso;
        bac = other.bac;
        heso = new double[bac + 1];
        for (int i = 0; i <= bac; i++) {
            heso[i] = other.heso[i];
        }
    }

    // 6. Hàm so sánh bằng (==)
    bool soSanhBang(DaThuc other) {
        if (bac != other.bac) return false;
        for (int i = 0; i <= bac; i++) {
            if (heso[i] != other.heso[i]) return false;
        }
        return true;
    }

    // 6. Hàm so sánh khác (!=)
    bool soSanhKhac(DaThuc other) {
        return !soSanhBang(other); // Đảo ngược kết quả của so sánh bằng
    }

    // 7. Hàm tính giá trị của đa thức tại x
    double tinhGiaTri(double x) {
        double kq = 0;
        for (int i = 0; i <= bac; i++) {
            kq += heso[i] * pow(x, i);
        }
        return kq;
    }
};

int main() {
    cout << "--- Nhap Da Thuc 1 ---" << endl;
    DaThuc dt1;
    dt1.nhap();

    cout << "\n--- Nhap Da Thuc 2 ---" << endl;
    DaThuc dt2;
    dt2.nhap();

    cout << "\nDa thuc 1: "; dt1.xuat();
    cout << "Da thuc 2: "; dt2.xuat();

    cout << "\nTong 2 da thuc: ";
    DaThuc tong = dt1.cong(dt2);
    tong.xuat();

    cout << "Hieu 2 da thuc (dt1 - dt2): ";
    DaThuc hieu = dt1.tru(dt2);
    hieu.xuat();

    cout << "Tich 2 da thuc: ";
    DaThuc tich = dt1.nhan(dt2);
    tich.xuat();

    double x;
    cout << "\nNhap gia tri x de tinh Da thuc 1: ";
    cin >> x;
    cout << "Gia tri cua Da thuc 1 tai x = " << x << " la: " << dt1.tinhGiaTri(x) << endl;

    return 0;
}