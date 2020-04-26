#ifndef BITMAP_H
#define BITMAP_H

class Bitmap{
	private:
		int N;
		char* M;
		void expand(int k);
	public:
		Bitmap(int n=8){
			M=new char[N=(n+7)/8];
			memset(M,0,N);
		}
		~Bitmap(){
			delete [] M;
			M = NULL;
		}
		void set(int k);
		void slear(int k);
		bool test(int k);
}

#endif
