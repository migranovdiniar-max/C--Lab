#include "Keeper.h"

Keeper::Keeper() : size(0), capacity(10) {
    data = new Base*[capacity];
    std::cout << "Keeper default constructor called" << std::endl;
}

Keeper::Keeper(int initialCapacity) : size(0), capacity(initialCapacity) {
    if (initialCapacity <= 0) throw Exception("Invalid capacity");
    data = new Base*[capacity];
    std::cout << "Keeper parameterized constructor called" << std::endl;
}

Keeper::Keeper(const Keeper& other) : size(other.size), capacity(other.capacity) {
    data = new Base*[capacity];
    for (int i = 0; i < size; ++i) {
        data[i] = other.data[i];
    }
    std::cout << "Keeper copy constructor called" << std::endl;
}

Keeper::~Keeper() {
    for (int i = 0; i < size; ++i) {
        delete data[i];
    }
    delete[] data;
    std::cout << "Keeper destructor called" << std::endl;
}

Keeper& Keeper::operator=(const Keeper& other) {
    if (this != &other) {
        for (int i = 0; i < size; ++i) {
            delete data[i];
        }
        delete[] data;

        size = other.size;
        capacity = other.capacity;
        data = new Base*[capacity];
        for (int i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }
    std::cout << "Keeper assignment operator called" << std::endl;
    return *this;
}

void Keeper::resize() {
    capacity *= 2;
    Base** newData = new Base*[capacity];
    for (int i = 0; i < size; ++i) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
}

void Keeper::add(Base* item) {
    if (size >= capacity) resize();
    data[size++] = item;
}

void Keeper::remove(Base* item) {
    int index = findIndex(item);
    if (index != -1) remove(index);
}

void Keeper::remove(int index) {
    if (index < 0 || index >= size) throw Exception("Index out of range");
    delete data[index];
    for (int i = index; i < size - 1; ++i) {
        data[i] = data[i + 1];
    }
    size--;
}

void Keeper::printAll() const {
    if (size == 0) {
        std::cout << "Keeper is empty\n";
        return;
    }
    for (int i = 0; i < size; ++i) {
        std::cout << i + 1 << ". ";
        data[i]->print();
    }
}

void Keeper::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file) throw Exception("Cannot open file for writing");

    file << size << "\n";
    for (int i = 0; i < size; ++i) {
        if (dynamic_cast<Student*>(data[i])) {
            file << "Student\n";
        } else if (dynamic_cast<Teacher*>(data[i])) {
            file << "Teacher\n";
        } else if (dynamic_cast<Administrative*>(data[i])) {
            file << "Administrative\n";
        }
        data[i]->saveToFile(file);
    }
    file.close();
}

void Keeper::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) throw Exception("Cannot open file for reading");

    for (int i = 0; i < size; ++i) delete data[i];
    size = 0;

    int fileSize;
    file >> fileSize;
    file.ignore();

    for (int i = 0; i < fileSize; ++i) {
        std::string type;
        std::getline(file, type);

        Base* item = nullptr;
        if (type == "Student") {
            item = new Student();
        } else if (type == "Teacher") {
            item = new Teacher();
        } else if (type == "Administrative") {
            item = new Administrative();
        } else {
            throw Exception("Unknown type in file");
        }

        item->loadFromFile(file);
        add(item);
    }
    file.close();
}

int Keeper::findIndex(Base* item) const {
    for (int i = 0; i < size; ++i) {
        if (data[i] == item) return i;
    }
    return -1;
}

int Keeper::getSize() const { return size; }

Base* Keeper::get(int index) const {
    if (index < 0 || index >= size) throw Exception("Index out of range");
    return data[index];
}