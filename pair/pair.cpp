#include <utility> //stl pair�� ����ϱ� ���� ��ó��

#include <iostream>
/*
pair�� �ΰ��� ��Ҹ� ������ �� �ִ� ����ü

template <typename T1 ,typename T2>
struct pair
{
	T1 first,
	T2 second
}
*/
using namespace std;
int main() 
{
	//pair ����
	pair<int, int> p;
	pair<int, char> p2;

	p = make_pair(1, 1);
	p = make_pair(2, 1); // ���뺯��
	cout << p.first;
	
	p2 = make_pair(1, 'a');

	cout << p2.second;


}