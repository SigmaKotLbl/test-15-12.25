#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Employee{
private:
    string name;
    int id;
    double salary;
public:
// создаем "нулевой" конструктор
    Employee(){
        name = "unknown";
        id = 0;
        salary = 0;
    }
// создаем "параметрический" конструктор
    Employee(string name_, int id_, double salary_){
        name = name_;
        id = id_;
        salary = salary_;
    }
// геттеры
    string getName() const{
        return name;
    }
    int getId() const{
        return id;
    }

    virtual double getSalary() const{ // virtual для последюущего переопределения в Manager
        return salary;
    }
// сеттеры
    void setName(const string& newName){
        name = newName;
    }
    void setId(const int newId){
        id = newId;
    }
    void setSalary(const double newSalary){
        salary = newSalary;
    }
};
// создали дочерний класс
class Manager: public Employee{
private:
    string department;
public:
    Manager(string name_, int id_, double salary_, string department_): Employee(name_, id_, salary_), department(department_) {} // все поля кроме department наследуются от Employee
    double getSalary() const override{ // переназначаем getSalary (надбавка)
        return Employee::getSalary() * 1.1; 
    }
    string getDepartment() const{
        return department;
    }
};
// проверка корректности введенных данных
bool isValidEmployeeData(const string& name, int id, double salary){
        if (name.empty() != 1 && id > 0 && salary >= 0){
            return true;
        }   else{
            return false;
        }
    }
// сохранение в файл (т.к. в условии сказано создать массив из указатаелей, мы подстраиваем функцию под указатели)
void saveToFile(Employee* employees[], int size, const string& filename){
    ofstream outFile(filename);

    if (outFile.is_open() == 0){ // проверяем открыт ли файл
        cerr << "error oppening file!" << filename << endl;
        return;
    }
    for (int i = 0; i < size; i++){
        if (employees[i] != nullptr){ // проверяем не является ли указатель нулевым
        outFile << employees[i]->getId() << " "
                << employees[i]->getName() << " "
                << employees[i]->getSalary() << endl;
        }
    }
}  
// небольшая проверка в main =)
int main(){
    const int size = 4;

    Employee* array[size];
    array[0] = new Employee("Nikita", 5201, 75000);
    array[1] = new Employee("Vanya", 5202, 150000);
    array[2] = new Manager("Mark", 5203, 200000, "programming");
    array[3] = new Manager("Sasha", 5204, 210000, "sales");

    cout << "employees data: " << endl;
    for (int i = 0; i < size; i++ ){
        cout << "Employee number " << i + 1 << " : ";
        cout << "ID: " << array[i]->getId() << ", ";
        cout << "Name: " << array[i]->getName() << ", ";
        cout << "Salary: " << array[i]->getSalary() << endl;
    }
    saveToFile(array, size, "output");
    return 0;
}

/*
В 3 и 4 ячейки массива мы занесли Manager, поэтому их зарплата в output указана с надбавкой:

*/
