#include <iostream>

using namespace std;

////////////////////////////////////////////////////////////////////////////////
//! Implementor
class DrawingAPI {
  public:
   virtual void drawCircle(double x, double y, double radius) = 0;
   virtual ~DrawingAPI() {}
};
////////////////////////////////////////////////////////////////////////////////
//! Concrete ImplementorA
class DrawingAPI1 : public DrawingAPI {
  public:
   void drawCircle(double x, double y, double radius) {
      cout << "API1.circle at " << x << ':' << y << ' ' << radius << endl;
   }
};
////////////////////////////////////////////////////////////////////////////////
//! Concrete ImplementorB
class DrawingAPI2 : public DrawingAPI {
public:
   void drawCircle(double x, double y, double radius) {
      cout << "API2.circle at " << x << ':' << y << ' ' <<  radius << endl;
   }
};
////////////////////////////////////////////////////////////////////////////////
//! Class created with a concrete implementation of the API
class CircleShape {
private:
   double m_x, m_y, m_radius;
   DrawingAPI& m_drawingAPI;

public:
   CircleShape(double x, double y,double radius, DrawingAPI& drawingAPI) :
	   m_x(x), m_y(y), m_radius(radius), m_drawingAPI(drawingAPI)
   {}
   void draw() { m_drawingAPI.drawCircle(m_x, m_y, m_radius); }
   void resizeByPercentage(double pct) { m_radius *= pct; }
};
////////////////////////////////////////////////////////////////////////////////
int main(void) {
    DrawingAPI1 concrete_api_1;
    CircleShape circle1(1, 2, 3, concrete_api_1);

    DrawingAPI2 concrete_api_2;
    CircleShape circle2(5, 7, 11, concrete_api_2);

    circle1.resizeByPercentage(2.5);
    circle2.resizeByPercentage(2.5);
    circle1.draw();
    circle2.draw();
    return 0;
}