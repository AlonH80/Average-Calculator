
#include "AcademicHandler.h"

AcademicHandler::AcademicHandler()
{
}

AcademicHandler::~AcademicHandler()
{
    for (vector<Semester*>::iterator runner=semesters.begin();runner!=semesters.end();++runner)
    {
        delete (*runner);
    }
}

void AcademicHandler::addSemester(Semester& newSem)
{
    this->semesters.push_back(&newSem);
    this->calculateAvg();
}

void AcademicHandler::addSemester(int year,semesterType semType)
{
    Semester* newSem=new Semester(year,semType);
    this->addSemester(*newSem);
}

void AcademicHandler::addCourseToSemester(Course& co,int semIndex)
{
    Semester* currSem=this->semesters[semIndex];
    this->addCourseToSemester(co,currSem);
}

void AcademicHandler::addCourseToSemester(Course& co,Semester* sem)
{
    sem->addCourse(co);
    this->calculateAvg();
}

double AcademicHandler::calculateAvg()
{
    this->avg=0;
    double totCredit=0,currAvg,currCredit;
    for(auto runner=this->semesters.begin();runner!=this->semesters.end();runner++)
    {
        currCredit=(double)((*runner)->getTotalCredit());
        currAvg=(double)(*runner)->getAverage();
        this->avg+=(currAvg*currCredit);
        totCredit+=currCredit;
    }
    this->avg/=totCredit;
    return this->avg;
}

void AcademicHandler::showAll() const
{
    for(auto runner=this->semesters.begin();runner!=this->semesters.end();runner++)
    {
        (*runner)->show();
    }
    cout << "Total average: " << this->avg << endl << endl;
}

const vector<Semester*>& AcademicHandler::getSemesters() const
{
    return this->semesters;
}

double AcademicHandler::getAverage() const
{
    return this->avg;
}

void AcademicHandler::searchCourse(string course) const
{
    vector<Course*> courses;
    vector<Course*>::iterator coRunner;
    auto semRunner=semesters.begin();
    bool found=false;
    while (semRunner!=semesters.end() && !found)
    {
        courses=(*semRunner)->getCourses();
        coRunner=courses.begin();
        while (coRunner!=courses.end() && !found)
        {
            if ((*coRunner)->getName()==course)
            {
                cout << *(*coRunner) << endl;
                found=true;
            }
            ++coRunner;
        }
        ++semRunner;
    }
    if (!found)
        cout << "Course not found" << endl;
}

void AcademicHandler::showAllCompulsoryCourses() const
{
    vector<Course*> courses;
    CompulsoryCourse* currCo;
    for (auto semRunner=semesters.begin();semRunner!=semesters.end();++semRunner)
    {
        courses=(*semRunner)->getCourses();
        for (auto coRunner=courses.begin();coRunner!=courses.end();++coRunner)
        {
            currCo=dynamic_cast<CompulsoryCourse*>(*coRunner);
            if (currCo)
                cout << *currCo << endl;
        }
    }
}

void AcademicHandler::showAllElectiveCourses() const
{
    vector<Course*> courses;
    ElectiveCourse* currCo;
    for (auto semRunner=semesters.begin();semRunner!=semesters.end();++semRunner)
    {
        courses=(*semRunner)->getCourses();
        for (auto coRunner=courses.begin();coRunner!=courses.end();++coRunner)
        {
            currCo=dynamic_cast<ElectiveCourse*>(*coRunner);
            if (currCo)
                cout << *currCo << endl;
        }
    }
}

Semester* AcademicHandler::findSemester (int year,semesterType semType) const
{
    Semester* curr=nullptr;
    auto runner=this->semesters.begin();
    while (runner!=this->semesters.end() && !curr)
    {
        if ((*runner)->getYear()==year && (*runner)->getSemType()==semType)
            curr=(*runner);
        ++runner;
    }
    return curr;
}

void AcademicHandler::showSemester(int year,semesterType semType) const
{
    Semester* sem=this->findSemester(year, semType);
    if (sem!=nullptr)
        sem->show();
    else
        cout << "Semester not found." << endl;
}

void AcademicHandler::showAllCourses() const
{
    vector<Course*> courses;
    for (auto semRunner=semesters.begin();semRunner!=semesters.end();++semRunner)
    {
        courses=(*semRunner)->getCourses();
        for (auto coRunner=courses.begin();coRunner!=courses.end();++coRunner)
        {
            cout << *(*coRunner) << endl;
        }
    }
}

void AcademicHandler::showCoursesOver(int grade) const
{
    vector<Course*> courses;
    for (auto semRunner=semesters.begin();semRunner!=semesters.end();++semRunner)
    {
        courses=(*semRunner)->getCourses();
        for (auto coRunner=courses.begin();coRunner!=courses.end();++coRunner)
        {
            if ((*coRunner)->getGrade()>grade)
            {
                cout << **coRunner << endl;
            }
        }
    }
}

void AcademicHandler::showCoursesUnder(int grade) const
{
    vector<Course*> courses;
    for (auto semRunner=semesters.begin();semRunner!=semesters.end();++semRunner)
    {
        courses=(*semRunner)->getCourses();
        for (auto coRunner=courses.begin();coRunner!=courses.end();++coRunner)
        {
            if ((*coRunner)->getGrade()<grade)
            {
                cout << **coRunner << endl;
            }
        }
    }
}
