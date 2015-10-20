/*
Implement the following classes:
Shape, Circle, Square.

Requirements: 
1. Shape is a base class. Circle and Square are subclasses of Shape.

2. Shape is an abstract class (i.e. can't be instantiated). Use a pure virtual
function to satisfy this requirement. (Code already provided)

3. For each sub-class, define a virtual function that computes
the area of the shape.

4. The data fields for each class must be private or protected. Define
the appropriate get/set functions for each data field.

5. For each class, define the appropriate constructors that initialize the data fields
as necessary. Moreover, define a defualt constructor for each class that sets the data
fields to default values.

 */
class Shape {
public:
  virtual double computeArea() = 0;  //a pure virtual function (=0) makes this class abstract
  virtual void printShapeType() = 0; //Prints "Circle" for Circle, "Square" for Square.
};

class Circle: public Shape {
};

class Square: public Shape {
};

/*Polymorphism:
6. Complete the code for the following function, which
calls computeArea() function of a Shape object.
 */

double computeArea(Shape *shape) {
}
