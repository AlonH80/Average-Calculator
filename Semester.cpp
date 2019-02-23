#include "Semester.h"

Semester::Semester(int year,semesterType semType):year(year),semType(semType)
{
    this->avg=NO_INFO;
}

Semester::Semester(const Semester& other)
{
    for (auto runner=other.courses.begin();runner!=other.courses.end();runner++)
    {
        this->courses.push_back(*runner);
    }
    this->year=other.getYear();
    this->semType=other.getSemType();
    this->avg=other.getAverage();
}

Semester::~Semester()
{
    for (vector<Course*>::iterator runner=this->courses.begin();runner!=this->courses.end();runner++)
    {
        delete (*runner);
    }
}

const vector<Course*>& Semester::getCourses() const
{
    return this->courses;
}

int Semester::getYear() const
{
    return this->year;
}

semesterType Semester::getSemType() const
{
    return this->semType;
}

double Semester::getAverage() const
{
    return this->avg;
}

int Semester::getTotalCredit() const
{
    int totalCredit=0;
    for (auto runner=this->courses.begin();runner!=this->courses.end();runner++)
    {
        if ((*runner)->getGrade()!=NO_INFO)
            totalCredit+=(*runner)->getCredit();
    }
    return totalCredit;
}

void Semester::addCourse(Course& course)
{
    this->courses.push_back(&course);
    this->calculateAvg();
}

void Semester::addCourse(string name,int grade,int credit,bool isCompulsory)
{
    Course* newCourse;
    if (isCompulsory)
        newCourse=new CompulsoryCourse(name,grade,credit);
    else
        newCourse=new ElectiveCourse(name,grade,credit);
    this->addCourse(*newCourse);
    this->calculateAvg();
}

double Semester::calculateAvg()
{
    double newAvg=0;
    int currGrade;
    for (auto runner=this->courses.begin();runner!=this->courses.end();runner++)
    {
        if ((currGrade=(*runner)->getGrade())!=NO_INFO)
            newAvg+=((*runner)->getCredit()*currGrade);
    }
    newAvg/=this->getTotalCredit();
    this->avg=newAvg;
    return newAvg;
}

void Semester::show() const
{
    cout << "Year: " << year << endl;
    cout << "Semester: " << printSemesterType(semType) << endl;
    cout << "Courses: " << endl;
    for (auto runner=this->courses.begin();runner!=this->courses.end();runner++)
    {
        cout << **runner << endl;
    }
    cout << "Average: " << setprecision(4) << avg << endl << endl;
}

const char* printSemesterType(semesterType sem)
{
    switch(sem)
    {
        case WINTER:
            return "winter";
            break;
        case SPRING:
            return "spring";
            break;
        case SUMMER:
            return "summer";
            break;
        case UNKNOWN:
            return "unknown";
            break;
    }
}
