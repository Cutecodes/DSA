#include "list.h"

template <typename T>
void List<T>::init(){
	header = new ListNode<T>;
	trailer = new ListNode<T>;
	header->succ = trailer;
	header->pred = NULL;
	trailer->pred = header;
	trailer->succ = NULL;
	_size = 0;
}

template <typename T> 
T List<T>::operator[](Rank r) const{
	//O(r)
	ListNodePosi(T) p = first();
	while (0<r--)
		p=p->succ;
	return p->data;
}

template <typename T> 
ListNodePosi(T) List<T>::insertB(ListNodePosi(T) p,T const & e){
	_size++;
	return p->insertAsPred(e);
}

template <typename T>
ListNodePosi(T) List<T>::insertA(ListNodePosi(T) p,T const & e){
	_size++;
	return p->insertAsSucc(e);
}

template <typename T>
T List<T>::remove(ListNodePosi(T) p){
	T e = p->data;
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;
	delete p;
	_size--;
	return e;
}

template <typename T>
void List<T>::copyNodes(ListNodePosi(T) p,int n){
	init();
	while(n--){
		insertAsLast(p->data);
		p=p->succ;
	}
}

template <typename T>
List<T>::List(List<T> const & L){
	copyNodes(L.first(),L._size);
}

template <typename T>
List<T>::List(ListNodePosi(T) p,int n){
	copyNodes(p,n);
}

template <typename T>
List<T>::List(List<T> const & L,Rnak r,int n){
	ListNodePosi(T) p =L.first();
	while(0<r--)
		p=p->succ;
	copyNodes(p,n);
}

template <typename T>
int List<T>::clear(){
	int oldSize =_size;
	while(0<_size)
		remove(header->succ);
	return oldSize;
}

template <typename T>
List<T>::~List(){
	clear();
	delete header;
	delete trailer;
}

template <typename T>
ListNodePosi(T) List<T>::find(T const & e,int n,ListNodePosi(T) p){
	while(0<n--)
		if(e==(p=p->pred)->data)
			return p;
	return NULL;
}

template <typename T>
ListNodePosi(T) List<T>::search(T const& e,int n,ListNodePosi(T) )const{
	do{
		p=p->pred;n--;
	}while((-1<n)&&(e<p->data));
	return p;
}

template <typename T>
void List<T>::selectionSort(ListNodePosi(T) p,int n){
	ListNodePosi(T) head =p->pred;
	ListNodePosi(T) tail =p;
	for(int i=0;i<n;i++)
		tail=tail->succ;
	while(1<n){
		insertB(tail,remove(selectMax(head->succ,n)));
		tail = tail->pred;
		n--;
	}
}

template <typename T>
ListNodePosi(T) List<T>::selectMax(ListNodePosi(T) p,int n){
	ListNodePosi(T) max = p;
	for(ListNodePosi(T) cur = p;1<n;n--)
		if((cur=cur->succ)->data>=max->data)
			max=cur;
	return max;
}

template <typename T>
void List<T>::insertionSort(ListNodePosi(T) p,int n){
	for(int r=0;r<n;r++){
		insertA(search(p->data,r,p),p->data);
		p = p->succ;
		remove(p->pred);
	}
}

template <typename T>
void List<T>::mergeSort(ListNodePosi(T)& p,int n){
	if(n<2)return;
	ListNodePosi(T) q=p;
	int m=n>>1;
	for(int i=0;i<m;i++)
		q=q->succ;
	mergeSort(p,m);
	mergeSort(q,n-m);
	merge(p,m,*this,q,n-m);
}

template <typename T>
void List<T>::merge(ListNodePosi(T) & p,int n,List<T> & L,ListNodePosi(T) q,int m){
	ListNodePosi(T) pp =p->pred;
	while(0<m)
		if((0<n)&&(p->data<=q->data)){
			if(q==(p=p->succ))
				break;
			n--;
		}else{
			insertB(p,L.remove((q=q->succ)->pred));
			m--;
		}
	p=pp->succ;
}
