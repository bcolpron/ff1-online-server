#ifndef INCLUDE_SERIALIZATION_H
#define INCLUDE_SERIALIZATION_H

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <string>
#include <sstream>
#include <vector>

rapidjson::Document::AllocatorType* a;

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
       
        rapidjson::Document::ValueType& value_; 
        rapidjson::Document::AllocatorType& allocator_; 
    };

    Serializer()
    {
    }
    
    template<class T>
    void operator() (const T& o)
    {
        Context c{doc_, doc_.GetAllocator()};
        serialize(c, const_cast<T&>(o));
    }

    std::string toString()
    {
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
        }
        
        Context& operator() (int& value)
        {
            value = value_.GetInt();
        }
       
        Context& operator() (std::string& value)
        {
            value = value_.GetString();
        }
       
        rapidjson::Document::ValueType& value_; 
    };

    explicit Deserializer(std::string json): str_(std::move(json))
    {
        doc_.ParseInsitu(const_cast<char*>(str_.c_str()));
    }
    
    Context context()
    {
        return Context{doc_};
    }

private:
    std::string str_;
    rapidjson::Document doc_;
};

template<class T>
std::string toJSON(const T& o)
{
    Serializer s;
    s(o);
    return s.toString();
}

template<class T>
T fromJSON(std::string json)
{
    T o;
    Deserializer s(std::move(json));
    auto context = s.context();
    serialize(context, o);
    return o;
}


template<class T>
void serialize(rapidjson::Document::ValueType& json, const char* name, std::vector<T>& value)
{
    if (json.HasMember(name))
    {
        //value = json[name].GetInt();
    }
}



#endif