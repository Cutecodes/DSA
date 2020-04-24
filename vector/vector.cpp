#include "vector.h"
#include<cstdlib>
#include "../fibonacci/fib.h"

template <typename T>
void Vector<T>::copyFrom(T const* A,Rank lo,Rank hi){
	_elem = new T[_capacity = 2 * (hi - lo)];
	_size = 0;
	while(lo < hi)
		_elem[_size++] = A[lo++];
}//O(n)

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T> const& V){
	if(_elem)
		delete [] _elem;
	copyFrom(V._elem,0,V.size());
	return *this;
}

template <typename T>
void Vector<T>::expand(){
	if(_size < _capacity)
		return;
	if(_capacity < DEFAULT_CAPACITY)
		_capacity = DEFAULT_CAPACITY;
	T* oldElem = _elem;
	_elem = new T[_capacity<<=1];
	for(int i = 0;i < _size;i++)
		_elem[i] = oldElem[i];
	delete [] oldElem;
}

template <typename T>
void Vector<T>::shrink(){
	if(_capacity <DEFAULT_CAPACITY<<1)
		return;
	if(_size <<2 > _capacity)
		return;
	T* oldElem = _elem;
	_elem = new T[_capacity >>=1];
	for(int i = 0;i < _size;i++)
		_elem[i] = oldElem[i];
	delete [] oldElem;

}

template <typename T>
T& Vector<T>::operator[](Rank r){
	return _elem[r];
}

template <typename T>
Rank Vector<T>::insert(Rank r,T const & e){
	expand();
	for(int i=_size;i>r;i--)
		_elem[i]=_elem[i-1];
	_elem[r]=e;
	_size++;
	return r;
}//O(n)

template <typename T>
int Vevtor<T>::remove(Rank lo,Rank hi){
	if(lo==hi)
		return 0;
	while(hi<_size)
		_elem[lo++]=_elem[hi++];
	_size = lo;
	shrink();
	return hi -lo;
}

template <typename T>
T Vector<T>::remove(Rank r){
	T e = _elem[r];
	remove(r,r+1);
	return e;
}

template <typename T>
Rank Vector<T>::find(T const& e,Rank lo,Rank hi) const{
	while((lo<hi--)&&(e!=_elem[hi]));
	return hi;
}

template <typename T>
int Vector<T>::deduplicate(){
	int oldSize = _size;
	Rank i =1;
	while(i<_size)
		if(find(_elem[i],0,i)<)
			i++;
		else
			remove(i);
	return oldSize-_size;
}

template <typename T>
void Vector<T>::traverse(void(*visit)(T&)){
	for(int i =0;i<_size;i++)visit(_elem[i]);
}

template <typename T> template <typename VST>
void Vector<T>::traverse(VST & visit){
	for(int i =0;i<_size;i++)visit(_elem[i]);
}

template <typename T>
int Vector<T>::disordered() const{
	int n=0;
	for(int i=1;i<_size;i++)
		n+=(_elem[i-1]>_elem[i]);
	return n;
}

template <typename T>
int Vector<T>::uniquify(){
	Rank i=0,j=0;
	while(++j<_size)
		if(_elem[i]!=_elem[j])
			_elem[++i]=_elem[j];
	_size = ++i;
	shrink();
	return j-i;
}

template <typename T> 
Rank Vector<T>::search(T const& e,Rank lo,Rank hi) const{
	return (rand()%2)?binSearch(_elem,e,lo,hi):fibSearch(_elem,e,lo,hi);
}

template <typename T>//binSearch A
static Rank binSearch(T * S,T const& e,Rank lo,Rank hi){
	while(lo < hi){
		Rank mi =(lo+hi)>>1;
		if(e<S[mi])
			hi=mi;
		else if(s[mi]<e)
			lo=mi+1;
		else
			return mi;
	}
	return -1;
}

template <typename T>
static Rank fibSearch(T *S,T const& e,Rank lo,Rank hi){
	for(Fib fib(hi-lo);lo<hi;){
		while(hi-lo<fib.get())
			fib.prev();
		Rank mi =lo+fib.get()-1;
		if(e<S[mi])
			hi = mi;
		else if(S[mi]<e)
			lo=mi+1;
		else 
			return mi;
	}
}

/*
 template <typename T>
 static Rank binSearch(T* S,T const& e,Rank lo,Rank hi){
 	while(1<hi-lo){
		Rank mi=(lo+hi)>>1;
		e<S[mi]?hi=mi:lo=mi;
	}
	return e==S[lo]?lo:-1;
	//return e<S[lo]?lo-1:lo;
 }
 */

/*
template <typename T>
static Rank binSearch(T* S,T const & e,Rank lo,Rank hi){
	while(lo<hi){
		Rank mi = (lo+hi)>>1;
		e<S[mi]?hi=mi:lo=mi+1;
	}
	return lo-1;
}
*/

template <typename T>
void Vector<T>::sort(Rank lo,Rank hi){
	switch(rand()%6){
		case 1: bubbleSort(lo,hi);break;
		case 2: selectionSort(lo,hi);break;
		case 3: mergeSort(lo,hi);break;
		case 4: heapSort(lo,hi);break;
		case 5: quickSort(lo,hi);break;
		default: shellSort(lo,hi);break;
	}
}

template <typename T>
void Vector<T>::bubbleSort(Rank lo,Rank hi){
	T temp;
	for(Rank last = --hi;lo<hi;hi=last)
		for(Rank i=last=lo;i<hi,i++)
			if(_elem[i]>_elem[i+1]){
				temp =_elem[i];
				_elem[i]=_elem[i+1];
				_elem[i+1]=temp;
				last=i;
			}
}

template <typename T>
void Vector<T>::mergeSort(Rank lo,Rank hi){
	if(hi-lo<2)
		return;
	int mi=(lo+hi)>>1;
	mergeSort(lo,mi);
	mergeSort(mi,hi);
	merge(lo,mi,hi);
}

template <typename T>
void Vector<T>::merge(Rank lo,Rank mi,Rank hi){
	T* A=_elem+lo;
	int lb=mi-lo;
	T* B=new T[lb];
	for(Rank i=0;i<lb;i++)
		B[i]=A[i];
	int lc=hi-mi;
	T* C=_elem+mi;
	for(Rank i=0,j=0,k=0;j<lb;)
		A[i++]=(lc<=k||B[j]<=C[k])?B[j++]:C[k++];
}
