#ifndef INCLUDED_QJSON_H
#define INCLUDED_QJSON_H

#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include <memory>
#include <algorithm>
#include <istream>
#include <utility>
#include <sstream>
#include <string.h>

// very small footprint json reader

namespace qjson {

inline std::string as_one_line(const std::string &in) {
    std::string ret=in;
    char *p=&ret[0];
    while(*p) {if (*p=='\n') *p=' '; ++p;}
    return ret;
}

class error : public std::runtime_error {
    public:
    error(const std::string &what) : std::runtime_error(as_one_line(what)) {}
};


class value;

typedef std::shared_ptr<value> value_ptr;
typedef std::map<std::string, value_ptr> value_map;
typedef std::vector<value_ptr> value_list;

class value {
    private:

    std::string d_str;
    value_list d_vec;
    value_map d_map;
    int d_int;
    double d_dbl;

    enum type {
        NONE,
        MAP,
        LIST,
        STRING,
        FLOAT,
        INT,
        BOOL
    } d_type;

    static std::string type_name(type type) {
        switch (type) {
            case STRING: return "string";
            case INT: case FLOAT: return "number";
            case MAP: return "map";
            case LIST: return "list";
            case BOOL: return "bool";
            case NONE: default: return "none";
        }
    }
    static std::string tolower(const std::string &in) {
        std::string tmp=in;
        std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
        return tmp;
    }

    static std::string read_len(std::istream &in, int len) {
        std::string buf(len+1,'\0');
        in.get(&buf[0],len+1,'\0');
        buf.resize(strlen(buf.c_str()));
        return buf;
    };

    static std::string read_sample(std::istream &in) {
        return read_len(in, 10);
    };

    static std::string read_string(std::istream &in) {
        std::string str;
        while (1) {
            char c = in.get();
            if (c < ' ') {
                in.unget();
                throw error("string error found at '" + read_sample(in) + "'");
                return "";
            } else if (c == '"') {
                return str;
            } else if (c == '\\') {
                if ((c = in.get()) == -1) {
                    throw error("string ends after \\");
                    return "";
                }
                switch (c) {
                    #define MAP(sym, val) case sym: str+=val; break
                    MAP('"', '\"');
                    MAP('\\', '\\');
                    MAP('/', '/');
                    MAP('b', '\b');
                    MAP('f', '\f');
                    MAP('n', '\n');
                    MAP('r', '\r');
                    MAP('t', '\t');
                    #undef MAP
                    default:
                        throw error("unhandled escape at '" + read_sample(in) + "'");
                }
            } else {
                str += c;
            }
        }
    }

    static void trim(std::istream &in) {
        while(isspace(in.peek())) in.get();
    };

    std::string type_name() const {
        return type_name(d_type);
    };

    const value_ptr get_map(const std:: string &key) const {
        value_map::const_iterator it=d_map.find(key);
        if (it != d_map.end())
            return it->second;
        throw error("key '" + key + "' not found in map");
    }

    public:

    bool isString() const { return d_type == STRING; }
    bool isMap() const { return d_type == MAP; }
    bool isList() const { return d_type == LIST; }
    bool isNumber() const { return d_type == INT || d_type==FLOAT; }
    bool isBool() const { return d_type == BOOL; }

    size_t size() const {
        if (isString()) {
          return d_str.size();
        }
        if (isMap()) {
          return d_map.size();
        }
        if (isList()) {
          return d_vec.size();
        }
        throw error("size() not defined for type " + type_name());
    }

    bool has(const std:: string &key) const {
        value_map::const_iterator it=d_map.find(key);
        return (it != d_map.end());
    }

    value &operator[](const char *key) const {
        if (isMap()) return *(get_map(key));
        throw error("operator[](char *) not defined for type " + type_name());
    }

    value &operator[](const std::string &key)const  {
        if (isMap()) return *(get_map(key));
        throw error("operator[](string) not defined for type " + type_name());
    }

    value &operator[](int index) const {
        if (index < 0)
            throw error("index < 0 invalid");
        return (*this)[(size_t)index];
    }

    value &operator[](size_t index) const {
        if (isList() && index < d_vec.size())
            return *(d_vec[index]);
        else
            throw error("index not found in list");
        throw error("operator[](int) not defined for type " + type_name());
    }

    value_map &map() {
        if (isMap()) return d_map;
        throw error("map() not defined for type " + type_name());
    }

    const value_map &map() const {
        if (isMap()) return d_map;
        throw error("map() not defined for type " + type_name());
    }

    value_list &list() {
        if (isList()) return d_vec;
        throw error("list() not defined for type " + type_name());
    }

    const value_list &list() const {
        if (isList()) return d_vec;
        throw error("list() not defined for type " + type_name());
    }

    std::string &string() {
        if (isString()) return d_str;
        throw error("str() not defined for type " + type_name());
    }

    const std::string &string() const {
        if (isString()) return d_str;
        throw error("str() not defined for type " + type_name());
    }

