#include <vector>
#include <iostream>
#include <memory>
#include <algorithm>
using namespace std;
    
////////////////////////////////////////////////////////////////////////////////
//! Interface class
class Graphic {
public:
    virtual void print() const = 0;
    virtual ~Graphic() {}
};
////////////////////////////////////////////////////////////////////////////////
//! Implentor 
class Ellipse : public Graphic {
public:
    void print() const { cout << "Ellipse \n"; }
};
////////////////////////////////////////////////////////////////////////////////
//! Composite class to hold other Graphics, but also implements the Graphic itself
class CompositeGraphic : public Graphic {
public:
    void add(std::shared_ptr<Graphic> aGraphic) { graphicList_.push_back(aGraphic); }
    void print() const { for(const auto& graphic: graphicList_) graphic->print(); }
private:
    vector<std::shared_ptr<Graphic>>  graphicList_;
};
////////////////////////////////////////////////////////////////////////////////
int main()
{
    // Composes two graphic to hold some ellipses...
    auto graphic1 = std::make_shared<CompositeGraphic>();
    graphic1->add( std::make_shared<Ellipse>() );
    graphic1->add( std::make_shared<Ellipse>() );
    graphic1->add( std::make_shared<Ellipse>() );

    auto graphic2 = std::make_shared<CompositeGraphic>();
    graphic2->add( std::make_shared<Ellipse>() );

    // Compose a graphic to hold ellipses and graphics
    CompositeGraphic graphic;
    graphic.add(graphic1);
    graphic.add(graphic2);
    
    // Prints the complete graphic with all ellipses
    graphic.print();
    return 0;
}