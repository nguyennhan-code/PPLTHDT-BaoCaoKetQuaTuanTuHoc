#include <iostream>
#include <cmath>
using namespace std;

class PhanSo {
private:
    int tuSo;
    int mauSo;

    // Hàm ẩn (private) tìm Ước chung lớn nhất để rút gọn phân số
    int timUCLN(int a, int b) {
        a = abs(a);
        b = abs(b);
        if (a == 0 || b == 0) return a + b;
        while (a != b) {
            if (a > b) a -= b;
            else b -= a;
        }
        return a;
    }

public:
    // 7. Hàm rút gọn phân số (Viết lên đầu để các hàm khởi tạo tái sử dụng được)
    void rutGon() {
        int ucln = timUCLN(tuSo, mauSo);
        if (ucln != 0) {
            tuSo /= ucln;
            mauSo /= ucln;
        }
        // Nếu mẫu số âm thì chuyển dấu trừ lên tử số
        if (mauSo < 0) {
            tuSo = -tuSo;
            mauSo = -mauSo;
        }
    }

    // 1. Phương thức khởi tạo mặc định (tử = 0, mẫu = 1)
    PhanSo() {
        tuSo = 0;
        mauSo = 1;
    }

    // 2. Phương thức khởi tạo có tham số
    PhanSo(int tu, int mau) {
        tuSo = tu;
        mauSo = (mau != 0) ? mau : 1; // Nếu truyền mẫu = 0 thì tự gán = 1
        rutGon();
    }

    // 3. Phương thức hủy
    ~PhanSo() {
        // Không cấp phát động nên hàm hủy để trống
    }

    // 4. Hàm nhập phân số
    void nhap() {
        cout << "Nhap tu so: ";
        cin >> tuSo;
        do {
            cout << "Nhap mau so (phai khac 0): ";
            cin >> mauSo;
            if (mauSo == 0) cout << "Mau so khong hop le! Vui long nhap lai.\n";
        } while (mauSo == 0);
        rutGon(); // Rút gọn ngay sau khi nhập
    }

    // 4. Hàm xuất phân số
    void xuat() {
        if (mauSo == 1) {
            cout << tuSo; // Nếu mẫu = 1 thì chỉ in tử số
        }
        else if (tuSo == 0) {
            cout << "0";
        }
        else {
            cout << tuSo << "/" << mauSo;
        }
    }

    // 5. Hàm cộng hai phân số
    PhanSo cong(PhanSo other) {
        int tu = tuSo * other.mauSo + other.tuSo * mauSo;
        int mau = mauSo * other.mauSo;
        return PhanSo(tu, mau); // Hàm khởi tạo có tham số sẽ tự động rút gọn kết quả
    }

    // 5. Hàm trừ hai phân số
    PhanSo tru(PhanSo other) {
        int tu = tuSo * other.mauSo - other.tuSo * mauSo;
        int mau = mauSo * other.mauSo;
        return PhanSo(tu, mau);
    }

    // 5. Hàm nhân hai phân số
    PhanSo nhan(PhanSo other) {
        int tu = tuSo * other.tuSo;
        int mau = mauSo * other.mauSo;
        return PhanSo(tu, mau);
    }

    // 5. Hàm chia hai phân số
    PhanSo chia(PhanSo other) {
        int tu = tuSo * other.mauSo;
        int mau = mauSo * other.tuSo;
        return PhanSo(tu, mau);
    }

    // 6. Hàm gán (=)
    void gan(PhanSo other) {
        tuSo = other.tuSo;
        mauSo = other.mauSo;
    }

    // 6. Hàm so sánh bằng (==)
    bool soSanhBang(PhanSo other) {
        // Áp dụng quy tắc nhân chéo: a/b == c/d <=> a*d == c*b
        return (tuSo * other.mauSo == other.tuSo * mauSo);
    }

    // 6. Hàm so sánh khác (!=)
    bool soSanhKhac(PhanSo other) {
        return !soSanhBang(other);
    }
};

int main() {
    cout << "--- Nhap Phan So 1 ---" << endl;
    PhanSo ps1;
    ps1.nhap();

    cout << "\n--- Nhap Phan So 2 ---" << endl;
    PhanSo ps2;
    ps2.nhap();

    cout << "\nPhan so 1: "; ps1.xuat(); cout << endl;
    cout << "Phan so 2: "; ps2.xuat(); cout << endl;

    cout << "\nTong: ";
    PhanSo tong = ps1.cong(ps2);
    tong.xuat(); cout << endl;

    cout << "Hieu: ";
    PhanSo hieu = ps1.tru(ps2);
    hieu.xuat(); cout << endl;

    cout << "Tich: ";
    PhanSo tich = ps1.nhan(ps2);
    tich.xuat(); cout << endl;

    cout << "Thuong: ";
    PhanSo thuong = ps1.chia(ps2);
    thuong.xuat(); cout << endl;

    cout << "\nSo sanh:" << endl;
    if (ps1.soSanhBang(ps2)) {
        cout << "Hai phan so BANG nhau." << endl;
    }
    else {
        cout << "Hai phan so KHAC nhau." << endl;
    }

    return 0;
}