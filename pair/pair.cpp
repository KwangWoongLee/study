#include <utility> //stl pair를 사용하기 위한 전처리

#include <iostream>
/*
pair는 두가지 요소를 저장할 수 있는 구조체

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
	//pair 선언
	pair<int, int> p;
	pair<int, char> p2;

	p = make_pair(1, 1);
	p = make_pair(2, 1); // 내용변경
	cout << p.first;
	
	p2 = make_pair(1, 'a');

	cout << p2.second;


}