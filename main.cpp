#include "Cuder.h"
const int N = 65536;
int main(){
	int A[N];  for (int i = 0; i < N; ++i) A[i] = i;
	
	//��ֹ���ⴴ��CUcontext,�����캯������Ϊprivate,��ȫ��������˿������캯���Ϳ�����ֵ�����
	redips::Cuder cuder = redips::Cuder::getInstance();
	//��Ӳ�����һ��.cu�ļ�,�൱��glsl shader �ļ�
	cuder.addModule("./kernel.cu");
	//�Դ�������һ����СΪ[sizeof(int)*N]������,����������Ϊ["a_dev"],���ں�������и�����ı�ʶ��
	//���������������Ϊnull,����ִ��cpu->gpu�����ݿ���
	cuder.applyArray("a_dev", sizeof(int)*N, A);
	//����["./kernel.cu"]�ļ���ָ����["fill"]����, ǰ���������趨��gridSize��blockSize
	//{ "a_dev", N }��C++11�е�initializer_list, ������ַ������Ӧǰ��������Դ�������,�����Ǳ�������
	cuder.launch(dim3(512, 1, 1), dim3(256, 1, 1), "./kernel.cu", "fill", { "a_dev", N });
	//��["a_dev"]��Ӧ���Դ����鿽����[A]
	cuder.fetchArray("a_dev", sizeof(int)*N, A);
	
	return 0;
}