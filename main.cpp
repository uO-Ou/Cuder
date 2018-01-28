#include "Cuder.h"
const int N = 65536;
int main(){
	int A[N];  for (int i = 0; i < N; ++i) A[i] = i;
	
	//禁止随意创建CUcontext,将构造函数声明为private,安全起见禁用了拷贝构造函数和拷贝赋值运算符
	redips::Cuder cuder = redips::Cuder::getInstance();
	//添加并编译一个.cu文件,相当于glsl shader 文件
	cuder.addModule("./kernel.cu");
	//显存上申请一个大小为[sizeof(int)*N]的数组,并将其命名为["a_dev"],用于后面操作中该数组的标识；
	//如果第三个参数不为null,还会执行cpu->gpu的数据拷贝
	cuder.applyArray("a_dev", sizeof(int)*N, A);
	//运行["./kernel.cu"]文件中指定的["fill"]函数, 前两个参数设定了gridSize和blockSize
	//{ "a_dev", N }是C++11中的initializer_list, 如果是字符串则对应前面申请的显存数组名,否则是变量类型
	cuder.launch(dim3(512, 1, 1), dim3(256, 1, 1), "./kernel.cu", "fill", { "a_dev", N });
	//将["a_dev"]对应的显存数组拷贝回[A]
	cuder.fetchArray("a_dev", sizeof(int)*N, A);
	
	return 0;
}