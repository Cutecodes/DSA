#pragma once

#include "../list/list.h"

template <typename T>
class Quene:public List<T>{
	public:
		void enqueue(T const& e){
			insertAsLast(e);
		}
		T dequeue(){
			return remove(first());
		}
		T& front(){
			return first()->data;
		}
}
