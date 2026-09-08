#include <iostream>
using namespace std;

class Rectangle {
private:
    double width;  // Chiều rộng
    double height; // Chiều cao

public:
    // 1. Phương thức khởi tạo mặc định gán giá trị 1.0 cho cả hai
    Rectangle() {
        width = 1.0;
        height = 1.0;
    }

    // 2. Phương thức khởi tạo với 2 tham số width và height
    Rectangle(double w, double h) {
        width = w;
        height = h;
    }

    // 3. Phương thức hủy
    ~Rectangle() {
        // Lớp không cấp phát bộ nhớ động nên hàm hủy có thể để trống
    }

    // 4. Các phương thức set, get
    void setWidth(double w) { width = w; }
    void setHeight(double h) { height = h; }

    double getWidth() { return width; }
    double getHeight() { return height; }

    // 5. Phương thức trả về diện tích
    double getArea() {
        return width * height;
    }

    // 6. Phương thức trả về chu vi
    double getPerimeter() {
        return 2 * (width + height);
    }
};

int main() {
    // Tạo đối tượng 1 với width = 15 và height = 40
    Rectangle r1(15.0, 40.0);
    cout << "--- Hinh chu nhat 1 ---" << endl;
    cout << "Chieu rong: " << r1.getWidth() << endl;
    cout << "Chieu cao: " << r1.getHeight() << endl;
    cout << "Dien tich: " << r1.getArea() << endl;
    cout << "Chu vi: " << r1.getPerimeter() << endl;

    // Tạo đối tượng 2 với width = 12.5 và height = 25.2
    Rectangle r2(12.5, 25.2);
    cout << "\n--- Hinh chu nhat 2 ---" << endl;
    cout << "Chieu rong: " << r2.getWidth() << endl;
    cout << "Chieu cao: " << r2.getHeight() << endl;
    cout << "Dien tich: " << r2.getArea() << endl;
    cout << "Chu vi: " << r2.getPerimeter() << endl;

    return 0;
}