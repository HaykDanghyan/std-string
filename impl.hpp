#include "string.h"

string::string() : m_capacity{24}, m_size{0}, m_buf{nullptr} {
    m_buf = new char[m_capacity];
    m_buf[0] = '\0';
}

string::string(size_t count, char ch) : m_capacity{count * 2}, m_size{count}, m_buf{nullptr} {
    m_buf = new char[m_capacity];
    for (int i = 0; i < count; ++i) {
        m_buf[i] = ch;
    }
    m_buf[count] = '\0';
}

string::string(const char* str) : m_capacity{strlen(str) * 2}, m_size{strlen(str)}, m_buf{nullptr} {
    m_buf = new char[m_capacity];
    for (int i = 0; i < m_size; ++i) {
        m_buf[i] = str[i];
    }    
    m_buf[m_size] = '\0';
}

string::string(const std::string& str) : m_capacity{str.length() * 2}, m_size{str.length()}, m_buf{nullptr} {
    m_buf = new char[m_capacity];
    for (int i = 0; i < m_size; ++i) {
        m_buf[i] = str[i];
    }
    m_buf[m_size] = '\0';
}

string::string(const string& str) : m_capacity{str.m_capacity}, m_size{str.m_size}, m_buf{nullptr} {
    m_buf = new char[m_capacity];
    for (int i = 0; i < m_size; ++i) {
        m_buf[i] = str.m_buf[i];
    }
    m_buf[m_size] = '\0';
}

string::string(string&& str) : m_capacity{str.m_capacity}, m_size{str.m_size}, m_buf{nullptr} {
    m_buf = str.m_buf;
    str.m_buf = nullptr;
}

string::~string() {
    delete[] m_buf;
    m_buf = nullptr;
}

string& string::operator=(const string& rhs) {
    if (this != &rhs) {
        if (m_buf) {
            delete[] m_buf;
        }
        m_size = rhs.m_size;
        m_capacity = rhs.m_capacity;
        m_buf = new char[m_capacity];
        for (int i = 0; i < m_size; ++i) {
            m_buf[i] = rhs.m_buf[i];
        }
        m_buf[m_size] = '\0';
    }
    return *this;
}

string& string::operator=(string&& rhs) {
    if (this != &rhs) {
        m_size = rhs.m_size;
        m_capacity = rhs.m_capacity;
        m_buf = rhs.m_buf;
        rhs.m_buf = nullptr;
    }
    return *this;
}

void string::assign(size_t count, char ch) {
    string temp(count, ch);
    *this = temp;
}

void string::assign(const char* str) {
    string temp(str);
    *this = temp;
}

void string::assign(const std::string& str) {
    string temp(str);
    *this = temp;
}

void string::assign(const string& str) {
    *this = str;
}

void string::assign(string&& str) {
    string temp(str);
    *this = temp;
}

char& string::at(size_t pos) {
    if (pos < 0 || pos > m_size) {
        throw std::out_of_range("Wrong index");
    }
    return m_buf[pos];
}

const char& string::at(size_t pos) const {
    if (pos < 0 || pos > m_size) {
        throw std::out_of_range("Wrong index");
    }
    return m_buf[pos];
}

char& string::operator[](size_t pos) {
    return m_buf[pos];
} 

const char& string::operator[](size_t pos) const {
    return m_buf[pos];
}

char& string::front() {
    return m_buf[0];
}

const char& string::front() const {
    return m_buf[0];
}

char& string::back() {
    return m_buf[m_size - 1];
}

const char* string::c_str() const {
    return m_buf;
}

const char& string::back() const {
    return m_buf[m_size - 1];
}

bool string::empty() const {
    return m_buf == nullptr;
}

size_t string::size() const {
    return m_size;
}

size_t string::length() const {
    return m_size;
}

void string::reserve(size_t count) {
    m_capacity += count;
    auto tmp = new char[m_capacity];
    for (int i = 0; i < m_size; ++i) {
        tmp[i] = m_buf[i];
    }
    tmp[m_size] = '\0';
    m_buf = tmp;
    tmp = nullptr;
}

size_t string::capacity() const {
    return m_capacity;
}

void string::shrink_to_fit() {
    if (m_size < m_capacity) {
        m_capacity = m_size;
    }
}

void string::clear() {
    delete[] m_buf;
    m_buf = nullptr;
}

void string::insert(size_t pos, char ch) {
    m_size += 1;
    if (m_capacity == m_size) {
        m_capacity *= 2;
    }
    char* tmp_buf = new char[m_capacity];
    int ix = 0;
    for (int i = 0; i < pos; ++i) {
        tmp_buf[i] = m_buf[ix++];
    }
    tmp_buf[pos] = ch;
    for (int i = pos + 1; i < m_size; ++i) {
        tmp_buf[i] = m_buf[ix++];
    }
    m_buf = std::move(tmp_buf);
}

void string::push_back(char ch) {
    ++m_size;
    if (m_size == m_capacity) {
        m_capacity *= 2;
    }
    int ix = 0;
    char* tmp_buf = new char[m_capacity];
    for (int i = 0; i < m_size; ++i) {
        tmp_buf[i] = m_buf[ix++];
    }
    tmp_buf[m_size - 1] = ch;
    m_buf = std::move(tmp_buf); 
    m_buf[m_size] = '\0';
}

void string::pop_back() {
    --m_size;
    char* tmp_buf = new char[m_capacity];
    for (int i = 0; i < m_size; ++i) {
        tmp_buf[i] = m_buf[i];
    }
    m_buf = std::move(tmp_buf);
}

void string::append(size_t count, char ch) {
    while (count--) {
        push_back(ch);
    }    
} 

void string::append(const char* str) {
    for (int i = 0; i < strlen(str); ++i) {
        push_back(str[i]);
    }
}

void string::append(const std::string& str) {
    append(str.c_str());
}

void string::append(const string& str) {
    append(str.c_str());
}

string& string::operator+=(char ch) {
    append(1, ch);
    return *this;
}

string& string::operator+=(const char* str) {
    append(str);
    return *this;
}

string& string::operator+=(const std::string& str) {
    append(str);
    return *this;
}

string& string::operator+=(const string& str) {
    append(str);
    return *this;
}

void string::replace(size_t pos, size_t count, const string& s) {
    int ix = 0;
    for (int i = pos; i < pos + s.length(); ++i) {
        m_buf[i] = s[ix++];
    }
}

string string::substr(size_t pos, size_t count) {
    if (pos > length()) {
        throw std::out_of_range("substr, this->length() = " + std::to_string(length()) + " pos = " + std::to_string(pos));
    }
    string tmp;
    int ix = 0;
    for (int i = pos; i < count; ++i) {
        tmp.m_buf[ix++] = m_buf[i];
    }
    tmp.m_buf[ix] = '\0';
    return tmp;
}

void string::copy(char* dest, size_t count) {
    for (int i = 0; i < count; ++i) {
        dest[i] = m_buf[i];
    }
    dest[count] = '\0';
}

void string::erase(size_t pos) {
    if (m_size == m_capacity) {
        m_capacity *= 2;
    }
    char* tmp = new char[m_capacity];
    int ix = 0;
    for (int i = 0; i < pos; ++i) {
        tmp[ix++] = m_buf[i];
    }
    for (int i = pos + 1; i < m_size; ++i) {
        tmp[ix++] = m_buf[i];
    }
    delete[] m_buf;
    m_buf = std::move(tmp);
} 