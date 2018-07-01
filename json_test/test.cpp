/*
����֧�� stl ����:	
			j.push_back()	
			j.insert()		
			j.erase()		
			j.find()		
			j[0]		
			j[0][0]			
			��� https://github.com/nlohmann/json  STL-like access

json������Դ���������: (��stl������ת��ע��)
	vector<person> v(3, person("annan", 28));
	json testJ(v);
	testJ.push_back(8); 
	vector<person> testV(testJ.begin(), testJ.end()); // ����testJ �Ǹ����飬��������Ͳ�ȫ�� person����
*/

#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "json.hpp"
using namespace std;
using json = nlohmann::json;

namespace ann {
	struct person {
		string name;
		int age;

		person() {
			name = "";
			age = 0;
		}
		person(string n, int a) {
			name = n;
			age = a;
		}
	};
	// json �� stl ������ת����Ҫ����������ת������
	void to_json(json& j, const person& p) {
		j = json{ { "name",p.name },{ "age",p.age } };
	}
	void from_json(const json& j, person& p) {
		p.name = j.at("name").get<std::string>();
		p.age = j.at("age").get<int>();
	}
} 

using namespace ann;

int main()
{
	vector<person> v(3, person("annan", 28));

	// vector <==> json���� ��ת
	json j(v);
	vector<person> v1(j.begin(), j.end());
	vector<person> v2;
	v2.assign(j.begin(), j.end());

	// json array ����
	cout << "json array for range: " << endl;
	person p;
	for (const auto& element : j) {
		cout << "\t" << element << endl;
		p = element; 
	}

	// map ==> json ����
	map<string, person> m;
	m["one"] = person("annan", 28);

	json jm(m);
	cout << "map ==> json obj: " << jm<< endl;
	
	// json ������һ������
	json jarr = { 1,"0",3 };

	json jobj;
	jobj["1"] = jarr;
	cout << "json value is an array " << jobj << endl;

	// arry Ԫ�� �� json obj
	json jobj1;
	jobj1["name"] = "ann";

	json jarr1 = { 1,"0",3 };
	jarr1.push_back(jobj1);
	cout << "array element is a json obj: " << jarr1 << endl;
	cout << "jarr1[3][\"name\"] = " << jarr1[3]["name"] << endl;

	system("pause");
	return 0;
}