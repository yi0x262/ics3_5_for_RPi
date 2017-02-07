#include<iostream>
using std::cout;
using std::endl;

//test for variable arguments with tmplate
template<typename Ret>
Ret any_sum()
{
  cout << "\b=";
  return 0;
}
template<typename Ret, typename First, typename... Rest>
Ret any_sum(const First& first, const Rest&... rest)
{
  cout << first << '+';
  return first+any_sum<Ret>(rest...);
}

int main(int argc,char* argv[])
{
  cout << argv[0] << endl;
  cout << any_sum<int>(1.0,2.2,3.3,4.9) << endl;
  cout << any_sum<double>(1.0,2.2,3.3,4.9) << endl;
  cout << any_sum<int>(10,25.3,-1e-3) << endl;
  return 0;
}
