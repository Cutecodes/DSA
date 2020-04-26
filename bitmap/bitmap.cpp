#include "bitmap.h"

bool Bitmap::test(int k){
	return M[k>>3] & ( 0x80 >> ( k & 0x07 ) );
}

void Bitmap::set(int k){
	expand(k);
	M[k>>3] |= ( 0x80 >> ( k & 0x07 ) );
}

void Bitmap::clear(int k){
	expand(k);
	M[k>>3] &= ~( 0x80 >> ( k & 0x07 ));
}

void Bitmap::expand(int k){
	char* temp;
	if((k+7)/8<=N)
		return;
	temp = M;
	M = new char[N=(k+7)/8];
	memset(M,0,N);
	for(int i=0;i<N;i++)
		M[i]=temp[i];
	delete [] temp;

}
