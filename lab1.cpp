#include <iostream>
#include <pthread.h>

using namespace std;

class LCG
{
	pthread_t tid;
	static void* handler_gen(void *temp)
	{
		LCG * cur = reinterpret_cast<LCG *>(temp);
		return cur->generator(cur);
	}
	void* generator(LCG* cur){
        int *rez = new int [cur->N];
        rez[0] = cur->x0;
        for (int i = 1; i < cur->N; i++)
        	rez[i] = (cur->a*rez[i-1] + cur->c) % cur->m;

        return rez;
    };
	public:
		int a,c,m,x0,N;
		LCG(int x0, int a, int c, int m, int N){
			this->a = a; this->x0 = x0;
			this->c = c; this->m = m;
			this->m = N;
		}
		int* run(){
			void *per;
			int *sum;
			pthread_create(&tid, NULL, handler_gen, this);
			int buf;
			buf = pthread_join(tid, &per);

			sum = (int*)per;

			return sum;
		}
};

int main()
{
	cout << "enter X0, a, c, m, N" << endl;
	int a,c,m,x0,N;
	cin >> x0 >> a >> c >> m  >> N;


	LCG lcg(a,c,m,x0,N);
	int* res = lcg.run();

	for(int i=0; i < N; i++)
		cout << res[i] << " ";
	cout << endl;
	return 0;
}
