#include <iostream>
using namespace std;

class Circle
{
private:
    const float PI = 3.1415;
    float r;

public:
    void setRadius(float bkinh)
    {
        r = bkinh;
    }
    float getRadius()
    {
        return r;
    }
    float area()
    {
        return PI * r * r;
    }
};

void main()
{
    // Cấp phát động một đối tượng kiểu con trỏ
    Circle* pc = new Circle;

    // Khai báo một đối tượng thông thường
    Circle c;
    c.setRadius(10);

    // Cho con trỏ pc trỏ đến địa chỉ của đối tượng c
    pc = &c;

    // Truy xuất hàm thành viên thông qua con trỏ bằng toán tử ->
    cout << "Dien tich duong tron ban kinh r = " << pc->getRadius() << " la " << pc->area() << endl;
}