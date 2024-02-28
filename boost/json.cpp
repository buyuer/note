#include <boost/json.hpp>

#include <iostream>

int main(int argc, char *argv[])
{
    boost::json::object person1, person2, person3;
    boost::json::object persons;
    person1["name"] = "ding";
    person1["sex"]  = "male";
    person2["name"] = "xin";
    person2["sex"]  = "male";
    person3["name"] = "tong";
    person3["sex"]  = "male";

    auto &arr = persons["member"].emplace_array();
    arr.emplace_back(person1);
    arr.emplace_back(person2);
    arr.emplace_back(person3);
    persons["size"] = arr.size();

    auto str = boost::json::serialize(persons);
    std::cout << str << std::endl;

    auto obj = boost::json::parse(str).as_object();
    for (auto &member : obj)
    {
        std::cout << member.key() << ": " << member.value() << std::endl;
    }
}