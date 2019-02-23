
#include "Interface.h"

template <class ToHandle>
void Interface<ToHandle>::runInterface()
{
    this->showMenu();
    while (!toExit)
    {
        this->execute(this->userSelect());
    }
}

template <class ToHandle>
void Interface<ToHandle>::addToMenu(string option)
{
    menu.push_back(option);
}

template <class ToHandle>
void Interface<ToHandle>::showMenu() const
{
    cout << "Menu: " << endl;
    unsigned int ind=0;
    for (auto runner=menu.begin();runner!=menu.end();++runner)
    {
        cout << '\t' <<  ++ind << ". " << (*runner) << endl;
    }
}

template <class ToHandle>
int Interface<ToHandle>::userSelect(string disp) const
{
    char* userInput = new char[4];
    cout << disp;
    cin.get(userInput, 4,'\n');
    cin.clear();
    cin.ignore(2000,'\n');
    int userChoice=convertStrToInt(userInput);
    delete[] userInput;
    if (userChoice>0 && userChoice<=menu.size())
        return userChoice;
    return INVALID_CHOICE;
}

AcademicInterface::AcademicInterface() : Interface<AcademicHandler>()
{
    this->addToMenu("Show menu");
    this->addToMenu("Search course");
    this->addToMenu("Show all compulsory courses");
    this->addToMenu("Show all elective courses");
    this->addToMenu("Show semester");
    this->addToMenu("Show all courses");
    this->addToMenu("Show courses with grades above _ ");
    this->addToMenu("Show courses with grades under _ ");
    this->addToMenu("Exit");
    this->setup();
    this->toExit=false;
}

void AcademicInterface::runInterface()
{
    Interface<AcademicHandler>::runInterface();
}

void AcademicInterface::execute(int userSelect)
{
    switch(userSelect)
    {
        case 1:
            this->showMenu();
            break;
        case 2:
            this->handler.searchCourse(userSelectCourse());
            break;
        case 3:
            this->handler.showAllCompulsoryCourses();
            break;
        case 4:
            this->handler.showAllElectiveCourses();
            break;
        case 5:
            this->handler.showSemester(userSelectYear(), userSelectSemType());
            break;
        case 6:
            this->handler.showAllCourses();
            break;
        case 7:
            this->handler.showCoursesOver(userSelectGrade());
            break;
        case 8:
            this->handler.showCoursesUnder(userSelectGrade());
            break;
        case 9:
            this->toExit=true;
            break;
        default:
            cout << "Invalid option." << endl;
            break;
    }
}

void AcademicInterface::setup()
{
    handler.addSemester(1, WINTER);
    handler.addSemester(1, SPRING);
    handler.addSemester(2, WINTER);
    handler.addCourseToSemester(*createCourse("Intro to CS",91,6), 0);
    handler.addCourseToSemester(*createCourse("Logic and group theory",88,4), 0);
    handler.addCourseToSemester(*createCourse("Calculus2",97,4), 0);
    handler.addCourseToSemester(*createCourse("Biology",87,3,false), 0);
    handler.addCourseToSemester(*createCourse("Project management",82,3,false), 0);
    handler.addCourseToSemester(*createCourse("Advanced Programming",98,4), 1);
    handler.addCourseToSemester(*createCourse("Discrete math",85,4), 1);
    handler.addCourseToSemester(*createCourse("Linear algebra in CS",87,4,false), 1);
    handler.addCourseToSemester(*createCourse("Riddles",100,3,false), 1);
    handler.addCourseToSemester(*createCourse("Self taught math",98,1,false), 1);
    handler.addCourseToSemester(*createCourse("OOP",100,4), 2);
    handler.addCourseToSemester(*createCourse("Computer Structure",100,4), 2);
    handler.addCourseToSemester(*createCourse("Data Structures",93,4), 2);
    handler.addCourseToSemester(*createCourse("Assembly",93,2), 2);
    handler.addCourseToSemester(*createCourse("Hardware and Embedded systems",98,3,false), 2);
    handler.addCourseToSemester(*createCourse("Functional progrmming",94,3,false), 2);
}

semesterType AcademicInterface::userSelectSemType()
{
    int choice=this->userSelect("Select semester: 1.Winter 2.Spring 3.Summer - ");
    if ((choice-1)>=WINTER && (choice-1) <= SUMMER)
        return (semesterType)(choice-1);
    return UNKNOWN;
}

int AcademicInterface::userSelectYear()
{
    return userSelect("Enter year: ");
}

int AcademicInterface::userSelectGrade()
{
    return userSelect("Enter grade: ");
}

string AcademicInterface::userSelectCourse()
{
    string co;
    cout << "Enter course name: ";
    cin >> co;
    cin.clear();
    cin.ignore(2000,'\n');
    return co;
}

int convertStrToInt(string str)
{
    int retVal=0;
    auto runner=str.begin();
    while (runner!=str.end() && (*runner)>='0' && (*runner)<='9')
    {
        retVal*=10;
        retVal+=((int)((*runner)-'0'));
        ++runner;
    }
    return retVal;
}

