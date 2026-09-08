#include <iostream>
using namespace std;

// Khai báo cấu trúc lớp
class Circle
{
private:
    const float PI = 3.1415; // Hằng số PI
    float r;                 // Bán kính, thành phần dữ liệu của từng đối tượng

public:
    // Khai báo các hàm thành viên (phương thức) bên trong lớp
    void setRadius(float bkinh)
    {
        r = bkinh;
    }

    float getRadius()
    {
        return r;
    }

    // Chỉ khai báo hàm ở đây, định nghĩa chi tiết ở bên ngoài
    float area();
};

// Định nghĩa hàm thành viên ở bên ngoài lớp sử dụng toán tử ::
float Circle::area()
{
    return PI * r * r;
}

void main()
{
    // Khai báo và sử dụng đối tượng
    Circle c;
    c.setRadius(10);
    cout << "Dien tich duong tron ban kinh r = " << c.getRadius() << " la " << c.area() << endl;
}