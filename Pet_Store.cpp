// Pet_Store.cpp

#include <iostream>
#include <sstream>
#include <vector>
#include "Pet_Store.h"

using namespace std;

Pet_Store::Pet_Store(size_t n) {
	set_size(n);
	_sort_order = NONE;
}

void Pet_Store::set_size(size_t n) {
	_pets.resize(n);
}

size_t Pet_Store::get_size() const {
	return _pets.size();
}

void Pet_Store::clear() {
	_pets.clear();
}

void Pet_Store::populate_with_n_random_pets(size_t n) {
	_sort_order = BY_ID;

	Pet::get_n_pets(n, _pets, 7);
}

bool Pet_Store::_id_compare(const Pet& p1, const Pet& p2) {
	return p1.get_id() < p2.get_id();
}

bool Pet_Store::_name_compare(const Pet& p1, const Pet& p2) {
	return p1.get_name() < p2.get_name();
}

void Pet_Store::_sort_pets_by_id() {
	std::sort(_pets.begin(), _pets.end(), Pet_Store::_id_compare);
	_sort_order = BY_ID;
}

void Pet_Store::_sort_pets_by_name() {
	std::sort(_pets.begin(), _pets.end(), Pet_Store::_name_compare);
	_sort_order = BY_NAME;
}

bool Pet_Store::find_pet_by_id_lin(long id, Pet& pet) {
	for (size_t i = 0; i < _pets.size(); i++) {
		if (id == _pets[i].get_id()) {
			pet.set_id(id);
			pet.set_name(_pets[i].get_name());
			pet.set_num_limbs(_pets[i].get_num_limbs());

			return true;
		}
	}

	return false;
}

bool Pet_Store::find_pet_by_name_lin(string name, Pet& pet) {
	for (size_t i = 0; i < _pets.size(); i++) {
		if (name.compare(_pets[i].get_name()) == 0) {
			pet.set_name(name);
			pet.set_id(_pets[i].get_id());
			pet.set_num_limbs(_pets[i].get_num_limbs());

			return true;
		}
	}

	return false;
}

// When this method starts, the _pets[] vector must be sorted in
// non-descending order by _id. If it is not already, then it will be resorted.
bool Pet_Store::find_pet_by_id_bin(long id, Pet& pet) {
	if (_sort_order != BY_ID)
		_sort_pets_by_id();

	int left = 0;
	int right = _pets.size();
	int pointer = 0;

	while ((right - left) / 2 != 0) {
		if (id == _pets[pointer].get_id()) {
			pet.set_id(id);
			pet.set_name(_pets[pointer].get_name());
			pet.set_num_limbs(_pets[pointer].get_num_limbs());

			return true;
		}

		if (id > _pets[pointer].get_id()) {
			left = pointer;
			pointer += (right - left) / 2;
		}
		else {
			right = pointer;
			pointer -= (right - left) / 2;
		}
	}

	return false;
}

// When this method is called, the _pets[] vector must be sorted in
// lexicographic non-descending order by _name. If it is not already,
// then it will be resorted.
bool Pet_Store::find_pet_by_name_bin(string name, Pet& pet) {
	if (_sort_order != BY_NAME)
		_sort_pets_by_name();

	int left = 0;
	int right = _pets.size();
	int pointer = 0;

	while ((right - left) / 2 != 0) {
		if (name.compare(_pets[pointer].get_name()) == 0) {
			pet.set_name(name);
			pet.set_id(_pets[pointer].get_id());
			pet.set_num_limbs(_pets[pointer].get_num_limbs());

			return true;
		}

		if (name.compare(_pets[pointer].get_name()) > 0) {
			left = pointer;
			pointer += (right - left) / 2;
		}
		else {
			right = pointer;
			pointer -= (right - left) / 2;
		}
	}

	return false;
}

// Return a string representation of the pets with indexes n1 through n2
// inclusive, exclusive of non-existent indices
// Each pet is on a line by itself.
string Pet_Store::to_string(size_t n1, size_t n2) {
	stringstream ss;

	for (size_t i = n1; i <= n2; i++)
		ss << _pets[i] << endl;

	return ss.str();
}