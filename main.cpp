#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <set>
#include <map>
#include <string>
using namespace std;

struct Student {
    string Name;
    string LastName;
    string GroupId;
    vector<unsigned> Ratings;
    vector<string> Subjects;
};

struct Group {
    string Id;
    vector<Student> Students;
};

size_t CountExcellent(const vector<Student>& students) {
    return count_if(students.begin(), students.end(), [](const Student& student) {
        return all_of(student.Ratings.begin(), student.Ratings.end(), [](int grade) {
            return grade == 5;
        });
    });
}

void SortByName(vector<Student>& students) {
    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.Name < b.Name;
    });
}

void SortByRating(vector<Student>& students) {
    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        double avg_a = accumulate(a.Ratings.begin(), a.Ratings.end(), 0.0) / a.Ratings.size();
        double avg_b = accumulate(b.Ratings.begin(), b.Ratings.end(), 0.0) / b.Ratings.size();
        return avg_a > avg_b;
    });
}

size_t CountTwoness(const vector<Student>& students) {
    return count_if(students.begin(), students.end(), [](const Student& student) {
        return any_of(student.Ratings.begin(), student.Ratings.end(), [](int grade) {
            return grade == 2;
        });
    });
}

vector<Student> VectorMathExcellent(const vector<Student>& students) {
    vector<Student> excellentStudents;
    for (const auto& student : students) {
        auto it = find(student.Subjects.begin(), student.Subjects.end(), "Math");
        if (it != student.Subjects.end()) {
            size_t index = distance(student.Subjects.begin(), it);
            if (index < student.Ratings.size() && student.Ratings[index] == 5) {
                excellentStudents.push_back(student);
            }
        }
    }
    return excellentStudents;
}

vector<string> GroupsId(const vector<Student>& students) {
    set<string> Groups;
    vector<string> groups;
    for (const auto& student : students) {
        if (Groups.insert(student.GroupId).second) {
            groups.push_back(student.GroupId);
        }
    }
    return groups;
}

vector<Group> Groups(const vector<Student>& students) {
    map<string, vector<Student>> groupMap;
    for (const auto& student : students) {
        groupMap[student.GroupId].push_back(student);
    }

    vector<Group> groups;
    for (const auto& pair : groupMap) {
        Group group;
        group.Id = pair.first;
        group.Students = pair.second;
        groups.push_back(group);
    }

    return groups;
}

int main() {
    setlocale(LC_ALL, "Russian");
    while (true) {
        int d;
        cout << "Выберите задание:\n"
             << "1. Отсортировать всех студентов по именам\n"
             << "2. Отсортировать всех студентов по средней оценке\n"
             << "3. Вернуть количество студентов, имеющих неудовлетворительную оценку хотя бы по одному предмету\n"
             << "4. Определить, сколько студентов сдали все экзамены на 5\n"
             << "5. Создать массив студентов, имеющих оценку 'отлично' по предмету 'Math'\n"
             << "6. Вернуть массив уникальных названий групп студентов из списка\n"
             << "7. Сформировать список групп и студентов в них\n"
             << "0. Выход\n";
        cin >> d;
        if (d == 0) break;

        Student vlad = {"Vladislave", "Khodorovskiy", "Group1", {5, 5, 5, 5}, {"Math", "Physics","Programming","Computer science"}};
        Student anna = {"Anna", "Ivanova", "Group2", {2, 4, 2,3}, {"Math", "Physics","Programming","Computer science"}};
        Student ivan = {"Ivan", "Jopkin", "Group1", {4, 5, 5, 2}, {"Math", "Physics","Programming","Computer science"}};
        vector<Student> students={anna, ivan, vlad};

        switch (d) {
            case 1: {
                SortByName(students);
                cout << "Студенты, отсортированные по именам:\n";
                for (const auto& student : students) {
                    cout << student.Name << " " << student.LastName << endl;
                }
                cout << endl;
                break;
            }
            case 2: {
                SortByRating(students);
                cout << "Студенты, отсортированные по средней оценке:\n";
                for (const auto& student : students) {
                    double avg = accumulate(student.Ratings.begin(), student.Ratings.end(), 0.0) / student.Ratings.size();
                    cout << student.Name << " " << student.LastName << " - Средний балл: " << avg << endl;
                }
                cout << endl;
                break;
            }
            case 3: {
                size_t count = CountTwoness(students);
                cout << "Количество студентов, имеющих неудовлетворительную оценку (2): " << count << endl;
                cout << endl;
                break;
            }
            case 4: {
                size_t excellentCount = CountExcellent(students);
                cout << "Количество студентов, сдавших все экзамены на 5: " << excellentCount << endl;
                cout << endl;
                break;
            }
            case 5: {
                vector<Student> excellentMathStudents = VectorMathExcellent(students);
                cout << "Студенты с оценкой 'отлично' по 'Math':\n";
                for (const auto& student : excellentMathStudents) {
                    cout << student.Name << " " << student.LastName << " (" << student.GroupId << ")\n";
                }
                cout << endl;
                break;
            }
            case 6: {
                vector<string> groups = GroupsId(students);
                cout << "Уникальные названия групп:\n";
                for (const auto& group : groups) {
                    cout << group << endl;
                }
                cout << endl;
                break;
            }
            case 7: {
                vector<Group> groups = Groups(students);
                cout << "Список групп и студентов в них:\n";
                for (const auto& group : groups) {
                    cout << "Группа: " << group.Id << "\nСтуденты:\n";
                    for (const auto& student : group.Students) {
                        cout << " - " << student.Name << " " << student.LastName << endl;
                    }
                    cout << endl;
                }
                break;
            }
        }
    }
    return 0;
}