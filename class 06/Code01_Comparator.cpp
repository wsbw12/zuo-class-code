#include <iostream>
#include <string>
#include <cstring>
#include <unordered_map>
#include <stack>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <cstdlib>
#include <cmath>

using namespace std;

#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cstdlib>

using namespace std;
const int Max = 100;

struct Student {
    string name;
    int id;
    int age;
};
// 自定义比较器的用法
bool cmpID(const Student &s1, const Student &s2) {
    return (s1.id < s2.id);
}

bool cmpAge(const Student &s1, const Student &s2) {
    return (s1.age < s2.age);
}
//按照ID从小到大,如果ID一样按照年龄从大到小
bool cmpIDAge(const Student &s1,const Student &s2)
{
    return s1.id!=s2.id ? (s1.id-s2.id) : (s2.age-s1.age)
}

void printStudents(Student students[], int Size) {
    for (int i = 0; i < Size; i++) {
        cout << students[i].name << ", " << students[i].id << ", " << students[i].age << endl;
    }
}

int main() {
    int test_time = 1000000;//进行测试的次数
    int size = 200;//生成数组的最大长度
    int value = 100;//生成数组的最大值
    bool is_accept = true;
    srand((int) time(NULL));//为随机数生成器产生随机种子
    Student s1 = {"张三", 5, 27};
    Student s2 = {"李四", 1, 17};
    Student s3 = {"王五", 4, 29};
    Student s4 = {"赵六", 3, 9};
    Student s5 = {"左七", 2, 34};
    Student students[] = {s1, s2, s3, s4, s5};
    printStudents(students, sizeof(students) / sizeof(s1));
    sort(students, students + sizeof(students) / sizeof(s1), cmpID);
    cout << "-----------" << endl;
    printStudents(students, sizeof(students) / sizeof(s1));
    cout << "-----------" << endl;
    sort(students, students + sizeof(students) / sizeof(s1), cmpAge);
    printStudents(students, sizeof(students) / sizeof(s1));
    cout << (is_accept ? "nice!\n" : "false!\n");
    return 0;
}