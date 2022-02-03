#include <iostream>
#include <memory>

////////////////////////////////////////////////////////////////////////////////
//! Class that is created by the Builder
class Pizza {
public:
    void setDough(const std::string& dough) { m_dough = dough; }
    void setSauce(const std::string& sauce) { m_sauce = sauce; }
    void setTopping(const std::string& topping) { m_topping = topping; }
    //! Prints the contents of the pizza
    void openAndDescribe() const {
        std::cout<< "The Pizza has "<<
        m_dough << " dough, " <<
        m_sauce << " sauce, " <<
        m_topping << " topping." << std::endl;
    }
private:
    std::string m_dough, m_sauce, m_topping;
};
////////////////////////////////////////////////////////////////////////////////
//! Holds the Pizza object to create it according to each implementor
class PizzaBuilderIntfc {
protected:
    std::unique_ptr<Pizza> m_pizza;
public:
    virtual ~PizzaBuilderIntfc() = default;
    void createNewPizza() { m_pizza = std::make_unique<Pizza>(); }
    Pizza* getPizza() { return m_pizza.release(); }
    virtual void buildDough() = 0;
    virtual void buildSauce() = 0;
    virtual void buildTopping() = 0;
};
////////////////////////////////////////////////////////////////////////////////
//! Class to call each Builder's steps, and get the final pizza
class Cook {
public:
    //! Builder method - abstracts the more complex creation of each pizza
    void createPizza(PizzaBuilderIntfc* pizzaBuilder) {
        m_pizzaBuilder = pizzaBuilder;
        m_pizzaBuilder->createNewPizza();
        m_pizzaBuilder->buildDough();
        m_pizzaBuilder->buildSauce();
        m_pizzaBuilder->buildTopping();
    }
    //! Grabs created object and describes whats been created
    void openPizza() const { m_pizzaBuilder->getPizza()->openAndDescribe(); }
private:
    PizzaBuilderIntfc* m_pizzaBuilder;
};

// PizzaBuilder Implementations
////////////////////////////////////////////////////////////////////////////////
class HawaiianPizzaBuilder : public PizzaBuilderIntfc {
public:
    ~HawaiianPizzaBuilder() override = default;
    void buildDough() override { m_pizza->setDough("Hawaiian dough"); }
    void buildSauce() override { m_pizza->setSauce("Hawaiian sauce"); }
    void buildTopping() override { m_pizza->setTopping("Hawaiian topping"); }
};
////////////////////////////////////////////////////////////////////////////////
class SpicyPizzaBuilder : public PizzaBuilderIntfc {
public:
    ~SpicyPizzaBuilder() override = default;
    void buildDough() override { m_pizza->setDough("Spicy dough"); }
    void buildSauce() override { m_pizza->setSauce("Spicy sauce"); }
    void buildTopping() override { m_pizza->setTopping("Spicy topping"); }
};

// Main
////////////////////////////////////////////////////////////////////////////////
int main() {
    Cook cook;
    HawaiianPizzaBuilder hawaiianPizzaBuilder;
    cook.createPizza(&hawaiianPizzaBuilder);
    cook.openPizza();

    SpicyPizzaBuilder spicyPizzaBuilder;
    cook.createPizza(&spicyPizzaBuilder);
    cook.openPizza();
}