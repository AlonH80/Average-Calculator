#include "Course.h"

Course::Course()
{
    this->grade=NO_INFO;
    this->credit=NO_INFO;
}

Course::Course(string name,int grade,int credit):name(name),grade(grade),credit(credit)
{
    
}

string Course::getName() const
{
    return this->name;
}

int Course::getGrade() const
{
    return this->grade;
}

int Course::getCredit() const
{
    return this->credit;
}

ostream& operator<<(ostream& os,const Course& course)
{
    os << "Course: " << course.name << "\nGrade: " << course.grade << "\nCredit: " << course.credit << endl;
    return os;
}

Course* createCourse(string name,int grade,int credit,bool isCompulsory)
{
    Course* newCourse;
    if (isCompulsory)
        newCourse=new CompulsoryCourse(name,grade,credit);
    else
        newCourse=new ElectiveCourse(name,grade,credit);
    return newCourse;
}