    operator std::string &() {
        if (isString()) return d_str;
        throw error("string &() not defined for type " + type_name());
    }

    operator const std::string &() const {
        if (isString()) return d_str;
        throw error("string &() not defined for type " + type_name());
    }

    operator int() const {
        if (d_type==INT || isBool()) return d_int;
        throw error("int &() not defined for type " + type_name());
    }

    operator bool() const {
        if (d_type==INT || isBool()) return d_int;
        throw error("bool &() not defined for type " + type_name());
    }

    operator double() const {
        if (d_type==FLOAT) return d_dbl;
        if (d_type==INT) return d_int;
        throw error("double &() not defined for type " + type_name());
    }

    void read(std::istream &in) {
        trim(in);
        char c;
        c=in.get();
        if (c == '{') {
            d_type=MAP;
            d_map.clear();
            if (in.peek() != '}') {
                do {
                    std::string key;
                    value_ptr val = std::make_shared<value>();

                    trim(in);
                    c=in.get();
                    if (c != '"') {
                        in.unget();
                        throw error("'\"' not found at '" + read_sample(in) + "'");
                    }
                    key = read_string(in);
                    trim(in);

                    c=in.get();
                    if (c != ':') {
                        in.unget();
                        throw error("':' not found at '" + read_sample(in) + "'");
                    }

                    val->read(in);
                    d_map[key]=val;
					c=in.get();
                } while (c == ',');
            } else {
                c=in.get();
            }
            if (c!='}') {
                throw error("'}' not found at '" + read_sample(in) + "'");
            }
        } else if (c == '[') {
            d_type=LIST;
            d_vec.clear();
            if (in.peek() != ']') {
                do {
                    trim(in);
                    value_ptr val = std::make_shared<value>();
                    val->read(in);
                    d_vec.push_back(val);
                    c=in.get();
                } while (c == ',');
            } else {
                c=in.get();
            }
            if (c!=']') {
                throw error("']' not found at '" + read_sample(in) + "'");
            }
        } else if (c == '"') {
            d_type=STRING;
            d_str=read_string(in);
        } else if (::tolower(c) == 't') {
            if (tolower(read_len(in,3))!="rue")
                throw error("bare word found at '" + read_sample(in) + "'");
            d_type=BOOL;
            d_int=1;
        } else if (::tolower(c) == 'f') {
            if (tolower(read_len(in, 4))!="alse")
                throw error("bare word found at '" + read_sample(in) + "'");
            d_type=BOOL;
            d_int=0;
        } else {
            in.unget();
            std::string num_str;
            d_type=INT;
            while (1) {
              c = in.get();
              if (('0' <= c && c <= '9') || c == '+' || c == '-'
                  || c == 'e' || c == 'E') {
                num_str += c;
                if (c=='e' || c=='E')
                    d_type=FLOAT;
              } else if (c == '.') {
                num_str += '.';
                d_type=FLOAT;
              } else {
                in.unget();
                break;
              }
            }
            if (d_type == FLOAT) {
                d_dbl=atof(num_str.c_str());
            } else {
                d_int=atoi(num_str.c_str());
            }
        }
		trim(in);
	}

    static void print(std::ostream &out, const std::string &in) {
        for (std::string::const_iterator p=in.begin();p!=in.end();++p) {
            switch(*p) {
                #define MAP(sym, val) case sym: out << '\\' << val; break
                MAP('"', '"');
                MAP('\\', '\\');
                MAP('/', '/');
                MAP('\b', 'b');
                MAP('\f', 'f');
                MAP('\n', 'n');
                MAP('\r', 'r');
                MAP('\t', 't');
                #undef MAP
                default:
                    out << *p;
            }
        }
    }

    void print(std::ostream &out) const {
        if (d_type==INT) {
            out << d_int;
        } else if (d_type==FLOAT) {
            out << d_dbl;
        } else if (d_type==BOOL) {
            out << (d_int ? "true" : "false");
        } else if (d_type==STRING) {
            out << '"';
            print(out, d_str);
            out << '"';
        } else if (d_type==LIST) {
            out << '[';
            for (value_list::const_iterator it=d_vec.begin();it!=d_vec.end();++it) {
                if (it!=d_vec.begin()) out << ',';
                (*it)->print(out);
            }
            out << ']';
        } else if (d_type==MAP) {
            out << '{';
            for (value_map::const_iterator it=d_map.begin();it!=d_map.end();++it) {
                if (it!=d_map.begin()) out << ',';
                out << '"';
                print(out, it->first);
                out << '"' << ':';
                it->second->print(out);
            }
            out << '}';
        }
    }

    void read(const std::string &str) {
        std::istringstream in(str);
        read(in);
    }

    value() : d_type(NONE) {};
    value(std::istream &in) : d_type(NONE) {read(in);}
    value(const std::string &in) : d_type(NONE) {read(in);}
};

};  // namespace qjson

inline std::ostream &operator <<(std::ostream &out, const qjson::value &v) {
    v.print(out); return out;
}

#endif // INCLUDED_QJSON_H