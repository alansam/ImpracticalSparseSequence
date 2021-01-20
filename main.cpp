//  STL smart-poinnter std::unique_ptr experiments
//
//  MARK: - References.
//  @see: https://en.cppreference.com/w/cpp/memory/unique_ptr
//

#include <iostream>
#include <iomanip>
#include <string>
#include <memory>

//  MARK: - Definitions.
//  MARK: Class Student
class Student {
private:
  static size_t ctr;
  size_t cc;  //  instance identifier
  std::string student;

public:
  Student(std::string name = "default");  //  C'tor - default
  //  copy and move disabled
  Student(Student const &) = delete;  //  copy
  Student(Student const &&) = delete; //  move
  Student const & operator=(Student const &) = delete;    //  copy
  Student const && operator=(Student const &&) = delete;  //  move
  virtual ~Student();   //  D'tor
  void HelloStudent(void) const;  //  accessor
};

//  MARK: - Implementation
//  MARK: Class Student statics.
size_t Student::ctr(0); // instance counter

//  MARK: Class Student methods.
//  MARK: C'tor
Student::Student(std::string name) : student(name) {
  cc = ctr++; // get current innstence ID then increment counter
}

//  MARK: D'tor
Student::~Student() {
  std::cout << "destroying"
            << std::setw(2) << cc << ' '
            << student
            << std::endl;
  student.clear();
}

//  MARK: Accessor
void Student::HelloStudent(void) const {
  std::cout << "Hello"
            << std::setw(2) << cc << ' '
            << student
            << std::endl;
}

/*
 *  MARK: main()
 */
int main() {
  Student s1("abc");
  Student * ptr0 = &s1;
  ptr0->HelloStudent();

  auto ptr1 = std::make_unique<Student>("bobby");
  ptr1->HelloStudent();

  std::unique_ptr<Student> ptr2(new Student("tommy"));
  ptr2->HelloStudent();

  std::unique_ptr<Student> ptr3 = std::make_unique<Student>();
  ptr3->HelloStudent();

  Student * ptr4x = new Student("owned");
  std::unique_ptr<Student> ptr4(ptr4x);
  ptr4->HelloStudent();

  std::unique_ptr<Student[]> ptr5(new Student[3]);
  for (size_t i_ = 0; i_ < 3; ++i_) {
    ptr5[i_].HelloStudent();
  }

  return 0;
}
