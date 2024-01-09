
:- [hogwarts].

studentOf(Student, Teacher) :-
  teacherOf(Teacher, Student).

classmates(StudentOne, StudentTwo):-
  studentOf(StudentOne, Teacher),studentOf(StudentTwo, Teacher).

liveFarAway(StudentOne, StudentTwo):-
  houseOf(HouseOne, StudentOne), houseOf(HouseTwo, StudentTwo),
  HouseOne \== HouseTwo,
  farLocation(HouseOne, HouseTwo).

isSeniorOf(PersonA, PersonB):-
  directSeniorOf(PersonA, PersonB); 
  (directSeniorOf(PersonA, PersonC), isSeniorOf(PersonC, PersonB)).

listSeniors(Person, Seniors):-
  findall(Senior, isSeniorOf(Senior, Person), Seniors).

listJuniors(Person, Juniors):-
  findall(Junior, isSeniorOf(Person, Junior), Juniors).

oldestStudent(Person, House):-
  findall(BirthYear, (houseOf(House, Student), birthYear(Student, BirthYear)), BirthYears),
  min_list(BirthYears, MinBirthYear),
  houseOf(House, Person), birthYear(Person, MinBirthYear).

youngestStudent(Person, House):- 
  findall(BirthYear, (houseOf(House, Student), birthYear(Student, BirthYear)), BirthYears),
  max_list(BirthYears, MaxBirthYear),
  houseOf(House, Person), birthYear(Person, MaxBirthYear).

oldestQuidditchStudent(Team, Student):- 
  findall(BirthYear, (quidditchTeamOf(Team, Student_Find), birthYear(Student_Find, BirthYear)), BirthYears),
  min_list(BirthYears, MinBirthYear),
  quidditchTeamOf(Team, Student), birthYear(Student, MinBirthYear).

youngestQuidditchStudent(Team, Student):- 
  findall(BirthYear, (quidditchTeamOf(Team, Student_Find), birthYear(Student_Find, BirthYear)), BirthYears),
  max_list(BirthYears, MaxBirthYear),
  quidditchTeamOf(Team, Student), birthYear(Student, MaxBirthYear).

rival(StudentOne, StudentTwo):- 
  houseOf(HouseOne, StudentOne), houseOf(HouseTwo, StudentTwo),
  HouseOne \== HouseTwo.

farRival(StudentOne, StudentTwo):-
  rival(StudentOne, StudentTwo), 
  liveFarAway(StudentOne, StudentTwo).