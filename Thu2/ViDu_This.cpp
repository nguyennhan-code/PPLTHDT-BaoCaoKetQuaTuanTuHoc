#include <iostream>
using namespace std;

class Circle
{
private:
    float r; // Thuộc tính của lớp có tên là r

public:
    // Tham số truyền vào cũng có tên là r
    void setRadius(float r)
    {
        // Sử dụng this->r để chỉ định rõ đây là thuộc tính r của đối tượng hiện tại
        this->r = r;
    }

    float getRadius()
    {
        return r;
    }
};

void main()
{
    Circle c;
    c.setRadius(15);
    cout << "Ban kinh cua hinh tron la: " << c.getRadius() << endl;
}