#include "lab2_drones_manager.hpp"
#include <iostream>

// TODO: Implement all of the listed functions below

DronesManager::DronesManager() {
	first = NULL;
	last = NULL;
	size = 0;
}

DronesManager::~DronesManager() {
	DroneRecord* cur = first;
	DroneRecord* prv = NULL;
	
	while(cur){
		prv = cur;
		cur = cur->next;
		delete(prv);
	}
	
	delete(first);
	delete(last);
}

bool operator==(const DronesManager::DroneRecord& lhs, const DronesManager::DroneRecord& rhs) {
	bool are_equal = lhs.droneID == rhs.droneID && lhs.range == rhs.range && lhs.yearBought == rhs.yearBought &&
					 lhs.droneType == rhs.droneType && lhs.manufacturer ==rhs.manufacturer &&
					 lhs.description == rhs.description && lhs.batteryType == rhs.batteryType;
	return are_equal;
}

unsigned int DronesManager::get_size() const {
	return size;
}

bool DronesManager::empty() const {
	if(size == 0)
		return true;
	if(first == NULL)
		return true;
	return false;
}

DronesManager::DroneRecord DronesManager::select(unsigned int index) const {
	if(empty())
		return DroneRecord(0);
		
	if(index < 1 || index > size)
		return *last;
		
	DroneRecord* cur = first;
	int track = 1;
	while(cur){
		if(index == track)
			return *cur;
		cur = cur->next;
		++track;
	}
	return *last;
}

unsigned int DronesManager::search(DroneRecord value) const {
	if(empty())
		return 0;
		
	DroneRecord* cur = first;
	int index = 1;
	while(cur){
		if(cur = &value)
			return index;	
		cur = cur->next;
		++index;
	}
	return size;
}

void DronesManager::print() const {
	if(empty())
		return;
	DroneRecord* cur = first;
	while(cur){
		cout << "DroneID: " << cur->droneID << endl << "Range: " << cur->range << endl 
		<< "Year Bought: " << cur->yearBought << endl << "Drone Type: " << cur->droneType << endl 
		<< "Manufactruer: " << cur->manufacturer << endl << "Description: " << cur->description << endl 
		<< "Battery Type: " << cur->batteryType << endl << endl;
		cur = cur->next;
	}
	return;
}

bool DronesManager::insert(DroneRecord value, unsigned int index) {
	if(index < 1 || index > size)
		return false;
	
	if (index == 1)
		return insert_front(value);
	
	if (index == size)
		return insert_back(value);

	
	DroneRecord* cur = first->next;
	int count = 2;
	
	// The passed in value takes and index in the middle of the list
	while(cur){
		if(index == count){
			cur->prev->next = &value;
			value.prev = cur->prev;
			cur->prev = &value;
			value.next = cur;
			++size;
			return true;
		}
		cur = cur->next;
		++count;
	}
		
	return false;
}

bool DronesManager::insert_front(DroneRecord value) {
	if(empty()){
		first = &value;
		last = &value;
		++size;
		return true;
	}

	value.next = first;
	first->prev = &value;
	value.prev = NULL;
	first = &value;
	++size;
	return true;
}

bool DronesManager::insert_back(DroneRecord value) {
	if(empty()){
		first = &value;
		last = &value;
		++size;
		return true;
	}

	last->next = &value;
	value.prev = last;
	value.next = NULL;
	last = &value;
	++size;
	return true;
}

bool DronesManager::remove(unsigned int index) {
	if(index < 1 || index > size || empty())
		return false;
			
	if(index == 1)
		return remove_front();
	
	if(index == size)
		return remove_back();
	
	DroneRecord* cur = first->next;
	int track = 2;
	while(cur){
		if(index == track){
			cur->prev->next = cur->next;
			cur->next->prev = cur->prev;
			delete(cur);
			--size;
			return true;			
		}
		cur = cur->next;
		++track;
	}
	return false;
}

bool DronesManager::remove_front() {
	if(empty())
		return false;
	
	if(size == 1){
		first = NULL;
		last = NULL;
		--size;
		return true;			
	}
	first = first->next;
	delete(first->prev);
	first->prev = NULL;				
	--size;
	return true;
}

bool DronesManager::remove_back() {
	if(empty())
		return false;
	
	if(size == 1){
		first = NULL;
		last = NULL;
		--size;
		return true;			
	}
	last = last->prev;
	delete(last->next);
	last->next = NULL;			
	--size;
	return true;
}

bool DronesManager::replace(unsigned int index, DroneRecord value) {
	if(index < 1 || index > size)
		return false;

	if(index == 1){
		return remove_front() && insert_front(value);
	}

	if(index == size){
		return remove_back() && insert_back(value);
	}
	
	return remove(index) && insert(value, index);
}

bool DronesManager::reverse_list() {
	if(empty() || size == 1)
		return false;
	DroneRecord* temp = first;
	first = last;
	last = temp;
	DroneRecord* cur = first;
	
	while(cur) {
		temp = cur->next;
		cur->next = cur->prev;
		cur->prev = temp;
		cur = cur->next; 
	}
	return true;
}
string get_status_str(bool status) {
    return status ? "TEST PASSED" : "TEST FAILED";
}
