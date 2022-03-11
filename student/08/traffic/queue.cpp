#include "queue.hh"
#include <iostream>
#include <string>

// Implement the member functions of Queue here

Queue::Queue(unsigned int cycle):
        first_(nullptr), last_(nullptr), cycle_(cycle){
}

Queue::~Queue()
{

}

void Queue::enqueue(const string &reg)
{
    // jos vihreät valot, ei jää jonoon - ei luoda structia
    if (is_green_ == true)
    {
        std::cout << "GREEN: the vehicle " << reg << " need not stop to wait" << std::endl;
    }
    // muuten luo vehiclen
    else
    {
        Vehicle* new_car = new Vehicle;

        new_car->reg_num = reg;
        new_car->next = nullptr;

        if (first_ == nullptr)
        {
            first_ = new_car;
            last_ = new_car;
        }
        else
        {
            last_->next = new_car;
            last_ = new_car;
        }
    }
}

void Queue::switch_light()
{
    if (is_green_ == false)
    {
        is_green_ = true;
        std::cout << "GREEN: ";
    }
    else
    {
        is_green_ = false;
        std::cout << "RED: ";
    }

    //jos jonoa ei oo
    if (first_ == nullptr)
    {
       std::cout << "No vehicles waiting in traffic lights" << std::endl;
    }
    else
    {
        // muuten dequeutetaan ja apumuuttujan avulla katotaan kuinka monta mennyt
        // jos nexti on nullptr ei mennä eteenp
        uint how_many_have_passed = 1;
        while (how_many_have_passed <= cycle_)
        {
            dequeue();
            ++how_many_have_passed;
        }
        is_green_ = false;
        std::cout << "can go on" << std::endl;
    }
}

void Queue::reset_cycle(unsigned int cycle)
{
    cycle_ = cycle;
}

void Queue::print() const
{  
    if (is_green_ == true)
    {
        std::cout << "GREEN: ";
    }
    else
    {
        std::cout << "RED: ";
    }

    Vehicle* car_to_print = first_;
    if (first_ == nullptr)
    {
        std::cout << "No vehicles waiting in traffic lights" << std::endl;
    }
    else
    {
        std::cout << "Vehicle(s) ";
        while(car_to_print != nullptr)
        {
            std::cout << car_to_print->reg_num << " ";
            car_to_print = car_to_print->next;
        }
        std::cout << "waiting in traffic lights" << std::endl;
    }
}

void Queue::dequeue()
{
    Vehicle* car_to_go = first_;

    //poistaa ekan auton
    if (first_ != nullptr)
    {
        std::cout << car_to_go->reg_num << " ";
        first_ = car_to_go->next;
        delete car_to_go;
    }
}
