#ifndef INCLUDE_SERIALIZATION_H
#define INCLUDE_SERIALIZATION_H

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <string>
#include <sstream>
#include <vector>

struct Serializer
{
    struct Context
    {
        template<class T>
        Context& operator() (const std::string& name, T& t)
        {
            if (!value_.IsObject()) value_.SetObject();
            rapidjson::Document::ValueType n(name.c_str(), allocator_);
            rapidjson::Document::ValueType v;
            value_.AddMember(n, v, allocator_);
            Context c{value_[name.c_str()], allocator_};
            c(t);
        }
        
        Context& operator() (int& value)
        {
            value_.SetInt(value);
        }
       
        Context& operator() (std::string& value)
        {
            value_.SetString(value.c_str(), allocator_);
        }

        template<class T>
        Context& operator() (std::vector<T>& value)
        {
            if (!value_.IsArray()) value_.SetArray();
            value_.Reserve(value.size(), allocator_);
            for(auto&& item : value)
            {
                rapidjson::Document::ValueType v;
                Context c{v, allocator_};
                serialize(c, item);
                value_.PushBack(v, allocator_);
            }
        }
       
        rapidjson::Document::ValueType& value_; 
        rapidjson::Document::AllocatorType& allocator_; 
    };

    template<class T>
    std::string operator() (const T& o)
    {
        Context c{doc_, doc_.GetAllocator()};
        serialize(c, const_cast<T&>(o));
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        doc_.Accept(writer);
        return buffer.GetString();
    }
    
private:
    rapidjson::Document doc_;
};

struct Deserializer
{
    struct Context
    {
        template<class T>
        Context& operator() (const std::string& name, T& value)
        {
            Context{value_[name.c_str()]}(value);
            value_.EraseMember(name.c_str());
        }
        
        Context& operator() (int& value)
        {
            value = value_.GetInt();
        }
       
        Context& operator() (std::string& value)
        {
            value = value_.GetString();
        }
       
        template<class T>
        Context& operator() (std::vector<T>& value)
        {
            value.resize(value_.Size());
            for(auto iter = value_.Begin(); iter != value_.End(); ++iter)
            {
                Context c{*iter};
                serialize(c, value[iter - value_.Begin()]);
            }
        }
        
        rapidjson::Document::ValueType& value_; 
    };

    explicit Deserializer(std::string json): str_(std::move(json))
    {
        doc_.ParseInsitu(const_cast<char*>(str_.c_str()));
    }
    
    template<class T>
    void operator() (T& value)
    {
        Context c{doc_};
        serialize(c, value);
    }

private:
    std::string str_;
    rapidjson::Document doc_;
};

template<class T>
std::string toJSON(const T& o)
{
    return Serializer()(o);
}

template<class T>
T fromJSON(std::string json)
{
    T o;
    Deserializer(std::move(json))(o);
    return o;
}

template<class Serializer>
void serialize(Serializer& serial, int& value)
{
    serial(value);
}

template<class Serializer>
void serialize(Serializer& serial, std::string& value)
{
    serial(value);
}

#endif