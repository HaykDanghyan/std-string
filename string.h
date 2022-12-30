#ifndef STRING_H
#define STRING_H

#include <iostream>
#include <cstring>
#include <iterator>

class string {
public:
    static const size_t npos = -1;

public: // special member functions
    string();
    string(size_t, char);
    string(const char*);
    string(const std::string&);
    string(const string&);
    string(string&&);
    ~string();
 
    string& operator=(const string&);
    string& operator=(string&&);

    void assign(size_t, char);
    void assign(const char*);
    void assign(const std::string&);
    void assign(const string&);
    void assign(string&&);

public:
    class iterator : public std::iterator<std::random_access_iterator_tag, char> {
    public:
        using difference_type = typename std::iterator<std::random_access_iterator_tag, char>::difference_type;
        
        iterator() : buf{nullptr} {}
        iterator(char* rhs) : buf{rhs} {}
        iterator(const iterator& rhs) : buf{rhs.buf} {}
        iterator& operator+=(difference_type rhs) {
            buf += rhs;
            return *this;
        }
        iterator& operator-=(difference_type rhs) {
            buf -= rhs;
            return *this;
        }
        char& operator*() {
            return *buf;
        }
        char* operator->() {
            return buf;
        }
        char& operator[](difference_type rhs) const {
            return buf[rhs];
        }
        iterator& operator++() {
            ++buf;
            return *this;
        }
        iterator& operator--() {
            --buf;
            return *this;
        }
        iterator& operator++(int) {
            iterator tmp(*this);
            ++buf;
            return tmp;
        }
        iterator& operator--(int) {
            iterator tmp(*this);
            --buf;
            return tmp;
        }
        difference_type operator-(const iterator& rhs) const {
            return buf - rhs.buf;
        }
        iterator operator+(difference_type rhs) const {
            return iterator(buf + rhs);
        }
        iterator operator-(difference_type rhs) const {
            return iterator(buf-rhs);
        }
        friend bool operator==(const iterator& lhs, const iterator& rhs) {
            return lhs.buf == rhs.buf;
        }
        friend bool operator!=(const iterator& lhs, const iterator& rhs) {
            return lhs.buf != rhs.buf;
        }
        friend bool operator>(const iterator& lhs, const iterator& rhs) {
            return lhs.buf > rhs.buf;
        }
        friend bool operator<(const iterator& lhs, const iterator& rhs) {
            return lhs.buf < rhs.buf;
        }
        friend bool operator>=(const iterator& lhs, const iterator& rhs) {
            return lhs.buf >= rhs.buf;
        }
        friend bool operator<=(const iterator& lhs, const iterator& rhs) {
            return lhs.buf <= rhs.buf;
        }
    private:
        char* buf;
    };


public: // element access
    char& at(size_t); // accesses the specified character with bounds checking
    const char& at(size_t) const;

    char& operator[](size_t); // accesses the specified character
    const char& operator[](size_t) const;

    char& front(); // accesses the first character
    const char& front() const;

    char& back(); // accesses the last character
    const char& back() const;

    const char* c_str() const; // returns a non-modifiable standard C character array version of the string

public: // capacity
    bool empty() const; // checks whether the string is empty

    size_t size() const; // returns the number of characters
    size_t length() const;

    void reserve(size_t); // reserves storage

    size_t capacity() const; // returns the number of characters that can be held in currently allocated storage

    void shrink_to_fit(); // reduces memory usage by freeing unused memory

public:
    void clear(); // clears the contents

    void insert(size_t, char); // inserts characters

    void erase(size_t); // removes characters

    void push_back(char); // appends a character to the end
    
    void pop_back(); // removes the last character

    void append(size_t, char); // appends characters to the end
    void append(const char*);
    void append(const std::string&);
    void append(const string&);

    string& operator+=(char); // appends characters to the end
    string& operator+=(const char*);
    string& operator+=(const std::string&);
    string& operator+=(const string&);

    void replace(size_t, size_t, const string&); // replaces specified portion of a string
    
    string substr(size_t pos = 0, size_t count = string::npos); // returns a substring
    
    void copy(char*, size_t); // copies characters


public:
    friend string operator+(string& str, char ch) {
        str.push_back(ch);
        return str;
    }

    friend string operator+(char ch, string& str) {
        str.insert(0, ch);
        return str;
    }
    
    friend string operator+(string& str, const char* csl) {
        str.append(csl);
        return str;
    }

    friend string operator+(const char* csl, string& str) {
        for (int i = 0; i < strlen(csl); ++i) {
            str.insert(i, csl[i]);
        }
        return str;
    }

    friend string operator+(string& str, const std::string& rhs) {
        str = str + rhs.c_str();
        return str;
    }

    friend string operator+(const std::string& lhs, string& str) {
        str = lhs.c_str() + str;
        return str;
    }

    friend string operator+(string& str, const string& rhs) {
        str = str + rhs.c_str();
        return str;
    }

    friend string operator+(const string& lhs, string& str) {
        str = lhs.c_str() + str;
        return str;
    }   

    friend bool operator==(const string& lhs, const string& rhs) {
        if (lhs.length() == rhs.length()) {
            for (int i = 0; i < lhs.length(); ++i) {
                if (lhs[i] != rhs[i]) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }

    friend bool operator!=(const string& lhs, const string& rhs) {
        return !(lhs == rhs);
    }

    friend std::ostream& operator<<(std::ostream& os, const string& str) {
        os << str.m_buf;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, string& str) {
        char input = 0;
        while (is.get(input)) {
            if (input == '\n') {
                break;
            }
            if (str.m_size == str.m_capacity) {
                str.m_capacity *= 2;
                char* new_buf = new char[str.m_capacity];
                strcpy(new_buf, str.m_buf);
                delete[] str.m_buf;
                str.m_buf = new_buf;
                new_buf = nullptr;
            }
            str.m_buf[str.m_size++] = input;
            str.m_buf[str.m_size] = '\0';
        }
        return is;
    }
private:
    char* m_buf;
    size_t m_size;
    size_t m_capacity;
};
#include "impl.hpp"
#endif // STRING_H