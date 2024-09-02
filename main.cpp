#define NOMIXMAX
#include <cstdio>
#include <cstring>
#include<limits>
#include <windows.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <set>
#include <clocale>
#include <ctime>
#include <string>
#include <regex>
#include <algorithm>
#include <random>
#include <list>
#include <json/json.h>
#include <json/value.h>
#define JSON "Result.txt"
#define TEST "Text.txt"
using namespace std;
int max_valuepar2 = 0;
struct Filelist
{
    char name[15];
    int main_par;
    int secondary_par;
};
Filelist temper;
bool compare(const Filelist& a, const Filelist& b)
{
    return strlen(a.name) > strlen(b.name);
}
bool is_even(Filelist);
template <typename T>
void fill_data(string str, T &temp, function<bool(T)> f)
{
    char c;
    cout << str;
    cin >> temp;
    if (!f(temp))
        cin.setstate(ios_base::failbit);
    while((c = getchar()) != '\n');
    while(cin.fail())
    {
        cin.clear();
        cout << str;
        cin >> temp;
        if (!f(temp))
            cin.setstate(ios_base::failbit);
        while((c = getchar()) != '\n');
    }
}
void print(Filelist & item)
{
    cout << "�������� " << " �������� �������� " << " ��������� �������� " << endl;
    cout << left << setw(18) << item.name << left << setw(19) << item.main_par << left << setw(10) << item.secondary_par<< endl;
    cout << endl;
}
bool isFilled(const Filelist& item)
{
    if (item.name[0]) return true;
    return false;
}
int main()
{
    setlocale(0, "rus");
    int menu;
    do
    {
        fill_data<int>("1 - �������� � ������������ ������ json\n2 - ������� ����� �� ������ ��������� �����\n3 - �����\n", menu, [](int a){return true;});
        switch(menu)
        {
            case 1:
            {
                char ch;
                fill_data<char>("���������� ������ ����� ���������� ������?(n/y)\n", ch, [](char a){return (a == 'y') || (a == 'n');});
                ifstream in;
                Json::Value actual;
                Json::Reader reader;
                list<Filelist> task_list;
                in.open(JSON);
                if (!in.is_open())
                {
                    cout << "������ �������� �����\n";
                    return -1;
                }
                reader.parse(in, actual);
                cout << "���� � ������� json\n" << actual << endl;
                for (auto & elem: actual.getMemberNames())
                {
                    for (int i = 0; i < 15; i++)
                        temper.name[i] = elem[i];
                    temper.main_par = actual[string(elem)]["Main parametr"].asInt();
                    temper.secondary_par = actual[string(elem)]["Secondary parametr"].asInt();
                    task_list.push_back(temper);
                }
                if (ch == 'y')
                {
                    //����������� ������ � ������
                    vector<Filelist> help(task_list.begin(), task_list.end());
                    //���������� ����������� ��������� ��������� �����
                    random_device rd;
                    mt19937 g(rd());
                    //������������ �������� � �������
                    shuffle(help.begin(), help.end(), g);
                    //�������� �������� �� ������� ������� � ������
                    task_list.assign(help.begin(), help.end());
                }
                cout << endl << "���������� ������ �� ����� json" << endl;
                for (auto elem: task_list)
                    print(elem);
                in.close();
                break;
            }
            case 2:
            {
                ifstream in;
                ofstream out;
                in.open(TEST);
                if (!in.is_open())
                {
                    cout << "������ �������� �����!\n";
                    return -1;
                }
                set<string> Names;
                int num1, num2, num3;
                auto it = Names.begin();
                list<Filelist> task_list;
                set<char> temp;
                map<char, int> freq_dict;
                auto pdict = freq_dict.begin();
                string mystr;
                getline(in, mystr);//��������� ��� ������ �� ����� � ������
                smatch result;
                /* ��������� ����� ����� ������� ����������� ��������*/
                for (char i = 65; i < 91; i++)
                {
                    freq_dict.emplace(i, 0);
                }
                for (char i = 97; i < 123; i++)
                {
                    freq_dict.emplace(i, 0);
                }
                /*�������� ��������� �� ���������� ���� � �����*/
                while (regex_search(mystr, result, regex("([^#]+){1}")) || regex_search(mystr, result, regex("[^#]+#*([^#]+)")))/*��������� �� ������
                                                                                                                            �������� ����� �� ������� #*/
                {
                    Names.insert(result.str());
                    mystr = result.suffix();//����������� ����������� ������ ��������� �� ����� ��������� ������������������ �� ����� ����������� ������
                }
                cout << "�������� ��������� �� ���������� ���� � �����\n";
                for (auto i: Names)
                {
                    cout << "�������� ����� �� ��������� - " << i << endl;
                }
                /*�������� ������� �� ���������� � ������� ��������(���� - �����, �������� - ������� ������� � ����� ����, ���������� ��� �����.)*/
                for (auto i: Names)
                {
                    for (auto j:i)
                        temp.insert(j);
                    for (auto j:temp)
                    {
                        for (auto& z:freq_dict)
                        {
                            if (j == z.first)
                            {
                                z.second++;
                                break;
                            }
                        }
                    }
                    temp.clear();
                }
                system("pause");
                system("cls");
                cout << "�������� ������� �� �������� ����: �����, ��������: ������� ������� ���� �����, ���������� ��� �����\n";
                for (auto i: freq_dict)
                {
                    cout << "���� - " << i.first;
                    cout << " �������� - " << i.second;
                    cout << endl;
                }
                system("pause");
                system("cls");
                cout << "������������ ������ �� 100 �������� � ������ \n�������� - ��������� ����� �� ���������; \n�������� �������� - ��������� std::advance �������� �������� ��� ��������� ��������� �� ������� � ����������� ��;\n��������� �������� - ������� �������� �� �������, ���������� � ���������(� ������ ����� ����� ������ ����� ��������).\n";
                for (int n{0}; n < 100; n++)
                {
                    srand(n);
                    it = Names.begin();
                    advance(it, rand() % Names.size());
                    int j = 0;
                    for (char * i = const_cast<char *>((*it).c_str()); j < 15; i++, j++)
                    {
                        temper.name[j] = *i;
                    }
                    advance(pdict, rand() % freq_dict.size()); //�������� �������� pdict �� ��������� ��������
                    num1 = (*pdict).second;
                    pdict = freq_dict.begin();// ���������� �������� pdict �� ������ �������
                    advance(pdict, rand() % freq_dict.size());//�������� �������� pdict �� ��������� ��������
                    num2 = (*pdict).second;
                    pdict = freq_dict.begin();// ���������� �������� pdict �� ������ �������
                    advance(pdict, rand() % freq_dict.size());//�������� �������� pdict �� ��������� ��������
                    num3 = (*pdict).second;
                    pdict = freq_dict.begin();// ���������� �������� pdict �� ������ �������
                    temper.main_par = num1 * num2 * num3;
                    temper.secondary_par = freq_dict[temper.name[0]] * freq_dict[temper.name[0]];
                    max_valuepar2 = max(temper.secondary_par, max_valuepar2);
                    task_list.push_back(temper);
                }
                for (auto i:task_list)
                    print(i);
                system("pause");
                system("cls");
                cout << "������������ ������ �� �������� ��������\n";
                task_list.sort(compare);
                for (auto i:task_list)
                    print(i);
                cout << endl << endl;
                system("pause");
                system("cls");
                /*��������� copy_if ������ ����� ������, � ������� ������ �������� � ������������ ��������� ���������� ���������*/
                cout << "��������� std::copy_if, ������ ����� ������, ��������� ������ �� ���������, ���������� ������������ �������� ���������� ���������\n";
                list<Filelist> newtask_list(task_list.size());
                copy_if(begin(task_list), end(task_list), begin(newtask_list), is_even);
                newtask_list.erase(std::remove_if(newtask_list.begin(), newtask_list.end(), [](const Filelist& item) { return strlen(item.name) == 0; }), newtask_list.end());
                task_list = newtask_list;
                for (auto i:task_list)
                    print(i);
                out.open(JSON);
                if (!out.is_open())
                {
                    cout << "�� ������� ������� ����\n";
                    return -1;
                }
                /*�� ������ ����������� ������ ���� ������� json*/
                Json::Value valueobj;
                for (auto j:task_list)
                {
                    valueobj[j.name]["Main parametr"] = j.main_par;
                    valueobj[j.name]["Secondary parametr"] = j.secondary_par;
                }
                Json::StyledWriter stylewriter;
                out << stylewriter.write(valueobj);
                out.close();
                in.close();
                break;
            }
        }
    }
    while(menu != 3);
    return 0;
}
bool is_even(Filelist n)
{
    return max_valuepar2 == n.secondary_par;
}
